#include "../game.hpp"
#include "../ui_menu.hpp"

UIMenuItem::UIMenuItem(Game *game, SDL_Rect box, const char *content):
  GameObject(game),
  box(box),
  text(game, 0, 0, 24, TTF_STYLE_BOLD){
    text.updateText(content);
  }

const SDL_Rect &UIMenuItem::getBox() const {
  return box;
}
void UIMenuItem::setPosition(int x, int y){
  box.x = x;
  box.y = y;
  const SDL_Rect &destination = text.getDestination();
  int margin_x = (box.w - destination.w) / 2;
  int margin_y = (box.h - destination.h) / 2;
  text.setPosition(margin_x + box.x, margin_y + box.y); // so that the text is aligned in the middle of MenuItem
}

void UIMenuItem::setBGColor(SDL_Color color){
  bgColor = color;
}

void UIMenuItem::update(){}
void UIMenuItem::render(){
  SDL_SetRenderDrawColor(game->renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
  SDL_RenderFillRect(game->renderer, &box);
  SDL_SetRenderDrawColor(game->renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderDrawRect(game->renderer, &box);
  text.render();
}


UIMenu::UIMenu(Game *game, SDL_Rect box):
  GameObject(game), box(box){
    this->box.h = marginV;
    this->box.x = (game->getWindowRect().w - box.w) / 2;
    this->box.y = (game->getWindowRect().h - box.h) / 2;
  }

const SDL_Rect &UIMenu::getBox() const {
  return box;
}
void UIMenu::setPosition(int x, int y){
  box.x = x;
  box.y = y;
}

void UIMenu::addItem(SDL_Rect itemBox, const char *content){
  items.emplace_back(game, itemBox, content);
  int margin_x = (box.w - itemBox.w) / 2;
  box.y -= (itemBox.h + marginV) / 2;
  // so that the MenuItem 'item' is aligned in the center of Menu
  for(int i = 0; i < items.size(); i++){
    items[i].setPosition(margin_x + box.x, marginV * (i + 1) + itemBox.h * i + box.y);
  }
  box.h += itemBox.h + marginV;
}

void UIMenu::update(){
  for(UIMenuItem &item: items){
    if(SDL_PointInRect(&game->getCursor(), &item.getBox())){
      item.setBGColor(Color::WHITE());
      // if(game->mouseEvent.leftUp && game->layers.has("mainMenu"))
      //   game->layers["mainMenu"].setVisibility(false);
    }else
      item.setBGColor(Color::TRANSPARENT());
  }
}

void UIMenu::render(){
  SDL_SetRenderDrawColor(game->renderer, 0, 255, 255, 255);
  SDL_RenderDrawRect(game->renderer, &box);
  for(UIMenuItem &item: items)
    item.render();
}