#include "screen.h"
#include <stdlib.h>

void change_screen(screen_t* next) {
        unsigned int previous_screen_id = current_screen->id;
        TraceLog(LOG_INFO, "Screen changed: [ID %d] -> [id %d]", previous_screen_id, next->id);
        destroy_screen(current_screen);
        next->is_perfect_screen = true;
        current_screen = next;
}

void add_element(screen_t* screen, element_t* element);

unsigned int id = 0;
screen_t* get_screen(void) {
        screen_t* screen = malloc(sizeof(screen_t));
        
        screen->id = id++;
        screen->update = screen_update;
        screen->render =  screen_render;
        screen->destroy = screen_destroy;

        screen->base.x = 0;
        screen->base.y = 0;

        screen->is_perfect_screen = true;

        screen->element_amount = 0;

        TraceLog(LOG_INFO, "[ID %d] New screen is created", screen->id);
        return screen;
}

void add_screen_element(screen_t* screen, element_t* element) {
        screen->elements[screen->element_amount++] = element;
}

void screen_update(screen_t* self) {
        element_t* e;
        for (uint32_t i=0; i<self->element_amount; i++) {
                e = self->elements[i];
                e->update(e);
        }
        return;
}

void screen_render(screen_t* self) {
        element_t* e;
        for (uint32_t i=0; i<self->element_amount; i++) {
                e = self->elements[i];
                e->render(e, self->base);
        }
        return;
}

void screen_destroy(screen_t* _) {
        return;
}

void destroy_screen(screen_t* screen) {
        uint32_t id = screen->id;
        screen->destroy(screen);
        for (uint32_t i=0; i<screen->element_amount; i++) {
                element_t* e = screen->elements[i];
                e->destroy(e);
                free(e);
        }
        free(screen);
        TraceLog(LOG_INFO, "[ID %d] Screen is destroyed", id);
        return;
}
