#pragma once
#include <SDL2/SDL.h>

class Game;

class Layer{
private:
  SDL_Color color;
  Game *game;
  bool visible = true;
public:
  Layer(Game *, SDL_Color = {0, 0, 0, 1});
  Layer(Layer &&);
  ~Layer();
  void setVisibility(bool);
  void setColor(SDL_Color);
  void update();
  void render();
};