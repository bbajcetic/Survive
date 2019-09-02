#include "Survivor.h"
#include "Constants.h"
#include "Map.h"

Survivor::Survivor(int x, int y) {
    //printf("---Entering Survivor constructor\n");
    this->objTexture = new ObjTexture();
    this->x = x;
    this->y = y;
    this->last_x = x;
    this->last_y = y;
    this->moving = false;
    this->angle = SURVIVOR_STARTING_ANGLE;
    this->speed = SURVIVOR_STARTING_SPEED;
    this->width = SURVIVOR_WIDTH;
    this->height = SURVIVOR_HEIGHT;
    this->health = SURVIVOR_STARTING_HEALTH;
    this->ammo = SURVIVOR_STARTING_AMMO;
    this->frame = 0;
    this->last_move = 0;
    this->last_turn = 0;
    this->last_shot = 0;
    //printf("---Leaving Survivor constructor\n");
}
Survivor::~Survivor() {
    //printf("---Entering Survivor destructor\n");
    delete objTexture;
    objTexture = NULL;
    //printf("---Leaving Survivor destructor\n");
}
void Survivor::resetWave() {
    this->last_x = x;
    this->last_y = y;
    this->moving = false;
    this->frame = 0;
    this->last_move = 0;
    this->last_turn = 0;
    this->last_shot = 0;
}
void Survivor::resetGame() {
    this->x = SURVIVOR_STARTING_X;
    this->y = SURVIVOR_STARTING_Y;
    this->last_x = x;
    this->last_y = y;
    this->moving = false;
    this->angle = SURVIVOR_STARTING_ANGLE;
    this->speed = SURVIVOR_STARTING_SPEED;
    this->width = SURVIVOR_WIDTH;
    this->height = SURVIVOR_HEIGHT;
    this->health = SURVIVOR_STARTING_HEALTH;
    this->ammo = SURVIVOR_STARTING_AMMO;
    this->frame = 0;
    this->last_move = 0;
    this->last_turn = 0;
    this->last_shot = 0;
}
bool Survivor::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    printf("Survivor health = %d\n", health);
    if (health <= 0) {
        return false;
    }
    return true;
}
Vec2D Survivor::getHitBox() {
    Vec2D temp(SURVIVOR_HITBOX_WIDTH, SURVIVOR_HITBOX_HEIGHT);
    return temp;
}

bool Survivor::changedTiles() {
    //printf("---Entering Survivor::changedTiles\n");
    int curr_tile = map.getTileIndex(getX(), getY());
    int last_tile = map.getTileIndex(getLastX(), getLastY());
    if (curr_tile != last_tile) {
        //printf("---Leaving Survivor::changedTiles\n");
        return true;
    }
    //printf("---Leaving Survivor::changedTiles\n");
    return false;
}
//void Survivor::move(std::string dir) {
//    //printf("---Entering Survivor::move\n");
//    float rad = float(angle) * (PI/float(180));
//    float move_x = float(speed) * (cos(float(rad)));
//    float move_y = float(speed) * (sin(float(rad)));
//    float temp_x, temp_y;
//    //printf("rad = %f, move_x = %f, move_y = %f\n", rad, move_x, move_y);
//    if (dir == "FORWARD") {
//        temp_x = x + move_x;
//        temp_y = y + move_y;
//    } else if (dir == "BACKWARD") {
//        temp_x = x - move_x;
//        temp_y = y - move_y;
//    }
//    if (!map.isWall(temp_x, temp_y, width, height)) {
//        x = temp_x;
//        y = temp_y;
//    } else if (!map.isWall(temp_x, y, width, height)) {
//        x = temp_x;
//    } else if (!map.isWall(x, temp_y, width, height)) {
//        y = temp_y;
//    }
//    //printf("---Leaving Survivor::move\n");
//}
bool Survivor::canMove(int current_time) {
    if (current_time - last_move < SURVIVOR_TIME_PER_MOVE) {
        return false;
    }
    return true;
}
void Survivor::turn(int x, int y) {
    float to_x = x - getX();
    float to_y = y - getY();
    float new_angle = findAngle(to_x, to_y);
    angle = int( new_angle * 180.0/PI );
}
void Survivor::update(std::string dir, int current_time) {
    //printf("---Entering Survivor::update\n");
    if (!canMove(current_time)) {
        return;
    }
    if ( moving == false ) {
        moving = true;
        frame = 0;
    }
    float temp_x = x;
    float temp_y = y;

    if (dir == "LEFT") {
        temp_x = x - float(speed);
    } else if (dir == "RIGHT") {
        temp_x = x + float(speed);
    } else if (dir == "UP") {
        temp_y = y - float(speed);
    } else if (dir == "DOWN") {
        temp_y = y + float(speed);
    }
    if (!map.isWall(temp_x, temp_y, width, height)) {
        x = temp_x;
        y = temp_y;
    } else if (!map.isWall(temp_x, y, width, height)) {
        x = temp_x;
    } else if (!map.isWall(x, temp_y, width, height)) {
        y = temp_y;
    }
    //printf("---Leaving Survivor::move\n");
    //last_move = current_time;
    frame = (frame + 1) % (SURVIVOR_NUM_SPRITES*SURVIVOR_FRAMES_PER_ANIMATION);

    //printf("---Leaving Survivor::update\n");
}
    
//void Survivor::update(std::string dir, int current_time) {
//    //printf("---Entering Survivor::update\n");
//    if (dir == "UP" || dir == "DOWN") {
//        if (current_time - last_move < SURVIVOR_TIME_PER_MOVE) {
//            return;
//        }
//    }
//    else if (dir == "LEFT" || dir == "RIGHT") {
//        if (current_time - last_turn < SURVIVOR_TIME_PER_TURN) {
//            return;
//        }
//    }
//
//    if ( moving == false && (dir == "UP" || dir == "DOWN") ) {
//        moving = true;
//        frame = 0;
//    }
//    if (dir == "LEFT") {
//        angle = angle - SURVIVOR_SENSITIVITY;
//    } else if (dir == "RIGHT") {
//        angle = angle + SURVIVOR_SENSITIVITY;
//    } else if (dir == "UP") {
//        move("FORWARD");
//    } else if (dir == "DOWN") {
//        move("BACKWARD");
//    }
//    if (dir == "UP" || dir == "DOWN") {
//        last_move = current_time;
//    } else if (dir == "LEFT" || dir == "RIGHT") {
//        last_turn = current_time;
//    }
//    frame = (frame + 1) % (SURVIVOR_NUM_SPRITES*SURVIVOR_FRAMES_PER_ANIMATION);
//
//    //printf("---Leaving Survivor::update\n");
//}
//void Survivor::move(std::string dir) {
//    //printf("---Entering Survivor::move\n");
//    float rad = float(angle) * (PI/float(180));
//    float move_x = float(speed) * (cos(float(rad)));
//    float move_y = float(speed) * (sin(float(rad)));
//    float temp_x, temp_y;
//    //printf("rad = %f, move_x = %f, move_y = %f\n", rad, move_x, move_y);
//    if (dir == "FORWARD") {
//        temp_x = x + move_x;
//        temp_y = y + move_y;
//    } else if (dir == "BACKWARD") {
//        temp_x = x - move_x;
//        temp_y = y - move_y;
//    }
//    if (!map.isWall(temp_x, temp_y, width, height)) {
//        x = temp_x;
//        y = temp_y;
//    } else if (!map.isWall(temp_x, y, width, height)) {
//        x = temp_x;
//    } else if (!map.isWall(x, temp_y, width, height)) {
//        y = temp_y;
//    }
//    //printf("---Leaving Survivor::move\n");
//}
void Survivor::shoot(int current_time) {
    //printf("---Entering Survivor::shoot\n");
    if (current_time - last_shot < SURVIVOR_TIME_PER_SHOT) {
        return;
    }
    if (ammo <= 0) {
        printf("OUT OF AMMO\n");
        return;
    }
    float temp_x, temp_y, temp_h;
    float rad = float(angle) * (PI/float(180));
    temp_h = 1.0 * (0.5*float(width));
    temp_x = (x+0.5*float(width)) + temp_h * cos(rad);
    temp_y = (y+0.5*float(height)) + temp_h * sin(rad);
    Projectile* temp = new Projectile(temp_x, temp_y, angle);
    temp->load("Projectile.png");
    projectiles.push_back(temp);

    ammo -= 1;
    if (ammo < 0) {
        ammo = 0;
    }
    last_shot = current_time;
    //printf("NEW PROJECTILE SIZE = %d\n", projectiles.size());
    //printf("---Leaving Survivor::shoot\n");
}

void Survivor::drawHitBox() {
    SDL_Rect hitbox = { int(getX()-SURVIVOR_HITBOX_WIDTH/2.0), int(getY()-SURVIVOR_HITBOX_HEIGHT/2.0), SURVIVOR_HITBOX_WIDTH, SURVIVOR_HITBOX_HEIGHT };
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF ); //green
    SDL_RenderDrawRect( gRenderer, &hitbox );
}
void Survivor::draw() {
    //printf("---Entering Survivor::draw\n");

    //draw sprite
    int anim_index = 1; //index 1 is non moving sprite
    if (moving) { anim_index = frame/SURVIVOR_FRAMES_PER_ANIMATION; }
    objTexture->render(x, y, angle, width, height, anim_index);

    //draw hitbox
    drawHitBox();
    
    //draw Survivor health bar
    int filled_length = int( float(health)/float(SURVIVOR_STARTING_HEALTH) * float(HEALTH_BAR_WIDTH) );
    int health_red_x = int(x);
    int health_green_x = int( x+(HEALTH_BAR_WIDTH-filled_length) );
    SDL_Rect redRect = { health_red_x, int(y+height), HEALTH_BAR_WIDTH-filled_length, HEALTH_BAR_HEIGHT*2 };
    SDL_Rect greenRect = { health_green_x, int(y+height), filled_length, HEALTH_BAR_HEIGHT*2 };

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF ); //green
    SDL_RenderFillRect( gRenderer, &greenRect );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF ); //red
    SDL_RenderFillRect( gRenderer, &redRect );

    //printf("---Leaving Survivor::draw\n");
}
bool Survivor::load(std::string path, int anim_rows, int anim_cols) {
    //printf("---Entering Survivor::load\n");

    return objTexture->load(path, anim_rows, anim_cols);
    
    //printf("---Leaving Survivor::load\n");
}
