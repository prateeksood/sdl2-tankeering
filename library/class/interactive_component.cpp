#include "../game.hpp"
#include "../interactive_component.hpp"

InteractiveComponent::InteractiveComponent(Game *game, SDL_Rect boundingBox):
  Component(game, boundingBox){
    eventListeners.set("click");
}

bool InteractiveComponent::addEventListener(std::string eventName, Listener listener){
  if(listener == nullptr || !eventListeners.has(eventName))
    return false;
  eventListeners[eventName].push_back(listener);
  return true;
}

void InteractiveComponent::handleEvents(){
  const SDL_Event &event = game->getEvent();
  switch(event.type){
    case SDL_MOUSEBUTTONUP:
      if(event.button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&game->getCursor(), &boundingBox)){
          auto &listeners = eventListeners["click"];
          for(auto &listener: listeners)
            listener(this);
        }
      }
    break;
  }
}