#include "../game.hpp"
#include "../text.hpp"

Text::Text(Game *game, int x, int y, Uint8 fontSize, int fontStyle):
  GameObject(game),
  destination{x, y, 0, 0},
  fontStyle(fontStyle){
    font = TTF_OpenFont("assets/fonts/lazy.ttf", fontSize);
    if(font == nullptr){
      LOG("Unable to load font! SDL_ttf Error: " << TTF_GetError());
      return;
    }
    TTF_SetFontStyle(font, fontStyle);
  }

const SDL_Rect &Text::getDestination(){
  return destination;
}

void Text::setPosition(int x, int y){
  destination.x = x;
  destination.y = y;
}

bool Text::updateText(const char* text){
  if(textTexture)
    SDL_DestroyTexture(textTexture);

  SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
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
  if(textTexture)
    SDL_RenderCopy(game->renderer, textTexture, nullptr, &destination);
}