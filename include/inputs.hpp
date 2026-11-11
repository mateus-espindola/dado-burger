#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "raylib.h"
#include "match.hpp"

Vector2 findMousePos(void);

bool mouseKeyLeftClicked(void);

bool keyUpClicked(void);

bool keyDownClicked(void);

int changeInvSlot(void);

void processButClick(Match& match, const Button& button);

#endif