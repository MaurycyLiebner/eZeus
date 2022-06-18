#include "efontcolor.h"

void eFontColorHelpers::colors(const eFontColor c,
                               SDL_Color& col1,
                               SDL_Color& col2) {
    switch(c) {
    case eFontColor::light:
        col1 = SDL_Color{255, 255, 255, 255};
        col2 = SDL_Color{0, 0, 0, 255};
        break;
    case eFontColor::dark:
        col1 = SDL_Color{16, 65, 99, 255};
        col2 = SDL_Color{140, 210, 247, 255};
        break;
    }
}
