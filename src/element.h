#pragma once

typedef struct element_t element_t;

struct element_t {
        float x, y;

        void (*init)(element_t* self);
        void (*update)(element_t* self);
        void (*render)(element_t* self);
        void (*destroy)(element_t* self);
};

element_t* get_element(void);
