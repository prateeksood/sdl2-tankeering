#pragma once
#include "util.hpp"
#include "game_object.hpp"

class Component extends GameObject{
protected:
  SDL_Rect boundingBox;
public:
  Component(Game *, SDL_Rect);
  const SDL_Rect &getBoundingBox() const;
};