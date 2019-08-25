#ifndef MAP_H
#define MAP_H

#include "ObjTexture.h"
#include "Constants.h"
#include <string>
#include <vector>
#include <stdio.h>

class Map {
    public:
        Map(int num_textures, std::string* texture_names, 
                int rows, int cols, int tile_width, int tile_height);
        ~Map();

        void draw();
        void load();

        int getTileWidth() { return tile_width; }
        int getTileHeight() { return tile_height; }
        int getRows() { return rows; }
        int getCols() { return cols; }
        int getRow(int y) { return y/tile_height; }
        int getCol(int x) { return x/tile_width; }

        int getTileValue(int x, int y);
        int getPathValue(int x, int y);
        int getTileIndex(int x, int y);
        bool onMap(int x, int y, int width, int height);
        bool isWall(int x, int y, int width, int height);
        void fillMap1();
        void initPath(int size);
        void updatePath();
        //ObjTexture* getTexture() { return texture; }

    private:
        std::vector<ObjTexture*> textures;
        //std::vector<ObjTexture> textures;
        int* tiles;
        int* path_to_survivor;
        int num_textures;
        std::string* texture_names;
        int rows;
        int cols;
        int tile_width;
        int tile_height;
};

#endif
