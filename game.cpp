#include "game.h"
#include <iostream>

Game::Game() {
    std::cerr << "Initializing SDL..." << std::endl;
    running = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    std::cerr << "Creating window..." << std::endl;
    window = SDL_CreateWindow("Battle City",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    std::cerr << "Creating renderer..." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
    generateWall();
    player=PlayerTank(((MAP_WIDTH-1)/2)*TITLE_SIZE,2*TITLE_SIZE);
    std::cerr << "Initialization complete!" << std::endl;
}
void Game::handleEvent(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            running=false;
        }
        else if(event.type==SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_UP:player.move(0,-10,walls);break;
                case SDLK_DOWN:player.move(0,10,walls);break;
                case SDLK_LEFT:player.move(-10,0,walls);break;
                case SDLK_RIGHT:player.move(10,0,walls);break;
            }
        }
    }

}
void Game::run() {
    std::cerr << "Starting game loop..." << std::endl;
    while (running) {
        handleEvent();
        render();
        SDL_Delay(16);
    }
    std::cerr << "Game loop exited!" << std::endl;
}

void Game::render() {

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            SDL_Rect tile = { j * TITLE_SIZE, i * TITLE_SIZE, TITLE_SIZE, TITLE_SIZE };
            SDL_RenderFillRect(renderer, &tile);
        }
    }
    for(int i=0;i<walls.size();i++){
        walls[i].render(renderer);
    }
    player.render(renderer);
    SDL_RenderPresent(renderer);
}
void Game::generateWall(){
    ifstream file("map1.txt");
    if(!file){
        cerr << "Cannot open txt map" << endl;
        return;
    }

    string line;
    int row = 0;

    while(getline(file, line)){
        for(int col = 0; col < line.size(); col++){
            char tile = line[col];
            if(tile == '1'){
                walls.push_back(Wall(col * TITLE_SIZE, row * TITLE_SIZE, BRICK));
            }
            else if(tile == '2'){
                walls.push_back(Wall(col * TITLE_SIZE, row * TITLE_SIZE, STEEL));
            }
            else if(tile == '3'){
                walls.push_back(Wall(col * TITLE_SIZE, row * TITLE_SIZE, BUSH));
            }
        }
        row++;
    }

    file.close();
    cerr << "Map loaded successfully, total walls: " << walls.size() << endl;
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
