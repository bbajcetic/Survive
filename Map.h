#ifndef MAP_H
#define MAP_H

#include "ObjTexture.h"
#include <string>

class Map {
    public:
        Map(int* tiles, int num_textures, std::string* texture_names, 
                int rows, int cols, int tile_width, int tile_height);
        ~Map();

        void draw();
        void load();

        int getTileWidth() { return tile_width; }
        int getTileHeight() { return tile_height; }
        int getRows() { return rows; }
        int getCols() { return cols; }

        int getTileValue(int row, int col);
        bool onMap(int x, int y, int width, int height);
        bool isWall(int x, int y, int width, int height);
        //ObjTexture* getTexture() { return texture; }

    private:
        ObjTexture** textures;
        int* tiles;
        int num_textures;
        std::string* texture_names;
        int rows;
        int cols;
        int tile_width;
        int tile_height;
};

#endif
