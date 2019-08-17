#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "ObjTexture.h"

class Survivor {
    public:
        Survivor(int width, int height);
        ~Survivor();

        void draw(int x, int y, int anim_index);
        void load(std::string path, int anim_rows, int anim_cols);
        void free();

        int getWidth() { return width; }
        int getHeight() { return height; }

    private:
        ObjTexture* texture;
        int width;
        int height;
};

#endif
