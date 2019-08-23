#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>
#include "ObjTexture.h"
#include "Map.h"
#include "Constants.h"

extern Map map;

class Projectile {
    public:
        Projectile(int x, int y, int angle);
        ~Projectile();

        bool update();
        void draw();
        void load(std::string path);

        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return x; }
        float getY() { return y; }
        int getAngle() { return angle; }
        int getSpeed() { return speed; }
        //ObjTexture* getTexture() { return objTexture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }


    private:
        ObjTexture objTexture;
        float x;
        float y;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
};

#endif