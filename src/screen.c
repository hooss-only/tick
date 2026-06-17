#include "screen.h"
#include <stdlib.h>

void destroy_screen(screen_t* screen) {
        free(screen);
        return;
}
