//
// Created by wirewhiz on 15/10/22.
//

#include "irScript.h"

template<typename T>
int16_t insertOnce(std::vector<T>& vec, const T& item)
{
    for(int16_t i = 0; i < vec.size(); ++i)
        if(vec[i] == item)
            return i;
    auto index = vec.size();
    vec.push_back(item);
    return index;
}

int16_t BraneScript::IRScript::findLocalFuncIndex(const std::string& name) const
{
    for(int16_t f = 0; f < localFunctions.size(); ++f)
        if(localFunctions[f].sig == name)
            return f;
    return -1;
}

int16_t BraneScript::IRScript::linkFunction(const std::string& name)
{
    return insertOnce(linkedFunctions, name);
}

int16_t BraneScript::IRScript::linkStruct(const std::string& name)
{
    return insertOnce(linkedStructs, name);
}
