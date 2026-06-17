#include "splash_screen.h"

#include <stdio.h>
#include <stdlib.h>

void init(void);
void update(void);
void render(void);

screen_t* get_splash_screen(void) {
        screen_t* splash_screen = malloc(sizeof(screen_t));

        splash_screen->init = init;
        splash_screen->update = update;
        splash_screen->render = render;

        return splash_screen;
}

void init(void) {
        return;
}

void update(void) {
        printf("update splash\n");
        return;
}

void render(void) {
        return;
}
