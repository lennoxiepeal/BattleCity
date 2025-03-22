#include "bullets.h"
Bullets::Bullets(int startX,int startY,int dirX,int dirY){
    x=startX;
    y=startY;
    dx=dirX;
    dy=dirY;
    active=true;
    inBush=false;
    rect={x,y,10,10};
}
void Bullets::move(){
    x+=dx;
    y+=dy;
    rect.x=x;
    rect.y=y;
    if(x<TITLE_SIZE||x>SCREEN_WIDTH-TITLE_SIZE||y>SCREEN_HEIGHT-TITLE_SIZE||y<TITLE_SIZE){
        active=false;
    }
}
void Bullets::render(SDL_Renderer* renderer){
    if(active&&!inBush){
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&rect);
    }
}
Lazer::Lazer(int startX, int startY) : currentFrame(0), frameCount(4), animationSpeed(10), active(false),canCollide(false) {
    x=startX;
    y=startY;
    rect.x = x;
    rect.y = y;
    rect.w = 60;
    rect.h = 400;
}

void Lazer::loadFrames(SDL_Renderer* renderer) {
    for (int i = 0; i < 4; i++) {
        std::string filename = "lazer/" + std::to_string(i) + ".png";
        lazerFrames[i] = IMG_LoadTexture(renderer, filename.c_str());
        if (!lazerFrames[i]) {
            std::cerr << "[ERROR] Failed to load " << filename << " - " << IMG_GetError() << std::endl;
        } else {
            std::cout << "[DEBUG] Loaded Lazer Frame " << i << " successfully!\n";
        }
    }
}

void Lazer::update() {
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter >= animationSpeed) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % frameCount;
        std::cout << "[DEBUG] Lazer Update - Frame: " << currentFrame
                  << " | Can Collide: " << canCollide << std::endl;

        if(currentFrame>=1){
            canCollide=true;
        }

        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }

    }
}


void Lazer::render(SDL_Renderer* renderer) {
    if (lazerFrames[currentFrame]) {
        SDL_RenderCopy(renderer, lazerFrames[currentFrame], nullptr, &rect);
    }
    else{
        std::cout<<"NO RENDERL"<<std::endl;
    }
    std::cout << "📏 Lazer position: x=" << rect.x << ", y=" << rect.y
          << ", w=" << rect.w << ", h=" << rect.h << "\n";

}


Lazer::~Lazer() {
    for (int i = 0; i < 4; i++) {
        if (lazerFrames[i]) {
            SDL_DestroyTexture(lazerFrames[i]);
        }
    }
}
