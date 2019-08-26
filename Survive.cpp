#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Constants.h"
#include "Survivor.h"
#include "Map.h"
#include "Zombie.h"

int global_count = 0;

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

//Globals
SDL_Window* gWindow = NULL;
SDL_Surface* gScreen = NULL;
SDL_Renderer* gRenderer = NULL;
//Initialize Player
//Survivor survivor(GAME_WIDTH/2, 3*GAME_HEIGHT/4);
Survivor survivor(SURVIVOR_STARTING_X, SURVIVOR_STARTING_Y);
//Initialize Enemies
std::vector<Zombie*> zombies;
//Initialize Projectiles
std::vector<Projectile*> projectiles;
//Initialize Map
std::string texture_names[4] = { "Floor.png", "WallEdge.png", 
    "WallCorner.png", "WallT.png" };
Map map( 4, (std::string*)texture_names, MAP1_TILE_ROWS, 
        MAP1_TILE_COLS, MAP1_TILE_WIDTH, MAP1_TILE_HEIGHT );

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized. Error: %s\n", SDL_GetError());
        return false;
    }
    //Set texture filtering?
    //Create window
    gWindow = SDL_CreateWindow("SURVIVE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("SDL_CreateWindow: %s\n", SDL_GetError());
        return false;
    }
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if (gRenderer == NULL) {
        printf("SDL_CreateRenderer: %s\n", SDL_GetError());
        return false;
    }
    //Initialize renderer color to white for clearing screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(gRenderer);

    //Initialize PNG/JPG loading
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted&flags) != flags) {
        printf("IMG_Init: %s\n", IMG_GetError());
        return false;
    }

    return true;
}
bool load() {
    bool success = true;
    //load main Character texture
    survivor.load("PlayerRight.png", 1, SURVIVOR_NUM_SPRITES);
    //load map
    map.load();

    return success;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    for (int i = 0; i < projectiles.size(); ++i) {
        delete projectiles[i];
        projectiles[i] = NULL;
    }
    for (int i = 0; i < zombies.size(); ++i) {
        delete zombies[i];
        zombies[i] = NULL;
    }
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    //Initialize SDL and window
    if ( !init() ) {
        printf("init() returned False (failed to initialize SDL)\n");
        close();
        return -1;
    }
    if ( !load() ) {
        printf("load() returned False (failed to load textures)\n");
        return -1;
    }

    //Main loop flag
    bool quit = false;
    int zombie_frame = 0;
    int current = SDL_GetTicks();
    int second_timer = current;
    int last = current;
    int last_player_move = current;
    int last_player_turn = current;
    int last_player_shot = current;
    int last_zombie_move = current;
    int last_zombie_spawn = current;
    int zombie_count = 0;
    int frame_count = 0;

    map.updatePath(survivor.getX(), survivor.getY()); //fill path for zombie path finding
    map.printPath();

    //Event handler
    SDL_Event e;

    while( !quit ) {
        current = SDL_GetTicks();

        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_SPACE:
                        if ( (current - last_player_shot) >= SURVIVOR_TIME_PER_SHOT ) {
                            survivor.shoot();
                            last_player_shot = current;
                            printf("NEW PROJECTILE SIZE = %d\n", projectiles.size());
                        }
                        break;
                }
            }
        }
        const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
        /* put all this in survivor update function by defining sdl library in
         * class and then putting scancode as an argument to the update func*/
        if (currentKeyState[SDL_SCANCODE_LEFT]) {
            if ( (current - last_player_turn) >= SURVIVOR_TIME_PER_MOVE ) {
                survivor.update("LEFT");
                last_player_turn = current;
            }
        }
        else if (currentKeyState[SDL_SCANCODE_RIGHT]) {
            if ( (current - last_player_turn) >= SURVIVOR_TIME_PER_MOVE ) {
                survivor.update("RIGHT");
                last_player_turn = current;
            }
        }
        if (currentKeyState[SDL_SCANCODE_UP]) {
            if ( (current - last_player_move) >= SURVIVOR_TIME_PER_MOVE ) {
                survivor.update("UP");
                last_player_move = current;
            }
        }
        if (currentKeyState[SDL_SCANCODE_DOWN]) {
            if ( (current - last_player_move) >= SURVIVOR_TIME_PER_MOVE ) {
                survivor.update("DOWN");
                last_player_move = current;
            }
        }
        if (!currentKeyState[SDL_SCANCODE_UP] 
                && !currentKeyState[SDL_SCANCODE_DOWN]) {
            survivor.setMoving(false);
        }

        //Update path finding
        
        /*comment out for now */
        if (survivor.changedTiles()) {
            map.updatePath(survivor.getX(), survivor.getY());
            map.printPath();
            printf("SURVIVOR CHANGED TILES!\n");
        }
        
        //Zombies updating
        std::vector<Zombie*>::iterator z_it = zombies.begin();
        if ( (current - last_zombie_move) >= ZOMBIE_TIME_PER_MOVE ) {
            while (z_it != zombies.end()) {
                (*z_it)->update();
                z_it++;
            }
            last_zombie_move = current;
        }
        if ( (current - last_zombie_spawn) >= ZOMBIE_SPAWN_TIME ) {
            if (zombie_count < MAX_ZOMBIES) {
                //spawn zombie
                Zombie* temp = new Zombie(0, 0, 0);
                temp->load("ZombieRight.png", 1, 4);
                zombies.push_back(temp);
                zombie_count++;
                printf("New zombie spawned\n");
            }
            last_zombie_spawn = current;
        }


        std::vector<Projectile*>::iterator it = projectiles.begin();
        //printf("check4\n");
        while (it != projectiles.end()) {
            //if ( !(it->update()) ) {
            if ( !((*it)->update()) ) {
                delete *it;
                it = projectiles.erase(it);
                //it++;
            } else {
                it++;
            }
            //printf("check6\n");
        }

        //RENDERING
        //clear screen
        SDL_SetRenderDrawColor( gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a );
        SDL_RenderClear(gRenderer);
        //Set up viewport for info area
        SDL_RenderSetViewport(gRenderer, &INFO_VIEWPORT);
        //Render info area
        SDL_SetRenderDrawColor( gRenderer, INFO_COLOR.r, INFO_COLOR.g, INFO_COLOR.b, INFO_COLOR.a );
        SDL_RenderFillRect(gRenderer, &INFO);
        //Set up viewport for gameplay area
        SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
        //Render gameplay area
        SDL_SetRenderDrawColor(gRenderer, GAME_COLOR.r, GAME_COLOR.g, GAME_COLOR.b, GAME_COLOR.a);
        SDL_RenderFillRect(gRenderer, &GAME);

        //Render map
        map.draw();

        //Render survivor
        survivor.draw();

        //Render zombies
        z_it = zombies.begin();
        while (z_it != zombies.end()) {
            (*z_it)->draw(zombie_frame/ZOMBIE_FRAMES_PER_ANIMATION);
            z_it++;
        }

        //Render projectiles
        it = projectiles.begin();
        while (it != projectiles.end()) {
            printf("drawing projectile at %f, %f\n", (*it)->getX(), (*it)->getY());
            //it->draw();
            (*it)->draw();
            it++;
        }
        
        //update screen
        SDL_RenderPresent(gRenderer);

        zombie_frame = (zombie_frame + 1) % (ZOMBIE_NUM_SPRITES*ZOMBIE_FRAMES_PER_ANIMATION);

        //end frame FrameManager checks
        frame_count++;
        current = SDL_GetTicks();
        //capture frame rate
        if (current - second_timer >= 1000) {
            printf("Frame Rate = %dfps\n", frame_count);
            second_timer = current;
            frame_count = 0;
        }
        //cap frame rate
        int since_last = current - last;
        if ( (current - last) < MS_PER_FRAME ) {
            SDL_Delay( MS_PER_FRAME - (current-last) );
        }
        last = SDL_GetTicks();
    }

    //Close SDL window and subsystems and free memory
    close();
}
