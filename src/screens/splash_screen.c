#include "splash_screen.h"

#include "elements/title_element.h"

#include <stdio.h>
#include <stdlib.h>

screen_t* get_splash_screen(void) {
        screen_t* s = get_screen();

        add_screen_element(s, get_title_element());

        return s;
}
