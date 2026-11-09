#ifndef WORLD_HPP
#define WORLD_HPP

#include "match_enums.hpp"

//Declaracao antecipada, ainda nao entendi muito bem como ela funciona
struct Match;

float worldWidthOf(const Match &match);

// static bool sameWorld(MatchScreen a, MatchScreen b);

World worldOf(MatchScreen s);

struct Limits { float min, max; };

Limits playerLimitsOf(const Match &match);

#endif