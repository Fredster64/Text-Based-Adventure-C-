#include "Enemy.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// Enemy constructor will initialise relevant data members
//  and tell the player that the enemy blocks their way
Enemy::Enemy( int hit_points, int att_power, int magic_energy, string (type) )
    :Character(hit_points, att_power, magic_energy, type)
{
    if( name != "" )
    {
        cout << "A " << name << " blocks your way." << endl << endl;
    }
}

// Attack function
void Enemy::attack(Character& player)
{
    cout << "The " << name << " attacks!" << endl;
    cout << "You lose " << min(att_pow, player.hp) << " hit points." << endl << endl;
    player.hp -= min(att_pow, player.hp);
}

// Gets enemy spell and casts it
int Enemy::spell(Character& player)
{
    int spellPicker = 0;
    // No magic points left
    if( magic == 0 )
    {
        cout << "The " << name << " attempts to cast a spell, but has no magic points remaining!" << endl << endl;
        return 1; // Spell has failed to cast
    }

    // Spell is successfully cast
    cout << "The " << name << " casts a spell!" << endl;

    // Different enemies have different spells
    if( name == "skeleton" )
    {
        cout << "The skeleton rebuilds itself, healing all of the damage it has taken." << endl << endl;
        hp = 11;
        magic--;
        return 0;
    }
    if( name == "magic carpet" )
    {
        // Two possible spells for magic carpet
        //  spellPicker helps us choose one at random
        spellPicker = rand()&3;

        // 'wrap' spell
        if( spellPicker != 0 ) // 2/3 chance
        {
            cout << "The carpet wraps itself around your body, causing you to lose " << min(6,player.hp) << " hit points." << endl << endl;
            player.hp -= min(6, player.hp);
        }
        // 'rub' spell
        else
        {
            cout << "The carpet rubs itself against your weapon, softening the blade." << endl;
            cout << "Your attack power has decreased by 1." << endl << endl;
            player.att_pow--;
        }
        magic--;
        return 0;
    }
    if( name=="mad warlock" )
    {
        // Same logic as with magic carpet here
        spellPicker=rand()%3;

        // 'drain' spell
        if( spellPicker != 0 )
        {
            cout << "The warlock drains the life force from your body, causing you to lose " << min(5, player.hp) << " hit points." << endl;
            player.hp -= min(5, player.hp);
            if( hp+5 <= 8 )
            {
                cout << "The warlock gains 5 hit points." << endl << endl;
                hp += 5;
            }
            else
            {
                cout << "The warlock gains " << 8-hp << " hit points." << endl << endl;
                hp = 8;
            }
        }
        // 'flame' spell
        else
        {
            cout << "The warlock summons a host of flames that dance around your feet." << endl;
            cout << "You lose " << min(6, player.hp) << " hit points. In addition, the flames damage your weapon, reducing your attack power by 1." << endl << endl;
            player.hp -= min(6, player.hp);
            player.att_pow--;
        }
        magic--;
        return 0;
    }
    if( name == "haunted suit of armour" )
    {
        cout << "Its sword glows with a blue flame, doubling its attack power." << endl << endl;
        att_pow *= 2;
        magic--;
        return 0;
    }

    // If no spell was cast
    return 1;
}
Enemy::~Enemy() {}
