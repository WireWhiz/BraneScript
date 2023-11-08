//
// Created by wirewhiz on 14/10/22.
//

#include "typeDef.h"

namespace BraneScript
{
    bool NativeType::isRef() const { return false; }

    bool NativeType::isStruct() const { return false; }

    std::string NativeType::signature() const { return name; }

    bool NativeType::isFunc() const { return false; }

    bool ReferenceType::isRef() const { return true; }

    bool ReferenceType::isStruct() const { return false; }

    std::string ReferenceType::signature() const { return "&" + containedType->signature(); }

    bool ReferenceType::isFunc() const { return false; }

    bool StructType::isRef() const { return false; }

    bool StructType::isStruct() const { return true; }

    std::string StructType::signature() const { return name; }

    bool StructType::isFunc() const { return false; }

    bool FunctionType::isRef() const { return true; }

    bool FunctionType::isStruct() const { return false; }

    bool FunctionType::isFunc() const { return true; }

    std::string FunctionType::signature() const {
        std::string sig = returnType->signature() + " fn(";
        auto param = paramTypes.begin();
        while (param != paramTypes.end())
        {
            sig += (*param)->signature();
            param++;
            if(param != paramTypes.end())
                sig += ", ";
        }
        sig += ")";
        return sig;
    }
} // namespace BraneScript