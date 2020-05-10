#include "polygone.h"

// Create a polygone out of an array of points
polygone* create_polygone(vector2 points[], vector2 origin, int nb_points){
    polygone* p_polygone = malloc(sizeof(polygone));
    p_polygone -> points = points;
    p_polygone -> origin = origin;
    p_polygone -> nb_points = nb_points;

    return p_polygone;
}

// Draw the given polygone
void draw_polygone(SDL_Renderer* p_renderer, polygone* p_polygone, SDL_Color col){
    vector2 next_point, current_point;
    SDL_SetRenderDrawColor(p_renderer, col.r, col.g, col.b, col.a);

    for(int i = 0; i < p_polygone -> nb_points; i++){

        current_point = sum_vectors(p_polygone -> points[i], p_polygone -> origin);

        if(i == p_polygone -> nb_points - 1){
            next_point = p_polygone -> points[0];
        } else {
            next_point = p_polygone -> points[i + 1];
        }

        next_point = sum_vectors(next_point, p_polygone -> origin);

        SDL_RenderDrawLine(p_renderer, current_point.x, current_point.y, next_point.x, next_point.y);
    }
    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
}
