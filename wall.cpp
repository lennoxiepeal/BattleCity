#include "wall.h"
#include "game.h"
Wall::Wall(int startX,int startY,WallType Thetype){
    x=startX;
    y=startY;
    type=Thetype;
    active=true;
    rect.x = x;
    rect.y = y;
    rect.w = TITLE_SIZE;
    rect.h = TITLE_SIZE;

}
void Wall::render(SDL_Renderer* renderer){
    if(!active) return;
    if (type == BRICK) {
        SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255);
    } else if (type == STEEL) {
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
    } else if (type == BUSH) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }

    SDL_RenderFillRect(renderer, &rect);
}
