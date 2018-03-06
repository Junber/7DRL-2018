#include "spell.h"
#include "global.h"
#include "object.h" //remove?

#include <fstream>

std::deque<std::string> split(std::string s, char seperator)
{
    std::deque<std::string> ret;
    ret.push_back("");
    for (char c: s)
    {
        if (c == seperator)
        {
            ret.push_back("");
        }
        else
        {
            ret[ret.size()-1] += c;
        }
    }

    return ret;
}

Spell::Spell(std::string name)
{
    std::fstream moves_file, effected_file;
    std::string line;

    moves_file.open(std::string("Data")+PATH_SEPARATOR+"Spells"+PATH_SEPARATOR+"Moves"+PATH_SEPARATOR+name+".txt");
    while (!moves_file.eof())
    {
        std::getline(moves_file,line);
        auto splitted = split(line,',');
        moves[0].push_back(std::stoi(splitted[0]));
        moves[1].push_back(std::stoi(splitted[1]));
    }
    moves_file.close();

    effected_file.open(std::string("Data")+PATH_SEPARATOR+"Spells"+PATH_SEPARATOR+"Effected"+PATH_SEPARATOR+name+".txt");
    while (!effected_file.eof())
    {
        std::getline(effected_file,line);
        auto splitted = split(line,',');
        effected[0].push_back(std::stoi(splitted[0]));
        effected[1].push_back(std::stoi(splitted[1]));
    }
    effected_file.close();
}

bool Spell::is_cast(std::deque<int>* moves_made)
{
    int mm_size = moves_made[0].size(), m_size = moves[0].size();

    if (mm_size <= m_size) return false;

    for (int i=-moves[0].size(); i<=-1; i++)
    {
        if (moves_made[0][mm_size+i-1] != moves[0][m_size+i] ||
            moves_made[1][mm_size+i-1] != moves[1][m_size+i]) return false;
    }

    return true;
}

void Spell::cast(int px, int py, int dx, int dy)
{
    for (int i=0; i<effected[0].size(); i++)
    {
        new Object(px+effected[0][i]*dx-effected[1][i]*dy,
                   py+effected[0][i]*dy+effected[1][i]*dx,"alien_dead");
    }
}
