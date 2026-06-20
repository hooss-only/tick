#pragma once

#include <raylib.h>

typedef struct element element_t;

struct element {
        Vector2 pos;

        void (*update)(element_t* self);
        void (*render)(element_t* self);
        void (*destroy)(element_t* self);
};

element_t* get_element(void);
