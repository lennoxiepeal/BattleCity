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
void PlayerTank::move(int dx,int dy,const vector<Wall>&walls,const vector<EnemyTank>enemies){
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
    for(const auto &enemy:enemies){
        if(enemy.active&&SDL_HasIntersection(&enemy.rect,&rect)){
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
EnemyTank::EnemyTank(int startX,int startY){
    x=startX;
    y=startY;
    rect={x,y,TITLE_SIZE,TITLE_SIZE};
    dirX=0;
    dirY=1;
    shootDelay=5;
    moveDelay=0;
    randomMoveTimer=0;
    active=true;
}
void EnemyTank::move(const vector<Wall>&walls,const vector<EnemyTank>enemies,const PlayerTank &player){
    if(--moveDelay>0) return;
    moveDelay=10;
    if(randomMoveTimer>0){
        randomMoveTimer--;
    }
    else{
        randomDirection(SCREEN_HEIGHT);
        randomMoveTimer=10;
    }
    int newX=x+this->dirX;
    int newY=y+this->dirY;
    SDL_Rect newRect={newX,newY,TITLE_SIZE,TITLE_SIZE};
    for(int i=0;i<walls.size();i++){
        if(walls[i].active&&walls[i].type!=BUSH&&SDL_HasIntersection(&newRect,&walls[i].rect)){
            return;
        }
    }
    for(auto &enemy:enemies){
        if(SDL_HasIntersection(&enemy.rect,&player.rect)){
            return;
        }
    }
    if(newX>=TITLE_SIZE&&newX<=SCREEN_WIDTH-TITLE_SIZE*2&&
       newY>=TITLE_SIZE&&newY<=SCREEN_HEIGHT-TITLE_SIZE*2){
        x=newX;
        y=newY;
        rect.x=x;
        rect.y=y;
    }
}
void EnemyTank::randomDirection(int screenheight){
    int ranDir= rand()%100;
    if(y<screenheight/2){
        if(ranDir<50){dirX=0;dirY=10;}
        else if(ranDir<70){dirX=-10;dirY=0;}
        else if(ranDir<90) {dirX=10;dirY=0;}
        else {dirX=0;dirY=-10;}
    }
    else{
        switch(rand()%4){
            case 0:dirX=10;dirY=0;break;
            case 1:dirX=-10;dirY=0;break;
            case 2:dirX=0;dirY=10;break;
            case 3:dirX=0;dirY=-10;break;
        }
    }
}

void EnemyTank::shoot(){
    if(--shootDelay>0) return;
    shootDelay=5;
    bullets.push_back(Bullets(x+TITLE_SIZE/2-5,y+TITLE_SIZE/2-5,
                              this->dirX,this->dirY));
}

void EnemyTank::updateBullets(const vector<Wall>&walls,const vector<EnemyTank>enemies,const PlayerTank &player){
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

void EnemyTank::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&rect);
    for(auto &Bullets:bullets){
        Bullets.render(renderer);
    }
}
