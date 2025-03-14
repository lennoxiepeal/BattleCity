#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <vector>
#include "wall.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const int SCREEN_HEIGHT=600;
const int SCREEN_WIDTH=800;
const int TITLE_SIZE=40;
const int MAP_WIDTH=SCREEN_WIDTH/TITLE_SIZE;
const int MAP_HEIGHT=SCREEN_HEIGHT/TITLE_SIZE;
class Game{
public:
    SDL_Window* window;
    bool running;
    SDL_Renderer* renderer;
    vector<Wall> walls;
    Game();
    void render();
    void generateWall();
    void run();
    ~Game();
};

#endif // GAME_H_INCLUDED
