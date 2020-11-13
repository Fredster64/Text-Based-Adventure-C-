#include "mainChar.h"
#include <iostream>
#include <cstdlib> //for rand()

#include "../util.h"

using namespace std;

MainChar::MainChar(int hit_points, int att_power, int magic_energy, string type)
    :Character(hit_points,att_power,magic_energy,type)
{
    hp_init = hp;
    // Get player name
    cout << "What is your name, adventurer?" << endl;
    cin >> name;
    cout << "Greetings, " << name << "." << endl << endl;
}

void MainChar::bolt_spell(Character& foe)
{
    // Test if spell can be cast
    if(magic != 0)
    {
        cout << "You cast a fiery bolt of magical energy to hurl at your foe." << endl;
        cout << "The bolt does " << min(7, foe.hp) << " damage to the " << foe.name << "." << endl;

        // Special case: damaging a pile of snakes
        //  reduces the number of them
        if( ( foe.name ) == "pile of slippery snakes" && ( foe.hp > 7 ) )
        {
            cout << "7 of the snakes are mortally wounded, decreasing the attack power of the pile." << endl;
            foe.att_pow -= 7;
        }
        // Update relevant data members
        foe.hp -= min(7, foe.hp);
        magic--;
    }

    // Spell not cast successfully
    else
        cout << "No magic points remaining!" << endl;

    cout << endl;
};

void MainChar::aura_spell()
{
    // Successful cast
    if(magic != 0)
    {
        cout << "You surround yourself with a mystical aura, healing some damage." << endl;
        cout << "You heal " << min(10, hp_init-hp) << " hit points." << endl;
        hp += min(10, hp_init-hp);
        magic--;
    }

    // Failed cast
    else
        cout << "No magic points remaining!" << endl;

    cout << endl;
};

void MainChar::attack(Character& foe)
{
    int crit_bit = rand()%4; // determines whether critical hit happens
    int damage = att_pow;
    cout << "You attack the " << foe.name << "." << endl;
    tba_sleep(300);

    // Adjust damage if hit is critical
    if( crit_bit == 0 )
    {
        damage += 2;
        cout << "You get a critical hit!" << endl;
    }

    cout << "Your attack does " << min(damage, foe.hp) << " damage." << endl;
    // Special case: damaging a pile of snakes and not killing it
    if( ( foe.name == "pile of slippery snakes" ) && ( foe.hp > damage ) )
    {
        cout << damage << " of the snakes are mortally wounded, decreasing the attack power of the pile." << endl;
        foe.att_pow -= damage;
    }
    // Adjust relevant variables
    foe.hp -= damage;
    cout << endl;
}

MainChar::~MainChar() {}
