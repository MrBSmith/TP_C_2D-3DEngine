#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "SDL_manager.h"
#include "SDL_event.h"
#include "delta.h"
#include "pile.h"
#include "cercle.h"
#include "vector.h"
#include "PhysicsBody.h"
#include "inputkey.h"
#include "polygone.h"

int main(int argc, char *argv[])
{
    const vector2 vector2ZERO = {0, 0};

    // The frames per seconds
    const int FPS = 60;

    SDL_manager* p_SDL_manager = SDL_InitManager();

    SDL_Color red = {255, 0, 0, 255};


    // Define the shapes
    SDL_Rect square_shape = {200, 10, 30, 30};
    physics_body* p_square = create_body(&square_shape, vector2ZERO);

    circle circle_shape1 = {30, 30, 30};
    physics_body* p_circle1 = create_body(&circle_shape1, vector2ZERO);

    circle circle_shape2 = {150, 150, 30};
    physics_body* p_circle2 = create_body(&circle_shape2, vector2ZERO);

    vector2 point_array[4] = {{0, -10}, {-10, 10}, {0, 100}, {10, 10}};
    vector2 pos = {300, 300};
    polygone* p_polygone = create_polygone(point_array, pos, 4);
    physics_body* p_triangle = create_body(p_polygone, vector2ZERO);


    // Define the variable holding the state of the program
    int prog_finished = 0;

    // Define the two players input manager
    player_input_manager* p_input_manager = SDL_CreateInputManager(SDLK_z, SDLK_s, SDLK_q, SDLK_d, SDLK_SPACE, SDLK_ESCAPE);
    player_input_manager* players_input_manager_array[1] = {p_input_manager};

    // Main loop
    while(prog_finished != 1)
    {
        // Check if an event has occurred, exit the program if necessary
        if(events_manager(players_input_manager_array, 1) == 1){
            return EXIT_SUCCESS;
        }

        // Compute the delta time between two frames
        Uint32 current_tick = SDL_GetTicks();
        double delta = SDL_GetDelta(current_tick);

        // Wait enough time to regulate the display
        SDL_regulate_FPS(FPS, delta);

        //// PHYSICS ////

        // Move the players
        move_player(p_input_manager, p_circle1, 10, BOTH);

        if((two_circles_collision((circle*) p_circle1 -> p_shape, (circle*) p_circle2 -> p_shape) == SDL_TRUE)
        || (circle_and_rect_collision((circle*) p_circle1 -> p_shape, (SDL_Rect*) p_square -> p_shape) == SDL_TRUE)
        || (circle_polygone_collision((circle*) p_circle1 -> p_shape, (polygone*) p_triangle -> p_shape)== SDL_TRUE)){
            revert_velocity(p_circle1);
        }

        p_circle1 -> velocity = vector2ZERO;

        //// RENDERING ////

        // Refresh render
        SDL_SetRenderDrawColor(p_SDL_manager -> p_renderer, 0, 0, 0, 255);
        SDL_RenderClear(p_SDL_manager -> p_renderer);

        // Set the draw color to be white
        SDL_SetRenderDrawColor(p_SDL_manager -> p_renderer, 255, 255, 255, 255);

        // Draw the shapes
        SDL_RenderFillRect(p_SDL_manager -> p_renderer, p_square -> p_shape);
        DrawFilledCircle(p_SDL_manager -> p_renderer, (circle*) p_circle1 -> p_shape, red);
        DrawFilledCircle(p_SDL_manager -> p_renderer, (circle*) p_circle2 -> p_shape, red);
        draw_polygone(p_SDL_manager -> p_renderer, (polygone*) p_triangle -> p_shape, red);

        // Render
        SDL_RenderPresent(p_SDL_manager -> p_renderer);
    }

    // Free from memory every elements of the manager
    SDL_FreeManager(p_SDL_manager);

    // Quit SDL before leaving th application
    SDL_Quit();
    return EXIT_SUCCESS;
}
