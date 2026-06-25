#include "clock_screen.h"

#include "elements/clock_element.h"

#include "screens/weather_screen.h"

#include "utils/swipe_transition.h"

#include <raylib.h>

static void update(screen_t* self);
static void render(screen_t* self);
static void destroy(screen_t* self);

bool activated = true;
double activated_time = 0;
element_t* clock_element;

screen_t* get_clock_screen(void) {
        screen_t* s = get_screen();

        s->update = update;
        s->render = render;
        s->destroy = destroy;

        activated_time = GetTime();
        
        clock_element = get_clock_element();
        add_screen_element(s, clock_element);

        return s;
}

#define ACTIVATION_DURATION 10
void update(screen_t* self) {
        screen_update(self); 

        if (activated)
                process_dragging(self, 0, get_weather_screen);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (!activated) {
                        activated = true;
                        activate_clock_element(clock_element);
                }
                activated_time = GetTime();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && activated) {
                activated_time = GetTime();
        }

        if (activated && GetTime() - activated_time >= ACTIVATION_DURATION) {
                activated = false;
                deactivate_clock_element(clock_element);
        }
}

void render(screen_t* self) {
        render_side_screens(self);
        screen_render(self);
}

void destroy(screen_t* self) {
        destroy_side_screens(self);
}
