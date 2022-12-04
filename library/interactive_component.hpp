#pragma once
#include "component.hpp"
#include <vector>
#include "map_wrapper.hpp"
#include <SDL2/SDL.h>

class InteractiveComponent extends Component{
public:
  typedef void (*Listener)(InteractiveComponent *);
  MapWrapper<std::string, std::vector<Listener>> eventListeners;
  InteractiveComponent(Game *, SDL_Rect boundingBox);
  bool addEventListener(std::string eventName, Listener);
  void handleEvents();
};