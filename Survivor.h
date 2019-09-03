#ifndef SURVIVOR_H
#define SURVIVOR_H

#include <string>
#include <cmath>
#include <vector>
#include "ObjTexture.h"
#include "Map.h"
#include "Projectile.h"
#include "Vec2D.h"
#include "CustomMath.h"

extern std::vector<Projectile*> projectiles;
extern Map map;
extern int score;

class Survivor {
    public:
        Survivor(int x, int y);
        ~Survivor();

        void resetWave();
        void resetGame();
        bool canMove(int current_time);
        void turn(int x, int y);
        void update(std::string dir, int current_time);
        void move(std::string dir);
        void shoot(int current_time);
        bool takeDamage(int damage);
        void buyHealth(int health, int cost);
        void buyAmmo(int ammo, int cost);
        void draw();
        void drawHitBox();
        Vec2D getHitBox();
        bool load(std::string path, int anim_rows, int anim_cols);
        bool changedTiles();

        int getWidth() { return width; }
        int getHeight() { return height; }
        /* get x value of center of object */
        float getX() { return x + float(width)/2.0; }
        /* get y value of center of object */
        float getY() { return y + float(height)/2.0; }
        /* get last x value of center of object */
        float getLastX() { return last_x + float(width)/2.0; }
        /* get last y value of center of object */
        float getLastY() { return last_y + float(height)/2.0; }
        bool getMoving() { return moving; }
        int getAngle() { return angle; }
        int getSpeed() { return speed; }
        int getHealth() { return health; }
        int getAmmo() { return ammo; }
        //ObjTexture* getTexture() { return objTexture; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setLastX(int x) { this->last_x = x; }
        void setLastY(int y) { this->last_y = y; }
        void setMoving(bool moving) { this->moving = moving; }
        void setLastMove(int last_move) { this->last_move = last_move; }
        void setAngle(int angle) { this->angle = angle; }
        void setSpeed(int speed) { this->speed = speed; }
        void setHealth(int health) { this->health = health; }
        void setAmmo(int ammo) { this->ammo = ammo; }


    private:
        ObjTexture* objTexture;
        //ObjTexture* objTexture;
        int health;
        int ammo;
        float x;
        float y;
        float last_x;
        float last_y;
        bool moving;
        int angle; //0 - 360
        int speed;
        int width;
        int height;
        int frame;
        int last_move;
        int last_turn;
        int last_shot;
};

#endif
