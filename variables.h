// ----- Global Variables ----- //

//weak enemies (level 0)
int weak_enemies[][3]=
{
    {11,3,1}, {5,3,0}, {12,3,0}, {4,3,3}, {7,4,0} // {hp, attack power, magic points}
};
std::string weak_enemy_names[]= {"skeleton","giant rat","possessed corpse","magic carpet","goblin"};

//strong enemies (level 1)
int strong_enemies[][3]=
{
    {6,8,0}, {8,2,3}, {14,5,1}, {8,8,0} // {hp, attack power, magic points}
};
std::string strong_enemy_names[]= {"venomous spider", "mad warlock", "haunted suit of armour", "pile of slippery snakes"};

//traps
std::string traps[]= {"It's a slippery banana peel!","You are teetering on the edge of a deep pit!","An arrow is whizzing towards you!","The walls of the room are closing in!"};
int trap_stats[][2]=
{
    {2,2},{5,2},{7,3},{10,3} // {damage, probability of getting hit}
};
std::string trap_events[][2]=  // {avoid,fall into}
{
    {"You step around it and avoid damage.","You fail to notice it and slip."},
    {"You manage to regain your balance and escape unharmed.","You fall into the dark pit and thud against the ground."},
    {"You duck, narrowly avoiding the missile.","The arrow strikes you, creating a deep wound."},
    {"You squeeze through the door as the walls slam behind you. You escape unharmed.","You don't make it out in time - the walls crush you as you exit the room."}
};

// ----- End of global variables ----- //
