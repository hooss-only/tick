#include "title_element.h"

#include "fonts/pretendard.h"

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
        Vector2 size = MeasureTextEx(pretendard_ttf.black, "TICK", 64, 0);
        Vector2 pos = {
                self->x - size.x / 2.f,
                self->y - size.y / 2.f
        };
        DrawTextEx(
                pretendard_ttf.black,
                "TICK.",
                pos,
                64,
                0,
                WHITE
        );
}
