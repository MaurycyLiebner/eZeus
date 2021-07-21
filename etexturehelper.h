#ifndef ETEXTUREHELPER_H
#define ETEXTUREHELPER_H

#include <SDL2/SDL_image.h>

#include <string>

namespace eTextureHelper {
    SDL_Texture* loadTexture(const std::string& path);
};

#endif // ETEXTUREHELPER_H
