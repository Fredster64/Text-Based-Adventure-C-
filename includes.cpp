#include <iostream> // Reading 'help' file
#include <cstdlib> // rand(), srand()
#include <fstream> // ifstream

#include "Objects/mainChar.h"
#include "Objects/enemy.h"
#include "includes.h"
#include "util.h"

// ----- Defining Non-member functions ----- //

// return a random integer between 0 and a-1
int random(int a)
{
    return rand()%a;
}

// checks if an object of a given class has been slaughtered
template <class T>
int dead_check(T& thing)
{
    if(thing.hp<=0)
    {
        tba_sleep(1000);
        std::cout << "The " << thing.name << " has been slaughtered." << std::endl << std::endl;
        return 1;
    }
    else
        return 0;

}

// special case for main character
template <>
int dead_check<>(MainChar& player)
{
    if( player.hp <= 0 )
    {
        tba_sleep(1000);
        std::cout << "You have died!" << std::endl;
        tba_sleep(1000);
        return 1;
    }
    else
        return 0;

}

// probability of an enemy attempting to cast a spell
int spellProb(Enemy foe)
{
    //probability of casting a spell is 1/prob
    int prob=100; //probability of a non-magic foe attempting to cast

    if( foe.name == "skeleton" )
        prob = foe.hp;

    else if( ( foe.name=="magic carpet" ) || ( foe.name == "mad warlock" ) )
        prob = 1;

    else if( foe.name == "haunted suit of armour" )
        prob = 16 - foe.hp;

    return prob;
}

// the battle sequence between an enemy and the main character
void battle(MainChar& player, Enemy& foe)
{
    // Decides whether foe will attack or cast a spell
    int foeChoice = 0;
    // Loops until one battler is defeated
    while( ( foe.hp > 0 ) && ( player.hp > 0 ) )
    {
        //--- Enemy turn ---//
        tba_sleep(1000);
        foeChoice = random( spellProb(foe) );
        if( (foeChoice == 0) )  //if the enemy will cast a spell
        {
            if( (foe.spell(player) == 1) ) //spell is cast in this function call if it can be cast
            // return value of 1 indicates that spell hasn't been cast
                foe.attack(player); //if spell can't be cast, player is attacked instead
        }
        // Default action for opponent
        else
            foe.attack(player);


        //--- Player turn ----//

        tba_sleep(1000);
        if(player.hp>0)
        {
            // UI text
            std::cout << player.name << ": hit points " << player.hp << "/att. power " << player.att_pow << "/magic points " << player.magic << std::endl;
            std::cout << "The " << foe.name << " has " << foe.hp << " hit points remaining." << std::endl << std::endl;
            tba_sleep(1500);
            std::cout << "What will you do?" << std::endl;
            tba_sleep(500);
            std::cout << "Choose: 'attack', 'bolt' or 'aura'." << std::endl;
            std::cout << "Type 'help' if you need the rules of combat explained." << std::endl;
            std::string turn_choice = "";

            // get the player's choice of action

            while( (turn_choice != "attack") && (turn_choice != "bolt") && (turn_choice != "aura") )
            {
                std::cin >> turn_choice;
                std::cout << std::endl;
                if(turn_choice == "help")
                {
                    // printing the help screen from a .txt file
                    std::string line;
                    std::ifstream combat_help("Text/combat_help.txt");
                    while( getline(combat_help, line) )
                    {
                        std::cout << line << std::endl;
                    }
                    std::cout << std::endl;
                    // Close file after use
                    combat_help.close();
                }

                // invalid command entered (or 'help')
                if( ( turn_choice != "attack" ) && ( turn_choice != "bolt" ) && ( turn_choice != "aura" ) )
                    std::cout << "Please choose 'attack', 'bolt' or 'aura'." << std::endl;
            }

            // A valid choice was entered
            if(turn_choice == "attack")
                player.attack(foe);

            if(turn_choice == "bolt")
                player.bolt_spell(foe);

            if(turn_choice == "aura")
                player.aura_spell();

        }
    }

    // ending the fight
    if(dead_check(foe) == 1)
        return;

    // dead_check for player happens in main loop
    //  so we don't need to call it here
    if(player.hp <= 0)
        return;

}

// ----- End of non-member functions ----- //
