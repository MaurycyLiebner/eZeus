#include "etexture.h"

eTexture::eTexture() {}

eTexture::~eTexture() {
    reset();
}

void eTexture::reset() {
    if(mTex) SDL_DestroyTexture(mTex);
    mTex = nullptr;
}

bool eTexture::create(SDL_Renderer* const r,
                      const int width, const int height) {
    reset();
    mTex = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(mTex, SDL_BLENDMODE_BLEND);
    mWidth = width;
    mHeight = height;
    return true;
}

void eTexture::setAsRenderTarget(SDL_Renderer* const r) {
    SDL_SetRenderTarget(r, mTex);
}

bool eTexture::load(SDL_Renderer* const r, const std::string& path) {
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
    SDL_FreeSurface(surf);
    if(!mTex) {
        printf("Unable to create texture from rendered text! "
               "SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool eTexture::loadText(SDL_Renderer* const r,
                        const std::string& text,
                        const SDL_Color& color,
                        const eFont& font) {
    const auto ttf = eFonts::requestFont(font);
    if(!ttf) return false;
    return loadText(r, text, color, *ttf);
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

void eTexture::setOffset(const int x, const int y) {
    mOffsetX = x;
    mOffsetY = y;
}

bool eTexture::isNull() const {
    return mWidth <= 0 || mHeight <= 0;
}

void eTexture::setAlpha(const Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTex, alpha);
}

void eTexture::setColorMod(const Uint8 r, const Uint8 g, const Uint8 b) {
    SDL_SetTextureColorMod(mTex, r, g, b);
}

void eTexture::clearColorMod() {
    setColorMod(255, 255, 255);
}
