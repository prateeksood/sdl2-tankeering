#include "../game.hpp"
#include "../text.hpp"

Text::Text(Game *game, int x, int y, Uint8 fontSize):
  destination{x, y, 0, 0},
  GameObject(game){
    font = TTF_OpenFont("assets/fonts/lazy.ttf", fontSize);
    if(font == nullptr)
      LOG("Unable to load font! SDL_ttf Error: " << TTF_GetError());
  }

bool Text::updateText(const char* text){
  if(textTexture)
    SDL_DestroyTexture(textTexture);

  SDL_Surface *surface = TTF_RenderText(font, text, color, Color::TRANSPARENT());
  if(surface == nullptr){
    LOG("Unable to load text " << text << "! SDL_ttf Error: " << TTF_GetError());
    return false;
  }

  textTexture = SDL_CreateTextureFromSurface(game->renderer, surface);
  if(textTexture == nullptr){
    LOG("Unable to load text " << text << "! SDL_ttf Error: " << SDL_GetError());
    return false;
  }

  destination.w = surface->w;
  destination.h = surface->h;
  SDL_FreeSurface(surface);
  return true;
}
void Text::update(){}
void Text::render(){
  LOG("r");
  if(textTexture)
    SDL_RenderCopy(game->renderer, textTexture, nullptr, &destination);
}