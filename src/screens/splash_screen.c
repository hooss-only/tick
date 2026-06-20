#include "splash_screen.h"

#include "elements/title_element.h"

#include <stdio.h>
#include <stdlib.h>

static void init(screen_t* self);

screen_t* get_splash_screen(void) {
        screen_t* s = get_screen();

        s->init = init;

        return s;
}

void init(screen_t* self) {
        add_screen_element(self, get_title_element());
}
