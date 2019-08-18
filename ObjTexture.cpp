#include "ObjTexture.h"

ObjTexture::ObjTexture() {
    texture = NULL;
    width = 0;
    height = 0;
    anim_rows = 0;
    anim_cols = 0;
}
ObjTexture::~ObjTexture() {
    free();
}
void ObjTexture::free() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
        anim_rows = 0;
        anim_cols = 0;
    }
}
bool ObjTexture::load(std::string path, int anim_rows, int anim_cols) {
    bool success = true;
    free();
    setAnimRows(anim_rows);
    setAnimCols(anim_cols);
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (loaded == NULL) {
        printf("IMG_Load: %s\n", IMG_GetError());
        success = false;
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loaded);
        if (newTexture == NULL) {
            printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
            success = false;
        } else {
            width = loaded->w;
            height = loaded->h;
        }
        SDL_FreeSurface(loaded);
    }
    texture = newTexture;
    return success;
}
void ObjTexture::render(int x, int y, int angle, int width, int height, int anim_index) {
    int row, col, row_height, col_width, textureX, textureY;
    row = anim_index / getAnimCols();
    col = anim_index % getAnimCols();
    row_height = getHeight() / getAnimRows();
    col_width = getWidth() / getAnimCols();

    textureX = col * col_width;
    textureY = row * row_height;

    //printf("%d, %d, %d, %d, %d, %d\n", row, col, col_width, row_height, textureX, textureY);
    SDL_Rect clip = { textureX, textureY, col_width, row_height };
    SDL_Rect quad = { x, y, width, height };
    SDL_RenderCopyEx(gRenderer, texture, &clip, &quad, -angle, NULL, SDL_FLIP_NONE);
    /*negative angle for counter clockwise rotation like in the unit circle*/
}
