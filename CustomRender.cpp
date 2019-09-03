#include "CustomRender.h"

void renderHealthBar(SDL_Rect health_rect, float health_percent,
        SDL_Color full_color, SDL_Color empty_color) {

    int filled_length = int (health_percent * health_rect.w);

    SDL_Rect emptyRect = { health_rect.x, health_rect.y, 
        health_rect.w - filled_length, health_rect.h };
    SDL_Rect fullRect = { health_rect.x + health_rect.w - filled_length, 
        health_rect.y, filled_length, health_rect.h };

    // fill empty part of health bar
    SDL_SetRenderDrawColor( gRenderer, empty_color.r, empty_color.g, empty_color.b, empty_color.a );
    SDL_RenderFillRect( gRenderer, &emptyRect );

    // fill full part of health bar
    SDL_SetRenderDrawColor( gRenderer, full_color.r, full_color.g, full_color.b, full_color.a );
    SDL_RenderFillRect( gRenderer, &fullRect );
}
