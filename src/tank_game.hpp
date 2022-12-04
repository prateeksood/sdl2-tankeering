#pragma once
#include "../library/game.hpp"
#include "../library/polygon_2d.hpp"
#include "../library/color.hpp"
#include "../library/ui_menu.hpp"

class TankGame extends Game{
public:
  float rotation = 0;
  TankGame(): Game("Tankerring", 720, 480){
    layers.set("background", this, SDL_Color {0xf3, 0xef, 0xe0, 155});
    layers.set("mainMenu", this, SDL_Color {0xf2, 0xe5, 0xe5, 255});

    UIMenu *mainMenu = new UIMenu(this, {0, 0, 360, 0});
    mainMenu->addItem({0, 0, 300, 50}, "New Game", [](InteractiveComponent *item){
      // item->setBGColor(Color::RED());
      item->game->layers["mainMenu"].setVisibility(false);
      // item->onclick = nullptr;
    });
    mainMenu->addItem({0, 0, 300, 50}, "Load Game");
    mainMenu->addItem({0, 0, 300, 50}, "Quit");

    layers["mainMenu"].objects.push_back(mainMenu);
  }
};