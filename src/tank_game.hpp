#pragma once
#include "../library/game.hpp"

class TankGame extends Game{
public:
  TankGame(): Game("Tankerring", 720, 480){
    layers.set("background", this);
    layers.set("mainMenu", this);
  }
};