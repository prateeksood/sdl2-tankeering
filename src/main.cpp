#include "tank_game.hpp"
#include <iostream>

int main(int argc, char *args[]){

  TankGame game;
  game.layers["background"].setVisibility(false);
  LOG(game.layers.size());
  game.run();

  return 0;
}