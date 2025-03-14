#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED
#include <vector>
#include "wall.h"
#include "constants.h"
using namespace std;
class PlayerTank{
public:
    int x,y;
    int dirX,dirY;
    SDL_Rect rect;
    PlayerTank(): x(0),y(0),dirX(0),dirY(0){}
    PlayerTank(int startX,int startY);
    void move(int dx,int dy,const vector<Wall>&walls);
    void render(SDL_Renderer* renderer);
};

#endif // TANK_H_INCLUDED
