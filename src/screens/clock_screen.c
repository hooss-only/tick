#include "clock_screen.h"

#include "elements/clock_element.h"

#include <raylib.h>

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

#define ACTIVATION_DURATION 10
void update(screen_t* self) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (!activated) {
                        activated = true;
                        activate_clock_element(clock_element);
                }
                activated_time = GetTime();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && activated)
                activated_time = GetTime();

        if (activated && GetTime() - activated_time >= ACTIVATION_DURATION) {
                activated = false;
                deactivate_clock_element(clock_element);
        }

        screen_update(self);
}
