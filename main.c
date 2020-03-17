#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "SDL_manager/SDL_manager.h"
#include "SDL_event/SDL_event.h"

 int main(int argc, char *argv[])
{
    // Initialisation du manager contenant la fenètre, le renderer, la surface et la texture principale de l'ecran
    SDL_manager manager;
    SDL_InitManager(&manager);

    int exit = 0;
    input current_input;

    // Boucle principale du programme
    while(exit != 1){
        // Reagit a un eventuel evenement (Quitter le programme, input...)
        events_manager(&exit, &current_input);
    }

    return exit;
}
