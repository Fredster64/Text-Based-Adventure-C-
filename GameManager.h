// Contains method declarations for the GameManager class 
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Objects/main_char.h"
#include "Objects/enemy.h"

class GameManager
{
    // ----- Methods ----- //
    
    // Constructor will execute setup and also the main game loop
    GameManager();
    // Player decides whether or not to start the game
    bool chooseToStart();
    // Main game loop 
    void gameLoop();
    
    // Event methods 
    void enemyEvent(); 
    void trapEvent(); 
    void benchEvent();
    void potionEvent(); 
    
    // ----- Data members ------ //
    
    // Main character
    int start_hp;
    int start_att;
    int start_magic;
    main_char player;

    //game set-up
    int steps_to_end;
    int steps_before_event;
    int r; //event determiner, used in main loop 
    int event_bit; //1 if an event occurs; 0 if it does not
    std::string answer; //answer to 'yes/no' questions
    
    // Enemy data
    enemy *foe;
    int levelSelector; //determines level of enemy (0 if weak, 1 if strong)
    int nameFinder; //finds enemy name
    int statsFinder; //finds enemy stats from enemy array
    std::string foeName;  //name of foe;
    
     // trap-related variables
    int trapSelector; //determines which trap you find
    int eventSelector; //determines whether you escape or not   
};

#endif
