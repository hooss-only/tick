#pragma once

#include "element.h"

#define MAXIMUM_ELEMENT_AMOUNT 100

typedef struct screen screen_t;

struct screen {
        void (*update)(screen_t* self);
        void (*render)(screen_t* self);
        void (*destroy)(screen_t* self);
        
        element_t* elements[MAXIMUM_ELEMENT_AMOUNT];
        unsigned int element_amount;
};

screen_t* current_screen;
void change_screen(screen_t* next_screen);

screen_t* get_screen(void);
void destroy_screen(screen_t* screen);
void add_screen_element(screen_t* screen, element_t* element);
