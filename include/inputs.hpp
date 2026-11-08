#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "raylib.h"
#include "match.hpp"

Vector2 findMousePos(void);

bool mouseKeyLeftClicked(void);

void processButClick(MatchScreen& matchScreen, const ButtonVec& screen, int clickInd);

#endif