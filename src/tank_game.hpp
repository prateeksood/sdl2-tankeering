#pragma once
#include "../library/game.hpp"

#define extends :public

class TankGame extends Game{
public:
  TankGame(): Game("Tankerring", 720, 480){}
};