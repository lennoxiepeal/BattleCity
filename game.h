#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <vector>
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <string>
#include "constants.h"
#include "wall.h"
#include "tank.h"
#include "bullets.h"
using namespace std;
class Game{
public:
    SDL_Window* window;
    bool running;
    SDL_Renderer* renderer;
    SDL_Texture* spritesheet;
    SDL_Texture* loadTexture(const string &path);
    vector<Wall> walls;
    vector<EnemyTank> enemies;
    PlayerTank player;
    PlayerTank player2;
    int enemynumber=3;
    Game();
    void handleEvent();
    void render();
    void generateWall();
    void spawnEnemyTank();
    void run();
    void update();
    ~Game();
};

#endif // GAME_H_INCLUDED
