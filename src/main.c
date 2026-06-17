#include <stdio.h>
#include <raylib.h>

int main(void) {
        const int screen_width = 800;
        const int screen_height = 480;

        InitWindow(screen_width, screen_height, "tick");
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
                BeginDrawing();
                        ClearBackground(BLACK);
                EndDrawing();
        }

        CloseWindow();
        return 0;
}
