#include "../game.hpp"
#include "../ui_menu.hpp"

UIMenuItem::UIMenuItem(Game *game, SDL_Rect boundingBox, const char *content, InteractiveComponent::Listener onclick):
  InteractiveComponent(game, boundingBox),
  text(game, 0, 0, 24, TTF_STYLE_BOLD){
    text.updateText(content);
    addEventListener("click", onclick);
  }

void UIMenuItem::setPosition(int x, int y){
  boundingBox.x = x;
  boundingBox.y = y;
  const SDL_Rect &destination = text.getDestination();
  int margin_x = (boundingBox.w - destination.w) / 2;
  int margin_y = (boundingBox.h - destination.h) / 2;
  text.setPosition(margin_x + boundingBox.x, margin_y + boundingBox.y); // so that the text is aligned in the middle of MenuItem
}

void UIMenuItem::setBGColor(SDL_Color color){
  bgColor = color;
}

void UIMenuItem::update(){
  if(SDL_PointInRect(&game->getCursor(), &boundingBox)){
    setBGColor(Color::WHITE());
  }else{
    setBGColor(Color::TRANSPARENT());
  }
  handleEvents();
}

void UIMenuItem::render(){
  SDL_SetRenderDrawColor(game->renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
  SDL_RenderFillRect(game->renderer, &boundingBox);
  SDL_SetRenderDrawColor(game->renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderDrawRect(game->renderer, &boundingBox);
  text.render();
}


UIMenu::UIMenu(Game *game, SDL_Rect boundingBox):
  Component(game, boundingBox){
    this->boundingBox.h = marginV;
    this->boundingBox.x = (game->getWindowRect().w - boundingBox.w) / 2;
    this->boundingBox.y = (game->getWindowRect().h - boundingBox.h) / 2;
  }

void UIMenu::setPosition(int x, int y){
  boundingBox.x = x;
  boundingBox.y = y;
}

void UIMenu::addItem(SDL_Rect itemBox, const char *content, InteractiveComponent::Listener onclick){
  items.emplace_back(game, itemBox, content, onclick);
  int margin_x = (boundingBox.w - itemBox.w) / 2;
  boundingBox.y -= (itemBox.h + marginV) / 2;
  // so that the MenuItem 'item' is aligned in the center of Menu
  for(int i = 0; i < items.size(); i++){
    items[i].setPosition(margin_x + boundingBox.x, marginV * (i + 1) + itemBox.h * i + boundingBox.y);
  }
  boundingBox.h += itemBox.h + marginV;
}

void UIMenu::update(){
  for(UIMenuItem &item: items){
    item.update();
  }
}

void UIMenu::render(){
  SDL_SetRenderDrawColor(game->renderer, 0, 255, 255, 255);
  SDL_RenderDrawRect(game->renderer, &boundingBox);
  for(UIMenuItem &item: items)
    item.render();
}