#include "ObjTexture.h"

ObjTexture::ObjTexture() {
    printf("---Entering ObjTexture constructor\n");
    global_count++;
    printf("Global count = %d\n", global_count);
    texture = NULL;
    width = 0;
    height = 0;
    anim_rows = 0;
    anim_cols = 0;
    printf("---Leaving ObjTexture constructor\n");
}
//ObjTexture::ObjTexture(ObjTexture& oldObj) {
//    texture = oldObj.texture;
//    oldObj.texture = NULL;
//    width = oldObj.width;
//    height = oldObj.height;
//    anim_rows = oldObj.anim_rows;
//    anim_cols = oldObj.anim_cols;
//}
ObjTexture::~ObjTexture() {
    printf("---Entering ObjTexture destructor\n");
    global_count--;
    printf("Global count = %d\n", global_count);
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
    //free_();
    printf("---Leaving ObjTexture destructor\n");
}
void ObjTexture::free_() {
    printf("---Entering ObjTexture::free\n");
    ;
    //if(texture != NULL) {
    //    SDL_DestroyTexture(texture);
    //    texture = NULL;
    //    width = 0;
    //    height = 0;
    //    anim_rows = 0;
    //    anim_cols = 0;
    //}
    printf("---Leaving ObjTexture::free\n");
}
bool ObjTexture::load(std::string path, int anim_rows, int anim_cols) {
    printf("---Entering ObjTexture::load\n");
    bool success = true;
    //free_();
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
        loaded = NULL;
    }
    this->texture = newTexture;
    newTexture = NULL;
    this->file_name = path;
    printf("---Leaving ObjTexture::load\n");
    return success;
}
void ObjTexture::render(int x, int y, int angle, int width, int height, int anim_index) {
    //printf("---Entering ObjTexture::render\n");
    printf("r");
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
    SDL_RenderCopyEx(gRenderer, this->texture, &clip, &quad, -angle, NULL, SDL_FLIP_NONE);
    //SDL_RenderCopy(gRenderer, this->texture, &clip, &quad);
    /*negative angle for counter clockwise rotation like in the unit circle*/
    //printf("---Leaving ObjTexture::render\n");
}
