#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_object.hpp"
#include "color.hpp"

class Text extends GameObject{
  SDL_Rect destination;
  TTF_Font *font = nullptr;
  int fontStyle;
  SDL_Texture *textTexture = nullptr;
public:
  SDL_Color color = Color::BLACK();
  Text(Game *game, int x, int y, Uint8 fontSize, int fontStyle = TTF_STYLE_NORMAL);
  const SDL_Rect &getDestination();
  void setPosition(int x, int y);
  bool updateText(const char* text);
  void update();
  void render();
};