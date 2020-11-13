#include <string>
#include "Objects/mainChar.h"
#include "Objects/enemy.h"

// Declaring non-member functions

// Get a random integer between 0 and a-1 inclusive
int random(int a);

// Check if a 'T'-type is dead
template <class T>
int dead_check(T& thing);
// Override for main_char
template <>
int dead_check<>(MainChar& player);

// Get probability of a spell being cast
int spellProb(Enemy foe);

// Battle sequence between player and foe
void battle(MainChar& player, Enemy& foe);

// Custom sleep function
void tba_sleep(int d);
