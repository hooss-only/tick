#include "weather_screen.h"

#include "screens/clock_screen.h"

#include <math.h>

static void update(screen_t* self);
static void render(screen_t* self);

screen_t* get_weather_screen(void) {
        screen_t* s = get_screen();

        s->update = update;
        s->render = render;

        return s;
}

bool dragging;
int initial_mouse_x;

screen_t* clock_screen;

void update(screen_t* self) {
        screen_update(self);

        if (!self->is_perfect_screen) {
                return;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                dragging = false;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                if (dragging) {
                        self->base.x = GetMouseX() - initial_mouse_x;
                } else {
                        dragging = true;
                        initial_mouse_x = GetMouseX() - self->base.x;

                        if (clock_screen == 0 && self->is_perfect_screen) {
                                clock_screen = get_clock_screen();
                                clock_screen->is_perfect_screen = false;
                        }
                }
        }

        if (clock_screen) {
                clock_screen->base.x = -1 * GetScreenWidth() + self->base.x;
                clock_screen->update(clock_screen);
        }

        if (!dragging) {
                if (fabsf(self->base.x) <= 0.01f) {
                        self->base.x = 0;
                        if (clock_screen) {
                                destroy_screen(clock_screen);
                                clock_screen = 0;
                        }
                        return;
                }

                if (fabs(GetScreenWidth() + self->base.x) <= 0.1f && clock_screen) {
                        clock_screen->base.x = 0;
                        screen_t* tmp = clock_screen;
                        clock_screen = 0;
                        change_screen(tmp);
                }

                if (self->base.x > GetScreenWidth() / 2.f) {
                        self->base.x = GetScreenWidth() - (GetScreenWidth() - self->base.x) * 0.95f;
                        return;
                }

                if (self->base.x < GetScreenWidth() / -2.f) {
                        self->base.x = -1 * GetScreenWidth() + (GetScreenWidth() + self->base.x) * 0.95f;
                        return;
                }

                self->base.x *= 0.95;
        }

}

void render(screen_t* self) {
        DrawText(
                "Weather screen",
                self->base.x,
                self->base.y,
                32,
                WHITE
        );

        if (clock_screen)
                clock_screen->render(clock_screen);
}

void destroy(screen_t* self) {
        if (clock_screen)
                destroy_screen(clock_screen);
}
