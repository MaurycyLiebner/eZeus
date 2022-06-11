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
    return load(r, surf);
}

bool eTexture::load(SDL_Renderer* const r,
                    SDL_Surface* const surf) {
    reset();
    mTex = SDL_CreateTextureFromSurface(r, surf);
    mWidth = surf->w;
    mHeight = surf->h;
    SDL_FreeSurface(surf);
    if(!mTex) {
        printf("Unable to create texture from surface!"
               "SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

SDL_Texture* generateTextTexture(SDL_Renderer* const r,
                                 const std::string& text,
                                 const SDL_Color& color,
                                 TTF_Font& font,
                                 const int width,
                                 int& w, int& h) {
    SDL_Surface* surf;
    if(width) {
        surf = TTF_RenderText_Blended_Wrapped(&font, text.c_str(), color, width);
    } else {
        surf = TTF_RenderText_Blended(&font, text.c_str(), color);
    }
    if(!surf) {
        printf("Unable to render text! SDL_ttf Error: %s\n",
               TTF_GetError());
        return nullptr;
    }
    const auto tex = SDL_CreateTextureFromSurface(r, surf);
    w = surf->w;
    h = surf->h;
    SDL_FreeSurface(surf);
    return tex;
}

bool eTexture::loadText(SDL_Renderer* const r,
                        const std::string& text,
                        const SDL_Color& color,
                        TTF_Font& font,
                        const int width) {
    reset();
    const auto mTex = generateTextTexture(r, text, color, font,
                                          width, mWidth, mHeight);
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
                        const eFont& font,
                        const int width) {
    const auto ttf = eFonts::requestFont(font);
    if(!ttf) return false;
    return loadText(r, text, color, *ttf, width);
}

void eTexture::render(SDL_Renderer* const r,
                      const SDL_Rect& srcRect,
                      const SDL_Rect& dstRect) const {
    if(mFlipTex) {
        SDL_RenderCopyEx(r, mFlipTex->mTex, &srcRect, &dstRect, 0, nullptr,
                         SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
    } else if(mTex) {
        SDL_RenderCopy(r, mTex, &srcRect, &dstRect);
    }
}

void eTexture::render(SDL_Renderer* const r,
                      const int x, const int y,
                      const SDL_Rect& srcRect) const {
    const SDL_Rect dstRect{x, y, srcRect.w, srcRect.h};
    render(r, srcRect, dstRect);
}

void eTexture::render(SDL_Renderer* const r,
                      const int x, const int y) const {
    const int w = mFlipTex ? mFlipTex->width() : mWidth;
    const int h = mFlipTex ? mFlipTex->height() : mHeight;
    const SDL_Rect srcRect{0, 0, w, h};
    const SDL_Rect dstRect{x, y, w, h};
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
    if(mFlipTex) mFlipTex->setAlpha(alpha);
    else SDL_SetTextureAlphaMod(mTex, alpha);
}

void eTexture::clearAlphaMod() {
    setAlpha(255);
}

void eTexture::setColorMod(const Uint8 r, const Uint8 g, const Uint8 b) {
    if(mFlipTex) mFlipTex->setColorMod(r, g, b);
    else SDL_SetTextureColorMod(mTex, r, g, b);
}

void eTexture::clearColorMod() {
    setColorMod(255, 255, 255);
}

void eTexture::setFlipTex(const std::shared_ptr<eTexture>& tex) {
    mFlipTex = tex;
}
