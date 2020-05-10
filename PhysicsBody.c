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
        if(bottom1 <= top2 || top1 >= bottom2 || right1 <= left2 || left1 >= right2)
            result = SDL_FALSE;
    } else { // intern collision (When you want to know when p_shape1 is colliding with the border of p_shape2 from within)
        if(top1 > top2 && bottom1 < bottom2 && left1 > left2 && right1 < right2)
            result = SDL_FALSE;
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


SDL_bool circle_and_rect_collision(circle* p_C, SDL_Rect* p_box){
    // Compute the box surrounding the circle, and check is there is collision with the rect
    SDL_Rect* p_boxCircle = get_box_around_circle(p_C);
    if (two_rects_collision(p_box, p_boxCircle, SDL_TRUE) == SDL_FALSE)
      return SDL_FALSE;

    // Check if one of the corner of the rect is inside the circle
    if (point_and_circle_collision(p_box -> x, p_box -> y, p_C) == SDL_TRUE
    || point_and_circle_collision(p_box -> x, p_box -> y + p_box -> h, p_C) == SDL_TRUE
    || point_and_circle_collision(p_box -> x + p_box -> w, p_box -> y, p_C) == SDL_TRUE
    || point_and_circle_collision(p_box -> x + p_box -> w, p_box -> y + p_box -> h, p_C) == SDL_TRUE)
        return SDL_TRUE;

    // Check if the center of the circle is inside the box
    if (point_and_rect_collision(p_C -> x, p_C -> y, p_box) == SDL_TRUE)
      return SDL_TRUE;

    // Check by projection that the circle is inside the rect
    SDL_bool proj_vertical = segment_projection(p_C -> x, p_C -> y, p_box -> x, p_box -> y, p_box -> x, p_box -> y + p_box -> h);
    SDL_bool proj_horizontal = segment_projection(p_C -> x, p_C -> y, p_box -> x, p_box -> y, p_box -> x + p_box -> w, p_box -> y);
    if (proj_vertical == SDL_TRUE || proj_horizontal == SDL_TRUE)
        return SDL_TRUE;

    return SDL_FALSE;
}

// Check if a point is inside the given rect
SDL_bool point_and_rect_collision(int x,int y, SDL_Rect* p_box){
   if (x >= p_box -> x
    && x < p_box -> x + p_box -> w
    && y >= p_box -> y
    && y < p_box -> y + p_box -> h)
       return SDL_TRUE;
   else
       return SDL_FALSE;
}


// Check if a point is inside the given circle
SDL_bool point_and_circle_collision(int x, int y, circle* p_C){
   int d2 = (x - p_C -> x) * (x - p_C -> x) + (y - p_C -> y) * (y - p_C -> y);
   if (d2 > p_C -> radius * p_C -> radius)
      return SDL_FALSE;
   else
      return SDL_TRUE;
}


// Check if the projection of the given point is inside the given segment
SDL_bool segment_projection(int Cx, int Cy, int Ax, int Ay, int Bx, int By){
   int ACx = Cx - Ax;
   int ACy = Cy - Ay;
   int ABx = Bx - Ax;
   int ABy = By - Ay;
   int BCx = Cx - Bx;
   int BCy = Cy - By;
   int s1 = (ACx * ABx) + (ACy * ABy);
   int s2 = (BCx * ABx) + (BCy * ABy);
   if(s1 * s2 > 0)
     return SDL_FALSE;
   return SDL_TRUE;
}

SDL_bool line_collision(vector2 A, vector2 B, circle* p_C)
{
   vector2 u, AC;
   u.x = B.x - A.x;
   u.y = B.y - A.y;
   AC.x = p_C -> x - A.x;
   AC.y = p_C -> y - A.y;
   float numerateur = u.x * AC.y - u.y * AC.x;   // norme du vecteur v
   if (numerateur < 0)
      numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.
   float denominateur = sqrt(u.x * u.x + u.y * u.y);  // norme de u
   float CI = numerateur / denominateur;
   if (CI < p_C -> radius)
      return SDL_TRUE;
   else
      return SDL_FALSE;
}


SDL_bool segment_circle_collision(vector2 A, vector2 B, circle* p_C){
   if (line_collision(A, B, p_C) == SDL_FALSE)
     return SDL_FALSE;  // si on ne touche pas la droite, on ne touchera jamais le segment
   vector2 AB, AC, BC;
   AB.x = B.x - A.x;
   AB.y = B.y - A.y;
   AC.x = p_C -> x - A.x;
   AC.y = p_C -> y - A.y;
   BC.x = p_C -> x - B.x;
   BC.y = p_C -> y - B.y;
   int pscal1 = AB.x * AC.x + AB.y * AC.y;  // produit scalaire
   int pscal2 = (-AB.x) * BC.x + (-AB.y) * BC.y;  // produit scalaire
   if (pscal1 >= 0 && pscal2 >= 0)
      return SDL_TRUE;   // I entre A et B, ok.
   // dernière possibilité, A ou B dans le cercle
   if (point_and_circle_collision(A.x, A.y, p_C))
     return SDL_TRUE;
   if (point_and_circle_collision(B.x, B.y, p_C))
     return SDL_TRUE;
   return SDL_FALSE;
}


// Return the surrounding box around the given circle
SDL_Rect* get_box_around_circle(circle* p_c){
    SDL_Rect* p_rect = malloc(sizeof(SDL_Rect));
    p_rect -> x = p_c -> x - p_c -> radius;
    p_rect -> y = p_c -> y - p_c -> radius;
    p_rect -> w = p_c -> radius * 2;
    p_rect -> h = p_c -> radius * 2;
    return p_rect;
}


// Check if a point is inside a convex polygone
SDL_bool point_polygone_collision(int point_x, int point_y, polygone* p_polygone){
  for(int i = 0; i < p_polygone -> nb_points; i++){

     vector2 A = sum_vectors(p_polygone -> points[i], p_polygone -> origin);
     vector2 B;

     if (i == p_polygone -> nb_points - 1)  // If its the last point, link to the first one
         B = sum_vectors(p_polygone -> points[0], p_polygone -> origin);
     else           // else links to the next one
         B = sum_vectors(p_polygone -> points[i + 1], p_polygone -> origin);

     vector2 D, T;
     D.x = B.x - A.x;
     D.y = B.y - A.y;
     T.x = point_x - A.x;
     T.y = point_y - A.y;
     int d = D.x * T.y - D.y * T.x;
     if(d < 0)
        return SDL_FALSE;
  }
  return SDL_TRUE;
}


// Check for a collision between a rect and a polygone
SDL_bool rect_polygone_collision(SDL_Rect* p_box, polygone* p_polygone){

    // Check if one of the corner of the rect is inside the circle
    if (point_polygone_collision(p_box -> x, p_box -> y, p_polygone) == SDL_TRUE
    || point_polygone_collision(p_box -> x, p_box -> y + p_box -> h, p_polygone) == SDL_TRUE
    || point_polygone_collision(p_box -> x + p_box -> w, p_box -> y, p_polygone) == SDL_TRUE
    || point_polygone_collision(p_box -> x + p_box -> w, p_box -> y + p_box -> h, p_polygone) == SDL_TRUE)
        return SDL_TRUE;

    return SDL_FALSE;
}

// Check for a collision between a circle and a polygone
SDL_bool circle_polygone_collision(circle* p_C, polygone* p_polygone){

    // Check if any corners of the rect of the circle is colliding with the polygone
    SDL_Rect* p_rect = get_box_around_circle(p_C);
    if (rect_polygone_collision(p_rect, p_polygone) == SDL_TRUE)
        return SDL_TRUE;

    // Check if any of the point of the polygone is inside the circle
    for(int i = 0; i < p_polygone -> nb_points; i++){
        vector2 current_point = sum_vectors(p_polygone -> points[i], p_polygone -> origin);
        if(point_and_circle_collision(current_point.x, current_point.y, p_C) == SDL_TRUE)
            return SDL_TRUE;
    }

    // Check if the origin of the circle is inside the polygone
    if(point_polygone_collision(p_C -> x, p_C -> y, p_polygone))
        return SDL_TRUE;


    // Check if any segment constituing the shape is crossing the polygone
    for(int i = 0; i < p_polygone -> nb_points; i++){
        vector2 next_point;
        vector2 current_point = sum_vectors(p_polygone -> points[i], p_polygone -> origin);
        if (i == p_polygone -> nb_points){
            next_point = sum_vectors(p_polygone -> points[0], p_polygone -> origin);
        } else {
            next_point = sum_vectors(p_polygone -> points[i + 1], p_polygone -> origin);
        }

        if (segment_circle_collision(current_point, next_point, p_C) == SDL_TRUE){
            return SDL_TRUE;
        }
    }

    return SDL_FALSE;
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
