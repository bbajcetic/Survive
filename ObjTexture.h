#ifndef OBJTEXTURE_H
#define OBJTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

extern SDL_Renderer* gRenderer;
extern int global_count;

class ObjTexture {
    public:
        ObjTexture();
//        ObjTexture(ObjTexture& oldObj);
        ~ObjTexture();

        bool load(std::string path, int anim_rows, int anim_cols);
        void render(int x, int y, int angle, int width, int height, int anim_index);
        void free_();

        SDL_Texture* getTexture() { return texture; }
        std::string getFileName() { return file_name; }
        int getWidth() { return width; }
        int getHeight() { return height; }
        int getAnimCols() { return anim_cols; }
        int getAnimRows() { return anim_rows; }
        void setAnimCols(int anim_cols) { this->anim_cols = anim_cols; }
        void setAnimRows(int anim_rows) { this->anim_rows = anim_rows; }

    private:
        SDL_Texture* texture;
        std::string file_name;
        int width;
        int height;
        int anim_rows; //number of rows in the animation sprite
        int anim_cols; //number of columns in the animation sprite
};

#endif

