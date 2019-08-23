#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include "ObjTexture.h"
#include "Map.h"
#include "Constants.h"

extern Map map;
extern SDL_Renderer* gRenderer;

class Zombie {
    public:
        Zombie(int x, int y, int angle);
        ~Zombie();

        bool update();
        void draw(int anim_index);
        void drawHitBox();
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
        void setMoving(int moving) { this->moving = moving; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }


    private:
        ObjTexture* objTexture;
        float x;
        float y;
        bool moving;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
};

#endif
