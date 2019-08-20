#include "Map.h"

Map::Map(int* tiles, int num_textures, std::string* texture_names, 
        int rows, int cols, int tile_width, int tile_height) {
    textures = NULL;
    this->tiles = tiles;
    this->num_textures = num_textures;
    this->texture_names = texture_names;
    this->rows = rows;
    this->cols = cols;
    this->tile_width = tile_width;
    this->tile_height = tile_height;
}
Map::~Map() {
    for (int i = 0; i < num_textures; ++i) {
        delete textures[i];
    }
    delete [] textures;
}
bool Map::onMap(int x, int y, int width, int height) {
    if (x > 0 && (x+width) < (cols*tile_width)) {
        if (y > 0 && (y+height) < (rows*tile_height)) {
            return true;
        }
    }
    return false;
}
bool Map::isWall(int x, int y, int width, int height) {
    if (!onMap(x, y, width, height)) { return true; }
    int row, col, tile_value;
    row = y/tile_height;
    col = x/tile_width;
    if (getTileValue(row, col) != 0) { return true; }
    col = (x+width)/tile_width;
    if (getTileValue(row, col) != 0) { return true; }
    row = (y+height)/tile_height;
    if (getTileValue(row, col) != 0) { return true; }
    col = x/tile_width;
    if (getTileValue(row, col) != 0) { return true; }
    return false;
}
int Map::getTileValue(int row, int col) {
    return (*(tiles+(row*cols)+col));
}
void Map::draw() {
    int curr_tile;
    int type;
    int angle;
    int x, y;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            curr_tile = *(tiles+(i*cols)+j);
            type = curr_tile/4;
            angle = (curr_tile%4) * 90;
            x = tile_width * j;
            y = tile_height * i;
            (*(textures+type))->render(x, y, angle, tile_width, tile_height, 0);
        }
    }
}
void Map::load() {
    textures = new ObjTexture*[num_textures];
    for (int i = 0; i < num_textures; ++i) {
        //*(textures+i) = new ObjTexture;
        textures[i] = new ObjTexture;
        //(*(textures+i))->load(*(texture_names+i), 1, 1);
        (textures[i])->load(*(texture_names+i), 1, 1);
    }
}
