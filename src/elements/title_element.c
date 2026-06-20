#include "title_element.h"

#include <stdio.h>
#include <string.h>
#include <raylib.h>

static void render(element_t* self);

element_t* get_title_element(void) {
        element_t* e = get_element();

        e->render = render;

        return e;
}

void render(element_t* self) {
        DrawText("TICK.", self->x, self->y, 10, WHITE);
}
