#include "../game.hpp"
#include "../component.hpp"

Component::Component(Game *game, SDL_Rect boundingBox): GameObject(game), boundingBox(boundingBox){}

const SDL_Rect &Component::getBoundingBox() const {
  return boundingBox;
}