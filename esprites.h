#ifndef ESPRITES_H
#define ESPRITES_H

#include "espriteframe.h"

#include <vector>

class eSprites {
public:
    eSprites();

    void renderFrame(SDL_Renderer* const r,
                     const int x, const int y,
                     const int frame) const;
private:
    std::vector<eSpriteFrame> mFrames;
};

#endif // ESPRITES_H
