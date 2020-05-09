#include "PhysicsBody.h"

// Create a body with the given shape and the given velocity
physics_body* create_body(void* p_shape, vector2 initial_velocity){

    physics_body* p_new_body = malloc(sizeof(physics_body));

    p_new_body -> p_shape = p_shape;
    p_new_body -> velocity = initial_velocity;

    return p_new_body;
}


// Return SDL_TRUE if the given collision is lateral, SDL_FALSE if it is vertical
SDL_bool is_collision_lateral(collision* p_collision){

    SDL_Rect* p_shape = p_collision -> p_shape;
    SDL_bool lateral = SDL_FALSE;

    if(p_shape -> w <= p_shape -> h){
        lateral = SDL_TRUE;
    }

    return lateral;
}


// Move the given body, based on his velocity
void apply_velocity(physics_body* p_body){
    p_body -> p_shape -> x += p_body -> velocity.x;
    p_body -> p_shape -> y += p_body -> velocity.y;
}

// Move the body back where he was
void revert_velocity(physics_body* p_body){
    p_body -> p_shape -> x -= p_body -> velocity.x;
    p_body -> p_shape -> y -= p_body -> velocity.y;
}


// Check for a collision between the p_shape1 and the p_shape2
// Create a collision entity if a collision happens, containing a shape that describe the shape of the collision
SDL_bool two_rects_collision(SDL_Rect* p_shape1, SDL_Rect* p_shape2, SDL_bool extern_collision){
    SDL_bool result = SDL_TRUE;

    // define each border of the two shapes
    int left1 = p_shape1 -> x;
    int left2 = p_shape2 -> x;
    int right1 = left1 + p_shape1 -> w;
    int right2 = left2 + p_shape2 -> w;
    int top1 = p_shape1 -> y;
    int top2 = p_shape2 -> y;
    int bottom1 = top1 + p_shape1 -> h;
    int bottom2 = top2 + p_shape2 -> h;

    // Check for a collision
    if(extern_collision == SDL_TRUE){ // extern collision
        if(bottom1 <= top2 || top1 >= bottom2 || right1 <= left2 || left1 >= right2){
            result = SDL_FALSE;
        }
    } else { // intern collision (When you want to know when p_shape1 is colliding with the border of p_shape2 from within)
        if(top1 > top2 && bottom1 < bottom2 && left1 > left2 && right1 < right2){
            result = SDL_FALSE;
        }
    }

    return result;
}


// Detect a collision between two circles
SDL_bool two_circles_collision(circle* c1, circle* c2){
   int d2 = (c1 -> x - c2 -> x) * (c1 -> x - c2 -> x) + (c1 -> y - c2 -> y) * (c1 -> y - c2 -> y);
   if (d2 > (c1 -> radius + c2 -> radius) * (c1 -> radius + c2 -> radius))
      return SDL_FALSE;
   else
      return SDL_TRUE;
}


// Respond to the input of the player by moving the character
void move_player(player_input_manager* p_player_input_manager, physics_body* p_body, int move_speed, move_flag flag){

    if(flag != HORIZONTAL){
        if(p_player_input_manager -> input_state_array[UP] == PRESSED){
            p_body -> velocity.y -= move_speed;
        }

        if(p_player_input_manager -> input_state_array[DOWN] == PRESSED){
            p_body -> velocity.y += move_speed;
        }
    }

    if(flag != VERTICAL){
        if(p_player_input_manager -> input_state_array[LEFT] == PRESSED){
            p_body -> velocity.x -= move_speed;
        }

        if(p_player_input_manager -> input_state_array[RIGHT] == PRESSED){
            p_body -> velocity.x += move_speed;
        }
    }

    apply_velocity(p_body);
}
