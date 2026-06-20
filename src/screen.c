#include "screen.h"
#include <stdlib.h>

void change_screen(screen_t* next) {
        destroy_screen(current_screen);
        current_screen = next;
}

void add_element(screen_t* screen, element_t* element);

screen_t* get_screen(void) {
        screen_t* screen = malloc(sizeof(screen_t));

        screen->update = screen_update;
        screen->render =  screen_render;
        screen->destroy = screen_destroy;

        screen->element_amount = 0;

        return screen;
}

void add_screen_element(screen_t* screen, element_t* element) {
        screen->elements[screen->element_amount++] = element;
}

void screen_update(screen_t* self) {
        element_t* e;
        for (unsigned int i=0; i<self->element_amount; i++) {
                e = self->elements[i];
                e->update(e);
        }
        return;
}

void screen_render(screen_t* self) {
        element_t* e;
        for (unsigned int i=0; i<self->element_amount; i++) {
                e = self->elements[i];
                e->render(e);
        }
        return;
}

void screen_destroy(screen_t* _) {
        return;
}

void destroy_screen(screen_t* screen) {
        screen->destroy(screen);
        for (unsigned int i=0; i<screen->element_amount; i++) {
                element_t* e = screen->elements[i];
                e->destroy(e);
                free(e);
        }
        free(screen);
        return;
}
