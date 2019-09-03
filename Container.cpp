#include "Container.h"

Container::Container( SDL_Rect box, int rows, int cols, SDL_Color color ) {
    this->x = box.x;
    this->y = box.y;
    this->width = box.w;
    this->height = box.h;
    this->rows = rows;
    this->cols = cols;
    this->color = color;
}
/* must be called after outline if there is an outline */
void Container::render() {
    SDL_Rect box = { x, y, width, height };
    SDL_SetRenderDrawColor( gRenderer, color.r, color.g, color.b, color.a );
    SDL_RenderFillRect( gRenderer, &box );
    printf("rendering box: %d, %d, %d, %d\n", x, y, width, height);
    printf("rows,cols = %d, %d\n", rows, cols);
}
/* outline must be called before render */
void Container::outline(int l_width) {
    SDL_Rect box = { x-l_width, y-l_width, width+l_width*2, height+l_width*2 };
    SDL_SetRenderDrawColor( gRenderer, color.r, color.g, color.b, color.a );
    SDL_RenderFillRect( gRenderer, &box );
}
bool Container::inButton(int posX, int posY) {
    if ( posX >= x && posY >= y && posX <= x+width && posY <= y+height ) {
        return true;
    }
    return false;
}
int Container::colToX(int col) {
    return int( float(col) * (float(width)/float(cols)) + x );
}
int Container::rowToY(int row) {
    return int( float(row) * (float(height)/float(rows)) + y );
}
void Container::write(std::string text, int row, int col, int offX, int offY) {
    gTextTexture.loadText(text, color);
    gTextTexture.render( colToX(col) + offX, rowToY(row) + offY, 
            gTextTexture.getWidth(), gTextTexture.getHeight(), 0 );
}
void Container::writeCenter(std::string text, int row, int offY) {
    int center_x = x + width/2;
    gTextTexture.loadText(text, color);
    gTextTexture.render( center_x - gTextTexture.getWidth()/2, 
            rowToY(row) + offY, 
            gTextTexture.getWidth(), gTextTexture.getHeight(), 0 );
    printf("rendering at height %d\n", rowToY(row) + offY);
}
