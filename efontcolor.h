#ifndef EFONTCOLOR_H
#define EFONTCOLOR_H

#include <SDL2/SDL.h>

enum class eFontColor {
    light, dark
};

namespace eFontColorHelpers {
    SDL_Color color(const eFontColor c);
    void colors(const eFontColor c,
                SDL_Color& col1,
                SDL_Color& col2);
};

#endif // EFONTCOLOR_H
