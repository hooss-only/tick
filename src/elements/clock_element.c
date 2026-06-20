#include "clock_element.h"

#include "fonts/pretendard.h"

#include <time.h>

static void update(element_t* self);
static void render(element_t* self);

char timetext[16];

element_t* get_clock_element(void) {
        element_t* e = get_element();
        
        e->update = update;
        e->render = render;
        
        return e;
}

void update(element_t* self) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        strftime(timetext, sizeof(timetext), "%H : %M", t);

        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        self->pos.x = GetScreenWidth() / 2.f - size.x / 2.f;
        self->pos.y = GetScreenHeight() / 2.f - size.y / 2.f;
}

void render(element_t* self) {
        DrawTextEx(
                pretendard_ttf.black,
                timetext,
                self->pos,
                128,
                0,
                WHITE
        );
}
