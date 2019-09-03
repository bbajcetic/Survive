#ifndef CUSTOMRENDER_H
#define CUSTOMRENDER_H

#include <SDL2/SDL.h>

extern SDL_Renderer* gRenderer;

void renderHealthBar(SDL_Rect health_rect, float health_percent,
        SDL_Color fill_color, SDL_Color empty_color);

#endif
