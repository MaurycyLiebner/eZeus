#ifndef EBINARYIMAGELOADER_H
#define EBINARYIMAGELOADER_H

#include "etexture.h"

class eBinaryImageLoader {
public:
    static std::shared_ptr<eTexture> load(SDL_Renderer* const r,
                                          const std::string& path);
};

#endif // EBINARYIMAGELOADER_H
