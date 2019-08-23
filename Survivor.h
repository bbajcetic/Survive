#ifndef SURVIVOR_H
#define SURVIVOR_H

#include <string>
#include <cmath>
#include <vector>
#include "ObjTexture.h"
#include "Map.h"
#include "Projectile.h"

extern std::vector<Projectile*> projectiles;
extern Map map;

class Survivor {
    public:
        Survivor(int x, int y);
        ~Survivor();

        void update(std::string dir);
        void move(std::string dir);
        void shoot();
        void draw(int anim_index);
        void load(std::string path, int anim_rows, int anim_cols);

        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return x; }
        float getY() { return y; }
        bool getMoving() { return moving; }
        int getAngle() { return angle; }
        int getSpeed() { return speed; }
        //ObjTexture* getTexture() { return objTexture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setMoving(bool moving) { this->moving = moving; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }


    private:
        ObjTexture* objTexture;
        //ObjTexture* objTexture;
        float x;
        float y;
        bool moving;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
};

#endif
