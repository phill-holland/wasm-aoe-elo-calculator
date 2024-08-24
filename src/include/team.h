#include "player.h"
#include <vector>
#include <tuple>
#include <string>

#ifndef _TEAM
#define _TEAM

class team
{
public:
    std::vector<std::tuple<int,player>> members;
    int elo;

public:
    team() { clear(); }

    void clear()
    {
        elo = 0;
        members.clear();
    }

    std::string serialise()
    {
        int length = members.size();
        int index = 0;

        std::string result = "{\"elo\":" + std::to_string(elo) + ",\"members\":[";
        for(auto &it:members)
        {
            player p1 = std::get<1>(it);
            result += p1.serialise();
            if(index < length - 1) result += ",";
            ++index;
        }
        result += "]}";
        return result;
    }
};

#endif