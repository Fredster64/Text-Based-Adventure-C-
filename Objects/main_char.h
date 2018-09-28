#ifndef MAIN_CHAR_H
#define MAIN_CHAR_H

#include "character.h"

class main_char : public character
{
public:
    main_char(int hit_points,int att_power, int magic_energy, std::string (type));
    void attack(character& foe);
    void bolt_spell(character& foe);
    void aura_spell();
    ~main_char();

    int hp_init;
};

#endif // MAIN_CHAR_H
