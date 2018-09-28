#include <string>
#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;

class character
{
public:
    character(int hit_points,int att_power,int magic_energy,std::string type);

    int hp;
    int att_pow;
    int magic;
    std::string name;
};

#endif // CHARACTER_H
