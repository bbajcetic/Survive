//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

//window global variables
const SDL_Color BG_COLOR = { 0, 0, 0, 255 }; //black
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int MS_PER_FRAME = 16;

//survivor global variables
const int SURVIVOR_STARTING_X = 0;
const int SURVIVOR_STARTING_Y = 0;
const int SURVIVOR_STARTING_ANGLE = 90;
const int SURVIVOR_STARTING_SPEED = 5;
const int SURVIVOR_STARTING_DIRECTION = 1;

const int SURVIVOR_WIDTH = 64;
const int SURVIVOR_HEIGHT = 64;

/*VIEWPORTS*/
//Info viewport
const SDL_Color INFO_COLOR = { 47, 79, 79, 255 }; //dark slate gray
const SDL_Rect INFO_VIEWPORT = { 10, 10, 940, 70 }; //x, y, width, height
const SDL_Rect INFO = { 0, 0, 940, 70 };

//Game viewport
const SDL_Color GAME_COLOR = { 105, 105, 105, 255 }; //dim gray
const SDL_Rect GAME_VIEWPORT = { 10, 90, 940, 540 }; //x, y, width, height
const SDL_Rect GAME = { 0, 0, 940, 540 };
const int GAME_WIDTH = 940;
const int GAME_HEIGHT = 540;

//math constants
const double PI = 3.141592653589793;

#endif
