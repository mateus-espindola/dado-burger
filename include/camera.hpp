#pragma once

#include "match.hpp"

void setKitchenCamera(Match&); //Called in graphics.cpp

void cameraProcess(Camera2D& camera, const Player& player, float worldWidth); //Called in match.cpp

bool sceneChanged(const MatchScreen& match, const MatchScreen& prevMatch);

void correctCamera(Match& match);