#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED
#include <vector>
#include "wall.h"
#include "constants.h"
#include "bullets.h"
using namespace std;
class Wall;
class EnemyTank;
class PlayerTank{
public:
    int x,y;
    int dirX,dirY;
    SDL_Rect rect;
    vector<Bullets> bullets;
    bool inBush=true;
    PlayerTank(): x(0),y(0),dirX(0),dirY(0){}
    PlayerTank(int startX,int startY);
    void move(int dx,int dy,const vector<Wall>&walls,const vector<EnemyTank>enemies);
    void render(SDL_Renderer* renderer);
    void shoot();
    void updateBullets(const vector<Wall>&walls);
};
class EnemyTank{
public:
    int x,y;
    int dirX,dirY;
    SDL_Rect rect;
    vector<Bullets> bullets;
    bool active;
    int moveDelay,shootDelay;
    int randomMoveTimer;
    EnemyTank(): x(0),y(0),dirX(0),dirY(0){}
    EnemyTank(int startX,int startY);
    void move(const vector<Wall>&walls,const vector<EnemyTank>enemies,const PlayerTank &player);
    void render(SDL_Renderer* renderer);
    void shoot();
    void updateBullets(const vector<Wall>&walls,const vector<EnemyTank>enemies,const PlayerTank &player);
    void randomDirection(int screenheight);
};

#endif // TANK_H_INCLUDED
