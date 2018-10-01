#include <string>
#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
    Character(int hit_points, int att_power, int magic_energy, std::string type);

    int hp;
    int att_pow;
    int magic;
    std::string name;
};

#endif // CHARACTER_H
