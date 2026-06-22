#include "weather_screen.h"

static void render(screen_t* self);

screen_t* get_weather_screen(void) {
        screen_t* s = get_screen();

        s->render = render;

        return s;
}

void render(screen_t* self) {
        DrawText(
                "Weather screen",
                self->base.x,
                self->base.y,
                32,
                WHITE
        );
}
