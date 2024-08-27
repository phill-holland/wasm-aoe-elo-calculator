#include "calculator.h"

std::vector<teams> calculator::calculate(std::vector<player> players, int total_teams)
{
    float average = 0.0f;    
    for(auto &it: players)
    {    
        average += (float)it.elo;     
    }

    average /= (float)total_teams;

    float max_team_elo = 0.0f;

    std::vector<permutation> data = permutations(players, max_team_elo, total_teams);
    return front(data, players, total_teams, average, max_team_elo); 
}

std::vector<permutation> calculator::permutations(std::vector<player> &players, float &max_team_elo, int total_teams)
{
std::vector<permutation> data;
    std::vector<int> play;
    std::unordered_map<std::string,std::string> duplicates;

    play.resize(players.size());

    int counter = 0;
    for(auto &it: players)
    {    
        play[counter] = counter;
        ++counter;
    }

    int players_per_team = players.size() / total_teams;

    do
    {
        std::unordered_map<int,team> map;
        permutation permutate;

        int previous_team_idx = 0;
        int counter = 0;
        for(auto &it:play)
        {
            float value = (float)players[it].elo;

            int team_idx = (int)std::floor((float)counter / (float)(players_per_team));
            if(map.find(team_idx) == map.end()) 
            {
                team t1;
                t1.elo = value;
                t1.members.push_back(std::tuple<int,player>(it,players[it]));
                map[team_idx] = t1;
            }
            else 
            {
                map[team_idx].members.push_back(std::tuple<int,player>(it,players[it]));
                map[team_idx].elo += value;
            }

            ++counter;
        }

        permutate.map = map;
        std::string key;

        for(auto &it:map)
        {            
            std::sort(it.second.members.begin(), it.second.members.end(), [](const std::tuple<int,player> &lhs, const std::tuple<int,player> &rhs)
            {
                return std::get<0>(lhs) < std::get<0>(rhs);
            });            
            
            for(auto &jt:it.second.members)
            {
                key += std::to_string(std::get<0>(jt));
            }

            if(it.second.elo>max_team_elo) max_team_elo = it.second.elo;        
        }

        if(duplicates.find(key) == duplicates.end())
        {
            data.push_back(permutate);
            duplicates[key] = key;
        }

    } while(std::next_permutation(play.begin(), play.end()));

    return data;
}

std::vector<teams> calculator::front(std::vector<permutation> &data, std::vector<player> &players, int total_teams, float average, float max_team_elo)
{
    std::vector<teams> results;

    int count = data.size();
    bool result[count];
    for(int i = 0; i < count; ++i)
    {
        result[i] = true;
    }

    point a(total_teams);
    point b(total_teams);

    for(int i =  0; i < count; ++i)
    {
        int counter = 0;
        for(auto &it:data[i].map)
        {
            float distance = abs(it.second.elo - average);
            distance = ((distance/max_team_elo) * -1.0f) + 1.0f;
            a.set((long)(distance * 1000.0f), counter++);
        }

        for(int j  = 0; j < count; ++j)        
        {
            if(i != j)
            {
                int counter = 0;
                for(auto &it:data[j].map)
                {
                    float distance = abs(it.second.elo - average);
                    distance = ((distance/max_team_elo) * -1.0f) + 1.0f;
                    b.set((long)(distance * 1000.0f), counter++);
                }

                if(b.dominates(a))
                {
                    result[i] = false;
                    break;
                }
            }
        }
    }

    int output_count = 0;

    for(int i = 0; i < count; ++i)
    {
        if(result[i])
        {
            teams teams1;
            for(auto&it:data[i].map)
            {
                team temp;
                temp.elo = it.second.elo;

                for(auto &jt:it.second.members) 
                {
                    temp.members.push_back(jt);
                }

                teams1.data.push_back(temp);
            }

            // ***
            for(int player_idx = 0; player_idx < players.size(); ++player_idx)
            {
                for(auto&it:data[i].map)
                {
                    for(auto &jt:it.second.members) 
                    {
                        if(std::get<0>(jt) == player_idx)
                        {
                            teams1.mapping.push_back(it.first + 1);
                        }
                    }
                }
            }

            results.push_back(teams1);

        }
    }

    return results;
}