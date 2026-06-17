#pragma once

typedef struct {
        void (*init)(void);
        void (*update)(void);
        void (*render)(void);
} screen_t;

void destroy_screen(screen_t* screen);
