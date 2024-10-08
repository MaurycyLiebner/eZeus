#include "etexture.h"

#include <algorithm>

eTexture::eTexture() {}

eTexture::~eTexture() {
    reset();
}

void eTexture::reset() {
    if(mTex) SDL_DestroyTexture(mTex);
    mTex = nullptr;
    mWidth = 0;
    mHeight = 0;
}

bool eTexture::create(SDL_Renderer* const r,
                      const int width, const int height) {
    reset();
    mTex = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, width, height);
    if(!mTex) return false;
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

SDL_Texture*  generateTextTexture(SDL_Renderer* const r,
                                 const std::string& text,
                                 const SDL_Color& color,
                                 TTF_Font& font,
                                 const int width,
                                 int& w, int& h) {
    SDL_Surface* surf;
    if(width) {
        surf = TTF_RenderUTF8_Blended_Wrapped(&font, text.c_str(), color, width);
    } else {
        surf = TTF_RenderUTF8_Blended(&font, text.c_str(), color);
    }
    if(!surf) {
        printf("Unable to render text! SDL_ttf Error: %s\n",
               TTF_GetError());
        return nullptr;
    }
    const auto tex = SDL_CreateTextureFromSurface(r, surf);
    if(!tex) {
        printf("Unable to create texture from rendered text! "
               "SDL Error: %s\n", SDL_GetError());
        return nullptr;
    }
    w = surf->w;
    h = surf->h;
    SDL_FreeSurface(surf);
    return tex;
}

std::vector<std::string> textLines(const std::string& text,
                                   TTF_Font& font,
                                   const int width) {
    std::vector<std::string> result;
    const int ts = text.size();
    std::string word;
    std::string line;
    int index = 0;
    while(index < ts) {
        const bool isLast = index == ts - 1;
        const auto c = text[index++];
        if(c == ' ' || c == '\n' || isLast) {
            if(isLast && c != ' ' && c != '\n') word += c;
            int w = 0;
            int h = 0;
            const auto newLine = line + (line.empty() ? "" : " ") + word;
            TTF_SizeUTF8(&font, newLine.c_str(), &w, &h);
            if(line.empty() || w < width) {
                line = newLine;
                if(c == '\n') {
                    result.push_back(line);
                    line = "";
                }
            } else {
                result.push_back(line);
                if(c == '\n') {
                    result.push_back(word);
                    line = "";
                } else {
                    line = word;
                }
            }
            word = "";
        } else {
            word += c;
        }
    }
    if(!word.empty()) line += (line.empty() ? "" : " ") + word;
    if(!line.empty()) result.push_back(line);
    return result;
}

bool eTexture::loadText(SDL_Renderer* const r,
                        const std::string& text,
                        const eFontColor color,
                        TTF_Font& font,
                        const int width,
                        const eAlignment align) {
    reset();

    if(width) {
        int w;
        int h;
        TTF_SizeUTF8(&font, text.c_str(), &w, &h);
        if(w > width) {
            const auto lines = textLines(text, font, width);
            mWidth = 0;
            mHeight = 0;
            std::vector<std::shared_ptr<eTexture>> texs;
            for(const auto& l : lines) {
                auto& tex = texs.emplace_back();
                if(!l.empty()) {
                    tex = std::make_shared<eTexture>();
                    tex->loadText(r, l, color, font);
                    mHeight += tex->height();
                    mWidth = std::max(mWidth, tex->width());
                } else {
                    mHeight += h;
                }
            }
            mTex = SDL_CreateTexture(r, SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);

            if(!mTex) {
                printf("Unable to create texture! "
                       "SDL Error: %s\n", SDL_GetError());
                return false;
            }
            {
                SDL_SetRenderTarget(r, mTex);
                const auto bm = SDL_ComposeCustomBlendMode(
                                    SDL_BLENDFACTOR_ONE,
                                    SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                                    SDL_BLENDOPERATION_ADD,

                                    SDL_BLENDFACTOR_ONE,
                                    SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                                    SDL_BLENDOPERATION_ADD);
                SDL_SetTextureBlendMode(mTex, bm);

                SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
                SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
                SDL_RenderFillRect(r, NULL);

                int y = 0;
                for(const auto& tex : texs) {
                    if(tex) {
                        const int w = tex->width();
                        const int x = align == eAlignment::hcenter ?
                                          (mWidth - w)/2 : 0;
                        const SDL_Rect dstRect{x, y, w, tex->height()};
                        SDL_RenderCopy(r, tex->mTex, NULL, &dstRect);
                        y += dstRect.h;
                    } else {
                        y += h;
                    }
                }

                SDL_SetRenderTarget(r, nullptr);
            }

            return true;
        }
    }

    SDL_Color col1;
    SDL_Color col2;
    eFontColorHelpers::colors(color, col1, col2);

    int w;
    int h;
    const auto tex1 = generateTextTexture(r, text, col1,
                                          font, width, w, h);
    if(!tex1) return false;
    const auto tex2 = generateTextTexture(r, text, col2,
                                          font, width, w, h);
    if(!tex2) return false;

    const int dx = 1;
    const int dy = 1;

    mWidth = w + dx;
    mHeight = h + dy;
    mTex = SDL_CreateTexture(r, SDL_PIXELFORMAT_ARGB8888,
                             SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);

    if(!mTex) {
        printf("Unable to create texture! "
               "SDL Error: %s\n", SDL_GetError());
        return false;
    }
    {
        SDL_SetRenderTarget(r, mTex);
        const auto bm = SDL_ComposeCustomBlendMode(
                            SDL_BLENDFACTOR_ONE,
                            SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                            SDL_BLENDOPERATION_ADD,

                            SDL_BLENDFACTOR_ONE,
                            SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                            SDL_BLENDOPERATION_ADD);
        SDL_SetTextureBlendMode(mTex, bm);

        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
        SDL_RenderFillRect(r, NULL);

        const SDL_Rect dstRect2{0, 0, w, h};
        SDL_RenderCopy(r, tex2, NULL, &dstRect2);
        SDL_SetTextureAlphaMod(tex2, 128);
        SDL_RenderCopy(r, tex2, NULL, &dstRect2);
        const SDL_Rect dstRect1{dx, dy, w, h};
        SDL_RenderCopy(r, tex1, NULL, &dstRect1);
        SDL_SetTextureAlphaMod(tex1, 128);
        SDL_RenderCopy(r, tex1, NULL, &dstRect1);

        SDL_DestroyTexture(tex2);
        SDL_DestroyTexture(tex1);

        SDL_SetRenderTarget(r, nullptr);
    }
    return true;
}

bool eTexture::loadText(SDL_Renderer* const r,
                        const std::string& text,
                        const eFontColor color,
                        const eFont& font,
                        const int width,
                        const eAlignment align) {
    const auto ttf = eFonts::requestFont(font);
    if(!ttf) return false;
    return loadText(r, text, color, *ttf, width, align);
}

void eTexture::render(SDL_Renderer* const r,
                      const SDL_Rect& srcRect,
                      const SDL_Rect& dstRect,
                      const bool flipped) const {
    if(mFlipTex) {
        mFlipTex->render(r, srcRect, dstRect, true);
    } else if(mParentTex) {
        mParentTex->render(r, srcRect, dstRect, flipped);
    } else if(mTex) {
        if(flipped) {
            SDL_RenderCopyEx(r, mTex, &srcRect, &dstRect, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
        } else {
            SDL_RenderCopy(r, mTex, &srcRect, &dstRect);
        }
    }
}

void eTexture::render(SDL_Renderer* const r,
                      const int x, const int y,
                      const bool flipped) const {
    const int sx = mFlipTex ? mFlipTex->x() : mX;
    const int sy = mFlipTex ? mFlipTex->y() : mY;
    const int width = mFlipTex ? mFlipTex->width() : mWidth;
    const int height = mFlipTex ? mFlipTex->height() : mHeight;
    const SDL_Rect srcRect{sx, sy, width, height};
    const SDL_Rect dstRect{x, y, width, height};
    render(r, srcRect, dstRect, flipped);
}

void eTexture::renderRelPortion(SDL_Renderer* const r,
                                const int dstX,
                                const int dstY,
                                const int srcX,
                                const int w,
                                const bool flipped) const {
    const int sx = mFlipTex ? mFlipTex->x() : mX;
    const int sy = mFlipTex ? mFlipTex->y() : mY;
    const int width = mFlipTex ? mFlipTex->width() : mWidth;
    const int height = mFlipTex ? mFlipTex->height() : mHeight;
    const int ww = std::min(w + srcX, width) - srcX;
    SDL_Rect srcRect{sx + srcX, sy, ww, height};
    SDL_Rect dstRect{dstX, dstY, ww, height};
    if(srcRect.x < sx) {
        const int dx = sx - srcRect.x;
        srcRect.x += dx;
        dstRect.x += dx;
        srcRect.w -= dx;
        dstRect.w -= dx;
    }
    if(srcRect.y < sy) {
        const int dy = sy - srcRect.y;
        srcRect.y += dy;
        dstRect.y += dy;
        srcRect.h -= dy;
        dstRect.h -= dy;
    }
    if(srcRect.x + srcRect.w > sx + width) {
        const int dw = sx + width - srcRect.x - srcRect.w;
        srcRect.w += dw;
        dstRect.w += dw;
    }
    if(srcRect.y + srcRect.h > sy + height) {
        const int dh = sy + height - srcRect.y - srcRect.h;
        srcRect.h += dh;
        dstRect.h += dh;
    }
    if(srcRect.w <= 0 || srcRect.h <= 0 ||
       dstRect.w <= 0 || dstRect.h <= 0) return;
    if(mFlipTex) {
        srcRect.x = mFlipTex->width() - srcRect.x - srcRect.w;
    }
    render(r, srcRect, dstRect, flipped);
}

void eTexture::setOffset(const int x, const int y) {
    mOffsetX = x;
    mOffsetY = y;
}

bool eTexture::isNull() const {
    if(mFlipTex) return mFlipTex->isNull();
    else if(mParentTex) mParentTex->isNull();
    return mWidth <= 0 || mHeight <= 0;
}

void eTexture::setAlpha(const Uint8 alpha) {
    if(mFlipTex) mFlipTex->setAlpha(alpha);
    else if(mParentTex) mParentTex->setAlpha(alpha);
    else SDL_SetTextureAlphaMod(mTex, alpha);
}

void eTexture::clearAlphaMod() {
    setAlpha(255);
}

void eTexture::setColorMod(const Uint8 r, const Uint8 g, const Uint8 b) {
    if(mFlipTex) mFlipTex->setColorMod(r, g, b);
    else if(mParentTex) mParentTex->setColorMod(r, g, b);
    else SDL_SetTextureColorMod(mTex, r, g, b);
}

void eTexture::clearColorMod() {
    setColorMod(255, 255, 255);
}

void eTexture::setFlipTex(const std::shared_ptr<eTexture>& tex) {
    mFlipTex = tex;
    mX = mFlipTex->x();
    mY = mFlipTex->y();
    mWidth = mFlipTex->width();
    mHeight = mFlipTex->height();
}

void eTexture::setParentTexture(const SDL_Rect& rect,
                                const std::shared_ptr<eTexture>& tex) {
    mParentTex = tex;
    mX = rect.x;
    mY = rect.y;
    mWidth = rect.w;
    mHeight = rect.h;
}
