#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "game.hpp"

void gameDraw(Game& game);
// void menuDraw();
// void tutorialDraw();
// void historyDraw();
// void settingsDraw();
void matchDraw(Match& match);

Vector2 getSpritePos(Object& object);

void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint);
void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint);
void hitboxDraw(Object& object);

void playerDraw(Player& player);


#endif
