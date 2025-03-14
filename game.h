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
using namespace std;
class Game{
public:
    SDL_Window* window;
    bool running;
    SDL_Renderer* renderer;
    vector<Wall> walls;
    PlayerTank player;
    Game();
    void handleEvent();
    void render();
    void generateWall();
    void run();
    ~Game();
};

#endif // GAME_H_INCLUDED
