#include "splash_screen.h"

#include "screens/clock_screen.h"
#include "elements/title_element.h"

#include <stdio.h>
#include <stdlib.h>

double start;

static void update(screen_t* self);

screen_t* get_splash_screen(void) {
        screen_t* s = get_screen();

        s->update = update;

        start = GetTime();

        add_screen_element(s, get_title_element());

        return s;
}

void update(screen_t* _) {
        if (GetTime() - start >= 3.f) {
                change_screen(get_clock_screen());
        }
}
