#include <vector>
#include <string>
#include <iostream>

import calculator;
import player;
import teams;

using namespace std;

int main(int argc, char *argv[])
{ 
    std::vector<player> players = {
        player(600, "dave"),
        player(600, "susan"),
        player(1200, "bob"),
        player(2000, "mary"),
        player(700, "barry"),
        player(1200, "linda")
    };

    int total_teams = 2;

    if(argc > 2)
    {
        total_teams = atoi(argv[1]);
        std::vector<player> temp;
        for(int i = 2; i < argc; ++i)
        {
            std::string name = "player" + std::to_string(i);
            temp.push_back(player(atoi(argv[i]), name));
        }

        players = temp;
    }
    
    std::vector<teams> data = calculator::calculate(players, total_teams);
    std::string output = data.front().serialise();
    std::cout << output << std::endl;

    return 0;
}