#include "clock_screen.h"

#include "elements/clock_element.h"

#include "screens/weather_screen.h"

#include <raylib.h>
#include <math.h>

static void update(screen_t* self);
static void render(screen_t* self);
static void destroy(screen_t* self);

bool activated = false;
double activated_time = 0;
element_t* clock_element;

screen_t* get_clock_screen(void) {
        screen_t* s = get_screen();

        s->update = update;
        s->render = render;
        s->destroy = destroy;
        
        clock_element = get_clock_element();
        add_screen_element(s, clock_element);

        return s;
}

bool dragging;
int initial_mouse_x;

screen_t* weather_screen = 0;

#define ACTIVATION_DURATION 10
void update(screen_t* self) {
        screen_update(self); 

        if (!self->is_perfect_screen) {
                return;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (!activated) {
                        activated = true;
                        activate_clock_element(clock_element);
                }
                activated_time = GetTime();
                dragging = false;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && activated) {
                activated_time = GetTime();
                if (dragging) {
                        self->base.x = GetMouseX() - initial_mouse_x;
                } else {
                        dragging = true;
                        initial_mouse_x = GetMouseX() - self->base.x;

                        if (weather_screen == 0 && self->is_perfect_screen) {
                                weather_screen = get_weather_screen();
                                weather_screen->is_perfect_screen = false;
                        }
                }
        }

        if (activated && GetTime() - activated_time >= ACTIVATION_DURATION) {
                activated = false;
                deactivate_clock_element(clock_element);
        }

        if (weather_screen) {
                weather_screen->base.x = GetScreenWidth() + self->base.x;
                weather_screen->update(weather_screen);
        }

        if (!dragging) {
                if (fabsf(self->base.x) <= 0.01f) {
                        self->base.x = 0;
                        if (weather_screen) {
                                destroy_screen(weather_screen);
                                weather_screen = 0;
                        }
                        return;
                }

                if (fabs(GetScreenWidth() + self->base.x) <= 0.1f && weather_screen) {
                        weather_screen->base.x = 0;
                        screen_t* tmp = weather_screen;
                        weather_screen = 0;
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
        if (weather_screen)
                weather_screen->render(weather_screen);
        screen_render(self);
}

void destroy(screen_t* self) {
        if (weather_screen) {
                destroy_screen(weather_screen);
        }
}
