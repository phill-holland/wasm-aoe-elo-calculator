#include "team.h"
#include "teams.h"
#include "player.h"
#include "point.h"
#include <vector>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <tuple>

#ifndef _CALCULATOR
#define _CALCULATOR

class permutation
{
public:
    std::unordered_map<int,team> map;
};

class calculator
{
public:
    static std::vector<teams> calculate(std::vector<player> players, int total_teams);

private:
    static std::vector<permutation> permutations(std::vector<player> &players, float &max_team_elo, int total_teams);
    static std::vector<teams> front(std::vector<permutation> &data, std::vector<player> &players, int total_teams, float average, float max_team_elo);
};

#endif