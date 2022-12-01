#pragma once
#include "util.hpp"

class Game;

// Base class for all game things
class GameObject{
public:
  Game * game;
  GameObject(Game *);
  virtual void update() = 0;
  virtual void render() = 0;
};