#include "tank_game.hpp"
#include <iostream>

int main(int argc, char *args[]){

  TankGame game;
  game.layers["mainMenu"].setVisibility(false);
  log_as(game.layers.size());
  game.run();

  return 0;
}