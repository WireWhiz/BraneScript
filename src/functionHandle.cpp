//
// Created by eli on 11/4/2022.
//

#include "functionHandle.h"
#include <string_view>

namespace BraneScript
{

    FuncDef::FuncDef(std::string def) : _def(std::move(def))
    {
        size_t i = _def.find('(');
        assert(i != std::string::npos);
        _nameEnd = i;
        ++i;

        bool commaFound = true;
        while(commaFound)
        {
            commaFound = false;
            ArgData data{};
            if(6 < _def.size() && std::string_view{_def.data() + i, 6} == "const ")
            {
                data.flags |= ArgFlags_Const;
                i += 6;
            }
            if(i + 4 < _def.size() && std::string_view{_def.data() + i, 4} == "ref ")
            {
                data.flags |= ArgFlags_Ref;
                i += 4;
            }
            size_t end = std::string_view{_def.data() + i, _def.size() - i}.find(',');
            if(end != std::string_view::npos)
            {
                commaFound = true;
                end += i;
            }
            else
                end = _def.size() - 1;

            data.tStart = i;
            data.tEnd = end;
            _argIndices.push_back(data);
            if(commaFound)
                i = end + 1;
            if(end >= _def.size())
            {
                assert(false);
                break;
            }
        }

    }

    std::string_view FuncDef::name() const
    {
        return std::string_view(_def.data(), _nameEnd);
    }

    size_t FuncDef::argCount() const
    {
        return _argIndices.size();
    }

    std::string_view FuncDef::argType(size_t index) const
    {
        assert(index < argCount());
        const auto& data = _argIndices[index];
        return std::string_view(_def.data() + data.tStart, data.tEnd - data.tStart);
    }

    bool FuncDef::argIsConst(size_t index) const
    {
        assert(index < argCount());
        return _argIndices[index].flags & ArgFlags_Const;
    }

    bool FuncDef::argIsRef(size_t index) const
    {
        return _argIndices[index].flags & ArgFlags_Ref;
    }
}