#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Initialize SDL and create window
bool init();

//Shut down SDL
void close();

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized. Error: %s\n", SDL_GetError());
        return false;
    } else {
        //Create window
        window = SDL_CreateWindow("SURVIVE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window failed to create. Error: %s\n", SDL_GetError());
            return false;
        } else {
            //Get surface/screen
            screen = SDL_GetWindowSurface(window);
        }
    }
    return true;
}

void close() {
    SDL_DestroyWindow(window);
    screen = NULL;
    window = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    //Initialize SDL and window
    if ( !init() ) {
        printf("init() returned False (failed to initialize SDL)\n");
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

        SDL_UpdateWindowSurface(window);
    }

    //Close SDL window and subsystems and free memory
    close();
}











