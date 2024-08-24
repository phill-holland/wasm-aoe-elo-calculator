# Age of Empire 1 - ELO Calculator

source ./emsdk_env.sh

python3 -m http.server 4040

emcc reverse.cpp -s STANDALONE_WASM –o reverse.wasm

emcc -o hello2.html hello2.cpp -O3 --shell-file html_template/shell_minimal.html

emcc -o hello3.html hello3.cpp --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"

// ***
em++ -lembind exwasm1.cpp -o exwasm1.js -s WASM=1
// ****



https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_Wasm



This code repo computes team members based on their ELO, or ranked score during setting up a multiplayer game of Age Of Empires 1.

# Generalised Problem

Give a random collection of players that all have assigned a ranking score called ELO, determining their skill level within the game, below;

```
        player(elo=600, name="dave")
        player(elo=600, name="susan")
        player(elo=1200, name="bob")
        player(elo=2000, name="mary")
        player(elo=700, name="barry")
        player(elo=1200, name="linda")
```

You then have to figure out given each players ranking how to compute the members of each team, such that the total ELO score for each team is balanced.

For example, given the players above, divided into two teams, the teams would be;

team1, total elo=3100
```
        player(elo=1200, name="bob")
        player(elo=700, name="barry")
        player(elo=1200, name="linda")
```

team 2, total elo=3200
```
        player(elo=600, name="dave")
        player(elo=600, name="susan")
        player(elo=2000, name="mary")
```

The difficult of solving this problem comes with many issues to solve;

- There maybe several solutions to the same problem
- There maybe no solutions to the problem
- Computing average scores per team may still result in an incorrect solution

# Method

It first finds all the permutations for all teams, computes the team ELO total score, and then finds the closes distance to the average ELO per team.

It then uses a "pareto front" algorithm to find the best combinations of teams closest to that average, this finds the best solution closest to the ideal total team average, using multi-dimensions (a algorithm which may often be used with genetic algorithms)

The solution is technically brute force, but the total players per multiplayer game (8) is so low it doesn't matter too much.

**Also testing C++ modules in this code repo for the first time!

# Problems To Fix

- Many permutations for team players are duplicates, i.e. team "bob & mary" are the same as team "mary & bob" the algorithm doesn't current account for this

- Needs to check for power of two teams organisation

- The calculator.cxx file could do with refactoring, I got lazy with static functions!

# Future Modifications

- Currently have to manually input players and their ELO, but could use screen capture overlay for the game screen and OCR to automatically generate the list in a future iteration

- Further additions also to include if two or more players always want to play on the same team.

# Building

written on a linux based machine!

```
mkdir build
cd build
cmake -GNinja -DCMAKE_CXX_FLAGS=\"-O0 -g\" ../
```

executable then located in the directory;

```
build/src/elo-calculator
```

# Usage

Command Line;

For the team example given above, you'd input the following on the command line;

```
./elo-calculator 2 600 600 1200 2000 700 1200
```

Which creates two balanced teams (the first number represents the number of teams desired). for 3 teams, you'd enter;

```
./elo-calculator 3 600 600 1200 2000 700 1200
```

The output for two teams may be;

```
team1 elo=3100(2[bob] 4[barry] 5[linda]) 
team0 elo=3200(0[dave] 1[susan] 3[mary]) 
112122
```

The number 112122 at the end of the output, if the order of players is retained tells the players
which team they're on, i.e.  dave & susan are on team 1, bob is on team 2.

# Build Dependencies

You need the following versions installed, which supports compiling C++ modules;

- Cmake >= 3.30
- Ninja >= 1.11
- GCC >= 14

There's a build container for docker configured for use in VSCode, in the .devcontainer folder.

