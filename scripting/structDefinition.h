//
// Created by eli on 11/13/2022.
//

#ifndef BRANESCRIPT_STRUCTDEFINITION_H
#define BRANESCRIPT_STRUCTDEFINITION_H

#include "typeDef.h"
#include <vector>

namespace BraneScript
{
    struct StructVar
    {
        std::string name;
        uint16_t offset = 0;
        TypeDef* type = nullptr;
        bool ref = false;
    };

    class StructDef : public TypeDef
    {
        std::string _name;
        std::vector<StructVar> _variables;
        std::vector<std::string> _functions;
        uint16_t _size;
    public:
        StructDef(std::string name);
        /**
         * Add a tightly packed member
         * Call padMembers after all members have been added if you want to use padding.
         * @see padMembers()
         * @param name member name
         * @param type member type
         */
        void addMember(std::string name, TypeDef* type);
        /**
         * initialize member offsets and struct size using padding
         */
        void padMembers();
        /**
         * initialize member offsets and struct size without padding
         */
        void packMembers();

        const StructVar* getMember(const std::string& name) const;
        const std::vector<StructVar>& members() const;

        const char* name() const override;
        uint16_t size() const override;
        ValueType type() const override;
    };
}



#endif //BRANESCRIPT_STRUCTDEFINITION_H
