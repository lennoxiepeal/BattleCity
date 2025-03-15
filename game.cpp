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
    player=PlayerTank(((MAP_WIDTH-1)/2)*TITLE_SIZE,(MAP_HEIGHT-2)*TITLE_SIZE);
    spawnEnemyTank();
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
                case SDLK_UP:player.move(0,-10,walls,enemies);break;
                case SDLK_DOWN:player.move(0,10,walls,enemies);break;
                case SDLK_LEFT:player.move(-10,0,walls,enemies);break;
                case SDLK_RIGHT:player.move(10,0,walls,enemies);break;
                case SDLK_SPACE:player.shoot();break;
            }
        }
    }

}
void Game::run() {
    std::cerr << "Starting game loop..." << std::endl;
    while (running) {
        handleEvent();
        render();
        update();
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
    for(auto &enemy:enemies){
        enemy.render(renderer);
    }
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

void Game::spawnEnemyTank(){
    enemies.clear();
    for(int i=0;i<enemynumber;i++){
        int ex,ey;
        bool validPos=false;
        while(!validPos){
            ex=(rand()%(MAP_WIDTH-2)+1)*TITLE_SIZE;
            ey=(rand()%(MAP_HEIGHT-2)+1)*TITLE_SIZE;
            validPos=true;
            for(const auto &Wall:walls){
                if(Wall.active&&Wall.x==ex&&Wall.y==ey){
                    validPos=false;
                    break;
                }
            }
        }
        enemies.push_back(EnemyTank(ex,ey));
    }
}

void Game::update(){
    player.updateBullets(walls);
    for(auto &enemy:enemies){
        enemy.move(walls,enemies,player);
        enemy.updateBullets(walls,enemies,player);
        if(rand()%100<2){
            enemy.shoot();
        }
    }
    for(auto &enemy:enemies){
        for(auto &Bullet:enemy.bullets){
            for(auto &Wall:walls){
            if(Wall.active&&Wall.type==BRICK&&SDL_HasIntersection(&Bullet.rect,&Wall.rect)){
                Wall.active=false;
                Bullet.active=false;
                break;
            }
            else if(Wall.active&&Wall.type==STEEL&&SDL_HasIntersection(&Bullet.rect,&Wall.rect)){
                Bullet.active=false;
                break;
            }
            else if(Wall.active&&Wall.type==BUSH&&SDL_HasIntersection(&Bullet.rect,&Wall.rect)){
                Bullet.inBush=true;
                break;
            }
            }
        }
    }

    for(auto &Bullets:player.bullets){
        for(auto &Wall:walls){
            if(Wall.active&&Wall.type==BRICK&&SDL_HasIntersection(&Bullets.rect,&Wall.rect)){
                Wall.active=false;
                Bullets.active=false;
                break;
            }
            else if(Wall.active&&Wall.type==STEEL&&SDL_HasIntersection(&Bullets.rect,&Wall.rect)){
                Bullets.active=false;
                break;
            }
            else if(Wall.active&&Wall.type==BUSH&&SDL_HasIntersection(&Bullets.rect,&Wall.rect)){
                Bullets.inBush=true;
                break;
            }
        }
    }
    for(auto &Bullet:player.bullets){
        for(auto &enemy:enemies){
            if(enemy.active&&SDL_HasIntersection(&Bullet.rect,&enemy.rect)){
                enemy.active=false;
                Bullet.active=false;
            }
        }
    }
    enemies.erase(remove_if(enemies.begin(),enemies.end(),
                            [](EnemyTank &e){return !e.active;}),enemies.end());
    for(auto &enemy:enemies){
        for(auto &Bullet1:player.bullets){
            for(auto &Bullet2:enemy.bullets){
                if(Bullet1.active&&Bullet2.active&&SDL_HasIntersection(&Bullet1.rect,&Bullet2.rect)){
                    Bullet1.active=false;
                    Bullet2.active=false;
                }
            }
        }
    }
    for(auto &enemy:enemies){
        for(auto &Bullet:enemy.bullets){
            if(SDL_HasIntersection(&Bullet.rect,&player.rect)){
                running=false;
                return;
            }
        }
    }
}
Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
