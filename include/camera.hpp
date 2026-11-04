#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "match.hpp"

void setCamera(Match&); //Called in graphics.cpp

// void cameraProcess(Match&); //Called in match.cpp

void cameraProcess(Camera2D& camera, Player& player, Sprite background); //Called in match.cpp

#endif