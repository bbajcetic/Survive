#include "Projectile.h"

Projectile::Projectile(int x, int y, int angle) {
    //printf("---Entering Projectile constructor\n");
    //objTexture = NULL;
    this->objTexture = new ObjTexture();
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->speed = PROJECTILE_STARTING_SPEED;
    this->width = PROJECTILE_WIDTH;
    this->height = PROJECTILE_HEIGHT;
    this->damage = PROJECTILE_STARTING_DAMAGE;
    //printf("---Leaving Projectile constructor\n");
}
Projectile::~Projectile() {
    //printf("---Entering Projectile destructor\n");
    delete objTexture;
    objTexture = NULL;
    //printf("---Leaving Projectile destructor\n");
}
bool Projectile::update() {
    //printf("---Entering Projectile::update\n");
    float rad = float(angle) * (PI/float(180));
    float move_x = float(speed) * (cos(float(rad)));
    float move_y = float(speed) * (sin(float(rad)));
    float temp_x, temp_y;
    temp_x = x + move_x;
    temp_y = y + move_y;
    if (!map.isWall(temp_x, temp_y, width, height)) {
        x = temp_x;
        y = temp_y;
        //printf("new x, y = %f, %f\n", x, y);
        //printf("---Leaving Projectile::update\n");
        return true;
    }
    //printf("---Leaving Projectile::update\n");
    return false;
}
void Projectile::draw() {
    //printf("---Entering Projectile::draw\n");
    objTexture->render(x, y, width, height, angle);
    drawHitBox();
    //printf("---Leaving Projectile::draw\n");
}
void Projectile::drawHitBox() {
    SDL_Rect hitbox = {int((x+0.25*float(width))-1.0), int((y+0.25*float(height))-1.0), int(float(width)/2.0+2.0), int(float(height)/2.0+2.0)};
    //SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 255); //green
    //SDL_RenderDrawRect(gRenderer, &hitbox);
}
void Projectile::load(std::string path) {
    //printf("---Entering Projectile::load\n");
    //if (objTexture != NULL) {
    //    delete objTexture;
    //}
    //objTexture = new ObjTexture();
    objTexture->load(path, 1, 1);
    //objTexture.load(path, 1, 1);
    printf("---Leaving Projectile::load\n");
}
