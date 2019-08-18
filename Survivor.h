#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "ObjTexture.h"

class Survivor {
    public:
        Survivor(int x, int y, int width, int height);
        ~Survivor();

        void draw(int anim_index);
        void load(std::string path, int anim_rows, int anim_cols);
        void free();

        int getWidth() { return width; }
        int getHeight() { return height; }
        int getX() { return x; }
        int getY() { return y; }
        int getDirection() { return direction; }
        ObjTexture* getTexture() { return texture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setDirection(int dir) { this->direction = dir; }


    private:
        ObjTexture* texture;
        int width;
        int height;
        int x;
        int y;
        int direction; //0 = left, 1 = up, 2 = right, 3 = down
};

#endif
