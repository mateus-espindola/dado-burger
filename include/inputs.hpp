#pragma once

#include "raylib.h"
#include "match.hpp"
#include "button_constants.hpp"

Vector2 findMousePos(void);

bool mouseKeyLeftClicked(void);

bool keyUpClicked(void);

bool keyDownClicked(void);

int changeInvSlot(void);

void processButClick(Match& match, Button& button);

bool isCuttable(IngredientType t);

bool canFlip(IngredientType t);

bool canCtrlAction(MatchScreen screen, IngredientType type);
