#include "clock_screen.h"

#include "elements/clock_element.h"

#include <raylib.h>
#include <math.h>

static void update(screen_t* self);

bool activated = false;
double activated_time = 0;
element_t* clock_element;

screen_t* get_clock_screen(void) {
        screen_t* s = get_screen();

        s->update = update;
        
        clock_element = get_clock_element();
        add_screen_element(s, clock_element);

        return s;
}

bool dragging;
int initial_mouse_x;
#define ACTIVATION_DURATION 10
void update(screen_t* self) {
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
                        initial_mouse_x = GetMouseX() - self->base.x ;
                }
        }

        if (activated && GetTime() - activated_time >= ACTIVATION_DURATION) {
                activated = false;
                deactivate_clock_element(clock_element);
        }

        screen_update(self);

        if (!dragging) {
                if (fabsf(self->base.x) <= 0.01f) {
                        self->base.x = 0;
                        return;
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
