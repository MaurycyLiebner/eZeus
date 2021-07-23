#include "etexture.h"

eTexture::eTexture() {}

eTexture::eTexture(const eTexture& other) {
    *this = other;
}

eTexture::~eTexture() {
    reset();
}

eTexture& eTexture::operator=(const eTexture& src) {
    if(&src == this) return *this;
    reset();
    mWidth = src.mWidth;
    mHeight = src.mHeight;
    mTex = src.mTex;
    mRefs = src.mRefs;
    return *this;
}

void eTexture::reset() {
    if(mTex) {
        if(--(*mRefs) == 0) {
            SDL_DestroyTexture(mTex);
        }
    }
    mTex = nullptr;
    mWidth = 0;
    mHeight = 0;
    mRefs.reset();
}

bool eTexture::load(SDL_Renderer* const r,
                    const std::string& path) {
    reset();
    const auto surf = IMG_Load(path.c_str());
    if(!surf) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
        return false;
    }
    mTex = SDL_CreateTextureFromSurface(r, surf);
    mWidth = surf->w;
    mHeight = surf->h;
    mRefs = std::make_shared<int>(1);
    SDL_FreeSurface(surf);
    if(!mTex) {
        printf("Unable to create texture from %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
        return false;
    }

    return true;
}

bool eTexture::loadText(SDL_Renderer* const r,
                        const std::string& text,
                        const SDL_Color& color,
                        TTF_Font& font) {
    reset();
    const auto surf = TTF_RenderText_Blended(&font, text.c_str(), color);
    if(!surf) {
        printf("Unable to render text! SDL_ttf Error: %s\n",
               TTF_GetError());
        return false;
    }
    mTex = SDL_CreateTextureFromSurface(r, surf);
    mWidth = surf->w;
    mHeight = surf->h;
    mRefs = std::make_shared<int>(1);
    SDL_FreeSurface(surf);
    if(!mTex) {
        printf("Unable to create texture from rendered text! "
               "SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void eTexture::render(SDL_Renderer* const r,
                      const SDL_Rect& srcRect,
                      const SDL_Rect& dstRect) const {
    if(!mTex) return;
    SDL_RenderCopy(r, mTex, &srcRect, &dstRect);
}

void eTexture::render(SDL_Renderer* const r,
                      const int x, const int y,
                      const SDL_Rect& srcRect) const {
    const SDL_Rect dstRect{x, y, srcRect.w, srcRect.h};
    render(r, srcRect, dstRect);
}

void eTexture::render(SDL_Renderer* const r,
                      const int x, const int y) const {
    const SDL_Rect srcRect{0, 0, mWidth, mHeight};
    const SDL_Rect dstRect{x, y, mWidth, mHeight};
    render(r, srcRect, dstRect);
}

bool eTexture::isNull() const {
    return mWidth <= 0 || mHeight <= 0;
}
