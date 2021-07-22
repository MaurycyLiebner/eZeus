#include "esprites.h"

eSprites::eSprites() {

}

void eSprites::renderFrame(SDL_Renderer* const r,
                           const int x, const int y,
                           const int frame) const {
    if(frame < 0) return;
    const uint uFrame = frame;
    if(uFrame >= mFrames.size()) return;
    mFrames[uFrame].render(r, x, y);
}
