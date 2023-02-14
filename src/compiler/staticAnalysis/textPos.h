#ifndef BRANESCRIPT_TEXTPOS_H
#define BRANESCRIPT_TEXTPOS_H

#include <cstdint>
#include <json/json.h>

namespace BraneScript
{
    struct TextPos {
        size_t line;
        size_t charPos;
        inline bool operator==(const TextPos& o){return line == o.line && charPos == o.charPos;};
        inline bool operator!=(const TextPos& o){return line != o.line || charPos != o.charPos;};
    };

    struct TextRange {
        TextPos start;
        TextPos end;
        inline bool posInRange(TextPos pos) const
        {
            if(start.line > pos.line || (start.line == pos.line && pos.charPos < start.charPos))
                return false;
            if(end.line < pos.line || (end.line == pos.line && pos.charPos > end.charPos))
                return false;
            return true;
        }

        template<typename T>
        std::pair<typename T::difference_type, typename T::difference_type> getBoundsForText(T& text)
        {
            std::pair<typename T::difference_type, typename T::difference_type> bounds;
            TextPos pos{0,0};
            typename T::difference_type i = 0;
            while(i < text.size())
            {
                if(pos == start)
                    bounds.first = i;
                if(pos == end) {
                    bounds.second = i;
                    return bounds;
                }
                if(text[i] == '\n') {
                    pos.line++;
                    pos.charPos = 0;
                }
                else
                    pos.charPos++;
                i++;
            }
            bounds.second = i;

            return bounds;
        }

        inline Json::Value toJson()
        {
            Json::Value jStart;
            jStart["line"] = start.line;
            jStart["character"] = start.charPos;
            Json::Value jEnd;
            jEnd["line"] = end.line;
            jEnd["character"] = end.charPos;
            Json::Value result;
            result["start"] = std::move(jStart);
            result["end"] = std::move(jEnd);
            return std::move(result);
        }

        inline static BraneScript::TextRange fromJson(const Json::Value& range)
        {
            auto& start = range["start"];
            auto& end = range["end"];
            return {
                {
                    start["line"].asUInt(),
                    start["character"].asUInt()
                },
                {
                    end["line"].asUInt(),
                    end["character"].asUInt()
                }
            };
        }
    };
}

#endif // BRANESCRIPT_TEXTPOS_H
