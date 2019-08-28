#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>
#include "ObjTexture.h"
#include "Map.h"
#include "Constants.h"

extern Map map;
extern SDL_Renderer* gRenderer;

class Projectile {
    public:
        Projectile(int x, int y, int angle);
        ~Projectile();

        bool update();
        void draw();
        void drawHitBox();
        void load(std::string path);

        int getWidth() { return width; }
        int getHeight() { return height; }
        float getX() { return x + float(width)/2.0; }
        float getY() { return y + float(height)/2.0; }
        int getAngle() { return angle; }
        float getRadians() { return float(angle) * PI/float(180); }
        int getSpeed() { return speed; }
        int getDamage() { return damage; }
        //ObjTexture* getTexture() { return objTexture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }
        void setDamage(int damage) { this->damage = damage; }


    private:
        ObjTexture* objTexture;
        int damage;
        float x;
        float y;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
};

#endif
