#include "list.h"

// Initization function for queues
List* list_init(){
    List* p_new_list = malloc(sizeof(List));

    // Error when loading the pile exit program
    if(p_new_list == NULL){
        exit(EXIT_FAILURE);
    }

    // Setup the new pile to be empty
    p_new_list -> first = NULL;

    return p_new_list;
}


// Function to add an element to the queue
void append_last_list(List* p_list, GameObject* p_new_object){
    // Allocation on the size of an element in the pile
    Element *new_elem = malloc(sizeof(*new_elem));

    // Error when loading either the pile or the new element
    // Exit program
    if (p_list == NULL || new_elem == NULL){
        exit(EXIT_FAILURE);
    }

    // Add an element to the list
    new_elem -> object = p_new_object;
    new_elem -> next_elem = NULL;

    // In case the p_list isn't empty
    if(p_list -> first != NULL){
        Element* current_elem = p_list -> first;
        // Loop through the entire list, until we get the very last element
        while(current_elem -> previous_elem != NULL){
            current_elem = current_elem -> previous_elem;
        }

        // Give to the next element the reference to the new one
        current_elem -> previous_elem = new_elem;
        new_elem -> next_elem = current_elem;
    } else {
        p_list -> first = new_elem;
    }
}


// Function to stack a new element on top of a pile
void append_first_list(List* p_list, GameObject* p_new_object){
    // Allocation on the size of an element in the pile
    Element *new_elem = malloc(sizeof(*new_elem));

    // Error when loading either the pile or the new element
    // Exit program
    if (p_list == NULL || new_elem == NULL){
        exit(EXIT_FAILURE);
    }

    // Add an element to the top of the list
    new_elem -> object = p_new_object;
    new_elem -> next_elem = p_list -> first;
    p_list -> first = new_elem;
}


// Append an element at th given position on the list, from the first element
void append_at_index_list(List* p_list, GameObject* p_new_object, int index){
    // Allocation on the size of an element in the pile
    Element *new_elem = malloc(sizeof(*new_elem));

    // Error when loading either the pile or the new element
    // Exit program
    if (p_list == NULL || new_elem == NULL){
        exit(EXIT_FAILURE);
    }


        // Add an element to the list
    new_elem -> object = p_new_object;
    new_elem -> next_elem = NULL;

    // In case the p_list isn't empty
    if(p_list -> first != NULL){
        Element* current_elem = p_list -> first;
        // Loop through the entire list, until we get the very last element
        for(int i = 0; i != index ;i++){
            current_elem = current_elem -> previous_elem;
        }

        // Give to the next element the reference to the new one
        current_elem -> previous_elem = new_elem;
        new_elem -> next_elem = current_elem;
    } else {
        p_list -> first = new_elem;
    }

}


// Free the first element of the list, and returns it
GameObject* free_first_list(List* p_list){
    // Error when loading the queue exit program
    if (p_list == NULL){
        exit(EXIT_FAILURE);
    }

    GameObject* p_removed_object = NULL;
    Element* p_removed_elem = p_list -> first;

    // Get the value of the element to unstack, if the queue is not empty
    if(p_list -> first != NULL){
        p_removed_object = p_removed_elem -> object;
        p_list -> first = p_removed_elem -> next_elem;
        free(p_removed_elem);
    }
    return p_removed_object;
}


// Free the last element of the list, and returns it
GameObject* free_last_list(List* p_list){
    // Error when loading the queue exit program
    if (p_list == NULL){
        exit(EXIT_FAILURE);
    }

    GameObject* p_removed_object = NULL;
    Element* p_removed_elem = p_list -> last;

    // Get the value of the element to unstack, if the queue is not empty
    if(p_list -> last != NULL){
        p_removed_object = p_removed_elem -> object;
        p_list -> last = p_removed_elem -> previous_elem;
        free(p_removed_elem);
    }
    return p_removed_object;
}


// Free the element at the given index in the list and returns it
GameObject* free_at_index_list(List* p_list, int index){
    // Error when loading either the pile
    if (p_list == NULL){
        exit(EXIT_FAILURE);
    }

    GameObject* p_removed_object = NULL;

    // In case the p_list isn't empty
    if(p_list -> first != NULL){
        Element* current_elem = p_list -> first;
        // Loop through the entire list, until we get the very last element
        for(int i = 0; i != index; i++){
            current_elem = current_elem -> previous_elem;
        }


        // Get the value of the element to unstack, if the queue is not empty
        p_removed_object = current_elem -> object;
        current_elem -> previous_elem -> next_elem = current_elem -> next_elem;
        current_elem -> next_elem -> previous_elem = current_elem -> previous_elem;
        free(current_elem);
    }

    return p_removed_object;
}
