#ifndef MATCH_ENUMS_HPP
#define MATCH_ENUMS_HPP

//This file was created to evade ciclic incldues with match.hpp
//There are files wich only include the enums of match.hpp, so we took them apart in another file

//Indexes of the vector that saves the camera2D position of the players in each scene that requires this
//We created a vector with this, the index WORLD_KITCHEN represents the saved player position in this scene. It values for all of the values in the include
//The last value is the size of this vector. It was declared inside the Player struct
enum World { WORLD_KITCHEN, WORLD_OVEN, WORLD_COUNT };


//Map game scenes
enum MatchScreen{

    KITCHEN,
    FRIDGE,
    OVEN,
    BOARD,
    PREPARE,
    PAUSED,
    DEFEAT,
    VICTORY,
    STATE_QUANTITY

};

#endif