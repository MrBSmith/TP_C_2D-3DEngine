#ifndef PHYSICSBODY_H_INCLUDED
#define PHYSICSBODY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include "vector.h"
#include "cercle.h"
#include "inputkey.h"

typedef enum move_flag {BOTH, VERTICAL, HORIZONTAL} move_flag;

typedef struct physics_body{
    SDL_Rect* p_shape;
    vector2 velocity;
} physics_body;


typedef struct collision{
    void* p_shape;
    SDL_bool external;
    physics_body* p_body1;
    physics_body* p_body2;
} collision;


physics_body* create_body(void* p_shape, vector2 initial_velocity);
void apply_velocity(physics_body* p_body);
void revert_velocity(physics_body* p_body);


// Collision test functions
SDL_bool point_and_circle_collision(int x, int y, circle* p_C);
SDL_bool point_and_rect_collision(int x,int y, SDL_Rect* p_box);
SDL_bool two_rects_collision(SDL_Rect* p_shape1, SDL_Rect* p_shape2, SDL_bool extern_collision);
SDL_bool two_circles_collision(circle* c1, circle* c2);
SDL_bool circle_and_rect_collision(circle* p_C, SDL_Rect* p_box);
SDL_bool is_collision_lateral(collision* p_collision);
SDL_bool segment_projection(int Cx, int Cy, int Ax, int Ay, int Bx, int By);

SDL_Rect* get_box_around_circle(circle* p_circle);

// Move the given rect accordingly to the input of the player
void move_player(player_input_manager* p_player_input_manager, physics_body* p_body, int move_speed, move_flag flag);

#endif // PHYSICSBODY_H_INCLUDED
