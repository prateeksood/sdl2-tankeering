#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.hpp"
#include "color.hpp"
#include "interactive_component.hpp"

class UIMenuItem extends InteractiveComponent{
  // using GameObject::GameObject;
private:
  SDL_Color bgColor = Color::TRANSPARENT();
  SDL_Color borderColor = Color::WHITE();
public:
  Text text;
  UIMenuItem(Game *, SDL_Rect, const char*, InteractiveComponent::Listener);
  void setPosition(int, int);
  void setBGColor(SDL_Color);
  void update();
  void render();
};

class UIMenu extends Component{
private:
  std::vector<UIMenuItem> items;
  int marginV = 25;
public:
  UIMenu(Game *, SDL_Rect);
  void setPosition(int x, int y);
  void addItem(SDL_Rect, const char *, InteractiveComponent::Listener = nullptr);
  void update();
  void render();
};