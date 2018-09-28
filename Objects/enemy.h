#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <string>

class enemy : public character
{
public:
    enemy(int hit_points, int att_power, int magic_energy, std::string (type));
    void attack(character& player);
    int spell(character& player);
    ~enemy();
};

#endif // ENEMY_H
