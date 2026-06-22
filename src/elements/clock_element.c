#include "clock_element.h"

#include "clock.h"
#include "fonts/pretendard.h"

#include <time.h>
#include <string.h>
#include <math.h>

static void update(element_t* self);
static void render(element_t* self, Vector2 base);

char timetext[16];
char combined[16];

element_t* get_clock_element(void) {
        element_t* e = get_element();
        
        e->update = update;
        e->render = render;

        strcpy(combined, "%H : %M : %S");

        strftime(timetext, sizeof(timetext), combined, t);
        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        e->pos.x = GetScreenWidth() / 2.f - size.x / 2.f;
        e->pos.y = GetScreenHeight() / 2.f - size.y / 2.f;

        return e;
}

void process_animation(element_t* self);
void update(element_t* self) {
        strftime(timetext, sizeof(timetext), combined, t);
        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        self->pos.x = GetScreenWidth() / 2.f - size.x / 2.f;
        self->pos.y = GetScreenHeight() / 2.f - size.y / 2.f;
        process_animation(self);
}

float alpha = 1;

void render(element_t* self, Vector2 base) {
        Vector2 tmp_pos = { self->pos.x, self->pos.y };
        self->pos.x += base.x;
        self->pos.y += base.y;

        strftime(timetext, sizeof(timetext), "%H : %M", t);
        DrawTextEx(
                pretendard_ttf.black,
                timetext,
                self->pos,
                128,
                0,
                WHITE
        );
        
        strftime(timetext, sizeof(timetext), "%H : %M : %S", t);
        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        float x = GetScreenWidth() / 2.f - size.x / 2.f;

        strftime(timetext, sizeof(timetext), "%H : %M", t);
        size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        x += size.x;

        Vector2 pos = { x + base.x, self->pos.y };

        strftime(timetext, sizeof(timetext), " : %S", t);
        
        DrawTextEx(
                pretendard_ttf.black,
                timetext,
                pos,
                128,
                0,
                ColorAlpha(WHITE, alpha)
        );
        
        self->pos.x = tmp_pos.x;
        self->pos.y = tmp_pos.y;
}

typedef enum {
        ACTIVATION,
        IDLE,
        DEACTIVATION,
} animations;
animations playing_animation = IDLE;

float dest_x;
float diff;

void activate_clock_element(element_t* e) {
        strftime(timetext, sizeof(timetext), "%H : %M : %S", t);

        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        dest_x = GetScreenWidth() / 2.f - size.x / 2.f;

        diff = dest_x - e->pos.x;

        alpha = 0;

        playing_animation = ACTIVATION;
}

void deactivate_clock_element(element_t* e) {
        strftime(timetext, sizeof(timetext), "%H : %M", t);

        Vector2 size = MeasureTextEx(pretendard_ttf.black, timetext, 128, 0);
        dest_x = GetScreenWidth() / 2.f - size.x / 2.f;

        diff = dest_x - e->pos.x;

        alpha = 1;

        playing_animation = DEACTIVATION;
}

void play_activation(element_t* self);
void play_deactivation(element_t* self);

void process_animation(element_t* self) {
        switch (playing_animation) {
                case IDLE: 
                        return;

                case ACTIVATION:
                        play_activation(self);
                        break;

                case DEACTIVATION:
                        play_deactivation(self);
                        break;
        }
}

void play_activation(element_t* self) {
        diff *= 0.95;
        self->pos.x = dest_x - diff;
        
        if (alpha < 1) alpha += 0.1;

        if (fabsf(diff) <= 0.01f) {
                strcpy(combined, "%H : %M : %S");
                playing_animation = IDLE;
        }
}

void play_deactivation(element_t* self) {
        diff *= 0.95;
        self->pos.x = dest_x - diff;
        
        if (alpha > 0) alpha -= 0.1;

        if (fabsf(diff) <= 0.1f) {
                strcpy(combined, "%H : %M");
                playing_animation = IDLE;
        }
}

