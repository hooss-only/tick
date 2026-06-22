#include "title_element.h"

#include "fonts/pretendard.h"

#include <stdio.h>
#include <string.h>

static void render(element_t* self, Vector2 base);

element_t* get_title_element(void) {
        element_t* e = get_element();
        
        Vector2 size = MeasureTextEx(pretendard_ttf.black, "TICK", 64, 0);
        e->pos.x = GetScreenWidth() / 2.f - size.x / 2.f;
        e->pos.y = GetScreenHeight() / 2.f - size.y / 2.f;

        e->render = render;

        return e;
}

void render(element_t* self, Vector2 base) {
        DrawTextEx(
                pretendard_ttf.black,
                "TICK.",
                self->pos,
                64,
                0,
                WHITE
        );
}
