//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

//game variables
const int KILL_POINTS = 10;
const int OUTLINE_WIDTH = 2;
const int WAVE1_ZOMBIES = 12;
const float ZOMBIE_MULTIPLIER = 1.5;
const int NUMBER_OF_WAVES = 10;


//survivor global variables
const int SURVIVOR_STARTING_HEALTH = 100;
const int SURVIVOR_STARTING_AMMO = 100;
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
const int ZOMBIE_STARTING_HEALTH = 30;
const int ZOMBIE_STARTING_DAMAGE = 20;
const int ZOMBIE_ATTACK_TIME = 1000;
const int ZOMBIE_MAX_SPEED = 6;
const int ZOMBIE_MIN_SPEED = 3;
const int ZOMBIE_WIDTH = 44;
const int ZOMBIE_HEIGHT = 44;
const int ZOMBIE_HITBOX_WIDTH = 36;
const int ZOMBIE_HITBOX_HEIGHT = 36;
const int ZOMBIE_SENSITIVITY = 20;
const int ZOMBIE_SPAWN_TIME = 800;
const int ZOMBIE_FRAMES_PER_ANIMATION = 3;
const int ZOMBIE_TIME_PER_MOVE = 33;
const int ZOMBIE_NUM_SPRITES = 4;

//health bar variables
const int HEALTH_BAR_WIDTH = 40;
const int HEALTH_BAR_HEIGHT = 5;

//projectile global variables
const int PROJECTILE_STARTING_DAMAGE = 10;
const int PROJECTILE_STARTING_SPEED = 6;
const int PROJECTILE_WIDTH = 15;
const int PROJECTILE_HEIGHT = 3;

//map global variables
const int MAP1_TILE_ROWS = 12;
const int MAP1_TILE_COLS = 20;
const int MAP1_TILE_WIDTH = 48;
const int MAP1_TILE_HEIGHT = 48;

//window global variables
const SDL_Color GREEN = { 0x00, 0xFF, 0x00, 0xFF };
const SDL_Color RED = { 0xFF, 0x00, 0x00, 0xFF };
const SDL_Color BLACK = { 0x00, 0x00, 0x00, 0xFF };
const SDL_Color BUTTON_DARKGRAY = { 0x20, 0x20, 0x20, 0xFF };
const SDL_Color BUTTON_GRAY = {0x40, 0x40, 0x40, 0xFF };
const SDL_Color CLOUD_GRAY = {0x92, 0x93, 0x85, 0xFF };
const SDL_Color BG_COLOR = { 0, 0, 0, 255 }; //black
const int SCREEN_WIDTH = 1190;
const int SCREEN_HEIGHT = 596;
const SDL_Rect SCREEN_RECT = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
const int MS_PER_FRAME = 16;

/*VIEWPORTS*/
//Info viewport
const int INFO_WIDTH = 200;
const int INFO_HEIGHT = 576;
const SDL_Color INFO_COLOR = { 0xFF, 0x00, 0x00, 0xFF };
const SDL_Rect INFO_VIEWPORT = { 980, 10, INFO_WIDTH, INFO_HEIGHT }; //x, y, width, height
const SDL_Rect INFO_RECT = { 5, 5, INFO_WIDTH-10, INFO_HEIGHT-10 };
const int INFO_HEALTH_BAR_WIDTH = 100;
const int INFO_HEALTH_BAR_HEIGHT = 10;

//Game viewport
const int GAME_WIDTH = 960;
const int GAME_HEIGHT = 576;
const SDL_Color GAME_COLOR = { 105, 105, 105, 255 }; //dim gray
const SDL_Rect GAME_VIEWPORT = { 10, 10, GAME_WIDTH, GAME_HEIGHT }; //x, y, width, height
const SDL_Rect GAME_RECT = { 0, 0, GAME_WIDTH, GAME_HEIGHT };

//Game over screen
const int GAMEOVER_WIDTH = 240;
const int GAMEOVER_HEIGHT = 240;
const SDL_Rect GAMEOVER_RECT = { GAME_WIDTH/2 - GAMEOVER_WIDTH/2, GAME_HEIGHT/2 - GAMEOVER_HEIGHT/2 , GAMEOVER_WIDTH, GAMEOVER_HEIGHT };

//Wave complete screen
const int AFTERWAVE_WIDTH = 360;
const int AFTERWAVE_HEIGHT= 240;
const SDL_Rect AFTERWAVE_VIEWPORT = { GAME_WIDTH/2 - AFTERWAVE_WIDTH/2 + 10, GAME_HEIGHT/2 - AFTERWAVE_HEIGHT/2 + 10, AFTERWAVE_WIDTH, AFTERWAVE_HEIGHT };
const SDL_Rect AFTERWAVE_RECT = { GAME_WIDTH/2 - AFTERWAVE_WIDTH/2, GAME_HEIGHT/2 - AFTERWAVE_HEIGHT/2 , AFTERWAVE_WIDTH, AFTERWAVE_HEIGHT };

//Buttons
/* Buy health button */
const int BUY_HEALTH_WIDTH = 144;
const int BUY_HEALTH_HEIGHT = 45;
const SDL_Rect BUY_HEALTH_RECT = { AFTERWAVE_WIDTH/2 - BUY_HEALTH_WIDTH/2, AFTERWAVE_HEIGHT*1/4, BUY_HEALTH_WIDTH, BUY_HEALTH_HEIGHT };
/* Buy ammo button */
const int BUY_AMMO_WIDTH = 144;
const int BUY_AMMO_HEIGHT = 45;
const SDL_Rect BUY_AMMO_RECT = { AFTERWAVE_WIDTH/2 - BUY_AMMO_WIDTH/2, AFTERWAVE_HEIGHT*2/4, BUY_AMMO_WIDTH, BUY_AMMO_HEIGHT };
/* Continue button */
const int CONTINUE_WIDTH = 144;
const int CONTINUE_HEIGHT = 40;
const SDL_Rect CONTINUE_RECT = { AFTERWAVE_WIDTH/2 - CONTINUE_WIDTH/2, AFTERWAVE_HEIGHT*3/4, CONTINUE_WIDTH, CONTINUE_HEIGHT };
/* Start Game button */
const int START_WIDTH = 300;
const int START_HEIGHT = 150;
const SDL_Rect START_RECT = { 3*GAME_WIDTH/4 - START_WIDTH/2, 3*GAME_HEIGHT/4 - START_HEIGHT/2, START_WIDTH, START_HEIGHT };
const SDL_Rect START_RECT1 = { GAME_WIDTH/2 - START_WIDTH/2, GAME_HEIGHT/2 - START_HEIGHT/2, START_WIDTH, START_HEIGHT };

//math constants
const double PI = 3.141592653589793;

#endif
