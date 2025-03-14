#include "tank.h"
PlayerTank::PlayerTank(int startX,int startY){
    x=startX;
    y=startY;
    rect={x,y,TITLE_SIZE,TITLE_SIZE};
    dirX=0;
    dirY=-1;
}
void PlayerTank::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderFillRect(renderer,&rect);
}
void PlayerTank::move(int dx,int dy,const vector<Wall>&walls){
    int newX=x+dx;
    int newY=y+dy;
    this->dirX=dx;
    this->dirY=dy;
    SDL_Rect newRect={newX,newY,TITLE_SIZE,TITLE_SIZE};
    for(int i=0;i<walls.size();i++){
        if(walls[i].active&&SDL_HasIntersection(&newRect,&walls[i].rect)){
            return;
        }
    }
    if(newX>=TITLE_SIZE&&newX<=SCREEN_WIDTH-TITLE_SIZE*2
       &&newY>=TITLE_SIZE&&newY<=SCREEN_HEIGHT-TITLE_SIZE*2){
        x=newX;
        y=newY;
        rect.x=x;
        rect.y=y;
       }
}
