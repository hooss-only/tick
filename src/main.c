#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "screen.h"
#include "screens/splash_screen.h"

#include "fonts/pretendard.h"
#include "font.h"

int main(void) {
        const int screen_width = 800;
        const int screen_height = 480;

        InitWindow(screen_width, screen_height, "tick");
        SetTargetFPS(60);

        load_pretendard();

        current_screen = get_splash_screen();

        while (!WindowShouldClose()) {
                BeginDrawing();
                        ClearBackground(BLACK);
                        current_screen->update(current_screen);
                        current_screen->render(current_screen);
                EndDrawing();
        }
        
        destroy_screen(current_screen);
        unload_font_family(&pretendard_ttf);
        CloseWindow();
        return 0;
}
