#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>

#include "Constants.h"
#include "Survivor.h"
#include "Map.h"
#include "Zombie.h"
#include "Collision.h"
#include "CustomMath.h"

int global_count = 0;
int score = 0;
int wave = 1;
int zombies_spawned = 0;
int zombies_dead = 0;
int total_zombies = WAVE1_ZOMBIES;

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

//Clear object vectors
void clearObjects();

//Main game functions
/* function that displays the start screen */
void startGame();
/* returns true if Survivor is alive and false if dead */
bool playWave();
/* function that displays the Game Over screen */
bool gameOver();
/* function that resets what is needed for the next wave */
void resetWave();
/* function that resets what is needed to restart the game */
void resetGame();
/* function that prints game info to info area */
void printInfo();

//Globals
SDL_Window* gWindow = NULL;
SDL_Surface* gScreen = NULL;
SDL_Renderer* gRenderer = NULL;
ObjTexture gTextTexture;
//SDL_Texture* gTextTexture = NULL;
TTF_Font* gFont = NULL;
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
    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return false;
    }

    return true;
}
bool loadFont(std::string file_name, int point_size) {
    bool success = true;
    TTF_CloseFont(gFont);
    gFont = NULL;
    gFont = TTF_OpenFont(file_name.c_str(), point_size);
    if (gFont == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        success = false;
    }
    return success;
}
bool load() {
    bool success = true;
    //load main Character texture
    if ( !(survivor.load("PlayerRight.png", 1, SURVIVOR_NUM_SPRITES)) ) {
        success = false;
    }
    //load map
    if ( !(map.load()) ) {
        success = false;
    }

    return success;
}
void clearObjects() {
    //Projectiles clear
    int size1 = projectiles.size();
    int size2 = zombies.size();
    printf("number of projectiles = %d\n", size1);
    printf("number of zombies = %d\n", size2);
    printf("clearing projectiles\n");
    std::vector<Projectile*>::iterator it = projectiles.begin();
    while (it != projectiles.end()) {
        printf("clearing projectile\n");
        delete *it;
        it = projectiles.erase(it);
        printf("success clearing\n");
    }
    //Zombies clear
    printf("clearing zombies\n");
    std::vector<Zombie*>::iterator z_it = zombies.begin();
    while (z_it != zombies.end()) {
        printf("clearing zombie\n");
        delete *z_it;
        z_it = zombies.erase(z_it);
    }
}
void close() {
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gFont = NULL;
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
    TTF_Quit();
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
    
    srand(time(NULL));

    bool restart, alive;
    do {
        restart = false;
        alive = true;
        startGame();
        while (alive) {
            alive = playWave();
            if (alive) {
                /* set up and go to next wave */
                wave++;
                resetWave();
            }
            else if (!alive) {
                restart = gameOver();
                if (restart) {
                    /* reset and restart game */
                    resetGame();
                    continue;
                }
                else if (!restart){
                    /* end game */
                    break;
                }
            }
        }
    } while (restart);

    //Close SDL window and subsystems and free memory
    close();
}
void resetGame() {
    survivor.resetGame();
    clearObjects();
    map.resetMap();
    global_count = 0;
    score = 0;
    wave = 1;
    zombies_spawned = 0;
    zombies_dead = 0;
}
void resetWave() {
    ;
}
void startGame() {
}
void printInfo() {
    SDL_Color text_color = { 0xFF, 0x00, 0x00, 0xFF };
    loadFont("fonts/AtariFull.ttf", 12);
    //output score
    char score_buff[20];
    snprintf(score_buff, sizeof(score_buff), "SCORE: %d", score);
    std::string score_string = score_buff;
    gTextTexture.loadText(score_string, text_color);
    gTextTexture.render(INFO_WIDTH/2-gTextTexture.getWidth()/2, 1*INFO_HEIGHT/16, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    //output wave
    char wave_buff[20];
    snprintf(wave_buff, sizeof(wave_buff), "WAVE: %d", wave);
    std::string wave_string = wave_buff;
    gTextTexture.loadText(wave_string, text_color);
    gTextTexture.render(INFO_WIDTH/2-gTextTexture.getWidth()/2, 3*INFO_HEIGHT/16, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    //output enemies remaining (only if less than 10) 
    char zombie_buff[20];
    if (total_zombies - zombies_dead < 10) {
        snprintf(zombie_buff, sizeof(zombie_buff), "ZOMBIES LEFT: %d", total_zombies - zombies_dead);
        std::string zombie_string = zombie_buff;
        gTextTexture.loadText(zombie_string, text_color);
        gTextTexture.render(INFO_WIDTH/2-gTextTexture.getWidth()/2, 4*INFO_HEIGHT/16, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    }
    //output ammo
    int ammo = survivor.getAmmo();
    char ammo_buff[20];
    snprintf(ammo_buff, sizeof(ammo_buff), "AMMO: %d/%d", ammo, SURVIVOR_STARTING_AMMO);
    std::string ammo_string = ammo_buff;
    gTextTexture.loadText(ammo_string, text_color);
    gTextTexture.render(INFO_WIDTH/2-gTextTexture.getWidth()/2, 6*INFO_HEIGHT/16, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    //output health
    int health = survivor.getHealth();
    char health_buff[20];
    snprintf(health_buff, sizeof(health_buff), "HEALTH: %d/%d", health, SURVIVOR_STARTING_HEALTH);
    std::string health_string = health_buff;
    gTextTexture.loadText(health_string, text_color);
    gTextTexture.render(INFO_WIDTH/2-gTextTexture.getWidth()/2, 7*INFO_HEIGHT/16, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    int filled_length = int( float(health)/float(SURVIVOR_STARTING_HEALTH) * float(INFO_HEALTH_BAR_WIDTH) );
    int health_red_x = int(INFO_WIDTH/2-INFO_HEALTH_BAR_WIDTH/2.0);
    int health_green_x = int(health_red_x+(INFO_HEALTH_BAR_WIDTH-filled_length));
    SDL_Rect redRect = { health_red_x, 8*INFO_HEIGHT/16, INFO_HEALTH_BAR_WIDTH-filled_length, INFO_HEALTH_BAR_HEIGHT };
    SDL_Rect greenRect = { health_green_x, 8*INFO_HEIGHT/16, filled_length, INFO_HEALTH_BAR_HEIGHT };

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF ); //green
    SDL_RenderFillRect( gRenderer, &greenRect );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF ); //red
    SDL_RenderFillRect( gRenderer, &redRect );
}
bool gameOver() {
    //Set up viewport for gameplay area
    SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF ); //red
    SDL_RenderFillRect( gRenderer, &GAMEOVER_OUTLINE );
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ); //black
    SDL_RenderFillRect( gRenderer, &GAMEOVER_RECT );
    loadFont("fonts/ArcadeClassic.ttf", 48);
    //write GAME OVER
    SDL_Color text_color = { 0xFF, 0x00, 0x00, 0xFF };
    gTextTexture.loadText("GAME", text_color);
    gTextTexture.render(GAME_WIDTH/2-gTextTexture.getWidth()/2, GAMEOVER_RECT.y+20, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    gTextTexture.loadText("OVER", text_color);
    gTextTexture.render(GAME_WIDTH/2-gTextTexture.getWidth()/2, GAMEOVER_RECT.y+20 + gTextTexture.getHeight()/2 + 3, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    //write wave 
    loadFont("fonts/AtariFull.ttf", 12);
    //loadFont("fonts/MotionControl-Bold.ttf", 24);
    char wave_buff[20];
    snprintf(wave_buff, sizeof(wave_buff), "WAVE REACHED: %d", wave);
    std::string wave_string = wave_buff;
    gTextTexture.loadText(wave_string, text_color);
    gTextTexture.render(GAME_WIDTH/2-gTextTexture.getWidth()/2, GAME_HEIGHT/2-10, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);
    //write score 
    loadFont("fonts/AtariFull.ttf", 12);
    //loadFont("fonts/MotionControl-Bold.ttf", 24);
    char score_buff[20];
    snprintf(score_buff, sizeof(score_buff), "Score: %d", score);
    std::string score_string = score_buff;
    gTextTexture.loadText(score_string, text_color);
    gTextTexture.render(GAME_WIDTH/2-gTextTexture.getWidth()/2, GAME_HEIGHT/2+10, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);

    loadFont("fonts/MotionControl-Bold.ttf", 24);
    //write exit/restart
    char exit_buff[40];
    snprintf(exit_buff, sizeof(exit_buff), "Restart(r)      Exit(q)");
    //snprintf(exit_buff, sizeof(exit_buff), "Exit(press q)");
    std::string exit_string = exit_buff;
    gTextTexture.loadText(exit_string, text_color);
    gTextTexture.render(GAME_WIDTH/2-gTextTexture.getWidth()/2, GAME_HEIGHT/2+GAMEOVER_HEIGHT/2-gTextTexture.getHeight()-10, 0, gTextTexture.getWidth(), gTextTexture.getHeight(), 0);

    //update screen
    SDL_RenderPresent(gRenderer);
    
    bool quit = false;
    bool restart = false;
    SDL_Event e;
    while( !quit && !restart) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_r:
                        restart = true;
                        break;
                }
            }
        }
        SDL_Delay(16); //check for input at 60fps
    }
    if (restart) {
        return true;
    }
    return false;

}

bool playWave() {
    total_zombies = int( float(WAVE1_ZOMBIES)*pow(ZOMBIE_MULTIPLIER, float(wave-1)) );
    //Main loop flag
    bool quit = false;
    bool alive = true;
    int current = SDL_GetTicks();
    int second_timer = current;
    /* last: for frame rate capping */
    int last = current;
    int last_zombie_spawn = current;
    int frame_count = 0;

    map.updatePath(survivor.getX(), survivor.getY()); //fill path for zombie path finding
    map.printPath();

    //Event handler
    SDL_Event e;

    while( !quit ) {
        current = SDL_GetTicks();

        /* set last x,y for Survivor to current x,y */
        survivor.setLastX(survivor.getX()-survivor.getWidth()/2.0);
        survivor.setLastY(survivor.getY()-survivor.getHeight()/2.0);

        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                alive = false;
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_SPACE:
                        survivor.shoot(current);
                        break;
                }
            }
        }
        const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
        /* put all this in survivor update function by defining sdl library in
         * class and then putting scancode as an argument to the update func*/
        if (currentKeyState[SDL_SCANCODE_LEFT]) {
            survivor.update("LEFT", current);
        }
        if (currentKeyState[SDL_SCANCODE_RIGHT]) {
            survivor.update("RIGHT", current);
        }
        if (currentKeyState[SDL_SCANCODE_UP]) {
            survivor.update("UP", current);
        }
        if (currentKeyState[SDL_SCANCODE_DOWN]) {
            survivor.update("DOWN", current);
        }
        if (!currentKeyState[SDL_SCANCODE_UP] 
                && !currentKeyState[SDL_SCANCODE_DOWN]) {
            survivor.setMoving(false);
        }
        //printf("current frames = %d\n", current);

        //Update path finding
        
        /*comment out for now */
        if (survivor.changedTiles()) {
            map.updatePath(survivor.getX(), survivor.getY());
            map.printPath();
            printf("SURVIVOR CHANGED TILES!\n");
        }
        
        //Zombies updating
        std::vector<Zombie*>::iterator z_it = zombies.begin();
        while (z_it != zombies.end()) {
            (*z_it)->update(current);
            z_it++;
        }
        if ( (current - last_zombie_spawn) >= ZOMBIE_SPAWN_TIME ) {
            if (zombies_spawned < total_zombies) {
                //spawn zombie
                Zombie* temp = new Zombie(0, 0, 0);
                temp->load("ZombieRight.png", 1, 4);
                zombies.push_back(temp);
                zombies_spawned++;
                printf("New zombie spawned\n");
            }
            last_zombie_spawn = current;
        }

        //Projectiles updating
        std::vector<Projectile*>::iterator it = projectiles.begin();
        while (it != projectiles.end()) {
            if ( !((*it)->update()) ) {
                delete *it;
                it = projectiles.erase(it);
            } else {
                it++;
            }
        }

        //Collision detection
        
        //check projectiles->zombies
        bool hit;
        it = projectiles.begin();
        while (it != projectiles.end()) {
            hit = false;
            z_it = zombies.begin();
            while (z_it != zombies.end()) {
                if (isCollision(**it, **z_it)) {
                    if ( !((*z_it)->takeDamage((*it)->getDamage())) ) {
                        zombies_dead++;
                        score += KILL_POINTS;
                        delete *z_it;
                        z_it = zombies.erase(z_it);
                    }
                    delete *it;
                    it = projectiles.erase(it);
                    hit = true;
                    break;
                }
                else {
                    z_it++;
                }
            }
            if (!hit) { it++; }
        }
        //check zombies->survivor
        z_it = zombies.begin();
        while (z_it != zombies.end()) {
            if ( (*z_it)->canAttack(current) ) {
                if (isCollision(survivor, **z_it)) {
                    if ( !survivor.takeDamage((*z_it)->getDamage()) ) {
                        alive = false;
                        quit = true;
                        break;
                    }
                    (*z_it)->updateAttackTime(current);
                }
            }
            z_it++;
        }

        //RENDERING
        //clear screen
        SDL_SetRenderDrawColor( gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a );
        SDL_RenderClear(gRenderer);
        //Set up viewport for info area
        SDL_RenderSetViewport(gRenderer, &INFO_VIEWPORT);
        //Render info area
        SDL_SetRenderDrawColor( gRenderer, INFO_COLOR.r, INFO_COLOR.g, INFO_COLOR.b, INFO_COLOR.a );
        SDL_RenderFillRect(gRenderer, &INFO_OUT);
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect(gRenderer, &INFO_IN);
        //Print game info to info area
        printInfo();

        //Set up viewport for gameplay area
        SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
        //Render gameplay area
        SDL_SetRenderDrawColor(gRenderer, GAME_COLOR.r, GAME_COLOR.g, GAME_COLOR.b, GAME_COLOR.a);
        SDL_RenderFillRect(gRenderer, &GAME_RECT);

        //Render map
        map.draw();

        //Render survivor
        survivor.draw();

        //Render zombies
        z_it = zombies.begin();
        while (z_it != zombies.end()) {
            (*z_it)->draw();
            z_it++;
        }

        //Render projectiles
        it = projectiles.begin();
        while (it != projectiles.end()) {
            (*it)->draw();
            it++;
        }
        
        //update screen
        SDL_RenderPresent(gRenderer);

        //Update frame counters

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
    return alive;

}
