//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

//game variables
const int KILL_POINTS = 10;
const int OUTLINE_WIDTH = 2;

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
const int SURVIVOR_HITBOX_WIDTH = 36;
const int SURVIVOR_HITBOX_HEIGHT = 36;

const int SURVIVOR_TIME_PER_MOVE = 33;
const int SURVIVOR_TIME_PER_TURN = 33; 
const int SURVIVOR_TIME_PER_SHOT = 250;

//zombie global variables
const int ZOMBIE_STARTING_HEALTH = 100;
const int ZOMBIE_STARTING_DAMAGE = 20;
const int ZOMBIE_ATTACK_TIME = 1000;
const int ZOMBIE_MAX_SPEED = 6;
const int ZOMBIE_MIN_SPEED = 3;
const int ZOMBIE_WIDTH = 44;
const int ZOMBIE_HEIGHT = 44;
const int ZOMBIE_HITBOX_WIDTH = 36;
const int ZOMBIE_HITBOX_HEIGHT = 36;
const int ZOMBIE_SENSITIVITY = 20;
const int ZOMBIE_SPAWN_TIME = 2000; //6000ms = 6s
const int ZOMBIE_FRAMES_PER_ANIMATION = 3;
const int ZOMBIE_TIME_PER_MOVE = 33;
const int ZOMBIE_NUM_SPRITES = 4;
const int MAX_ZOMBIES = 3;

//health bar variables
const int HEALTH_BAR_WIDTH = 40;
const int HEALTH_BAR_HEIGHT = 5;

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
const int INFO_WIDTH = 200;
const int INFO_HEIGHT = 576;
const SDL_Color INFO_COLOR = { 0xFF, 0x00, 0x00, 0xFF };
const SDL_Rect INFO_VIEWPORT = { 980, 10, INFO_WIDTH, INFO_HEIGHT }; //x, y, width, height
const SDL_Rect INFO_OUT = { 0, 0, INFO_WIDTH, INFO_HEIGHT };
const SDL_Rect INFO_IN = { OUTLINE_WIDTH, OUTLINE_WIDTH, INFO_WIDTH-OUTLINE_WIDTH*2, INFO_HEIGHT-OUTLINE_WIDTH*2 }; //x, y, width, height

//Game viewport
const int GAME_WIDTH = 960;
const int GAME_HEIGHT = 576;
const SDL_Color GAME_COLOR = { 105, 105, 105, 255 }; //dim gray
const SDL_Rect GAME_VIEWPORT = { 10, 10, GAME_WIDTH, GAME_HEIGHT }; //x, y, width, height
const SDL_Rect GAME_RECT = { 0, 0, 960, 576 };

//Game over screen
const int GAMEOVER_WIDTH = 240;
const int GAMEOVER_HEIGHT = 240;
const SDL_Rect GAMEOVER_RECT = { GAME_WIDTH/2 - GAMEOVER_WIDTH/2, GAME_HEIGHT/2 - GAMEOVER_HEIGHT/2 , GAMEOVER_WIDTH, GAMEOVER_HEIGHT };
const SDL_Rect GAMEOVER_OUTLINE = { GAMEOVER_RECT.x-OUTLINE_WIDTH, GAMEOVER_RECT.y-OUTLINE_WIDTH , GAMEOVER_RECT.w+2*OUTLINE_WIDTH, GAMEOVER_RECT.h+2*OUTLINE_WIDTH };

//math constants
const double PI = 3.141592653589793;

#endif
