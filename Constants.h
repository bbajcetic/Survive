//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

//survivor global variables
const int SURVIVOR_STARTING_X = 0;
const int SURVIVOR_STARTING_Y = 0;
const int SURVIVOR_STARTING_ANGLE = 90;
const int SURVIVOR_STARTING_SPEED = 3;
const int SURVIVOR_TIME_PER_MOVE = 16;
const int SURVIVOR_STARTING_DIRECTION = 1;
const int SURVIVOR_NUM_SPRITES = 4;
const int FRAMES_PER_ANIMATION = 6;

const int SURVIVOR_WIDTH = 44;
const int SURVIVOR_HEIGHT = 44;

//projectile global variables
const int PROJECTILE_STARTING_SPEED = 8;
const int PROJECTILE_WIDTH = 3;
const int PROJECTILE_HEIGHT = 15;

//map global variables
const int MAP1_TILE_ROWS = 12;
const int MAP1_TILE_COLS = 20;
const int MAP1_TILE_WIDTH = 48;
const int MAP1_TILE_HEIGHT = 48;

//window global variables
const SDL_Color BG_COLOR = { 0, 0, 0, 255 }; //black
const int SCREEN_WIDTH = 1190;
const int SCREEN_HEIGHT = 596;
const int MS_PER_FRAME = 16;

/*VIEWPORTS*/
//Info viewport
const SDL_Color INFO_COLOR = { 47, 79, 79, 255 }; //dark slate gray
const SDL_Rect INFO_VIEWPORT = { 980, 10, 200, 576 }; //x, y, width, height
const SDL_Rect INFO = { 0, 0, 200, 576 };

//Game viewport
const SDL_Color GAME_COLOR = { 105, 105, 105, 255 }; //dim gray
const SDL_Rect GAME_VIEWPORT = { 10, 10, 960, 576 }; //x, y, width, height
const SDL_Rect GAME = { 0, 0, 960, 576 };
const int GAME_WIDTH = 960;
const int GAME_HEIGHT = 576;

//math constants
const double PI = 3.141592653589793;

#endif
