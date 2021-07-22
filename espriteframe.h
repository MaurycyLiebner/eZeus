#ifndef ESPRITEFRAME_H
#define ESPRITEFRAME_H

#include "etexture.h"

class eSpriteFrame {
public:
    eSpriteFrame(const eTexture& tex,
                 const SDL_Rect& srcRect);

    void render(SDL_Renderer* const r,
                const int x, const int y) const;
private:
    const eTexture mTex;
    const SDL_Rect mSrcRect;
};

#endif // ESPRITEFRAME_H
