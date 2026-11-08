#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "game.hpp"

// void gameDraw(Game& game);
// void menuDraw();
// void tutorialDraw();
// void historyDraw();
// void settingsDraw();
// void matchDraw(Match& match);

Vector2 getSpritePos(Object& object);


//MOVIDOS PARA SPRITES.HPP
// void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint);
// void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint);

void hitboxDraw(const Object&);

//COLOCAR CONST DEPOIS
void playerDraw(Player&);

// void drawNearestBut(const Player &player, Button **buttons);
int drawNearestBut(const Player& player, const ButtonVec& screen);

void drawButtons(const ButtonVec& screen);

void drawKitchen(Match& match, int butUnderMouseInd);

void drawButGlow(Rectangle r, Color cor, int camadas, float alpha);

void drawPrepare(Match match, int butUnderMouseInd);

#endif
