#include "font.h"

#define FAMILY_AMOUNT 9

void unload_font_family(font_family_t* font_family) {
        Font* fonts = (Font*) font_family;
        for (int i=0; i<FAMILY_AMOUNT; i++) {
                UnloadFont(fonts[i]);
        }
}
