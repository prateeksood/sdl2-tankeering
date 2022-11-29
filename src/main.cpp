#include "tank_game.hpp"
#include <iostream>

int main(int argc, char *args[]){

  TankGame game;
  game.layers.set("background", &game, SDL_Color {255, 0, 0, 105});
  game.layers.set("mainMenu", &game, SDL_Color {0, 255, 0, 100});
  game.run();

  return 0;
}