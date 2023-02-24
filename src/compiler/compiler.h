//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_COMPILER_H
#define BRANESCRIPT_COMPILER_H

#include <unordered_map>
#include <string>
#include <list>
#include <any>
#include <exception>
#include <memory>

#include "antlr4/braneBaseVisitor.h"
#include "aotInlineFunctions/aotInlineFunction.h"
#include "aotNodes/aotNode.h"
#include "aotNodes/aotValueNodes.h"
#include "irFunction.h"
#include "irScript.h"
#include "robin_hood.h"
#include "src/utility/staticIndexVector.h"
#include "staticAnalysis/documentContext.h"
#include "structDefinition.h"

namespace BraneScript
{

    class Compiler : public braneBaseVisitor
    {
        robin_hood::unordered_map<std::string, const TypeDef*> _nativeTypes;
        robin_hood::unordered_map<std::string, std::unique_ptr<StructDef>> _registeredStructs;
        robin_hood::unordered_map<std::string, std::vector<std::unique_ptr<AotInlineFunction>>> _inlineFunctions;

        StructDef structFromDocumentContext(const StructContext* ctx);
      public:
        Compiler();

        /** @brief Add an unmanaged type not controlled by this compiler */
        void registerType(const TypeDef* type);
        /** @brief Used to create and update struct definitions.
         * Must be called with every script linked to a script you wish to compile so that all types will be defined.
         */
        void updateDefinedStructs(const ScriptContext* script);
        void clearDefinedStructs();

        const TypeDef* getType(const std::string& id) const;
        IRScript* compile(const ScriptContext* script);

        void registerInlineFunction(AotInlineFunction* function);
        const AotInlineFunction* getInlineFunction(const std::string& name, const std::vector<AotNode*>& args);
    };

    struct FunctionCompilerCtx;
    struct ScriptCompilerCtx
    {
        Compiler* compiler;
        std::unique_ptr<IRScript> script;
        std::vector<std::unique_ptr<const StructDef>> localStructDefs;

        std::vector<std::unique_ptr<FunctionCompilerCtx>> functions;

        std::vector<std::unique_ptr<AotValue>> globalValues;
        AotValue* newGlobal(const TypeDef* type, uint8_t flags);

        const TypeDef* getType(const std::string& string) const;

        int16_t linkFunction(const std::string& sig);
        int16_t linkConstructor(const StructDef* type);
        int16_t linkMoveConstructor(const StructDef* type);
        int16_t linkCopyConstructor(const StructDef* type);
        int16_t linkDestructor(const StructDef* type);
    };

    struct FunctionCompilerCtx
    {
        ScriptCompilerCtx& script;
        IRFunction* function;
        std::string signature;

        struct ValueIndex
        {
            std::unique_ptr<AotValue> aotValue;
            size_t index;
            bool isReg;
        };
        staticIndexVector<ValueIndex> values;

        bool compareFlagsInUse = false;

        staticIndexVector<Value> registers;
        staticIndexVector<Value> memoryLocations;
        uint8_t jumpTargetIDCounter = 0;

        robin_hood::unordered_map<const StructDef*, int16_t> localStructIndices;

        FunctionCompilerCtx(ScriptCompilerCtx& s, std::string sig);

        uint32_t newJumpTargetID();

        AotValue* newReg(const TypeDef* type, uint8_t flags);
        AotValue* newConst(const TypeDef* type, uint8_t flags = AotValue::Const | AotValue::Constexpr);
        AotValue* newCompareResult();
        AotValue* castValue(AotValue* value);
        AotValue* castTemp(AotValue* value);
        AotValue* castReg(AotValue* value);
        AotValue* derefPtr(AotValue* value, const TypeDef* type, uint16_t offset = 0);

        Value serialize(AotValue* value) const;
        void releaseValue(AotValue* value);

        void appendCode(Operand op);
        void appendCode(const std::string& string);

        void appendCode(Operand op, Value a);
        void appendCode(Operand op, Value a, Value b);
        void appendCode(Operand op, int16_t index);
        void appendCode(Operand op, uint16_t index);
        void appendCode(Operand op, uint32_t index);

        template<typename T>
        void appendCode(Operand op, Value a, T value)
        {
            appendCode(op, a);
            static_assert(!std::is_pointer<T>());
            size_t index = function->code.size();
            function->code.resize(function->code.size() + sizeof(T));
            *(T*)(function->code.data() + index) = value;
        }

        template<typename T>
        void appendCode(T value)
        {
            static_assert(!std::is_pointer<T>());
            size_t index = function->code.size();
            function->code.resize(function->code.size() + sizeof(T));
            *(T*)(function->code.data() + index) = value;
        }
    };

    class CompilerError : public std::runtime_error
    {
      public:
        CompilerError(const std::string& message);
    };
}
#endif //BRANESCRIPT_COMPILER_H
