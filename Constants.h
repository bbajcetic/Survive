//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

//survivor global variables
const int SURVIVOR_STARTING_HEALTH = 100;
const int SURVIVOR_STARTING_X = 384;
const int SURVIVOR_STARTING_Y = 336;
const int SURVIVOR_STARTING_ANGLE = 270;
const int SURVIVOR_STARTING_SPEED = 6;
const int SURVIVOR_SENSITIVITY = 10;
const int SURVIVOR_NUM_SPRITES = 4;
const int SURVIVOR_FRAMES_PER_ANIMATION = 4;

const int SURVIVOR_WIDTH = 44;
const int SURVIVOR_HEIGHT = 44;

const int SURVIVOR_TIME_PER_MOVE = 33;
const int SURVIVOR_TIME_PER_SHOT = 500;

//zombie global variables
const int ZOMBIE_STARTING_HEALTH = 100;
const int ZOMBIE_STARTING_SPEED = 4;
const int ZOMBIE_WIDTH = 44;
const int ZOMBIE_HEIGHT = 44;
const int ZOMBIE_SENSITIVITY = 20;
const int ZOMBIE_SPAWN_TIME = 2000; //6000ms = 6s
const int ZOMBIE_FRAMES_PER_ANIMATION = 12;
const int ZOMBIE_TIME_PER_MOVE = 33;
const int ZOMBIE_NUM_SPRITES = 4;
const int MAX_ZOMBIES = 3;

//projectile global variables
const int PROJECTILE_STARTING_DAMAGE = 10;
const int PROJECTILE_STARTING_SPEED = 3;
const int PROJECTILE_WIDTH = 15;
const int PROJECTILE_HEIGHT = 3;

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
