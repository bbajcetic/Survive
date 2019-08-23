#include "Zombie.h"

Zombie::Zombie(int x, int y, int angle) {
    printf("---Entering Zombie constructor\n");
    //objTexture = NULL;
    this->objTexture = new ObjTexture();
    this->x = x;
    this->y = y;
    this->moving = false;
    this->angle = angle;
    this->speed = ZOMBIE_STARTING_SPEED;
    this->width = ZOMBIE_WIDTH;
    this->height = ZOMBIE_HEIGHT;
    printf("---Leaving Zombie constructor\n");
}
Zombie::~Zombie() {
    printf("---Entering Zombie destructor\n");
    delete objTexture;
    objTexture = NULL;
    printf("---Leaving Zombie destructor\n");
}
bool Zombie::update() {
    printf("---Entering Zombie::update\n");
    float rad = float(angle) * (PI/float(180));
    float move_x = float(speed) * (cos(float(rad)));
    float move_y = float(speed) * (sin(float(rad)));
    float temp_x, temp_y;
    temp_x = x + move_x;
    temp_y = y - move_y;
    if (!map.isWall(temp_x, temp_y, width, height)) {
        x = temp_x;
        y = temp_y;
        //printf("new x, y = %f, %f\n", x, y);
        printf("---Leaving Zombie::update\n");
        return true;
    }
    printf("---Leaving Zombie::update\n");
    return false;
}
void Zombie::draw(int anim_index) {
    printf("---Entering Zombie::draw\n");
    objTexture->render(x, y, angle, width, height, anim_index);
    //objTexture.render(x, y, angle, width, height, 0);
    printf("---Leaving Zombie::draw\n");
}
void Zombie::load(std::string path, int anim_rows, int anim_cols) {
    printf("---Entering Zombie::load\n");
    //if (objTexture != NULL) {
    //    delete objTexture;
    //}
    //objTexture = new ObjTexture();
    objTexture->load(path, anim_rows, anim_cols);
    //objTexture.load(path, 1, 1);
    printf("---Leaving Zombie::load\n");
}
