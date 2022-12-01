#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../game.hpp"

Game::Game(const char *title, int width, int height, int x, int y):
  windowRect{0, 0, width, height}{
    std::cout << "[width: " << windowRect.w;
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
    isRunning = false;
    return;
  }

  std::cout << "[Game]: SDL initialised" << std::endl;
  window = SDL_CreateWindow(title, x, y, windowRect.w, windowRect.h, SDL_WINDOW_SHOWN);
  if(window == nullptr){
    isRunning = false;
    return;
  }

  std::cout << "[Game]: Window created!" << std::endl;
  renderer = SDL_CreateRenderer(window, -1, 0);
  if(renderer == nullptr){
    isRunning = false;
    return;
  }

  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ){
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    isRunning = false;
    return;
  }

  if(TTF_Init() == -1){
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    isRunning = false;
    return;
  }

  std::cout << "[Game]: Renderer created!" << std::endl;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  isRunning = true;
}

Game::~Game(){
  clean();
}


void Game::run(){
    const int FPS = 60;
    const int frameDelay = 1000 / 60; // 1s / 60fps = 16ms
    uint32_t frameStart;              // time (in ms) on start of every frame

    while(isRunning){
      // std::cout << "FPS: " << (int) (game->frameTime) << std::endl;
      frameStart = SDL_GetTicks(); // eg. 1000
      eventHandler();
      update();
      render();

      frameTime = SDL_GetTicks() - frameStart; // time taken by a frame. eg. 1010 - 1000 = 10
      if (frameDelay > frameTime)              // eg. 16 > 10
          SDL_Delay(frameDelay - frameTime);   // eg. Delay(6)
      // else no delay
  }
}

void Game::update(){
  // layers.forEach([](Layer &layer, const char *key){
    // (*layer)->update();
  // });
}

void Game::render(){
  SDL_RenderClear(renderer);

  layers.forEach([](Layer &layer, const char *key){
    layer.render();
  });

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderPresent(renderer);
}

void Game::eventHandler(){
  SDL_Event e;
  SDL_PollEvent( &e );
  switch (e.type){
    case SDL_QUIT:
      isRunning = false;
      break;

    case SDL_KEYDOWN:
      switch (e.key.keysym.sym){
        case SDLK_ESCAPE:
          isRunning = false;
          break;
        case SDLK_LEFT:
          break;
        case SDLK_RIGHT:
          break;
        case SDLK_SPACE:
          break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      break;
  }
  SDL_PumpEvents();
  SDL_GetMouseState(&cursor.x, &cursor.y);
}

void Game::clean(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::running(){
  return isRunning;
}

const SDL_Rect &Game::getWindowRect(){
  return windowRect;
}