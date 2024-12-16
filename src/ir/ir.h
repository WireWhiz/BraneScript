#ifndef BRANESCRIPT_IR_H
#define BRANESCRIPT_IR_H

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace BraneScript
{

    template<typename T>
    using IRNode = std::shared_ptr<T>;


    /// References can be stored as either full paths, or as context dependent ids, with positive ids representing local
    /// symbols, and negative representing external symbols, and 0 being a null value
    using IDRef = std::variant<std::string, int32_t>;

    enum class BSBaseType
    {
        U8,
        I8,
        U16,
        I16,
        U32,
        I32,
        F32,
        U64,
        I64,
        F64,
        U128,
        I128
    };

    struct BSStructType
    {
        IDRef structId;
    };

    struct BSRefType;
    using BSType = std::variant<BSBaseType, IRNode<BSStructType>, IRNode<BSRefType>>;

    struct BSRefType
    {
        BSType contained;
        bool valueMutable;
    };

    struct IRValue
    {
        uint32_t id;
    };

    struct MovOp;
    struct LoadOp;
    struct StoreOp;

    struct AddOp;
    struct SubOp;
    struct MulOp;
    struct DivOp;
    struct ModOp;

    struct EqOp;
    struct NeOp;
    struct GtOp;
    struct GeOp;

    struct LogicNotOp;
    struct LogicAndOp;
    struct LogicOrOp;

    struct BitNotOp;
    struct BitAndOp;
    struct BitOrOp;
    struct BitXorOp;

    struct I32ToF32;
    struct U32ToF32;
    struct F32ToI32;
    struct U32ToF32;

    struct ConstI32;
    struct ConstU32;
    struct ConstF32;

    struct CallOp;
    using Operation = std::variant<IRNode<MovOp>,
                                   IRNode<LoadOp>,
                                   IRNode<StoreOp>,

                                   IRNode<AddOp>,
                                   IRNode<SubOp>,
                                   IRNode<MulOp>,
                                   IRNode<DivOp>,
                                   IRNode<ModOp>,

                                   IRNode<EqOp>,
                                   IRNode<NeOp>,
                                   IRNode<GtOp>,
                                   IRNode<GeOp>,

                                   IRNode<LogicNotOp>,
                                   IRNode<LogicAndOp>,
                                   IRNode<LogicOrOp>,

                                   IRNode<BitNotOp>,
                                   IRNode<BitAndOp>,
                                   IRNode<BitOrOp>,
                                   IRNode<BitXorOp>,

                                   IRNode<I32ToF32>,
                                   IRNode<U32ToF32>,
                                   IRNode<F32ToI32>,

                                   IRNode<ConstI32>,
                                   IRNode<ConstU32>,
                                   IRNode<ConstF32>>;


    using AsyncOperation = std::variant<

        >;

    struct ConstI32
    {
        int32_t value;
    };

    struct ConstU32
    {
        uint32_t value;
    };

    struct ConstF32
    {
        float value;
    };

    struct MovOp
    {
        IRValue src;
        IRValue dest;
    };

    struct LoadOp
    {
        std::variant<IRValue, ConstU32> store = ConstU32{0};
        IRValue src;
        IRValue dest;
    };

    struct StoreOp
    {
        std::variant<IRValue, ConstU32> store = ConstU32{0};
        IRValue src;
        IRValue dest;
    };

    struct UnaryOp
    {
        IRValue in;
        IRValue out;
    };

    struct BinaryOp
    {
        IRValue left;
        IRValue right;
        IRValue out;
    };

    struct AddOp : public BinaryOp
    {
    };

    struct SubOp : public BinaryOp
    {
    };

    struct MulOp : public BinaryOp
    {
    };

    struct DivOp : public BinaryOp
    {
    };

    struct ModOp : public BinaryOp
    {
    };

    struct EqOp : public BinaryOp
    {
    };

    struct NeOp : public BinaryOp
    {
    };

    struct GtOp : public BinaryOp
    {
    };

    struct GeOp : public BinaryOp
    {
    };

    struct LogicNotOp : public UnaryOp
    {
    };

    struct LogicAndOp : public BinaryOp
    {
    };

    struct LogicOrOp : public BinaryOp
    {
    };

    struct BitNotOp : public BinaryOp
    {
    };

    struct BitAndOp : public BinaryOp
    {
    };

    struct BitOrOp : public BinaryOp
    {
    };

    struct BitXorOp : public BinaryOp
    {
    };

    struct I32ToF32 : public UnaryOp
    {
    };

    struct U32ToF32 : public UnaryOp
    {
    };

    struct F32ToI32 : public UnaryOp
    {
    };

    struct F32ToU32 : public UnaryOp
    {
    };

    struct BSCallOp
    {
        IDRef function;
        std::vector<IRValue> inputs;
        std::vector<IRValue> outputs;
    };

    struct BSPipelineStage
    {
        std::vector<BSType> localVars;
        std::vector<Operation> operations;
        std::vector<AsyncOperation> asyncOps;
    };

    struct BSStruct
    {
        std::string id;
        std::vector<BSType> members;
    };

    struct BSPipeline
    {
        std::string id;
        std::vector<BSType> inputs;
        std::vector<BSType> outputs;
        std::optional<std::vector<BSPipelineStage>> stages;
    };

    struct BSFunction
    {
        std::string id;
        std::vector<BSType> localVars;
        std::vector<BSType> inputs;
        std::vector<BSType> outputs;
        std::vector<Operation> operations;
    };

    struct BSModule
    {
        std::string name;
        std::vector<std::shared_ptr<BSStruct>> structs;
        std::vector<std::shared_ptr<BSFunction>> functions;
        std::vector<std::shared_ptr<BSPipeline>> pipelines;
    };

} // namespace BraneScript

#endif
