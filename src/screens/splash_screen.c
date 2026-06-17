#include "splash_screen.h"

#include <stdio.h>
#include <stdlib.h>

void update(void);

screen_t* get_splash_screen(void) {
        screen_t* splash_screen = get_screen();

        splash_screen->update = update;

        return splash_screen;
}

void update(void) {
        printf("update splash\n");
        return;
}
