#ifndef POLYGONE_H_INCLUDED
#define POLYGONE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "vector.h"

typedef struct polygone{
    vector2* points;
    vector2 origin;
    int nb_points;
} polygone;


// Create a polygone out of an array of point and an origin
polygone* create_polygone(vector2 points[], vector2 origin, int nb_points);

// Draw the given polygone
void draw_polygone(SDL_Renderer* p_renderer, polygone* p_polygone, SDL_Color col);

#endif // POLYGONE_H_INCLUDED
