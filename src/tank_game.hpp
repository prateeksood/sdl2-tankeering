#pragma once
#include "../library/game.hpp"
#include "../library/polygon_2d.hpp"
#include "../library/color.hpp"
#include "../library/text.hpp"

class TankGame extends Game{
public:
  float rotation = 0;
  TankGame(): Game("Tankerring", 720, 480){
    layers.set("background", this, SDL_Color {255, 0, 0, 100});
    layers.set("mainMenu", this, SDL_Color {0, 0, 255, 100});
    Text *text = new Text(this, 100, 100, 18);
    Text *text2 = new Text(this, 100, 200, 18);
    layers["mainMenu"].objects.push_back(text);
    layers["mainMenu"].objects.push_back(text2);
    text->updateText("Hello World");
    text2->updateText("Hello World 2");
  }
};