#include "etexturehelper.h"

#include "ewindowrenderer.h"

SDL_Texture* eTextureHelper::loadTexture(const std::string& path) {
    const auto surf = IMG_Load(path.c_str());
    if(!surf) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
        return nullptr;
    }
    const auto renderer = eWindowRenderer::instance();
    const auto result = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if(!result) {
        printf("Unable to create texture from %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
        return nullptr;
    }

    return result;
}
