#include "clock.h"

void update_clock(void) {
        time_t now = time(NULL);
        t = localtime(&now);
}
