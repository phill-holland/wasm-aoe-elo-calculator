module;
#include <string>

export module player;

export class player
{
public:
    int elo;    
    std::string name;

public:
    player()
    {
        clear();
    }

    player(int _elo, std::string _name = "")
    {
        elo = _elo;
        name = _name;
    }

    void clear()
    {
        elo = 0;
        name = "";
    }

    std::string serialise()
    {
        std::string result = "{\"name\":\"";
        result += name + "\",\"elo\":" + std::to_string(elo) + "}";
        return result;
    }
};
