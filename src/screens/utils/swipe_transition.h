#pragma once

#include "screen.h"

void process_dragging(screen_t* s, screen_t* (*get_left_screen)(void), screen_t* (*get_right_screen)(void));

void render_side_screens(screen_t* main_screen);

void destroy_side_screens(screen_t* main_screen);
