#include "../layer.hpp"
#include "../library/game.hpp"
#include <iostream>

Layer::Layer(Game *game, SDL_Color color): game(game), color(color){
  std::cout << "[Layer]: created" << std::endl;
}
Layer::Layer(Layer &&layer){
  this->game = layer.game;
  this->color = layer.color;
  std::cout << "[Layer]: copied" << std::endl;
}
Layer::~Layer(){
  std::cout << "[Layer]: destroyed" << std::endl;
}

void Layer::setVisibility(bool show){
  visible = show;
}

void Layer::setColor(SDL_Color color){
  this->color = color;
}

void Layer::update(){
}

void Layer::render(){
  // std::cout << std::to_string(color.r) << std::endl;
  if(!visible)
    return;
  SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(game->renderer, &game->getWindowRect());
}