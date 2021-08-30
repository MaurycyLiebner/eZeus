#include "espriteframe.h"

eSpriteFrame::eSpriteFrame(const std::shared_ptr<eTexture>& tex,
                           const SDL_Rect& srcRect) :
    mTex(tex), mSrcRect(srcRect) {

}

void eSpriteFrame::render(SDL_Renderer* const r,
                          const int x, const int y) const {
    mTex->render(r, x, y, mSrcRect);
}
