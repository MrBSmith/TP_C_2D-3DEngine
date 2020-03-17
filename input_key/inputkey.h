#ifndef INPUTKEY_H_INCLUDED
#define INPUTKEY_H_INCLUDED

#include <SDL.h>

typedef enum input {UP, DOWN, RIGHT, LEFT, CONFIRM, CANCEL, ERROR, EMPTY} input;

// Get the input from the player, and return it
input get_input(int sym);

// Print the given input in the console
void print_input(input inp);

#endif // INPUTKEY_H_INCLUDED
