#pragma once
#include <SDL2/SDL.h>
#include "game_object.hpp"

class Game;

class Layer extends GameObject{
private:
  SDL_Color color;
  bool visible = true;
public:
  Layer(Game *, SDL_Color = {0, 0, 0, 0});
  Layer(Layer &&);
  ~Layer();
  void setVisibility(bool);
  void setColor(SDL_Color);
  void update();
  void render();
};