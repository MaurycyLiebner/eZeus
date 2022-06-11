#include "efontcolor.h"

SDL_Color eFontColorHelpers::color(const eFontColor c) {
    switch(c) {
    case eFontColor::light:
        return SDL_Color{255, 255, 255, 255};
    case eFontColor::dark:
        return SDL_Color{0, 0, 0, 255};
    }
}

void eFontColorHelpers::colors(const eFontColor c,
                               SDL_Color& col1,
                               SDL_Color& col2) {
    switch(c) {
    case eFontColor::light:
        col1 = eFontColorHelpers::color(eFontColor::light);
        col2 = eFontColorHelpers::color(eFontColor::dark);
        break;
    case eFontColor::dark:
        col1 = eFontColorHelpers::color(eFontColor::dark);
        col2 = eFontColorHelpers::color(eFontColor::light);
        break;
    }
}
