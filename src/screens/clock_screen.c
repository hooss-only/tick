#include "clock_screen.h"

#include "elements/clock_element.h"

#include <raylib.h>

screen_t* get_clock_screen(void) {
        screen_t* s = get_screen();

        add_screen_element(s, get_clock_element());

        return s;
}
