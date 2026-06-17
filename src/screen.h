#pragma once

typedef struct screen_t screen_t;

struct screen_t {
        void (*init)(void);
        void (*update)(void);
        void (*render)(void);
        void (*destroy)(screen_t* self);
};

screen_t* get_screen(void);
void destroy_screen(screen_t* screen);
