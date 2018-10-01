#ifndef MAINCHAR_H
#define MAINCHAR_H

#include "Character.h"

class MainChar : public Character
{
public:
    MainChar(int hit_points,int att_power, int magic_energy, std::string (type));
    void attack(Character& foe);
    void bolt_spell(Character& foe);
    void aura_spell();
    ~MainChar();

    int hp_init;
};

#endif // MAINCHAR_H
