#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "match.hpp"

void setKitchenCamera(Match&); //Called in graphics.cpp

// void cameraProcess(Match&); //Called in match.cpp

void cameraProcess(Camera2D& camera, const Player& player, float worldWidth); //Called in match.cpp

bool sceneChanged(const MatchScreen& match, const MatchScreen& prevMatch);

void correctCamera(Match& match);

// Limits playerLimitsOf(const Match &match);

#endif