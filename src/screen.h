#pragma once

#include "element.h"

#define MAXIMUM_ELEMENT_AMOUNT 100

typedef struct screen_t screen_t;

struct screen_t {
        void (*init)(void);
        void (*update)(void);
        void (*render)(void);
        void (*destroy)(screen_t* self);
        
        element_t* elements[MAXIMUM_ELEMENT_AMOUNT];
        unsigned int element_amount;
};

screen_t* get_screen(void);
void destroy_screen(screen_t* screen);
void add_element(screen_t* screen, element_t* element);
