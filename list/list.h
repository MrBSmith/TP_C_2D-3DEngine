#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "element.h"

typedef struct List{
    Element* first;
    Element* last;
} List;

//// PROTOTYPES ////

// Initialize a list and returns a pointer to it
List* list_init();

// Add a gameobject as the first element of the list
void append_first_list(List* p_list, GameObject* new_object);

// Add a gameobject as the last element of the list
void append_last_list(List* p_list, GameObject* new_object);

// Add a gameobject at the given index of the list
void append_at_index_list(List* p_list, GameObject* p_new_object, int index);

// Free the first element of the list, and returns it
GameObject* free_first_list(List *p_list);

// Free the last element of the list, and returns it
GameObject* free_last_list(List* p_list);

// Free the element at the given index in the list and returns it
GameObject* free_at_index_list(List* p_list, int index);

#endif // LIST_H_INCLUDED
