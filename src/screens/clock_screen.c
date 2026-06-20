#include "clock_screen.h"

#include "elements/clock_element.h"

#include <raylib.h>

static void update(screen_t* self);

bool activated = false;
double activated_time = 0;

screen_t* get_clock_screen(void) {
        screen_t* s = get_screen();

        s->update = update;

        add_screen_element(s, get_clock_element());

        return s;
}

#define ACTIVATION_DURATION 10
void update(screen_t* self) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (!activated) {
                        activated = true;
                }
                activated_time = GetTime();
        }

        if (activated && GetTime() - activated_time >= ACTIVATION_DURATION) {
                activated = false;
        }

        screen_update(self);
}
