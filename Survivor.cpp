#include "Survivor.h"
#include "Constants.h"
#include "Map.h"

Survivor::Survivor(int x, int y) {
    printf("---Entering Survivor constructor\n");
    this->objTexture = new ObjTexture();
    this->x = x;
    this->y = y;
    this->moving = false;
    this->angle = SURVIVOR_STARTING_ANGLE;
    this->speed = SURVIVOR_STARTING_SPEED;
    this->width = SURVIVOR_WIDTH;
    this->height = SURVIVOR_HEIGHT;
    printf("---Leaving Survivor constructor\n");
}
Survivor::~Survivor() {
    printf("---Entering Survivor destructor\n");
    delete objTexture;
    objTexture = NULL;
    printf("---Leaving Survivor destructor\n");
}
void Survivor::update(std::string dir) {
    printf("---Entering Survivor::update\n");
    if (dir == "LEFT") {
        angle = angle + 5;
    } else if (dir == "RIGHT") {
        angle = angle - 5;
    } else if (dir == "UP") {
        move("FORWARD");
    } else if (dir == "DOWN") {
        move("BACKWARD");
    }
    printf("---Leaving Survivor::update\n");
}
void Survivor::move(std::string dir) {
    printf("---Entering Survivor::move\n");
    float rad = float(angle) * (PI/float(180));
    float move_x = float(speed) * (cos(float(rad)));
    float move_y = float(speed) * (sin(float(rad)));
    float temp_x, temp_y;
    //printf("rad = %f, move_x = %f, move_y = %f\n", rad, move_x, move_y);
    if (dir == "FORWARD") {
        temp_x = x + move_x;
        temp_y = y - move_y;
    } else if (dir == "BACKWARD") {
        temp_x = x - move_x;
        temp_y = y + move_y;
    }
    if (!map.isWall(temp_x, temp_y, width, height)) {
        x = temp_x;
        y = temp_y;
    } else if (!map.isWall(temp_x, y, width, height)) {
        x = temp_x;
    } else if (!map.isWall(x, temp_y, width, height)) {
        y = temp_y;
    }
    printf("---Leaving Survivor::move\n");
}
void Survivor::shoot() { //fix to use origin instead of top left of objTexture
    printf("---Entering Survivor::shoot\n");
    float temp_x, temp_y, temp_h;
    float rad = float(angle) * (PI/float(180));
    temp_h = 1.5 * (0.5*float(width));
    temp_x = (x+0.5*float(width)) + temp_h * cos(rad);
    temp_y = (y+0.5*float(height)) - temp_h * sin(rad);
    //Projectile temp(temp_x, temp_y, angle);
    Projectile* temp = new Projectile(temp_x, temp_y, angle);
    //temp.load("Projectile.png");
    temp->load("Projectile.png");
    projectiles.push_back(temp);
    printf("NEW PROJECTILE SIZE = %d\n", projectiles.size());
    printf("---Leaving Survivor::shoot\n");
}
void Survivor::draw(int anim_index) {
    printf("---Entering Survivor::draw\n");
    objTexture->render(x, y, angle, width, height, anim_index);
    //this->objTexture.render(x, y, angle, width, height, anim_index);
    printf("---Leaving Survivor::draw\n");
}
void Survivor::load(std::string path, int anim_rows, int anim_cols) {
    printf("---Entering Survivor::load\n");
    //if (objTexture != NULL) {
    //    delete objTexture;
    //}
    //objTexture = new ObjTexture();
    objTexture->load(path, anim_rows, anim_cols);
    //objTexture.load(path, anim_rows, anim_cols);
    printf("---Leaving Survivor::load\n");
}
