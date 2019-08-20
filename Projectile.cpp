#include "Projectile.h"

Projectile::Projectile(int x, int y, int angle) {
    texture = NULL;
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->speed = PROJECTILE_STARTING_SPEED;
    this->width = PROJECTILE_WIDTH;
    this->height = PROJECTILE_HEIGHT;
}
Projectile::~Projectile() {
    delete texture;
}
void Projectile::draw() {
    texture->render(x, y, angle, width, height, 0);
}
void Projectile::load(std::string path) {
    if (texture != NULL) {
        delete texture;
    }
    texture = new ObjTexture();
    texture->load(path, 1, 1);
}
