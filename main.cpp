#include <sdl.h>
#include <iostream>
#include "game.h"
#include <SDL_image.h>
using namespace std;

int main(int argc, char* argv[]) {
    Game game;
    //vòng lặp game
    if (game.running) {
        game.run();
    }
    return 0;
}
