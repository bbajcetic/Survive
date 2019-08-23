#include "Map.h"

Map::Map(int* tiles, int num_textures, std::string* texture_names, 
        int rows, int cols, int tile_width, int tile_height) {
    printf("---Entering Map constructor\n");
    //textures = NULL;
    this->tiles = tiles;
    this->num_textures = num_textures;
    this->texture_names = texture_names;
    this->rows = rows;
    this->cols = cols;
    this->tile_width = tile_width;
    this->tile_height = tile_height;
    printf("---Leaving Map constructor\n");
}
Map::~Map() {
    printf("---Entering Map destructor\n");
    //for (int i = 0; i < num_textures; ++i) {
    //    delete textures[i];
    //}
    textures.clear();
    printf("---Leaving Map destructor\n");
}
//Map::~Map() {
//    //for (int i = 0; i < num_textures; ++i) {
//    //    delete textures[i];
//    //    textures[i] = NULL;
//    //}
//    delete [] textures;
//    textures = NULL;
//}
bool Map::onMap(int x, int y, int width, int height) {
    printf("---Entering Map::onMap\n");
    if (x > 0 && (x+width) < (cols*tile_width)) {
        if (y > 0 && (y+height) < (rows*tile_height)) {
            printf("---Leaving Map::onMap\n");
            return true;
        }
    }
    printf("---Leaving Map::onMap\n");
    return false;
}
bool Map::isWall(int x, int y, int width, int height) {
    printf("---Entering Map::isWall\n");
    if (!onMap(x, y, width, height)) { printf("---Leaving Map::isWall\n");return true; }
    int row, col, tile_value;
    row = y/tile_height;
    col = x/tile_width;
    if (getTileValue(row, col) != 0) { printf("---Leaving Map::isWall\n");return true; }
    col = (x+width)/tile_width;
    if (getTileValue(row, col) != 0) { printf("---Leaving Map::isWall\n");return true; }
    row = (y+height)/tile_height;
    if (getTileValue(row, col) != 0) { printf("---Leaving Map::isWall\n");return true; }
    col = x/tile_width;
    if (getTileValue(row, col) != 0) { printf("---Leaving Map::isWall\n");return true; }
    printf("---Leaving Map::isWall\n");
    return false;
}
int Map::getTileValue(int row, int col) {
    printf("---Entering Map::getTileValue\n");
    printf("---Leaving Map::getTileValue\n");
    return (*(tiles+(row*cols)+col));
}
void Map::draw() {
    printf("---Entering Map::draw\n");
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
            //(*(textures+type))->render(x, y, angle, tile_width, tile_height, 0);
            //textures[type]->render(x, y, angle, tile_width, tile_height, 0);
            //printf("TYPE=%d\n", type);
            //printf("rendering texture %s\n", textures[type].getFileName().c_str());
            //printf("address = %p\n", &textures[type]);
            this->textures[type].render(x, y, angle, tile_width, tile_height, 0);
        }
    }
    printf("---Leaving Map::draw\n");
}
void Map::load() {
    printf("---Entering Map::load\n");
    for (int i = 0; i < num_textures; ++i) {
        ObjTexture temp;
        printf("LOADING %s\n", texture_names[i].c_str());
        temp.load(texture_names[i], 1, 1);
        //ObjTexture* temp = new ObjTexture;
        //temp->load(texture_names[i], 1, 1);
        this->textures.push_back(temp);
    }
    printf("---Leaving Map::load\n");
}
//void Map::load() {
//    textures = new ObjTexture*[num_textures];
//    for (int i = 0; i < num_textures; ++i) {
//        //*(textures+i) = new ObjTexture;
//        textures[i] = new ObjTexture;
//        //(*(textures+i))->load(*(texture_names+i), 1, 1);
//        (textures[i])->load(texture_names[i], 1, 1);
//    }
//}
