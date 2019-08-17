#include "Survivor.h"

Survivor::Survivor(int width, int height) {
    texture = NULL;
    this->width = width;
    this->height = height;
}
Survivor::~Survivor() {
    delete texture;
}
void Survivor::draw(int x, int y, int anim_index) {
    texture->render(x, y, width, height, anim_index);
}
void Survivor::load(std::string path, int anim_rows, int anim_cols) {
    texture->load(path, anim_rows, anim_cols);
}
