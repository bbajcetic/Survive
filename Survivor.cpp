#include "Survivor.h"
#include "Constants.h"

Survivor::Survivor(int x, int y, int width, int height) {
    texture = NULL;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->direction = SURVIVOR_STARTING_DIRECTION;
}
Survivor::~Survivor() {
    delete texture;
}
void Survivor::draw(int anim_index) {
    texture->render(x, y, width, height, anim_index);
}
void Survivor::load(std::string path, int anim_rows, int anim_cols) {
    if (texture != NULL) {
        delete texture;
    }
    texture = new ObjTexture();
    texture->load(path, anim_rows, anim_cols);
}
