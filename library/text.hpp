#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_object.hpp"
#include "color.hpp"

class Text extends GameObject{
  SDL_Rect destination;
  TTF_Font *font = nullptr;
  SDL_Texture *textTexture = nullptr;
public:
  SDL_Color color = Color::BLACK();
  Text(Game *game, int x, int y, Uint8 fontSize);
  bool updateText(const char* text);
  void update();
  void render();
};