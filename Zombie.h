#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "ObjTexture.h"
#include "Map.h"
#include "Constants.h"

extern Map map;
extern SDL_Renderer* gRenderer;

class Zombie {
    public:
        Zombie(int x, int y, int angle);
        ~Zombie();

        void update();
        void turn();
        void move();
        void updateNext();
        void draw();
        void drawHitBox();
        bool takeDamage();
        void load(std::string path, int anim_rows, int anim_cols);

        int getWidth() { return width; }
        int getHeight() { return height; }
        /* get x value of center of object */
        float getX() { return x + float(width)/2.0; }
        /* get y value of center of object */
        float getY() { return y + float(height)/2.0; }
        bool getMoving() { return moving; }
        int getAngle() { return angle; }
        int getSpeed() { return speed; }
        //ObjTexture* getTexture() { return objTexture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setMoving(int moving) { this->moving = moving; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }


    private:
        ObjTexture* objTexture;
        float x;
        float y;
        int angle; //0 - 360
        float next_x;
        float next_y;
        float next_angle;
        bool moving;
        int speed;
        int width;
        int height;
        int frame;
};

#endif
