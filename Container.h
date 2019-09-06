#ifndef CONTAINER_H
#define CONTAINER_H

#include <SDL2/SDL.h>
#include <string>
#include "ObjTexture.h"

extern SDL_Renderer* gRenderer;
extern ObjTexture gTextTexture;

class Container {
    public:
        Container(SDL_Rect box, int rows, int cols, SDL_Color color);
        void render();
        void outline(int width);
        bool inButton(int posX, int posY);
        void write(std::string text, int row, int col, int offX, int offY, int angle = 0);
        void writeCenter(std::string text, int row, int offY);

        int colToX(int col);
        int rowToY(int row);

        int getX() { return x; }
        int getY() { return y; }

        void setColor(SDL_Color color) { this->color = color; }

    private:
        int x;
        int y;
        int width;
        int height;
        int rows;
        int cols;
        SDL_Color color;
};

#endif
