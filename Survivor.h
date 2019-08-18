#ifndef SURVIVOR_H
#define SURVIVOR_H

#include <string>
#include <cmath>
#include "ObjTexture.h"

class Survivor {
    public:
        Survivor(int x, int y);
        ~Survivor();

        void update(std::string dir);
        void move(std::string dir);
        void draw(int anim_index);
        void load(std::string path, int anim_rows, int anim_cols);
        void free();

        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return x; }
        float getY() { return y; }
        bool getMoving() { return moving; }
        int getDirection() { return direction; }
        int getAngle() { return angle; }
        int getSpeed() { return speed; }
        ObjTexture* getTexture() { return texture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setMoving(bool moving) { this->moving = moving; }
        void setDirection(int dir) { this->direction = dir; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }


    private:
        ObjTexture* texture;
        float x;
        float y;
        bool moving;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
        int direction; //0 = left, 1 = up, 2 = right, 3 = down
};

#endif
