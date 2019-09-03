#include "Map.h"

Map::Map(int num_textures, std::string* texture_names, 
        int rows, int cols, int tile_width, int tile_height) {
    //printf("---Entering Map constructor\n");
    //textures = NULL;
    //this->tiles = tiles;
    this->num_textures = num_textures;
    this->texture_names = texture_names;
    this->rows = rows;
    this->cols = cols;
    this->tile_width = tile_width;
    this->tile_height = tile_height;
    this->tiles = new int[rows*cols];
    this->survivor_path = new int[rows*cols];
    fillMap1();
    initPath(rows*cols);
    //printf("---Leaving Map constructor\n");
}
Map::~Map() {
    //printf("---Entering Map destructor\n");
    delete [] tiles;
    for (int i = 0; i < num_textures; ++i) {
        delete textures[i];
        textures[i] = NULL;
    }
    textures.clear();
    //printf("---Leaving Map destructor\n");
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
    //printf("---Entering Map::onMap\n");
    if (x >= 0 && (x+width) < (cols*tile_width)) {
        if (y >= 0 && (y+height) < (rows*tile_height)) {
            //printf("---Leaving Map::onMap\n");
            return true;
        }
    }
    //printf("---Leaving Map::onMap\n");
    return false;
}
bool Map::onMap(int index) {
    //printf("---Entering Map::onMap\n");
    if ( (index >= rows*cols) || (index < 0) ) {
        return false;
    }
    return true;
}
bool Map::isRightEdge(int index) {
    if ( ((index+1) % cols) == 0) {
        return true;
    }
    return false;
}
bool Map::isLeftEdge(int index) {
    if ( (index % cols) == 0) {
        return true;
    }
    return false;
}
/*checks if a rectangle is touching a Wall or is off screen */
bool Map::isWall(int x, int y, int width, int height) {
    //printf("---Entering Map::isWall\n");

    bool invalid = false;
    if (!onMap(x, y, width, height)) { invalid = true; }
    else if (getTileValue(x, y) != 0) { invalid = true; }
    else if (getTileValue(x+width, y) != 0) { invalid = true; }
    else if (getTileValue(x+width, y+height) != 0) { invalid = true; }
    else if (getTileValue(x, y+height) != 0) { invalid = true; }

    //printf("---Leaving Map::isWall\n");
    return invalid;
}
/* Returns the value/type of Tile at the row, col specified */
int Map::getTileValue(int x, int y) {
    //printf("---Entering Map::getTileValue\n");
    //printf("---Leaving Map::getTileValue\n");
    return tiles[getTileIndex(x, y)];
}
int Map::getPathValue(int x, int y) {
    //printf("---Entering Map::getPathValue\n");
    //printf("---Leaving Map::getPathValue\n");
    return survivor_path[getTileIndex(x, y)];
}
int Map::getPathValue(int index) {
    //printf("---Entering Map::getPathValue\n");
    //printf("---Leaving Map::getPathValue\n");
    return survivor_path[index];
}
int Map::getTileIndex(int x, int y) {
    //printf("---Entering Map::getTileIndex\n");
    //printf("---Leaving Map::getTileIndex\n");
    return getRow(y)*cols + getCol(x);
}
int Map::getXFromIndex(int index) {
    return (index % cols) * tile_width;
}
int Map::getYFromIndex(int index) {
    return (index / cols) * tile_height;
}

void Map::draw() {
    //printf("---Entering Map::draw\n");
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
            this->textures[type]->render(x, y, tile_width, tile_height, angle, 0);
        }
    }
    //printf("---Leaving Map::draw\n");
}
bool Map::load() {
    //printf("---Entering Map::load\n");
    bool success = true;
    for (int i = 0; i < num_textures; ++i) {
        ObjTexture* temp = new ObjTexture;
        //printf("LOADING %s\n", texture_names[i].c_str());
        if (! (temp->load(texture_names[i], 1, 1)) ) {
            success = false;
        }
        //ObjTexture* temp = new ObjTexture;
        //temp->load(texture_names[i], 1, 1);
        textures.push_back(temp);
    }
    //printf("---Leaving Map::load\n");
    return success;
}

void Map::printPath() {
    //printf("printPath:\n");
    for (int i = 0; i < rows*cols; ++i) {
        if ((i % 20) == 0 ) {
            ;//printf("\n");
        }
        //printf(" %2d ", survivor_path[i]);
    }
    //printf("\n");
}
/* updates Path for survivor at center of object coordinates x, y */
void Map::updatePath(int x, int y) {
    initPath(rows*cols);
    /* -2:  unfilled space
     *
     * -1:  invalid space (such as a wall)
     *
     * x:   tile is x tiles away from Survivor, where x >= 0 */
    std::queue<int> to_process; //index of tile
    int temp = getTileIndex(x, y);
    survivor_path[temp] = 0; //survivor tile = 0 tiles away from survivor
    to_process.push(temp); //insert survivor tile index
    
    while (!to_process.empty()) {
        temp = to_process.front();
        int top = temp - cols;
        int bottom = temp + cols;
        /* around is an array holding the surrounding tile indices */
        int around[8] = {
            top-1, top, top+1, temp+1, bottom+1, bottom, bottom-1, temp-1
        };
        /* if left side tile, make sure it doesn't wrap around */
        if (isLeftEdge(temp)) {
            /* invalidate tiles to the left */
            around[0] = -1; around[6] = -1; around[7] = -1;
        }
        /* if right side tile, make sure it doesn't wrap around */
        else if (isRightEdge(temp)) {
            /* invalidate tiles to the right */
            around[2] = -1; around[3] = -1; around[4] = -1;
        }
        for (int i = 0; i < 8; ++i) {
            /* if tile is off map, do nothing */
            if (!onMap(around[i])) {
                continue;
            }
            /* if tile is wall, do nothing */
            else if (survivor_path[around[i]] == -1) {
                continue;
            }
            /* if tile is unfilled, fill it */
            else if (survivor_path[around[i]] == -2) {
                if (tiles[around[i]] != 0) {
                    survivor_path[around[i]] = -1;
                }
                else {
                    survivor_path[around[i]] = survivor_path[temp] + 1;
                    to_process.push(around[i]);
                }
            }
            /* if tile is already filled, check for a possible lower value */
            else if (survivor_path[around[i]] > survivor_path[temp]+1) {
                survivor_path[around[i]] = survivor_path[temp] + 1;
                to_process.push(around[i]);
            }
        }
        to_process.pop();
    }
}
void Map::resetMap() {
    fillMap1();
    initPath(rows*cols);
}
void Map::initPath(int size) {
    for (int i = 0; i < size; ++i) {
        survivor_path[i] = -2;
    }
}
void Map::fillMap1() {
    /* 0 = Floor, 4 = WallEdge, 8 = WallCorner, 12 = WallT */
    tiles[0] = 0; tiles[1] = 0; tiles[2] = 0; tiles[3] = 0; 
    tiles[4] = 0; tiles[5] = 0; tiles[6] = 0; tiles[7] = 0; 
    tiles[8] = 0; tiles[9] = 0; tiles[10] = 0; tiles[11] = 0; 
    tiles[12] = 0; tiles[13] = 0; tiles[14] = 0; tiles[15] = 0; 
    tiles[16] = 0; tiles[17] = 0; tiles[18] = 0; tiles[19] = 0; 
    tiles[20] = 0; tiles[21] = 0; tiles[22] = 0; tiles[23] = 0; 
    tiles[24] = 0; tiles[25] = 0; tiles[26] = 0; tiles[27] = 0; 
    tiles[28] = 0; tiles[29] = 0; tiles[30] = 0; tiles[31] = 0; 
    tiles[32] = 0; tiles[33] = 0; tiles[34] = 0; tiles[35] = 0; 
    tiles[36] = 0; tiles[37] = 0; tiles[38] = 0; tiles[39] = 0; 
    tiles[40] = 0; tiles[41] = 0; tiles[42] = 0; tiles[43] = 0; 
    tiles[44] = 0; tiles[45] = 0; tiles[46] = 0; tiles[47] = 4; 
    tiles[48] = 0; tiles[49] = 0; tiles[50] = 5; tiles[51] = 5; 
    tiles[52] = 5; tiles[53] = 12; tiles[54] = 0; tiles[55] = 0; 
    tiles[56] = 5; tiles[57] = 5; tiles[58] = 5; tiles[59] = 5; 
    tiles[60] = 0; tiles[61] = 0; tiles[62] = 8; tiles[63] = 5; 
    tiles[64] = 5; tiles[65] = 12; tiles[66] = 5; tiles[67] = 10; 
    tiles[68] = 0; tiles[69] = 0; tiles[70] = 0; tiles[71] = 0; 
    tiles[72] = 0; tiles[73] = 4; tiles[74] = 0; tiles[75] = 0; 
    tiles[76] = 0; tiles[77] = 0; tiles[78] = 0; tiles[79] = 0; 
    tiles[80] = 0; tiles[81] = 0; tiles[82] = 4; tiles[83] = 0; 
    tiles[84] = 0; tiles[85] = 4; tiles[86] = 0; tiles[87] = 0; 
    tiles[88] = 0; tiles[89] = 0; tiles[90] = 0; tiles[91] = 0; 
    tiles[92] = 0; tiles[93] = 4; tiles[94] = 0; tiles[95] = 0; 
    tiles[96] = 0; tiles[97] = 0; tiles[98] = 0; tiles[99] = 0; 
    tiles[100] = 0; tiles[101] = 0; tiles[102] = 4; tiles[103] = 0; 
    tiles[104] = 0; tiles[105] = 4; tiles[106] = 0; tiles[107] = 0; 
    tiles[108] = 0; tiles[109] = 0; tiles[110] = 0; tiles[111] = 0; 
    tiles[112] = 0; tiles[113] = 4; tiles[114] = 0; tiles[115] = 0; 
    tiles[116] = 0; tiles[117] = 0; tiles[118] = 0; tiles[119] = 0; 
    tiles[120] = 0; tiles[121] = 0; tiles[122] = 4; tiles[123] = 0; 
    tiles[124] = 0; tiles[125] = 4; tiles[126] = 0; tiles[127] = 0; 
    tiles[128] = 0; tiles[129] = 0; tiles[130] = 0; tiles[131] = 0; 
    tiles[132] = 0; tiles[133] = 4; tiles[134] = 0; tiles[135] = 0; 
    tiles[136] = 0; tiles[137] = 0; tiles[138] = 0; tiles[139] = 0; 
    tiles[140] = 0; tiles[141] = 0; tiles[142] = 4; tiles[143] = 0; 
    tiles[144] = 0; tiles[145] = 0; tiles[146] = 0; tiles[147] = 0; 
    tiles[148] = 0; tiles[149] = 0; tiles[150] = 0; tiles[151] = 5; 
    tiles[152] = 5; tiles[153] = 14; tiles[154] = 5; tiles[155] = 5; 
    tiles[156] = 5; tiles[157] = 5; tiles[158] = 12; tiles[159] = 4; 
    tiles[160] = 0; tiles[161] = 0; tiles[162] = 4; tiles[163] = 0; 
    tiles[164] = 0; tiles[165] = 0; tiles[166] = 0; tiles[167] = 0; 
    tiles[168] = 0; tiles[169] = 0; tiles[170] = 0; tiles[171] = 0; 
    tiles[172] = 0; tiles[173] = 0; tiles[174] = 0; tiles[175] = 0; 
    tiles[176] = 0; tiles[177] = 0; tiles[178] = 4; tiles[179] = 0; 
    tiles[180] = 0; tiles[181] = 0; tiles[182] = 11; tiles[183] = 5;
    tiles[184] = 5; tiles[185] = 5; tiles[186] = 5; tiles[187] = 9; 
    tiles[188] = 0; tiles[189] = 0; tiles[190] = 0; tiles[191] = 0; 
    tiles[192] = 0; tiles[193] = 0; tiles[194] = 0; tiles[195] = 0; 
    tiles[196] = 0; tiles[197] = 0; tiles[198] = 4; tiles[199] = 0; 
    tiles[200] = 0; tiles[201] = 0; tiles[202] = 0; tiles[203] = 0; 
    tiles[204] = 0; tiles[205] = 0; tiles[206] = 0; tiles[207] = 15; 
    tiles[208] = 5; tiles[209] = 5; tiles[210] = 5; tiles[211] = 5; 
    tiles[212] = 5; tiles[213] = 0; tiles[214] = 5; tiles[215] = 5; 
    tiles[216] = 5; tiles[217] = 5; tiles[218] = 10; tiles[219] = 0; 
    tiles[220] = 0; tiles[221] = 0; tiles[222] = 0; tiles[223] = 0; 
    tiles[224] = 0; tiles[225] = 0; tiles[226] = 0; tiles[227] = 5; 
    tiles[228] = 0; tiles[229] = 0; tiles[230] = 0; tiles[231] = 0; 
    tiles[232] = 0; tiles[233] = 0; tiles[234] = 0; tiles[235] = 0; 
    tiles[236] = 0; tiles[237] = 0; tiles[238] = 0; tiles[239] = 0;
}
//void Map::fillMap1() {
//    /* 0 = Floor, 4 = WallEdge, 8 = WallCorner, 12 = WallT */
//    tiles[0] = 0; tiles[1] = 0; tiles[2] = 0; tiles[3] = 0; 
//    tiles[4] = 0; tiles[5] = 0; tiles[6] = 0; tiles[7] = 0; 
//    tiles[8] = 0; tiles[9] = 0; tiles[10] = 0; tiles[11] = 0; 
//    tiles[12] = 0; tiles[13] = 0; tiles[14] = 0; tiles[15] = 0; 
//    tiles[16] = 0; tiles[17] = 0; tiles[18] = 0; tiles[19] = 0; 
//    tiles[20] = 0; tiles[21] = 0; tiles[22] = 0; tiles[23] = 0; 
//    tiles[24] = 0; tiles[25] = 0; tiles[26] = 0; tiles[27] = 0; 
//    tiles[28] = 0; tiles[29] = 0; tiles[30] = 0; tiles[31] = 0; 
//    tiles[32] = 0; tiles[33] = 0; tiles[34] = 0; tiles[35] = 0; 
//    tiles[36] = 0; tiles[37] = 0; tiles[38] = 0; tiles[39] = 0; 
//    tiles[40] = 0; tiles[41] = 0; tiles[42] = 8; tiles[43] = 5; 
//    tiles[44] = 5; tiles[45] = 12; tiles[46] = 5; tiles[47] = 5; 
//    tiles[48] = 5; tiles[49] = 5; tiles[50] = 5; tiles[51] = 5; 
//    tiles[52] = 5; tiles[53] = 0; tiles[54] = 0; tiles[55] = 12; 
//    tiles[56] = 5; tiles[57] = 0; tiles[58] = 0; tiles[59] = 5; 
//    tiles[60] = 0; tiles[61] = 0; tiles[62] = 4; tiles[63] = 0; 
//    tiles[64] = 0; tiles[65] = 4; tiles[66] = 0; tiles[67] = 0; 
//    tiles[68] = 0; tiles[69] = 0; tiles[70] = 0; tiles[71] = 0; 
//    tiles[72] = 0; tiles[73] = 0; tiles[74] = 0; tiles[75] = 4; 
//    tiles[76] = 0; tiles[77] = 0; tiles[78] = 0; tiles[79] = 0; 
//    tiles[80] = 0; tiles[81] = 0; tiles[82] = 4; tiles[83] = 0; 
//    tiles[84] = 0; tiles[85] = 4; tiles[86] = 0; tiles[87] = 0; 
//    tiles[88] = 0; tiles[89] = 0; tiles[90] = 0; tiles[91] = 0; 
//    tiles[92] = 0; tiles[93] = 0; tiles[94] = 0; tiles[95] = 4; 
//    tiles[96] = 0; tiles[97] = 0; tiles[98] = 0; tiles[99] = 0; 
//    tiles[100] = 0; tiles[101] = 0; tiles[102] = 4; tiles[103] = 0; 
//    tiles[104] = 0; tiles[105] = 4; tiles[106] = 0; tiles[107] = 0; 
//    tiles[108] = 0; tiles[109] = 0; tiles[110] = 0; tiles[111] = 0; 
//    tiles[112] = 0; tiles[113] = 0; tiles[114] = 0; tiles[115] = 4; 
//    tiles[116] = 0; tiles[117] = 0; tiles[118] = 0; tiles[119] = 0; 
//    tiles[120] = 0; tiles[121] = 0; tiles[122] = 4; tiles[123] = 0; 
//    tiles[124] = 0; tiles[125] = 4; tiles[126] = 0; tiles[127] = 0; 
//    tiles[128] = 0; tiles[129] = 0; tiles[130] = 0; tiles[131] = 0; 
//    tiles[132] = 0; tiles[133] = 0; tiles[134] = 0; tiles[135] = 4; 
//    tiles[136] = 0; tiles[137] = 0; tiles[138] = 0; tiles[139] = 0; 
//    tiles[140] = 0; tiles[141] = 0; tiles[142] = 4; tiles[143] = 0; 
//    tiles[144] = 0; tiles[145] = 0; tiles[146] = 0; tiles[147] = 0; 
//    tiles[148] = 0; tiles[149] = 0; tiles[150] = 0; tiles[151] = 0; 
//    tiles[152] = 5; tiles[153] = 5; tiles[154] = 5; tiles[155] = 14; 
//    tiles[156] = 5; tiles[157] = 5; tiles[158] = 12; tiles[159] = 4; 
//    tiles[160] = 0; tiles[161] = 0; tiles[162] = 4; tiles[163] = 0; 
//    tiles[164] = 0; tiles[165] = 0; tiles[166] = 0; tiles[167] = 0; 
//    tiles[168] = 0; tiles[169] = 0; tiles[170] = 0; tiles[171] = 0; 
//    tiles[172] = 0; tiles[173] = 0; tiles[174] = 0; tiles[175] = 0; 
//    tiles[176] = 0; tiles[177] = 0; tiles[178] = 4; tiles[179] = 0; 
//    tiles[180] = 0; tiles[181] = 0; tiles[182] = 11; tiles[183] = 5;
//    tiles[184] = 5; tiles[185] = 5; tiles[186] = 5; tiles[187] = 9; 
//    tiles[188] = 0; tiles[189] = 4; tiles[190] = 0; tiles[191] = 0; 
//    tiles[192] = 0; tiles[193] = 0; tiles[194] = 0; tiles[195] = 0; 
//    tiles[196] = 0; tiles[197] = 0; tiles[198] = 4; tiles[199] = 0; 
//    tiles[200] = 0; tiles[201] = 0; tiles[202] = 0; tiles[203] = 0; 
//    tiles[204] = 0; tiles[205] = 0; tiles[206] = 0; tiles[207] = 4; 
//    tiles[208] = 0; tiles[209] = 11; tiles[210] = 5; tiles[211] = 5; 
//    tiles[212] = 5; tiles[213] = 5; tiles[214] = 5; tiles[215] = 5; 
//    tiles[216] = 5; tiles[217] = 5; tiles[218] = 10; tiles[219] = 0; 
//    tiles[220] = 0; tiles[221] = 0; tiles[222] = 0; tiles[223] = 0; 
//    tiles[224] = 0; tiles[225] = 0; tiles[226] = 0; tiles[227] = 5; 
//    tiles[228] = 0; tiles[229] = 0; tiles[230] = 0; tiles[231] = 0; 
//    tiles[232] = 0; tiles[233] = 0; tiles[234] = 0; tiles[235] = 0; 
//    tiles[236] = 0; tiles[237] = 0; tiles[238] = 0; tiles[239] = 0;
//}
