#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "Constants.h"
#include "Survivor.h"
#include "Map.h"

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

//Globals
SDL_Window* gWindow = NULL;
SDL_Surface* gScreen = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
//Initialize Player
Survivor survivor(GAME_WIDTH/2, 3*GAME_HEIGHT/4);
//Initialize Enemies

//Initialize tiles Array
int tiles[MAP1_TILE_ROWS][MAP1_TILE_COLS] = {
    {},
    {},
    { 0, 0, 8, 5, 5, 12, 5, 5, 5, 5, 5, 5, 5, 0, 0, 12, 5, 0, 0, 5 },
    { 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 14, 5, 5, 12, 4 },
    { 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0 },
    { 0, 0, 9, 5, 5, 5, 5, 11, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 4, 0, 9, 5, 5, 5, 5, 5, 5, 5, 5, 10, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//Print tiles
void printMultiArray(int* tiles, int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%d, ", *(tiles+i*c+j));
        }
        printf("\n");
    }
}
//Initialize Map
std::string textures[4] = { "Floor.png", "WallEdge.png", "WallCorner.png", 
    "WallT.png" };
Map map( (int*)tiles, 4, (std::string*)textures, MAP1_TILE_ROWS, 
        MAP1_TILE_COLS, MAP1_TILE_WIDTH, MAP1_TILE_HEIGHT );

bool init() {
    //printMultiArray((int*)tiles, 12, 20);
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

    //Initialize PNG loading
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted&flags) != flags) {
        printf("IMG_Init: %s\n", IMG_GetError());
        return false;
    }

    return true;
}
SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loaded = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loaded);
    SDL_FreeSurface(loaded);
    return newTexture;
}

bool load() {
    bool success = true;
    //load main Character texture
    map.load();
    survivor.load("PlayerRight.png", 1, SURVIVOR_NUM_SPRITES);

    //gTexture = survivor.getTexture()->getTexture();
    //
    //gTexture = loadTexture("mario.png");
    //if (gTexture == NULL) {
    //    printf("Failed to load person1.png\n");
    //    success = false;
    //}
    return success;
}

void close() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
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
    int frame = 0;
    int current = SDL_GetTicks();
    int second_timer = current;
    int last = current;
    int last_player_move = current;
    int frame_count = 0;

    //Event handler
    SDL_Event e;

    while( !quit ) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        //    else if (e.type == SDL_KEYDOWN) {
        //        switch(e.key.keysym.sym) {
        //            case SDLK_UP:
        //                survivor.setMoving(true);
        //                break;
        //            case SDLK_DOWN:
        //                survivor.setMoving(true);
        //        }
        //    }
        //    else if (e.type == SDL_KEYUP) {
        //        switch(e.key.keysym.sym) {
        //            case SDLK_UP:
        //                survivor.setMoving(
        }
        const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
        /* put all this in survivor update function by defining sdl library in
         * class and then putting scancode as an argument to the update func*/
        if (currentKeyState[SDL_SCANCODE_LEFT]) {
            survivor.update("LEFT");
            //frame = 0;
        }
        else if (currentKeyState[SDL_SCANCODE_RIGHT]) {
            survivor.update("RIGHT");
            //frame = 0;
        }
        if (currentKeyState[SDL_SCANCODE_UP]) {
            if ( (current - last_player_move) > SURVIVOR_TIME_PER_MOVE ) {
                if (!survivor.getMoving()) {
                    survivor.setMoving(true);
                    frame = 0;
                }
                survivor.update("UP");
                last_player_move = current;
            }
        }
        if (currentKeyState[SDL_SCANCODE_DOWN]) {
            if ( (current - last_player_move) > SURVIVOR_TIME_PER_MOVE ) {
                if (!survivor.getMoving()) {
                    survivor.setMoving(true);
                    frame = 0;
                }
                survivor.update("DOWN");
                last_player_move = current;
            }
        }
        if (!currentKeyState[SDL_SCANCODE_UP] 
                && !currentKeyState[SDL_SCANCODE_DOWN]) {
            survivor.setMoving(false);
        }
        

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
        map.draw();

        //render texture to the renderer to render to screen

        if (survivor.getMoving()) {
            survivor.draw(frame/FRAMES_PER_ANIMATION);
        }
        else {
            survivor.draw(1);
        }
        
        
        //update screen
        SDL_RenderPresent(gRenderer);

        frame = (frame + 1) % SURVIVOR_NUM_SPRITES*FRAMES_PER_ANIMATION;

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
