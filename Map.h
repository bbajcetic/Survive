#ifndef MAP_H
#define MAP_H

#include "ObjTexture.h"
#include "Constants.h"
#include <string>
#include <vector>
#include <queue>
#include <stdio.h>

class Map {
    public:
        Map(int num_textures, std::string* texture_names, 
                int rows, int cols, int tile_width, int tile_height);
        ~Map();

        void draw();
        bool load();

        int getTileWidth() { return tile_width; }
        int getTileHeight() { return tile_height; }
        int getRows() { return rows; }
        int getCols() { return cols; }
        int getRow(int y) { return y/tile_height; }
        int getCol(int x) { return x/tile_width; }

        int getTileValue(int x, int y);
        int getPathValue(int index);
        int getPathValue(int x, int y);
        int getTileIndex(int x, int y);
        int getXFromIndex(int index);
        int getYFromIndex(int index);
        bool isRightEdge(int index);
        bool isLeftEdge(int index);
        bool onMap(int index);
        bool onMap(int x, int y, int width, int height);
        bool isWall(int x, int y, int width, int height);
        void resetMap();
        void fillMap1();
        void initPath(int size);
        void printPath();
        void updatePath(int x, int y);
        //ObjTexture* getTexture() { return texture; }

    private:
        std::vector<ObjTexture*> textures;
        //std::vector<ObjTexture> textures;
        int* tiles;
        int* survivor_path;
        int num_textures;
        std::string* texture_names;
        int rows;
        int cols;
        int tile_width;
        int tile_height;
};

#endif
