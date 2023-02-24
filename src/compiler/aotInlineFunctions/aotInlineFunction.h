//
// Created by wirewhiz on 2/18/23.
//

#ifndef BRANESCRIPT_AOTINLINEFUNCTION_H
#define BRANESCRIPT_AOTINLINEFUNCTION_H

#include <vector>
#include "aotNodes/aotNode.h"


namespace BraneScript
{
    class AotInlineFunction
    {
      protected:
        std::string _name;
        const TypeDef* _resType;
      public:
        AotInlineFunction(std::string name, const TypeDef* resType);
        virtual ~AotInlineFunction() = default;

        virtual bool argsMatch(const std::vector<AotNode*>& args) const = 0;
        virtual AotNode* generateAotTree(const std::vector<AotNode*>& args) const = 0;

        inline const std::string& name() const {return _name;};
        inline const TypeDef* resType() const {return _resType;};
    };
} // namespace BraneScript

#endif // BRANESCRIPT_AOTINLINEFUNCTION_H
