#include "swipe_transition.h"

#include <math.h>

bool dragging;
int initial_mouse_x;

screen_t* left_screen = 0;
screen_t* right_screen = 0;

#define SWIPE_THRESHOLD_RATIO 0.5f
#define SWIPE_SMOOTHING 0.95f
#define TRANSITION_THRESHOLD 1

void process_dragging(screen_t* s, screen_t* (*get_left_screen)(void), screen_t* (*get_right_screen)(void)) {
        if (!s->is_perfect_screen)
                return;
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { 
                dragging = false;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                if (dragging)
                        s->base.x = GetMouseX() - initial_mouse_x;
                else {
                        dragging = true;
                        initial_mouse_x = GetMouseX() - s->base.x;
                        
                        if (left_screen == 0 && get_left_screen) {
                                left_screen = get_left_screen();
                                left_screen->is_perfect_screen = false;
                        }
                        if (right_screen == 0 && get_right_screen) {
                                right_screen = get_right_screen();
                                right_screen->is_perfect_screen = false;
                        }
                }
        }

        if (left_screen) {
                left_screen->base.x = -1 * GetScreenWidth() + s->base.x;
                left_screen->update(left_screen);
        }
        if (right_screen) {
                right_screen->base.x = GetScreenWidth() + s->base.x;
                right_screen->update(right_screen);
        }

        if (!dragging) {
                if (fabsf(s->base.x) < TRANSITION_THRESHOLD) {
                        s->base.x = 0;
                        if (left_screen) {
                                destroy_screen(left_screen);
                                left_screen = 0;
                        }
                        if (right_screen) {
                                destroy_screen(right_screen);
                                right_screen = 0;
                        }
                }

                if (left_screen && left_screen->base.x > -TRANSITION_THRESHOLD) {
                        screen_t* tmp = left_screen;
                        left_screen = 0;
                        change_screen(tmp);
                }
                if (right_screen && right_screen->base.x < TRANSITION_THRESHOLD) {
                        screen_t* tmp = right_screen;
                        right_screen = 0;
                        change_screen(tmp);
                }

                if (s->base.x > GetScreenWidth() * SWIPE_THRESHOLD_RATIO) {
                        s->base.x = GetScreenWidth() - (GetScreenWidth() - s->base.x) * SWIPE_SMOOTHING;
                        return;
                }

                if (s->base.x < GetScreenWidth() * -SWIPE_THRESHOLD_RATIO) {
                        s->base.x = -1 * GetScreenWidth() + (GetScreenWidth() + s->base.x) * SWIPE_SMOOTHING;
                        return;
                }

                s->base.x *= SWIPE_SMOOTHING;
        }
}

void render_side_screens(screen_t* s) {
        if (!s->is_perfect_screen) return;
        if (left_screen)
                left_screen->render(left_screen);
        if (right_screen)
                right_screen->render(right_screen);
}

void destroy_side_screens(screen_t* s) {
        if (!s->is_perfect_screen) return;
        if (left_screen)
                destroy_screen(left_screen);
        if (right_screen)
                destroy_screen(right_screen);
}
