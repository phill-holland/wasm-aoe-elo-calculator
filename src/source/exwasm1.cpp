// source exwasm1.cpp
// em++ -lembind exwasm1.cpp -o exwasm1.js -s WASM=1 [compilation]
// output: exwasm1.wasm (bytecode) and exwasm1.js (JS glue-code)
#include<string>
#include<emscripten.h>
#include<emscripten/bind.h>

using namespace std;
using namespace emscripten;

// C++ function exposed to JS
string modifyStr(const string & s)
{ // returns a copy of s whose the first/last characters are
    string str(s); // replaced by 'X'
    if(str.size()>=3)
    {
        str[0]='X';
        str[str.size()-1]='X';
    }
    return str;
}

int mooMoo(emscripten::val arg)
{
    vector<int> v = vecFromJSArray<int>(arg);

    int total = 0;
    for(auto &it:v)
    {
        total += it;
    }

    return total;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("modify", &modifyStr); //called from JS as Module.modify(...)
    emscripten::function("moo", &mooMoo);
}