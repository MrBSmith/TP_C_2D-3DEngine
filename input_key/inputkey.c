#include <stdio.h>
#include <stdlib.h>

#include "inputkey.h"

// Get the input from the player, and return it
input get_input(int sym){
    input control;

    switch(sym){
        case SDLK_z:
            control = UP; break;

        case SDLK_q:
            control = LEFT; break;

        case SDLK_d:
            control = RIGHT; break;

        case SDLK_s:
            control = DOWN; break;

        case SDLK_v:
            control = CONFIRM; break;

        case SDLK_n:
            control = CANCEL; break;

        default :
            control = ERROR; break;
    }

    return control;
}

// Print the given input in the console
void print_input(input inp){
    if (inp != EMPTY){
        printf("Input: ");
        switch(inp)
        {
            case UP:
                 printf("UP\n"); break;
            case LEFT:
                 printf("LEFT\n"); break;
            case RIGHT:
                printf("RIGHT\n"); break;
            case DOWN:
                printf("DOWN\n"); break;
            case CONFIRM:
                printf("CONFIRM\n"); break;
            case CANCEL:
                printf("CANCEL\n"); break;
            default :
                printf("ERROR\n"); break;
        }
    }
}

