#include "element.h"
#include <stdlib.h>

static void basic_update(element_t* e) { return; }
static void basic_render(element_t* e, Vector2 base) { return; }
static void basic_destroy(element_t* self);

element_t* get_element(void) {
        element_t* element = malloc(sizeof(element_t));

        element->update = basic_update;
        element->render =  basic_render;
        element->destroy = basic_destroy;

        return element;
}

void basic_destroy(element_t* _) {
        return;
}

void destroy_element(element_t* element) {
        free(element);
        return;
}
