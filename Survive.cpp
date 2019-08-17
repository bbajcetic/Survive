#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Constants.h"
#include <string>

//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

//Loads image as texture
SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;
SDL_Surface* gScreen = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

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
    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int flags = IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted&flags) != flags) {
        printf("IMG_Init: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

SDL_Texture* loadTexture( std::string path) {
    //texture to return
    SDL_Texture* newTexture = NULL;

    //load image
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    //Create texture from surface
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
    }
    //Get rid of surface
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
bool load() {
    bool success = true;
    gTexture = loadTexture("person1.png");
    if (gTexture == NULL) {
        printf("Failed to load person1.png\n");
        success = false;
    }
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

    //Event handler
    SDL_Event e;

    while( !quit ) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Rect person1Pos;
        person1Pos.x = 20;
        person1Pos.y = 20;
        person1Pos.w = 60;
        person1Pos.h = 60;
        SDL_Rect box2Pos;
        box2Pos.x = 200;
        box2Pos.y = 200;
        box2Pos.w = 60;
        box2Pos.h = 60;
        //clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(gRenderer);
        //render texture to the renderer to render to screen
        SDL_RenderCopy(gRenderer, gTexture, NULL, &person1Pos);
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect(gRenderer, &box2Pos);
        //update screen
        SDL_RenderPresent(gRenderer);

    }

    //Close SDL window and subsystems and free memory
    close();
}











