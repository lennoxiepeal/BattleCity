#include "tank.h"
PlayerTank::PlayerTank(int startX,int startY){
    x=startX;
    y=startY;
    rect={x,y,TITLE_SIZE,TITLE_SIZE};
    dirX=0;
    dirY=-1;
}
void PlayerTank::render(SDL_Renderer* renderer){
    if(inBush){
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
    }
    else{
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    }
    SDL_RenderFillRect(renderer,&rect);
    for(auto &Bullets:bullets){
        Bullets.render(renderer);
    }
}
void PlayerTank::move(int dx,int dy,const vector<Wall>&walls){
    int newX=x+dx;
    int newY=y+dy;
    this->dirX=dx;
    this->dirY=dy;
    SDL_Rect newRect={newX,newY,TITLE_SIZE,TITLE_SIZE};
    for(int i=0;i<walls.size();i++){
        if(walls[i].active&&walls[i].type!=BUSH&&SDL_HasIntersection(&newRect,&walls[i].rect)){
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
    inBush=false;
    for(auto &Wall:walls){
        if(Wall.active&&Wall.type==BUSH&&SDL_HasIntersection(&newRect,&Wall.rect)){
            inBush=true;
            break;
        }
    }
}
void PlayerTank::shoot(){
    bullets.push_back(Bullets(x+TITLE_SIZE/2-5,y+TITLE_SIZE/2-5,
                              this->dirX,this->dirY));
}
void PlayerTank::updateBullets(const vector<Wall> &walls){
    for(auto &Bullets:bullets){
        Bullets.move();
        Bullets.inBush=false;
        for(auto &Wall:walls){
            if(Wall.active&&Wall.type==BUSH&&SDL_HasIntersection(&Bullets.rect,&Wall.rect)){
                Bullets.inBush=true;
                break;
            }
        }
    }
    bullets.erase(remove_if(bullets.begin(),bullets.end(),[](Bullets &b){return !b.active;}),bullets.end());
}
