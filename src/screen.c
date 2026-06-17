#include "screen.h"
#include <stdlib.h>

void basic_init(void) { return; }
void basic_update(void) { return; }
void basic_render(void) { return; }
void basic_destroy(screen_t* self);

screen_t* get_screen(void) {
        screen_t* screen = malloc(sizeof(screen_t));

        screen->init = basic_init;
        screen->update = basic_update;
        screen->render =  basic_render;
        screen->destroy = basic_destroy;

        return screen;
}

void basic_destroy(screen_t* self) {
        return;
}

void destroy_screen(screen_t* screen) {
        free(screen);
        return;
}
