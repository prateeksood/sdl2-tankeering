#pragma once
#include "../library/game.hpp"
#include "../library/polygon_2d.hpp"
#include "../library/color.hpp"
#include <vector>

template <unsigned int sides>
class GameRPolygon2D: public RegularPolygon2D<sides>{
  SDL_Color color;
  Game *game;
public:
  GameRPolygon2D(Game *game, int x, int y, unsigned int side, SDL_Color color = { 255, 255, 255, 255 }):
    RegularPolygon2D<sides>(x, y, side),
    game(game), color(color){}

  void setColor(SDL_Color color){
    this->color = color;
  }

  void render(){
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(game->renderer, this->position.x, this->position.y);
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
    for(int i = 0; i < sides; i++){
      auto *point = this->getEdge(i).point;
      SDL_RenderDrawLine(game->renderer, point[0].x, point[0].y, point[1].x, point[1].y);
    }
  }
};

class TankGame extends Game{
public:
  float rotation = 0;
  std::vector<GameRPolygon2D<3>> triangles;
  std::vector<GameRPolygon2D<4>> squares;
  TankGame(): Game("Tankerring", 720, 480){
    layers.set("background", this);
    layers.set("mainMenu", this);
    triangles.emplace_back(this, this->getWindowRect().w / 1.5f, this->getWindowRect().h / 2, 100);
    triangles.emplace_back(this, this->getWindowRect().w / 3.5f, this->getWindowRect().h / 2, 100);
    triangles.emplace_back(this, this->getWindowRect().w / 2, this->getWindowRect().h / 1.25f, 100);
    squares.emplace_back(this, this->getWindowRect().w / 2, this->getWindowRect().h / 2, 100);
    squares.emplace_back(this, this->getWindowRect().w / 2, this->getWindowRect().h / 4, 100);
    for(auto &triangle: triangles)
      triangle.setRadius(100);
  }
  void update(){
    if(rotation >= 2 * M_PI)
      rotation = 0;

    for(auto &triangle: triangles){
      triangle.setColor(Color::WHITE());
      triangle.setRotation(rotation += M_PI / 180 / 2);
    }

    for(auto &square: squares){
      square.setColor(Color::WHITE());
      square.setRotation(-rotation * 2);
    }

    for(int ti = 0; ti < triangles.size(); ti++){

      // collision with triangles
      for(int tj = ti + 1; tj < triangles.size(); tj++){
        if(triangles[ti].isColliding<3>(&triangles[tj])){
          triangles[ti].setColor(Color::RED());
          triangles[tj].setColor(Color::RED());
        }
      }

      // collision with sqaures
      for(int s = 0; s < squares.size(); s++){
        if(squares[s].isColliding<3>(&triangles[ti])){
          squares[s].setColor(Color::RED());
          triangles[ti].setColor(Color::RED());
        }
      }

    }

    for(int si = 0; si < squares.size() - 1; si++){
      for(int sj = 0; sj < squares.size(); sj++){
        if(squares[si].isColliding<4>(&squares[sj])){
          squares[si].setColor(Color::RED());
          squares[sj].setColor(Color::RED());
        }
      }
    }

  }
  void render(){
    SDL_RenderClear(renderer);
    for(auto &triangle: triangles)
      triangle.render();
    for(auto &square: squares)
      square.render();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
  }
};