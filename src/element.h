#pragma once

typedef struct element element_t;

struct element {
        float x, y;

        void (*update)(element_t* self);
        void (*render)(element_t* self);
        void (*destroy)(element_t* self);
};

element_t* get_element(void);
