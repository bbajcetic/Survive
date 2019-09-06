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
#include "ZombieManager.h"
#include "Collision.h"
#include "Container.h"
#include "CustomMath.h"
#include "CustomRender.h"

int score = 0;
int wave = 1;

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

//Clear object vectors
void clearObjects();

//Main game functions
/* function that cleans up resources and exits game */
void exitGame();
/* function that displays the start screen */
void startGame();
/* returns true if Survivor is alive and false if dead */
bool playWave();
/* function that allows purchasing of health, ammo, etc. between waves */
void afterWave();
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
SDL_Renderer* gRenderer = NULL;
ObjTexture gTextTexture;
//SDL_Texture* gTextTexture = NULL;
TTF_Font* gFont = NULL;

//Survivor survivor(GAME_WIDTH/2, 3*GAME_HEIGHT/4);
Survivor survivor(SURVIVOR_STARTING_X, SURVIVOR_STARTING_Y);

//Initialize ZombieManager
ZombieManager zombieManager(1);

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
    int size2 = zombieManager.getSize();
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
}
void close() {
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gFont = NULL;
    gWindow = NULL;
    gRenderer = NULL;
    std::vector<Projectile*>::iterator it = projectiles.begin();
    while (it != projectiles.end()) {
        printf("clearing projectile\n");
        delete *it;
        it = projectiles.erase(it);
        printf("success clearing\n");
    }

    zombieManager.destroyZombies();

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
                if (wave < NUMBER_OF_WAVES) {
                    /* set up and go to next wave */
                    afterWave();
                    wave++;
                    resetWave();
                }
                else {
                    //end of game, you beat the game!!! Shows score
                    restart = gameOver();
                    resetGame();
                    if (!restart)
                        break; //end game
                }
            }
            else if (!alive) {
                restart = gameOver();
                if (!restart) {
                    /* end game */
                    break;
                }
            }
            if (restart) {
                resetGame();
                break;
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
    zombieManager.reset(1); /* wave 1 */
    score = 0;
    wave = 1;
}
void resetWave() {
    survivor.resetWave();
    zombieManager.reset(wave);

}
void afterWave() {
    //Set up viewport for wave complete / shop area
    SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
    //create Shop container and render Shop area
    Container shopCont( AFTERWAVE_RECT, 12, 1, RED );

    //write WAVE COMPLETE
    shopCont.writeCenter("WAVE COMPLETE", 1, 0);
    
    //Set up wave complete viewport for buttons
    SDL_RenderSetViewport(gRenderer, &AFTERWAVE_VIEWPORT);

    //buy health button
    Container healthCont( BUY_HEALTH_RECT, 2, 1, BUTTON_DARKGRAY); 
    //buy ammo button
    Container ammoCont( BUY_AMMO_RECT, 2, 1, BUTTON_DARKGRAY);
    //continue button
    Container continueCont( CONTINUE_RECT, 1, 1, BUTTON_DARKGRAY);

    bool continue_ = false;

    SDL_Event e;
    int x = 0; int y = 0; //current mouse position
    while( !continue_ ) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                exitGame();
            }
            else if (e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&x, &y);
                x = x - AFTERWAVE_RECT.x - GAME_VIEWPORT.x;
                y = y - AFTERWAVE_RECT.y - GAME_VIEWPORT.y;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (healthCont.inButton(x, y)) {
                    survivor.buyHealth(10, 50);
                }
                else if (ammoCont.inButton(x, y)) {
                    survivor.buyAmmo(10, 10);
                }
                else if (continueCont.inButton(x, y)) {
                    continue_ = true;
                }
            }
        }

        //RENDERING
        //clear screen
        SDL_SetRenderDrawColor( gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a );
        SDL_RenderClear(gRenderer);

        //Print game info to info area
        printInfo();
        //Set up viewport for wave complete / shop area
        SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
        SDL_SetRenderDrawColor(gRenderer, GAME_COLOR.r, GAME_COLOR.g, GAME_COLOR.b, GAME_COLOR.a);
        SDL_RenderFillRect(gRenderer, &GAME_RECT);

        map.draw();
        survivor.draw();
        zombieManager.render();
        std::vector<Projectile*>::iterator it = projectiles.begin();
        while (it != projectiles.end()) {
            (*it)->draw();
            it++;
        }

        shopCont.setColor(RED);
        shopCont.outline(4);
        shopCont.setColor(BLACK);
        shopCont.render();
        shopCont.setColor(RED);
        //write WAVE COMPLETE
        loadFont("fonts/KongText.ttf", 24);
        shopCont.writeCenter("WAVE COMPLETE", 1, 0);
        //Set up wave complete viewport for buttons
        SDL_RenderSetViewport(gRenderer, &AFTERWAVE_VIEWPORT);

        loadFont("fonts/MotionControl-Bold.ttf", 24);
        if (healthCont.inButton(x, y)) {
            printf("check2\n");
            //healthCont.setColor(BUTTON_GRAY);
            healthCont.setColor(GREEN);
            healthCont.render();
            healthCont.setColor(RED);
            healthCont.writeCenter("Buy +10 Health", 0, -3);
            healthCont.writeCenter("[Cost: 50 Score]", 1, -3);
        }
        else {
            healthCont.setColor(BUTTON_DARKGRAY);
            healthCont.render();
            healthCont.setColor(RED);
            healthCont.writeCenter("Buy +10 Health", 0, -3);
            healthCont.writeCenter("[Cost: 50 Score]", 1, -3);
        }
        if (ammoCont.inButton(x, y)) {
            //ammoCont.setColor(BUTTON_GRAY);
            ammoCont.setColor(GREEN);
            ammoCont.render();
            ammoCont.setColor(RED);
            ammoCont.writeCenter("Buy +10 Ammo", 0, -3);
            ammoCont.writeCenter("[Cost: 10 Score]", 1, -3);
        }
        else {
            ammoCont.setColor(BUTTON_DARKGRAY);
            ammoCont.render();
            ammoCont.setColor(RED);
            ammoCont.writeCenter("Buy +10 Ammo", 0, -3);
            ammoCont.writeCenter("[Cost: 10 Score]", 1, -3);
        }
        loadFont("fonts/MotionControl-Bold.ttf", 36);
        if (continueCont.inButton(x, y)) {
            //continueCont.setColor(BUTTON_GRAY);
            continueCont.setColor(GREEN);
            continueCont.render();
            continueCont.setColor(RED);
            continueCont.writeCenter("CONTINUE", 0, 0);
        }
        else {
            continueCont.setColor(BUTTON_DARKGRAY);
            continueCont.render();
            continueCont.setColor(RED);
            continueCont.writeCenter("CONTINUE", 0, 0);
        }
        //update screen
        SDL_RenderPresent(gRenderer);

        SDL_Delay(16); //check for input at 60fps
    }

}

void exitGame() {
    close();
    exit(1);
}
void startGame() {

    //screen container
    Container screenCont( SCREEN_RECT, 1, 1, BLACK );
    //start game button
    Container startCont( START_RECT, 2, 1, BUTTON_DARKGRAY );

    bool continue_ = false;

    SDL_Event e;
    int x = 0; int y = 0; //current mouse position
    while( !continue_ ) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                exitGame();
            }
            else if (e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&x, &y);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (startCont.inButton(x, y)) {
                    continue_ = true;
                }
            }
        }
        //RENDERING
        //clear screen
        SDL_SetRenderDrawColor( gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a ); SDL_RenderClear(gRenderer);

        screenCont.setColor(BLACK);
        screenCont.render();
        loadFont("fonts/AtariFull.ttf", 128);
        screenCont.setColor(RED);
        screenCont.write("SURVIVE", 0, 0, 50, 225, 330);

        if (startCont.inButton(x, y)) {
            startCont.setColor(GREEN);
            startCont.render();
            startCont.setColor(RED);
            loadFont("fonts/AtariFull.ttf", 36);
            startCont.writeCenter("START", 0, 30);
            startCont.writeCenter("GAME", 1, 10);
        }
        else {
            startCont.setColor(BLACK);
            startCont.outline(4);
            startCont.setColor(BUTTON_DARKGRAY);
            startCont.render();
            startCont.setColor(RED);
            loadFont("fonts/AtariFull.ttf", 36);
            startCont.writeCenter("START", 0, 30);
            startCont.writeCenter("GAME", 1, 10);
        }
        //update screen
        SDL_RenderPresent(gRenderer);

        SDL_Delay(16); //check for input at 60fps
    }

}
//void startGame() {
//    //Set up viewport for info area
//    SDL_RenderSetViewport(gRenderer, &INFO_VIEWPORT);
//    //create Info container and render info area
//    Container infoCont( INFO_RECT, 16, 1, RED );
//
//    //Set up viewport for gameplay area
//    SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
//
//    //start game button
//    Container startCont( START_RECT, 2, 1, BUTTON_DARKGRAY);
//
//    bool continue_ = false;
//
//    SDL_Event e;
//    int x = 0; int y = 0; //current mouse position
//    while( !continue_ ) {
//        //Handle events on queue
//        while (SDL_PollEvent( &e ) != 0) {
//            if (e.type == SDL_QUIT) {
//                exitGame();
//            }
//            else if (e.type == SDL_MOUSEMOTION) {
//                SDL_GetMouseState(&x, &y);
//                x = x - GAME_VIEWPORT.x;
//                y = y - GAME_VIEWPORT.y;
//            }
//            else if (e.type == SDL_MOUSEBUTTONDOWN) {
//                if (startCont.inButton(x, y)) {
//                    continue_ = true;
//                }
//            }
//        }
//        //RENDERING
//        //clear screen
//        SDL_SetRenderDrawColor( gRenderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a ); SDL_RenderClear(gRenderer);
//
//        //Set up viewport for info area
//        SDL_RenderSetViewport(gRenderer, &INFO_VIEWPORT);
//        infoCont.outline(2);
//        infoCont.setColor(BLACK);
//        infoCont.render();
//        infoCont.setColor(RED);
//        loadFont("fonts/AtariFull.ttf", 12);
//        infoCont.writeCenter("Press START GAME", 8, 0);
//        //Set up viewport for gameplay area
//        SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
//        SDL_SetRenderDrawColor(gRenderer, GAME_COLOR.r, GAME_COLOR.g, GAME_COLOR.b, GAME_COLOR.a);
//        SDL_RenderFillRect(gRenderer, &GAME_RECT);
//
//        //Render map
//        map.draw();
//
//        if (startCont.inButton(x, y)) {
//            startCont.setColor(GREEN);
//            startCont.render();
//            startCont.setColor(RED);
//            loadFont("fonts/AtariFull.ttf", 36);
//            startCont.writeCenter("START", 0, 30);
//            startCont.writeCenter("GAME", 1, 10);
//        }
//        else {
//            startCont.setColor(BLACK);
//            startCont.outline(4);
//            startCont.setColor(BUTTON_DARKGRAY);
//            startCont.render();
//            startCont.setColor(RED);
//            loadFont("fonts/AtariFull.ttf", 36);
//            startCont.writeCenter("START", 0, 30);
//            startCont.writeCenter("GAME", 1, 10);
//        }
//        //update screen
//        SDL_RenderPresent(gRenderer);
//
//        SDL_Delay(16); //check for input at 60fps
//    }
//
//}
void printInfo() {
        //Set up viewport for info area
        SDL_RenderSetViewport(gRenderer, &INFO_VIEWPORT);
        //create Info container and render info area
        Container infoCont( INFO_RECT, 16, 1, RED );
        infoCont.outline(2);
        infoCont.setColor(BLACK);
        infoCont.render();
        infoCont.setColor(RED);

        std::string temp;
        char buff[40];
        loadFont("fonts/AtariFull.ttf", 12);
        //output score
        snprintf(buff, sizeof(buff), "SCORE: %d", score);
        temp = buff;
        infoCont.writeCenter(temp, 1, 0);

        //output wave
        snprintf(buff, sizeof(buff), "WAVE: %d", wave);
        temp = buff;
        infoCont.writeCenter(temp, 6, 0);

        //output zombies remaining
        int num_total = zombieManager.getNumZombies();
        int num_dead = zombieManager.getNumDead();
        if (num_total - num_dead < 10) {
            snprintf( buff, sizeof(buff), 
                    "ZOMBIES LEFT: %d", num_total - num_dead );
            temp = buff;
            infoCont.writeCenter(temp, 7, 0);
        }

        //output ammo
        int ammo = survivor.getAmmo();
        snprintf(buff, sizeof(buff), "AMMO: %d/%d", ammo, SURVIVOR_STARTING_AMMO);
        temp = buff;
        infoCont.writeCenter(temp, 9, 0);

        //output health
        int health = survivor.getHealth();
        snprintf(buff, sizeof(buff), 
                "HEALTH: %d/%d", health, SURVIVOR_STARTING_HEALTH);
        temp = buff;
        infoCont.writeCenter(temp, 3, 0);

        //output health bar
        SDL_Rect healthRect = { INFO_WIDTH/2-INFO_HEALTH_BAR_WIDTH/2, 
            infoCont.rowToY(4), 
            INFO_HEALTH_BAR_WIDTH, INFO_HEALTH_BAR_HEIGHT };
        renderHealthBar( healthRect, 
                float(health)/float(SURVIVOR_STARTING_HEALTH), GREEN, RED );

}
bool gameOver() {
    //Set up viewport for gameplay area
    SDL_RenderSetViewport(gRenderer, &GAME_VIEWPORT);
    //create Game Over container and render game over area
    Container gameoverCont( GAMEOVER_RECT, 8, 1, RED );
    gameoverCont.outline(4);
    gameoverCont.setColor(BLACK);
    gameoverCont.render();
    gameoverCont.setColor(RED);

    std::string temp;
    char buff[40];
    loadFont("fonts/ArcadeClassic.ttf", 48);
    //write GAME OVER
    gameoverCont.writeCenter("GAME", 1, 0);
    gameoverCont.writeCenter("OVER", 2, 0);

    loadFont("fonts/AtariFull.ttf", 12);
    //write wave 
    snprintf(buff, sizeof(buff), "WAVE REACHED: %d", wave);
    temp = buff;
    gameoverCont.writeCenter(temp, 4, 0);

    //write score 
    snprintf(buff, sizeof(buff), "Score: %d", score);
    temp = buff;
    gameoverCont.writeCenter(temp, 5, 0);

    loadFont("fonts/MotionControl-Bold.ttf", 24);
    //write exit/restart
    snprintf(buff, sizeof(buff), "Restart(r)      Exit(q)");
    temp = buff;
    gameoverCont.writeCenter(temp, 7, 0);

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
    //Main loop flag
    bool quit = false;
    bool alive = true;
    int current = SDL_GetTicks();
    int second_timer = current;
    /* last: for frame rate capping */
    int last = current;
    //int last_zombie_spawn = current;
    zombieManager.setLastSpawn(current);
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
                        quit = true;
                        break;
                }
            }
            else if (e.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                survivor.turn(x, y);
                printf("mouse at %d, %d\n", x, y);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                survivor.shoot(current);
            }
        }
        const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
        /* put all this in survivor update function by defining sdl library in
         * class and then putting scancode as an argument to the update func*/
        if ( currentKeyState[SDL_SCANCODE_LEFT] 
                || currentKeyState[SDL_SCANCODE_A] ) {
            survivor.update("LEFT", current);
        }
        if ( currentKeyState[SDL_SCANCODE_RIGHT] 
                || currentKeyState[SDL_SCANCODE_D] ) {
            survivor.update("RIGHT", current);
        }
        if ( currentKeyState[SDL_SCANCODE_UP] 
                || currentKeyState[SDL_SCANCODE_W] ) {
            survivor.update("UP", current);
        }
        if ( currentKeyState[SDL_SCANCODE_DOWN] 
                || currentKeyState[SDL_SCANCODE_S] ) {
            survivor.update("DOWN", current);
        }
        if ( !currentKeyState[SDL_SCANCODE_UP] 
                && !currentKeyState[SDL_SCANCODE_DOWN]
                && !currentKeyState[SDL_SCANCODE_RIGHT]
                && !currentKeyState[SDL_SCANCODE_LEFT]
                && !currentKeyState[SDL_SCANCODE_W]
                && !currentKeyState[SDL_SCANCODE_S]
                && !currentKeyState[SDL_SCANCODE_A]
                && !currentKeyState[SDL_SCANCODE_D] ) {
            survivor.setMoving(false);
        }
        else {
            if (survivor.canMove(current)) {
                survivor.setLastMove(current);
            }
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
        zombieManager.update(current);

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
            std::vector<Zombie*>::iterator z_it = zombieManager.zombies.begin();
            while (z_it != zombieManager.zombies.end()) {
                if (isCollision(**it, **z_it)) {
                    if ( !((*z_it)->takeDamage((*it)->getDamage())) ) {
                        zombieManager.zombieDead();
                        if (zombieManager.getNumDead() >= zombieManager.getNumZombies()) {
                            quit = true;
                        }
                        score += KILL_POINTS;
                        delete *z_it;
                        z_it = zombieManager.zombies.erase(z_it);
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
        std::vector<Zombie*>::iterator z_it = zombieManager.zombies.begin();
        while (z_it != zombieManager.zombies.end()) {
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
        zombieManager.render();

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
