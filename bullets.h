#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED
#include "constants.h"


class Bullets{
public:
    int x,y;
    int dx,dy;
    int dirX,dirY;
    Direction direction; //Huong
    bool active;
    bool inBush; //Kiem tra trong bui
    SDL_Rect rect;
    Bullets():x(0),y(0),direction(UP){};
    Bullets(int startX,int startY,Direction directionX);
    void move();
    void render(SDL_Renderer* renderer);
};
class Lazer{
public:
    int x,y;
    SDL_Rect rect;
    bool active;
    bool canCollide=false; //Kiem tra dieu kien va cham
    int currentFrame;
    int frameCount;
    int animationSpeed;
    SDL_Texture* lazerFrames[4]; //Lazer co 4 frames
    Lazer() : x(0), y(0), active(false) {}
    Lazer(int startX,int startY);
    ~Lazer(); //ham huy
    void activate(int _x,int _y) { //ham khoi dong lazer
        x=_x;
        y=_y;
        active = true;
    }
    void deactivate() { //ham tat lazer
        active = false;
    }
    void update();
    void render(SDL_Renderer* renderer);
    void loadFrames(SDL_Renderer* renderer);
};
#endif // BULLETS_H_INCLUDED
