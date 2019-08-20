#include "Survivor.h"
#include "Constants.h"
#include "Map.h"

Survivor::Survivor(int x, int y) {
    texture = NULL;
    this->x = x;
    this->y = y;
    this->moving = false;
    this->angle = SURVIVOR_STARTING_ANGLE;
    this->speed = SURVIVOR_STARTING_SPEED;
    this->width = SURVIVOR_WIDTH;
    this->height = SURVIVOR_HEIGHT;
}
Survivor::~Survivor() {
    delete texture;
}
void Survivor::update(std::string dir) {
    if (dir == "LEFT") {
        angle = angle + 5;
    } else if (dir == "RIGHT") {
        angle = angle - 5;
    } else if (dir == "UP") {
        move("FORWARD");
    } else if (dir == "DOWN") {
        move("BACKWARD");
    }
}
void Survivor::move(std::string dir) {
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
}
void Survivor::draw(int anim_index) {
    texture->render(x, y, angle, width, height, anim_index);
}
void Survivor::load(std::string path, int anim_rows, int anim_cols) {
    if (texture != NULL) {
        delete texture;
    }
    texture = new ObjTexture();
    texture->load(path, anim_rows, anim_cols);
}
