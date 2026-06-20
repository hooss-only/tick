#include "title_element.h"

#include <stdio.h>
#include <string.h>
#include <raylib.h>

static void render(element_t* self);

element_t* get_title_element(void) {
        element_t* e = get_element();
        
        e->x = GetScreenWidth() / 2.f; e->y = GetScreenHeight() / 2.f;
        e->render = render;

        return e;
}

void render(element_t* self) {
        int width = MeasureText("TICK", 48);
        DrawText("TICK.", self->x - width/2.f, self->y - 24, 48, WHITE);
}
