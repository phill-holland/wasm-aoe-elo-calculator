module;

#include <vector>
#include <string>

import team;

export module teams;

export class teams
{
public:
    std::vector<team> data;
    std::vector<int> mapping;

public:
    teams() { clear(); }

    void clear()
    {
        data.clear();
    }

    std::string serialise()
    {
        auto map = [](std::vector<int> source)
        {
            std::string result;
            for(auto &it:source)
            {
                result += std::to_string(it);
            }
            return result;
        };

        int length = data.size();
        int index = 0;

        std::string result = "{\"mappings\":\"";
        result += map(mapping);
        result += "\",\"teams\":[";
        for(auto &it:data)
        {
            result += it.serialise();
            if(index < length - 1) result += ",";
            ++index;
        }
        result += "]}";

        return result;
    }
};
