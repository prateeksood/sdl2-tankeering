#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.hpp"
#include "color.hpp"

class UIMenuItem extends GameObject{
  // using GameObject::GameObject;
private:
  SDL_Rect box;
  SDL_Color bgColor = Color::TRANSPARENT();
  SDL_Color borderColor = Color::WHITE();
public:
  Text text;
  UIMenuItem(Game *, SDL_Rect, const char*);
  const SDL_Rect &getBox() const;
  void setPosition(int, int);
  void setBGColor(SDL_Color);
  void update();
  void render();
};

class UIMenu extends GameObject{
private:
  SDL_Rect box;
  std::vector<UIMenuItem> items;
  int marginV = 25;
public:
  UIMenu(Game *, SDL_Rect);
  const SDL_Rect &getBox() const;
  void setPosition(int x, int y);
  void addItem(SDL_Rect, const char *);
  void update();
  void render();
};