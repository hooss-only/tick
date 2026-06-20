#pragma once

#include <raylib.h>

typedef struct font_family font_family_t;

struct font_family {
        Font thin;
        Font extralight;
        Font light;
        Font regular;
        Font medium;
        Font semibold;
        Font bold;
        Font extrabold;
        Font black;
};

void unload_font_family(font_family_t* font_family);
