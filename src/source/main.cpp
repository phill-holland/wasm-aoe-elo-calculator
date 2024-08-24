// source exwasm1.cpp
// em++ -lembind exwasm1.cpp -o exwasm1.js -s WASM=1 [compilation]
// output: exwasm1.wasm (bytecode) and exwasm1.js (JS glue-code)
#include<string>
#include<emscripten.h>
#include<emscripten/bind.h>
#include "player.h"
#include "teams.h"
#include "calculator.h"

using namespace std;
using namespace emscripten;

string calculate(emscripten::val arg)
{
    vector<int> source = vecFromJSArray<int>(arg);
    std::vector<player> players;
    int total_teams = 2;
    
    int counter = 1;
    for(auto &it:source)
    {
        std::string name = "player" + std::to_string(counter);
        players.push_back(player(it, name));
        ++counter;
    }

    std::vector<teams> data = calculator::calculate(players, total_teams);
    std::string output = data.front().serialise();

    return output;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("calculate", &calculate);
}