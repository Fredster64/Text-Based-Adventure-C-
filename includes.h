#include <string>
#include "Objects/main_char.h"
#include "Objects/enemy.h"

// Declaring non-member functions

// Get a random integer between 0 and a-1 inclusive
int random(int a);

// Check if a 'T'-type is dead
template <class T>
int dead_check(T& thing);
// Override for main_char
template <>
int dead_check<>(main_char& player);

// Get probability of a spell being cast
int spellProb(enemy foe);

// Battle sequence between player and foe
void battle(main_char& player, enemy& foe);
