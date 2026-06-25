#include "weather_screen.h"

#include "screens/clock_screen.h"
#include "utils/swipe_transition.h"

static void update(screen_t* self);
static void render(screen_t* self);

screen_t* get_weather_screen(void) {
        screen_t* s = get_screen();

        s->update = update;
        s->render = render;

        return s;
}

void update(screen_t* self) {
        screen_update(self);

        process_dragging(self, get_clock_screen, 0);
}

void render(screen_t* self) {
        DrawText(
                "Weather screen",
                self->base.x,
                self->base.y,
                32,
                WHITE
        );
        
        render_side_screens(self);
}

void destroy(screen_t* self) {
        destroy_side_screens(self);
}
