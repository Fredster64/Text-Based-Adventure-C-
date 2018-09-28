#include "character.h"
using namespace std;

character::character(int hit_points, int att_power, int magic_energy, string type)
{
    hp = hit_points;
    att_pow = att_power;
    magic = magic_energy;
    name = type;
};


