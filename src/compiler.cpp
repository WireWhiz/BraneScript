//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include "../antlr4/braneLexer.h"
#include "ANTLRInputStream.h"
#include "nativeTypes.h"
#include "aotNode/aotOperationNodes.h"
#include "aotNode/aotValueNodes.h"
#include "aotNode/aotFlowNodes.h"
#include "linker.h"
#include "library.h"
#include "structDefinition.h"
#include "operator.h"
#include <memory>

namespace BraneScript
{
#define RETURN_NULL return (AotNode*)nullptr
#define PROPAGATE_NULL(node) \
    if(!node) return (AotNode*)nullptr

    class LexerErrorListener : public antlr4::BaseErrorListener
    {

        Compiler& _compiler;
    public:
        LexerErrorListener(Compiler& compiler) : _compiler(compiler)
        {};

        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line,
                         size_t charPositionInLine,
                         const std::string& msg, std::exception_ptr e) override
        {
            if (offendingSymbol)
                _compiler.throwError(offendingSymbol, msg);
            else
            {
                size_t charIndex = 0;
                size_t lineIndex = 0;
                while (lineIndex < line - 1)
                {
                    if ((*_compiler._currentFile)[charIndex] == '\n')
                        ++lineIndex;
                    charIndex++;
                }
                _compiler.throwError(
                        (std::string)"Unknown Token \"" + (*_compiler._currentFile)[charIndex + charPositionInLine] +
                        "\" on line " + std::to_string(line) + ":" + std::to_string(charPositionInLine));
            }
        }
    };

    class ParserErrorListener : public antlr4::BaseErrorListener
    {
        Compiler& _compiler;
    public:
        ParserErrorListener(Compiler& compiler) : _compiler(compiler)
        {

        }

        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line,
                         size_t charPositionInLine,
                         const std::string& msg, std::exception_ptr e) override
        {
            if (offendingSymbol)
                _compiler.throwError(offendingSymbol, msg);
        }
    };

    IRScript* Compiler::compile(const std::string& script)
    {
        _currentFile = &script;
        antlr4::ANTLRInputStream input(script);

        LexerErrorListener lexErrListener(*this);
        braneLexer lexer(&input);
        lexer.removeErrorListeners();
        lexer.addErrorListener(&lexErrListener);
        antlr4::CommonTokenStream tokens(&lexer);

        ParserErrorListener parserErrListener(*this);
        braneParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(&parserErrListener);

        _ctx = std::make_unique<CompilerCtx>(*this, new IRScript());
        visit(parser.program());

        IRScript* ret = nullptr;

        if (contextValid())
            ret = _ctx->script;
        _ctx = nullptr;
        return ret;
    }

    std::any Compiler::visitProgram(braneParser::ProgramContext* context)
    {
        return braneBaseVisitor::visitProgram(context);
    }

    std::any Compiler::visitInclude(braneParser::IncludeContext* context)
    {
        return braneBaseVisitor::visitInclude(context);
    }

    std::any Compiler::visitConstChar(braneParser::ConstCharContext* context)
    {
        std::string text = context->getText();
        return (AotNode*)new AotConstNode(text[1], getNativeTypes()[7]);
    }

    std::any Compiler::visitConstString(braneParser::ConstStringContext* context)
    {
        std::string text = context->getText();
        return (AotNode*)new AotConstNode(std::string(text.data() + 1, text.size() - 2), getNativeTypes()[8]);
    }

    std::any Compiler::visitInlineScope(braneParser::InlineScopeContext* context)
    {
        return visit(context->expression());
    }

    std::any Compiler::visitAssignment(braneParser::AssignmentContext* context)
    {
        auto* rValue = std::any_cast<AotNode*>(visit(context->expr));
        PROPAGATE_NULL(rValue);
        auto* lValue = std::any_cast<AotNode*>(visit(context->dest));
        PROPAGATE_NULL(lValue);

        if(rValue->resType() != lValue->resType())
        {
            auto* castOpr = _linker->getOperator(oprSig(lValue->resType()->name(), rValue->resType()));
            if(!castOpr)
            {
                throwError(context, "Can't implicitly cast " + std::string(rValue->resType()->name()) + " to " + lValue->resType()->name());
                RETURN_NULL;
            }
            rValue = new AotUnaryOperatorNode(castOpr, rValue);
        }

        return (AotNode*)new AotAssignNode(lValue, rValue);
    }

    std::any Compiler::visitScope(braneParser::ScopeContext* context)
    {
        pushScope();
        std::vector<AotNode*> operations;
        for (auto stmt: context->statement())
        {
            auto* operation = std::any_cast<AotNode*>(visit(stmt));
            PROPAGATE_NULL(operation);
            operations.push_back(operation);
        }
        popScope();
        return (AotNode*)new AotScope(std::move(operations));
    }

    std::any Compiler::visitConstFloat(braneParser::ConstFloatContext* context)
    {
        return (AotNode*)new AotConstNode(std::stof(context->FLOAT()->getText()), getType("float"));
    }

    std::any Compiler::visitAddsub(braneParser::AddsubContext* context)
    {
        auto left = std::any_cast<AotNode*>(visit(context->left));
        PROPAGATE_NULL(left);
        auto right = std::any_cast<AotNode*>(visit(context->right));
        PROPAGATE_NULL(right);

        auto* opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        if(!opr)
        {
            castSameScalarType(left, right);
            opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        }
        if(!opr)
        {
            throwError(context, "Could not find operator \"" + context->op->getText() + "\" with args " + left->resType()->name() + " and " + right->resType()->name());
            RETURN_NULL;
        }
        return (AotNode*)new AotBinaryOperatorNode(opr, left, right);
    }

    std::any Compiler::visitMuldiv(braneParser::MuldivContext* context)
    {
        auto left = std::any_cast<AotNode*>(visit(context->left));
        PROPAGATE_NULL(left);
        auto right = std::any_cast<AotNode*>(visit(context->right));
        PROPAGATE_NULL(right);

        auto* opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        if(!opr)
        {
            castSameScalarType(left, right);
            opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        }
        if(!opr)
        {
            throwError(context, "Could not find operator \"" + context->op->getText() + "\" with args " + left->resType()->name() + " and " + right->resType()->name());
            RETURN_NULL;
        }
        return (AotNode*)new AotBinaryOperatorNode(opr, left, right);
    }

    std::any Compiler::visitConstInt(braneParser::ConstIntContext* context)
    {
        return (AotNode*)new AotConstNode((int32_t)std::stoi(context->getText()), getType("int"));
    }

    std::any Compiler::visitId(braneParser::IdContext* context)
    {
        auto text = context->getText();
        AotNode* node = getValueNode(text);
        if (node)
            return node;
        if(_ctx->structDef)
        {
            auto member = _ctx->structDef->getMemberVar(text);
            if (!member)
            {
                throwError(context->start, "Undeclared identifier");
                return (AotNode*)nullptr;
            }

            return (AotNode*)new AotDerefNode(getValueNode("this"), member->type, member->offset);
        }

        if(_ctx->libraryAliases.count(text))
        {
            Library* library = _linker->getLibrary(_ctx->script->linkedLibraries[_ctx->libraryAliases[text]]);
            return (AotNode*)new AotLibraryNode(library);
        }

        throwError(context, "Library or identifier not found!");
        RETURN_NULL;
    }

    std::any Compiler::visitMemberAccess(braneParser::MemberAccessContext* context)
    {
        auto base = std::any_cast<AotNode*>(visit(context->base));
        PROPAGATE_NULL(base);

        auto structDef = dynamic_cast<const StructDef*>(base->resType());
        if(!structDef)
        {
            throwError(context->base, "Cant get member of void type");
            RETURN_NULL;
        }

        auto structMemberDef = structDef->getMemberVar(context->member->getText());
        if(!structMemberDef)
        {
            throwError(context->member, "Member for struct " + context->base->getText() + " not found");
            RETURN_NULL;
        }

        return (AotNode*)new AotDerefNode(base, structMemberDef->type, structMemberDef->offset);
    }

    std::any Compiler::visitIndexAccess(braneParser::IndexAccessContext* context)
    {
        auto base = std::any_cast<AotNode*>(visit(context->base));
        auto index = std::any_cast<AotNode*>(visit(context->arg));
        PROPAGATE_NULL(base);

        auto* indexOpr = _linker->getOperator(oprSig("[]", base->resType(), index->resType()));
        if(!indexOpr)
        {
            auto* castOpr = _linker->getOperator(oprSig(getNativeTypeDef(UInt32)->name(), index->resType()));
            if(!castOpr)
            {
                throwError(context, "Could not automatically cast " + std::string(index->resType()->name()) + " to index type");
                RETURN_NULL;
            }
            index = new AotUnaryOperatorNode(castOpr, index);
            indexOpr = _linker->getOperator(oprSig("[]", base->resType(), index->resType()));
            if(!indexOpr)
            {
                throwError(context, "Could not automatically cast " + std::string(index->resType()->name()) + " to index type");
                RETURN_NULL;
            }
        }
        return (AotNode*)new AotBinaryOperatorNode(indexOpr, base, index);
    }

    std::any Compiler::visitDecl(braneParser::DeclContext* context)
    {
        return visit(context->declaration());
    }

    std::any Compiler::visitType(braneParser::TypeContext* context)
    {
        TypeInfo t;
        t.type = context->id->getText();
        t.isConst = context->isConst;
        t.isRef = context->isRef;
        return t;
    }

    std::any Compiler::visitDeclaration(braneParser::DeclarationContext* context)
    {
        auto name = context->id->getText();
        auto typeInfo = visitT<TypeInfo>(context->type());
        auto type = getType(typeInfo.type);
        if(!type)
        {
            throwError(context->type()->id, "Undefined type");
            return (AotNode*)nullptr;
        }
        if(localValueExists(name))
        {
            throwError(context->id, "Identifier is already in use");
            return (AotNode*)nullptr;
        }
        if(typeInfo.isRef && type->type() != Struct)
        {
            throwError(context->type(), "Only types of struct can be marked as references");
            return (AotNode*)nullptr;
        }
        if(!typeInfo.isRef && type->type() == Struct)
            typeInfo.stackRef = true;
        registerLocalValue(name, typeInfo);
        return getValueNode(name);
    }

    const std::vector<std::string>& Compiler::errors() const
    {
        return _errors;
    }

    std::any Compiler::visitArgumentList(braneParser::ArgumentListContext* ctx)
    {
        return braneBaseVisitor::visitArgumentList(ctx);
    }

    std::any Compiler::visitFunction(braneParser::FunctionContext* ctx)
    {
        IRFunction* previousFunction = _ctx->function;

        _ctx->script->localFunctions.push_back({});
        _ctx->setFunction(&*--_ctx->script->localFunctions.end());

        //TODO: TypeAssert()
        _ctx->function->returnType = visitT<TypeInfo>(ctx->type());
        if (!getType(_ctx->function->returnType.type) && _ctx->function->returnType.type != "void")
        {
            throwError(ctx->type()->id, "Unknown return type");
            return {};
        }

        if(_ctx->structDef)
            _ctx->function->name = _ctx->structDef->name() + std::string("::");

        _ctx->function->name += ctx->id->getText();
        _ctx->function->name += "(";
        pushScope();
        if(_ctx->structDef)
        {
            //_ctx->function->name += std::string("(ref ") + _ctx->structDef->name() + ",";
            TypeInfo info = {_ctx->structDef->name(), false, true, false};
            _ctx->function->arguments.push_back(info);
            AotValue* value = _ctx->newReg(info.type, 0);
            value->valueIndex = _ctx->regIndex++;
            value->flags |= AotValue::Initialized;
            registerLocalValue("this", value, info);
        }
        for (auto argument: ctx->arguments->declaration())
        {
            if(*--_ctx->function->name.end() != '(')
                _ctx->function->name += ',';
            auto type = visitT<TypeInfo>(argument->type());
            auto* typeDef = getType(type.type);
            if(!typeDef)
            {
                throwError(argument->type()->id, "Undefined type");
                return {};
            }
            if(!type.isRef && typeDef->type() == Struct)
            {
                throwError(argument->type(), "Structs may only be passed as reference. Consider using the \"const ref\" prefix.");
                return {};
            }
            if(type.isConst)
                _ctx->function->name += "const ";
            if(type.isRef)
                _ctx->function->name += "ref ";

            _ctx->function->name += type.type;
            _ctx->function->arguments.push_back(type);

            AotValue* value = _ctx->newReg(type.type, 0);
            value->valueIndex = _ctx->regIndex++;
            value->flags |= AotValue::Initialized;
            registerLocalValue(argument->id->getText(), value, type);
        }
        _ctx->function->name += ")";

        bool previousReturnVal = _ctx->returnCalled;
        _ctx->returnCalled = false;
        for (auto* stmtCtx: ctx->statement())
        {
            auto stmt = std::any_cast<AotNode*>(visit(stmtCtx));
            if (!stmt)
                continue;

            //TODO optimize toggle
            auto expr = std::unique_ptr<AotNode>(stmt);

            AotNode* optimizedTree = expr->optimize();
            if (expr.get() != optimizedTree)
                expr = std::unique_ptr<AotNode>(optimizedTree);

            expr->generateBytecode(*_ctx);
        }
        if (!_ctx->returnCalled && _ctx->function->returnType.type != "void")
        {
            size_t begin = ctx->start->getStartIndex();
            size_t end = ctx->stop->getStopIndex() + 1;
            throwError(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                       "\n" + _currentFile->substr(begin, end - begin), "Function missing call to return");
            return {};
        }
        _ctx->returnCalled = previousReturnVal;
        popScope();

        _ctx->function = previousFunction;
        return {};
    }

    std::any Compiler::visitCast(braneParser::CastContext* ctx)
    {
        auto* expression = std::any_cast<AotNode*>(visit(ctx->expression()));
        PROPAGATE_NULL(expression);

        auto* castType = getType(ctx->ID()->getText());
        if(!castType)
        {
            throwError(ctx->start++, "Type not found");
            RETURN_NULL;
        }

        auto* castOpr = _linker->getOperator(oprSig(castType->name(), expression->resType()));
        if(!castOpr)
        {
            throwError("Could not cast " + std::string(expression->resType()->name()) + " to " + castType->name());
        }

        return (AotNode*)new AotUnaryOperatorNode(castOpr, expression);
    }

    std::any Compiler::visitReturnVoid(braneParser::ReturnVoidContext* ctx)
    {
        assert(false);
        throwError("Void return statements not implemented");
        _ctx->returnCalled = true;
        return (AotNode*)new AotReturnNode();
    }

    std::any Compiler::visitReturnVal(braneParser::ReturnValContext* ctx)
    {
        auto retVal = std::any_cast<AotNode*>(visit(ctx->expression()));
        PROPAGATE_NULL(retVal);
        if(!retVal->resType())
        {
            throwError(ctx->expression()->start, "can't cast from void to " + _ctx->function->returnType.type);
            RETURN_NULL;
        }

        if (retVal->resType()->name() != _ctx->function->returnType.type)
        {
            auto* castOpr = _linker->getOperator(oprSig(_ctx->function->returnType.type, retVal->resType()));
            if(!castOpr)
            {
                throwError("Could not implicitly cast " + std::string(retVal->resType()->name()) + " to " + _ctx->function->returnType.type);
                RETURN_NULL;
            }

            retVal =  new AotUnaryOperatorNode(castOpr, retVal);
        }
        _ctx->returnCalled = true;
        return (AotNode*)new AotReturnValueNode(retVal);
    }

    void Compiler::registerLocalValue(std::string name, const TypeInfo& type)
    {
        const TypeDef* typeDef = getType(type.type);
        assert(typeDef);
        _scopes.back().localValues.emplace(std::move(name), AotValueNode(typeDef, type));
    }

    void Compiler::registerLocalValue(std::string name, AotValue* value, const TypeInfo& type)
    {
        const TypeDef* typeDef = getType(type.type);
        assert(typeDef);
        _scopes.back().localValues.emplace(std::move(name), AotValueNode(typeDef, value, type));
    }

    AotNode* Compiler::getValueNode(const std::string& name)
    {
        for (auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
        {
            auto v = i->localValues.find(name);
            if (v != i->localValues.end())
                return new AotValueNode(v->second);
        }
        return nullptr;
    }

    void Compiler::pushScope()
    {
        _scopes.push_back({});
    }

    void Compiler::popScope()
    {
        _scopes.pop_back();
    }

    std::any Compiler::visitConstBool(braneParser::ConstBoolContext* ctx)
    {
        if (ctx->getText() == "true")
            return (AotNode*)new AotConstNode(true, getType("bool"));
        else
            return (AotNode*)new AotConstNode(false, getType("bool"));
    }

    std::any Compiler::visitIf(braneParser::IfContext* ctx)
    {
        auto condition = std::any_cast<AotNode*>(visit(ctx->cond));
        auto operation = std::any_cast<AotNode*>(visit(ctx->operation));
        return (AotNode*)new AotIf(condition, operation);
    }

    std::any Compiler::visitWhile(braneParser::WhileContext* ctx)
    {
        auto condition = std::any_cast<AotNode*>(visit(ctx->cond));
        auto operation = std::any_cast<AotNode*>(visit(ctx->operation));
        return (AotNode*)new AotWhile(condition, operation);
    }

    std::any Compiler::visitComparison(braneParser::ComparisonContext* context)
    {
        auto* left = std::any_cast<AotNode*>(visit(context->left));
        auto* right = std::any_cast<AotNode*>(visit(context->right));

        std::string symbol = context->op->getText();
        auto* opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        if(!opr)
        {
            castSameScalarType(left, right);
            opr = _linker->getOperator(oprSig(context->op->getText(), left->resType(), right->resType()));
        }
        if(!opr)
        {
            throwError(context, "Could not find operator \"" + context->op->getText() + "\" with args " + left->resType()->name() + " and " + right->resType()->name());
            RETURN_NULL;
        }

        return (AotNode*)new AotBinaryOperatorNode(opr, left, right);
    }

    std::any Compiler::visitExprStatement(braneParser::ExprStatementContext* context)
    {
        return visit(context->expression());
    }

    std::any Compiler::visitArgumentPack(braneParser::ArgumentPackContext* context)
    {
        std::vector<AotNode*> arguments;
        for(auto& arg : context->expression())
            arguments.push_back(std::any_cast<AotNode*>(visit(arg)));
        return std::move(arguments);
    }

    std::any Compiler::visitFunctionCall(braneParser::FunctionCallContext* context)
    {
        std::string functionName = context->name->getText();
        std::vector<AotNode*> arguments = std::any_cast<std::vector<AotNode*>>(visit(context->argumentPack()));
        functionName += "(";
        for(auto* arg : arguments)
        {
            PROPAGATE_NULL(arg);
            const TypeDef* argType = arg->resType();
            if(!argType)
            {
                throwError(context->getStart()->getLine(), context->getStart()->getChannel(), "", "Tried to pass void argument into function");
                RETURN_NULL;
            }
            if(*--functionName.end() != '(')
                functionName += ',';
            functionName += argType->name();
        }
        functionName += ")";

        int16_t fIndex = getLocalFunction(functionName);

        //Account for member functions
        if(fIndex < 0 && _ctx->structDef)
        {
            functionName = std::string(_ctx->structDef->name()) + "::" + functionName;
            fIndex = getLocalFunction(functionName);
            arguments.insert(arguments.begin(), getValueNode("this"));
        }

        if(fIndex < 0)
        {
            throwError(context->getStart(), "Could not find function with signature " + functionName);
            RETURN_NULL;
        }
        const TypeDef* retType = getType(_ctx->script->localFunctions[fIndex].returnType.type);
        return (AotNode*)new AotFunctionCall(fIndex, retType, arguments);
    }

    std::any Compiler::visitMemberFunctionCall(braneParser::MemberFunctionCallContext* context)
    {
        auto* base = std::any_cast<AotNode*>(visit(context->base));

        std::string functionName = context->name->getText();
        std::vector<AotNode*> arguments = std::any_cast<std::vector<AotNode*>>(visit(context->argumentPack()));
        functionName += "(";
        for(auto* arg : arguments)
        {
            PROPAGATE_NULL(arg);
            const TypeDef* argType = arg->resType();
            if(!argType)
            {
                throwError(context->getStart()->getLine(), context->getStart()->getChannel(), "", "Tried to pass void argument into function");
                RETURN_NULL;
            }
            if(*--functionName.end() != '(')
                functionName += ',';
            functionName += argType->name();
        }
        functionName += ")";


        if(base->type() == AotNode::NodeType::Lib)
        {
            auto lib = static_cast<AotLibraryNode*>(base)->lib();
            functionName = lib->name() + "::" + functionName;
            auto funcDef = _linker->getFunction(functionName);
            if(!funcDef)
            {
                throwError(context, "library does not contain member function");
                RETURN_NULL;
            }
            int16_t fIndex = int16_t{-1} -  _ctx->script->linkFunction(functionName);
            auto retType = getType(funcDef->ret);
            return (AotNode*)new AotFunctionCall(fIndex, retType, arguments);
        }
        if(base->type() == AotNode::NodeType::Value || base->type() == AotNode::NodeType::Deref)
        {
            if(base->resType()->type() != Struct)
            {
                throwError(context->base, "Type does not support member functions");
                RETURN_NULL;
            }

            auto sDef = static_cast<const StructDef*>(base->resType());

            int16_t fIndex;
            const TypeDef* retType = nullptr;
            if(_ctx->localStructIndices.count(sDef))
            {
                fIndex = _ctx->script->findLocalFuncIndex(std::string(sDef->name()) + "::" + functionName);
                if(fIndex < 0)
                {
                    throwError(context, "Could not find member function for local struct: " + std::string(sDef->name()));
                    RETURN_NULL;
                }
                retType = getType(_ctx->script->localFunctions[fIndex].returnType.type);
            }
            else
            {
                functionName = std::string(sDef->name()) + "::" + functionName;
                auto funcDef = _linker->getFunction(functionName);
                if(!funcDef)
                {
                    throwError(context, "Linker could not find member function for external struct: " + std::string(sDef->name()));
                    RETURN_NULL;
                }
                fIndex = int16_t{-1} -  _ctx->script->linkFunction(functionName);
                retType = getType(funcDef->ret);
            }
            arguments.insert(arguments.begin(), base);
            return (AotNode*)new AotFunctionCall(fIndex, retType, arguments);
        }

        throwError(context->base, "Unable to resolve base");
        RETURN_NULL;
    }

    std::any Compiler::visitLink(braneParser::LinkContext* context)
    {
        std::string libraryName = removePars(context->library->getText());
        if(!_linker)
        {
            throwError("You must set a linker to be able to link libraries");
            return {};
        }
        if(!_linker->getLibrary(libraryName))
        {
            throwError("Library \"" + libraryName + "\" not found");
            return {};
        }
        _ctx->script->linkedLibraries.push_back(libraryName);
        if(context->alias)
            _ctx->libraryAliases.insert({removePars(context->alias->getText()), (uint32_t)_ctx->libraryAliases.size()});
        else
            _ctx->libraryAliases.insert({libraryName, (uint32_t)_ctx->libraryAliases.size()});
        return {};
    }

    std::any Compiler::visitDelete(braneParser::DeleteContext* context)
    {
        auto ptr = std::any_cast<AotNode*>(visit(context->ptr));
        if(ptr->resType()->type() != Struct)
        {
            throwError(context->start, "Can only delete objects");
            RETURN_NULL;
        }
        return (AotNode*)new AotDeleteNode(ptr);
    }

    std::any Compiler::visitStructDef(braneParser::StructDefContext* context)
    {
        std::vector<StructVar> members;
        for(auto& member : context->memberVars->structMember())
        {
            if(!member->var)
                continue;
            auto var = member->var;
            StructVar m;
            auto type = getType(var->type()->id->getText());
            if(!type)
            {
                throwError(var->type()->id, "Could not create struct member with undefined type");
                continue;
            }
            m.name = var->id->getText();
            m.type = type;
            members.push_back(std::move(m));
        }
        if(!contextValid())
            return {};
        auto newDef = new StructDef(context->id->getText());

        for(auto& m : members)
            newDef->addMemberVar(std::move(m.name), m.type);
        if(context->packed)
            newDef->packMembers();
        else
            newDef->padMembers();
        _privateTypes.insert({newDef->name(), newDef});
        _ctx->localStructIndices.emplace(newDef, (uint16_t)_ctx->localStructDefs.size());
        _ctx->localStructDefs.push_back(std::unique_ptr<StructDef>(newDef));

        //We need to store a copy of this info in the ir script for the runtime
        IRScript::IRStructDef irDef;
        irDef.name = newDef->name();
        irDef.packed = context->packed;
        irDef.isPublic = context->isPublic;

        for(auto& m : newDef->memberVars())
            irDef.members.push_back({m.name, m.offset, m.type->name()});
        _ctx->script->localStructs.push_back(irDef);

        _ctx->structDef = newDef;
        bool constructors[4] = {false, false, false, false};
        for(auto& member : context->memberVars->structMember())
        {
            if(!member->func)
                continue;
            if(member->func->id->getText() == "_construct")
                constructors[0] = true;
            if(member->func->id->getText() == "_copy")
                constructors[1] = true;
            if(member->func->id->getText() == "_move")
                constructors[2] = true;
            if(member->func->id->getText() == "_destruct")
                constructors[3] = true;
        }

        //Generate default constructor
        if(!constructors[0])
        {
            IRFunction constructor;
            _ctx->setFunction(&constructor);
            constructor.name = irDef.name + "::_construct()";

            TypeInfo info = {_ctx->structDef->name(), false, true, false};
            constructor.arguments.push_back(info);
            AotValue* thisRef = _ctx->newReg(info.type, 0);
            thisRef->valueIndex = _ctx->regIndex++;
            thisRef->flags |= AotValue::Initialized;

            for(auto& m : newDef->memberVars())
            {
                if(m.type->type() == Struct)
                {
                    auto member = _ctx->newReg(m.type, 0);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), thisRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, member->value(*_ctx), (int32_t)m.offset);
                    auto s = dynamic_cast<const StructDef*>(m.type);
                    int16_t cIndex;
                    if(_ctx->localStructIndices.count(s))
                        cIndex = _ctx->script->findLocalFuncIndex(std::string(s->name()) + "::_construct()");
                    else
                        cIndex = int16_t{-1} - _ctx->script->linkFunction(std::string(s->name()) + "::_construct()");
                    constructor.appendCode(Operand::CALL, cIndex);
                    constructor.appendCode(member->value(*_ctx));
                    break;
                }

            }
            _ctx->script->localFunctions.push_back(std::move(constructor));
            _ctx->function = nullptr;
        }

        //Generate default copy constructor
        if(!constructors[1])
        {
            IRFunction constructor;
            _ctx->setFunction(&constructor);
            constructor.name = irDef.name + "::_copy(const ref " + irDef.name + ")";

            TypeInfo info = {_ctx->structDef->name(), false, true, false};
            constructor.arguments.push_back(info);
            info.isConst = true;
            constructor.arguments.push_back(info);
            AotValue* thisRef = _ctx->newReg(info.type, 0);
            thisRef->valueIndex = _ctx->regIndex++;
            thisRef->flags |= AotValue::Initialized;

            AotValue* otherRef = _ctx->newReg(info.type, 0);
            otherRef->valueIndex = _ctx->regIndex++;
            otherRef->flags |= AotValue::Initialized;

            for(auto& m : newDef->memberVars())
            {
                if(m.type->type() != Struct)
                {
                    auto member = _ctx->derefPtr(thisRef, m.type, m.offset);
                    auto otherMember = _ctx->derefPtr(otherRef, m.type, m.offset);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), otherMember->value(*_ctx));
                }
                else
                {
                    auto member = _ctx->newReg(m.type, 0);
                    auto otherMember = _ctx->newReg(m.type, 0);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), thisRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, member->value(*_ctx), (int32_t)m.offset);
                    constructor.appendCode(Operand::MOV, otherMember->value(*_ctx), otherRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, otherMember->value(*_ctx), (int32_t)m.offset);
                    auto s = dynamic_cast<const StructDef*>(m.type);
                    int16_t cIndex;
                    if(_ctx->localStructIndices.count(s))
                        cIndex = _ctx->script->findLocalFuncIndex(std::string(s->name()) + "::_copy(const ref " + s->name() + ")");
                    else
                        cIndex = int16_t{-1} - _ctx->script->linkFunction(std::string(s->name()) + "::_copy(const ref " + s->name() + ")");
                    constructor.appendCode(Operand::CALL, cIndex);
                    constructor.appendCode(member->value(*_ctx));
                    constructor.appendCode(otherMember->value(*_ctx));
                }
            }
            _ctx->script->localFunctions.push_back(std::move(constructor));
            _ctx->function = nullptr;
        }

        //Generate default move constructor, exactly the same as copy except for calls to member struct move calls
        if(!constructors[2])
        {
            IRFunction constructor;
            _ctx->setFunction(&constructor);
            constructor.name = irDef.name + "::_move(ref " + irDef.name + ")";

            TypeInfo info = {_ctx->structDef->name(), false, true, false};
            constructor.arguments.push_back(info);
            info.isConst = true;
            constructor.arguments.push_back(info);
            AotValue* thisRef = _ctx->newReg(info.type, 0);
            thisRef->valueIndex = _ctx->regIndex++;
            thisRef->flags |= AotValue::Initialized;

            AotValue* otherRef = _ctx->newReg(info.type, 0);
            otherRef->valueIndex = _ctx->regIndex++;
            otherRef->flags |= AotValue::Initialized;

            for(auto& m : newDef->memberVars())
            {
                if(m.type->type() != Struct)
                {
                    auto member = _ctx->derefPtr(thisRef, m.type, m.offset);
                    auto otherMember = _ctx->derefPtr(otherRef, m.type, m.offset);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), otherMember->value(*_ctx));
                }
                else
                {
                    auto member = _ctx->newReg(m.type, 0);
                    auto otherMember = _ctx->newReg(m.type, 0);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), thisRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, member->value(*_ctx), (int32_t)m.offset);
                    constructor.appendCode(Operand::MOV, otherMember->value(*_ctx), otherRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, otherMember->value(*_ctx), (int32_t)m.offset);
                    auto s = dynamic_cast<const StructDef*>(m.type);
                    int16_t cIndex;
                    if(_ctx->localStructIndices.count(s))
                        cIndex = _ctx->script->findLocalFuncIndex(std::string(s->name()) + "::_move(ref " + s->name() + ")");
                    else
                        cIndex = int16_t{-1} - _ctx->script->linkFunction(std::string(s->name()) + "::_move(ref " + s->name() + ")");
                    constructor.appendCode(Operand::CALL, cIndex);
                    constructor.appendCode(member->value(*_ctx));
                    constructor.appendCode(otherMember->value(*_ctx));
                }
            }
            _ctx->script->localFunctions.push_back(std::move(constructor));
            _ctx->function = nullptr;
        }

        //Generate default destructor
        if(!constructors[3])
        {
            IRFunction constructor;
            _ctx->setFunction(&constructor);
            constructor.name = irDef.name + "::_destruct()";

            TypeInfo info = {_ctx->structDef->name(), false, true, false};
            constructor.arguments.push_back(info);
            AotValue* thisRef = _ctx->newReg(info.type, 0);
            thisRef->valueIndex = _ctx->regIndex++;
            thisRef->flags |= AotValue::Initialized;

            for(auto& m : newDef->memberVars())
            {
                if(m.type->type() == Struct)
                {
                    auto member = _ctx->newReg(m.type, 0);
                    constructor.appendCode(Operand::MOV, member->value(*_ctx), thisRef->value(*_ctx));
                    constructor.appendCode(Operand::ADDI, member->value(*_ctx), (int32_t)m.offset);
                    auto s = dynamic_cast<const StructDef*>(m.type);
                    int16_t cIndex;
                    if(_ctx->localStructIndices.count(s))
                        cIndex = _ctx->script->findLocalFuncIndex(std::string(s->name()) + "::_destruct()");
                    else
                        cIndex = int16_t{-1} - _ctx->script->linkFunction(std::string(s->name()) + "::_destruct()");
                    constructor.appendCode(Operand::CALL, cIndex);
                    constructor.appendCode(member->value(*_ctx));
                }
            }
            _ctx->script->localFunctions.push_back(std::move(constructor));
            _ctx->function = nullptr;
        }

        for(auto& member : context->memberVars->structMember())
        {
            if(!member->func)
                continue;
            visitFunction(member->func);
        }
        _ctx->structDef = nullptr;
        return {};
    }

    void Compiler::throwError(const std::string& message)
    {
        _errors.push_back(message);
    }

    void Compiler::throwError(antlr4::Token* token, const std::string& message)
    {
        assert(token);
        throwError(token->getLine(), token->getCharPositionInLine(), token->getText(), message);
    }

    void Compiler::throwError(antlr4::ParserRuleContext* ctx, const std::string& message)
    {
        assert(ctx);
        throwError(ctx->start->getLine(), ctx->start->getCharPositionInLine(), ctx->getText(), message);
    }

    void Compiler::throwError(size_t line, size_t position, const std::string& context, const std::string& message)
    {
        std::string error =
                "Compile Error at [" + std::to_string(line) + ":" + std::to_string(position) + "] " + message;
        if (!context.empty())
            error += ": " + context;
        _errors.push_back(std::move(error));
    }

    bool Compiler::contextValid()
    {
        return _errors.empty();
    }

    const TypeDef* Compiler::getType(const std::string& typeName) const
    {
        if(_privateTypes.count(typeName))
            return _privateTypes.at(typeName);
        return _linker->getType(typeName);
    }

    bool Compiler::localValueExists(const std::string& name)
    {
        for (auto& s: _scopes)
        {
            if (s.localValues.count(name))
                return true;
        }
        return false;
    }

    std::string Compiler::removePars(const std::string& str)
    {
        assert(str.size() >= 2);
        return str.substr(1, str.size() - 2);
    }

    Compiler::Compiler(Linker* linker)
    {
        _linker = linker;
    }

    int16_t Compiler::getLocalFunction(const std::string& name)
    {
        uint32_t fIndex = 0;
        for(auto& func : _ctx->script->localFunctions)
        {
            if(name == func.name)
                return fIndex;
            ++fIndex;
        }
        return -1;
    }

    void Compiler::castSameScalarType(AotNode*& a, AotNode*& b)
    {
        if(a->resType() == b->resType())
            return;
        enum Side
        {
            Left, //cast b, keep a
            Right //cast a, keep b
        } side = Left;
        switch(a->resType()->type())
        {
            case UInt32:
                side = Right;
                break;
            case UInt64:
                switch(b->resType()->type())
                {
                    case UInt32:
                        side = Left;
                        break;
                    case Int32:
                    case Int64:
                    case Float32:
                    case Float64:
                        side = Right;
                        break;
                }
                break;
            case Int32:
                switch(b->resType()->type())
                {
                    case UInt32:
                    case UInt64:
                        side = Left;
                        break;
                    case Int64:
                    case Float32:
                    case Float64:
                        side = Right;
                        break;
                }
                break;
            case Int64:
                switch(b->resType()->type())
                {
                    case UInt32:
                    case UInt64:
                    case Int32:
                        side = Left;
                        break;
                    case Float32:
                    case Float64:
                        side = Right;
                        break;
                }
                break;
            case Float32:
                switch(b->resType()->type())
                {
                    case UInt32:
                    case UInt64:
                    case Int32:
                    case Int64:
                        side = Left;
                        break;
                    case Float64:
                        side = Right;
                        break;
                }
                break;
            case Float64:
                side = Left;
                break;
        }
        auto* originalType = (side == Left) ? b->resType() : a->resType();
        auto* domType      = (side == Left) ? a->resType() : b->resType();
        auto* castOpr = _linker->getOperator(oprSig(domType->name(), originalType));
        if(!castOpr)
            return;

        if(side == Left)
            b = new AotUnaryOperatorNode(castOpr, b);
        else
            a = new AotUnaryOperatorNode(castOpr, a);
    }

    CompilerCtx::CompilerCtx(Compiler& c, IRScript* s) : compiler(c), script(s)
    {

    }

    AotValue* CompilerCtx::newReg(const std::string& type, uint8_t flags)
    {
        const TypeDef* t = compiler.getType(type);
        return newReg(t, flags);
    }

    AotValue* CompilerCtx::newReg(const TypeDef* type, uint8_t flags)
    {
        auto* value = new AotValue{};
        value->def = type;
        value->flags = flags;
        if (!value->isVoid())
            value->storageType = (type->type() != ValueType::Struct) ? ValueStorageType_Reg : ValueStorageType_Ptr;
        value->compileIndex = values.size();
        values.push_back(std::unique_ptr<AotValue>(value));
        return value;
    }

    AotValue* CompilerCtx::castValue(AotValue* value)
    {
        if (value->isCompare())
            return castReg(value);
        assert(value->storageType != ValueStorageType_Null);
        return value;
    }

    AotValue* CompilerCtx::newConst(ValueType type, uint8_t flags)
    {
        auto* value = new AotValue();
        value->def = getNativeTypeDef(type);
        assert(value->def);
        value->flags = flags;
        value->storageType = ValueStorageType_Const;
        value->compileIndex = values.size();
        values.push_back(std::unique_ptr<AotValue>(value));
        return value;
    }

    AotValue* CompilerCtx::castTemp(AotValue* value)
    {
        assert(function);
        if (value->isTemp())
            return value;
        AotValue* tempValue = newReg(value->def, AotValue::Temp | (AotValue::Constexpr & value->flags));
        function->appendCode(MOV, tempValue->value(*this), value->value(*this));
        return tempValue;
    }

    AotValue* CompilerCtx::castReg(AotValue* value)
    {
        if (value->storageType == ValueStorageType_Reg || value->storageType == ValueStorageType_Ptr)
            return value;
        auto* regValue = newReg(value->def, AotValue::Temp | value->flags);
        if(!value->isCompare())
        {
            function->appendCode(MOV, regValue->value(*this), value->value(*this));
            return regValue;
        }
        assert(value->isCompare());
        switch (value->compareType)
        {
            case AotValue::EqualRes:
            {
                function->appendCode(SETE, regValue->value(*this));
                return regValue;
            }
            case AotValue::NotEqualRes:
            {
                function->appendCode(SETNE, regValue->value(*this));
                return regValue;
            }
            case AotValue::AboveRes:
            {
                function->appendCode(SETA, regValue->value(*this));
                return regValue;
            }
            case AotValue::GreaterRes:
            {
                function->appendCode(SETG, regValue->value(*this));
                return regValue;
            }
            case AotValue::AboveEqualRes:
            {
                function->appendCode(SETAE, regValue->value(*this));
                return regValue;
            }
            case AotValue::GreaterEqualRes:
            {
                function->appendCode(SETGE, regValue->value(*this));
                return regValue;
            }
            default:
                assert(false);
        }
    }


    AotValue* CompilerCtx::derefPtr(AotValue* value, const TypeDef* type, uint16_t offset)
    {
        assert(value->storageType == ValueStorageType_Ptr);
        assert(value->valueIndex != (uint16_t)-1);
        assert(type);
        assert(offset == 0 || value->def->type() == ValueType::Struct);
        if(type->type() == Struct)
        {
            auto* offsetPtr = newReg(type, AotValue::Initialized & value->flags);
            function->appendCode(Operand::MOV, offsetPtr->value(*this), value->value(*this));
            function->appendCode(Operand::ADDI, offsetPtr->value(*this), (int32_t)offset);
            return offsetPtr;
        }

        auto* drefValue = new AotValue(*value);
        drefValue->storageType = ValueStorageType_DerefPtr;
        drefValue->def = type;
        drefValue->ptrOffset = offset;
        value->compileIndex = values.size();
        values.push_back(std::unique_ptr<AotValue>(drefValue));
        return drefValue;
    }

    uint32_t CompilerCtx::newMark()
    {
        return markIndex++;
    }

    void CompilerCtx::setFunction(IRFunction* f)
    {
        function = f;
        regIndex = 0;
        memIndex = 0;
        markIndex = 0;
        values.clear();
    }

    AotValue* CompilerCtx::blankValue()
    {
        auto* value = new AotValue();
        value->compileIndex = values.size();
        values.push_back(std::unique_ptr<AotValue>(value));
        return value;
    }

}