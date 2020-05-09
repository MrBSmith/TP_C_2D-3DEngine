#ifndef SDL_MANAGER_H_INCLUDED
#define SDL_MANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct SDL_manager
{
    SDL_Window *p_window;
    SDL_Renderer *p_renderer;
    SDL_Texture *p_texture;
    SDL_Surface *p_surface;

} SDL_manager;


// Cr�e la fen�tre le renderer et la texture et les stock dans le type SDL_manager
SDL_manager* SDL_InitManager();

// Procedure de rendu
void SDL_ManagerRender(SDL_manager* p_SDL_manager);

// Lib�re de la m�moire tous les �l�ments du manager (fenetre, renderer, texture)
void SDL_FreeManager(SDL_manager* p_SDL_manager);

#endif // SDL_MANAGER_H_INCLUDED
