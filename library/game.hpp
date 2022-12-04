#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "library/map_wrapper.hpp"
#include "library/layer.hpp"

template <class C>
class GameEvent{
  static std::vector<GameEvent *> events;
  C *object;
  void (*listener)(C *);
public:
  GameEvent(C *object, void (*listener)(C *)): object(object), listener(listener){
    events.push_back(this);
  }
  void handleEvents(){
    for(GameEvent *event of events)
      event->listener(object);
  }
};

class Game{
private:
  SDL_Rect windowRect;
  bool isRunning = false;

  SDL_Window *window;
  SDL_Point cursor;
  SDL_Event event;

public:
  struct mouseEvent{
    bool leftDown = false;
    bool leftUp = false;
  } mouseEvent;
  MapWrapper<std::string, Layer> layers;
  SDL_Renderer *renderer;
  int frameTime = 0;
  Game(const char *title, int width, int height, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
  ~Game();
  void run();
  virtual void update();
  virtual void render();
  void eventHandler();
  void clean();
  bool running();
  const SDL_Rect &getWindowRect();
  const SDL_Point &getCursor();
  const SDL_Event &getEvent();
};