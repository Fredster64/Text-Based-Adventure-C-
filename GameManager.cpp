// Contains definitions of member methods for GameManager

#include "GameManager.h"
#include "variables.h"
#include "includes.h"
#include "Objects/main_char.h"
#include "Objects/enemy.h"

#include <iostream> // Input and output text
#include <fstream> //for reading text files
#include <windows.h> // Sleep()
#include <ctime> // Use time() to give a seed to random()

using namespace std; 

// Constructor will set up game 
//  and enter game loop
GameManager::GameManager() 
{
    // Set random seed 
    srand( (unsigned) time(0) ); 
    
    // See if player wants to start game 
    if ( !chooseToStart() )
      return;
      
    // ----- Initialise data members ----- //
    
    // Create player
    start_hp = 30;
    start_att = 5;
    start_magic = 5;
    player = main_char(start_hp, start_att, start_magic, "");

    // Game variables
    steps_to_end = 30;
    steps_before_event = 0;
    r = 1; 
    event_bit = 1; 
    answer = ""; 
    
    //initialise the enemy pointer (as null)
    foe = 0;

    // Enemy-related variables
    levelSelector = 0; //determines level of enemy (0 if weak, 1 if strong)
    nameFinder = 0; //finds enemy name
    statsFinder = 0; //finds enemy stats from enemy array
    foeName = "";  //name of foe;

    // trap-related variables
    trapSelector = 0; //determines which trap you find
    eventSelector = 0; //determines whether you escape or not

    // ----- Set up and Play ----- //

    //Pre-game text
    Sleep(1000);
    cout << "Your quest is to reach the treasure, which is " << steps_to_end << " steps away." << endl;
    cout << "You start with " << start_hp << " hit points, as well as " << start_magic << " magic points." << endl;
    cout << "Your regular attack does " << start_att << " damage." << endl;
    cout << "Good luck!" << endl << endl;

    gameLoop();
      
    return;
};

// Player decides whether or not they want to start the game 
bool GameManager::chooseToStart()
{
    //reading introduction text
    string line;
    ifstream intro("Text/intro.txt");
    while(getline(intro, line))
        cout << line << endl;

    intro.close();

    Sleep(2000);
    cout << "Will you?" << endl;
    
    // Get user input in play_bit
    string play_bit;
    while( (play_bit != "yes" ) && ( play_bit != "no" ) )
    {
        cin >> play_bit;
        if( (play_bit != "yes" ) && ( play_bit != "no" ) )
            cout << "Answer 'yes' or 'no'." << endl;
    }
    
    //Saying no to 'will you?'
    if( play_bit == "no" )
    {
        cout << "Never mind then.";
        Sleep(500);
        return false; // end the game
    }
    
    // play_bit = 'yes'
    return true;
};

// ----- Event Methods ----- //

void GameManager::enemyEvent()
{
    Sleep(2000);
    cout << "You walk " << steps_before_event << " steps before..." << endl;
    statsFinder = random(5); //default setting (for random weak enemy)

    //see if we get a strong enemy - 1 in 4 chance
    levelSelector=random(4);
    if( levelSelector == 1 )
    {
        statsFinder = random(4);
        nameFinder = 1; // toggles because we now need to find name for strong enemy
    }

    //Construct enemy and battle it
    Sleep(1000);

    // Strong enemy case
    if( nameFinder == 1 )
    {
        // Get enemy data and battle it
        foeName = strong_enemy_names[statsFinder];
        foe = new enemy(strong_enemies[statsFinder][0],strong_enemies[statsFinder][1],strong_enemies[statsFinder][2],foeName);
        battle(player, *foe);
        delete foe;
    }
    // Weak enemy case
    if( nameFinder == 0 )
    {
        // Get enemy data and battle it
        foeName=weak_enemy_names[statsFinder];
        foe = new enemy(weak_enemies[statsFinder][0],weak_enemies[statsFinder][1],weak_enemies[statsFinder][2],foeName);
        battle(player,*foe);
        delete foe;
    }
    return;
};

void GameManager::trapEvent()
{
      Sleep(2000);
    cout << "You walk " << steps_before_event << " steps. Something doesn't feel right..." << endl;
    trapSelector = random(4); //chooses trap
    Sleep(1000);
    
    // Print trap intro text
    cout << "It's a trap!" << endl << traps[trapSelector] << endl;
    
    eventSelector = random( trap_stats[trapSelector][1] ); //see if you escape
    Sleep(1000);

    // Trap triggered
    if( eventSelector == 0 )
    {
        cout << trap_events[trapSelector][1] << " You lose " << min(trap_stats[trapSelector][0], player.hp) << " hit points." << endl;
        player.hp -= min( trap_stats[trapSelector][0], player.hp );
    }
    // Trap avoided
    else
        // Prints trap avoid text
        cout << trap_events[trapSelector][0] << endl;

    cout << endl;
    return;    
};

void GameManager::benchEvent()
{
    Sleep(2000);
    
    // Print explanatory text
    cout << "You walk " << steps_before_event << " steps before..." << endl;
    Sleep(1000);
    cout << "You reach a comfortable-looking bench." << endl;
    cout << "However, you also see a potentially useful object on the floor ahead of you." << endl;
    Sleep(500);
    cout << "Will you take a seat?" << endl;
    
    // Get player answer
    cin >> answer;
    while( ( answer != "yes" ) && ( answer!="no" ) )
    {
        cout << "Answer 'yes' or 'no'." << endl;
        cin >> answer;
    }
    
    // Sit on the bench
    if( answer == "yes" )
    {
        cout << "You take a seat and relax, recovering from previous battles." << endl;
        cout << "However, when you set off, you notice that the object that was on the floor has disappeared." << endl;
        cout << "You heal " << min(10,player.hp_init-player.hp) << " hit points." << endl << endl;
        player.hp += min(10, player.hp_init - player.hp);
    }
    // Don't sit on the bench
    if( answer == "no" )
    {
        // A whetstone is found on the floor
        cout << "You walk away. As you do, you collect the object ahead of you. It's a whetstone!" << endl;
        cout << "You sharpen your blade, increasing your attack power by 1." << endl << endl;
        player.att_pow++;
    }
    return;
};

void GameManager::potionEvent()
{
    Sleep(2000);
    cout << "You walk " << steps_before_event << " steps before..." << endl;
    Sleep(1000);
    // Explanatory text
    cout << "You see a strange potion on a shelf to your right." << endl;
    cout << "Will you drink the potion?" << endl;
    
    cin >> answer;
    // Make sure answer is 'yes' or 'no'
    while( ( answer != "yes" ) && ( answer != "no" ) )
    {
        cout << "Answer 'yes' or 'no'." << endl;
        cin >> answer;
    }
    Sleep(500);
    
    // Drink the potion
    if( answer == "yes" )
    {
        // Randomly decide which potion will be drunk
        int potion_choice=random(2);

        // Bitter potion
        if( potion_choice == 0 )
        {
            cout << "The potion tastes bitter. It seems to be draining your very life force." << endl;
            cout << "You lose " << min(6, player.hp) << " hit points." << endl << endl;
            player.hp -= min(6, player.hp);
        }
        // Sweet potion
        else
        {
            cout << "The potion tastes sweet. You feel raw magical power surging through your veins." << endl;
            cout << "You gain 2 magic points." << endl << endl;
            player.magic += 2;
        }
    }

    // Potion not drunk
    else
        cout << "You leave the potion behind."<< endl << endl;
            
    return;
};

// ----- End of Event Methods ----- //


// The game loop itself 
// Uses r to determine randomly what events occur at a given step
void GameManager::gameLoop()
{
    while( ( steps_to_end > 0 ) && ( dead_check(player) == 0 ) )
    {
        answer = "";
        event_bit = 1; //assumes something happens, unless we go to default case
        r = random(21); //determines what event happens
        if( r <= 4 )
            r = 0; //so 'case 0' below is actually 'case <= 4'

        // Gets event based on value of r
        switch(r)
        {
            // enemy event
            case 0:
                enemyEvent();
                break;

            //trap event
            case 5:
                trapEvent();
                break;

            //sit on a bench
            case 6:
                benchEvent();
                break;

            //potion event
            case 7:
                potionEvent();
                break;

            //just walk forward (no event)
            default:
                // Update relevant variables
                event_bit = 0;
                steps_to_end--;
                steps_before_event++;
                break;
                
            } // End of switch
        
        // Check if game will continue (after an event has occurred)
        if( ( event_bit == 1 ) && ( player.hp > 0 ) )
        {
            Sleep(1000);
            cout << "You must travel a further " << steps_to_end << " steps before you reach the treasure." << endl << endl;
            steps_to_end--;
            steps_before_event = 1;
        }
    } // end of while loop
    
    // Test if player has won the game
    if( ( steps_to_end <= 0 ) && ( player.hp > 0 ) ) 
    {
        Sleep(2000);
        cout << "You walk " << steps_before_event << " steps before..." << endl;
        Sleep(1000);
        cout << "...you see a golden glow ahead of you." << endl;
        cout << "You find yourself in a room full of unimaginable treasures." << endl;
        Sleep(1000);
        cout << "Claiming the treasure as your own, you fill your bag and rush out of the castle." << endl;
        Sleep(500);
        cout << "Congratulations, " << player.name << ", you have completed the quest and obtained the treasure!" << endl;
    }
    return;
};
