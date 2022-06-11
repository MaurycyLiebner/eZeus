#ifndef ETEXTURE_H
#define ETEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

#include "widgets/efonts.h"

#include "efontcolor.h"

class eTexture {
public:
    eTexture();
    ~eTexture();

    void reset();
    bool create(SDL_Renderer* const r,
                const int width, const int height);
    void setAsRenderTarget(SDL_Renderer* const r);
    bool load(SDL_Renderer* const r,
              const std::string& path);
    bool load(SDL_Renderer* const r,
              SDL_Surface* const surf);
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const eFontColor color,
                  TTF_Font& font,
                  const int width = 0);
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const eFontColor color,
                  const eFont& font,
                  const int width = 0);

    void render(SDL_Renderer* const r,
                const SDL_Rect& srcRect,
                const SDL_Rect& dstRect) const;
    void render(SDL_Renderer* const r,
                const int x, const int y,
                const SDL_Rect& srcRect) const;
    void render(SDL_Renderer* const r,
                const int x, const int y) const;

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    void setOffset(const int x, const int y);

    int offsetX() const { return mOffsetX; }
    int offsetY() const { return mOffsetY; }

    bool isNull() const;

    void setAlpha(const Uint8 alpha);
    void clearAlphaMod();
    void setColorMod(const Uint8 r, const Uint8 g, const Uint8 b);
    void clearColorMod();

    void setFlipTex(const std::shared_ptr<eTexture>& tex);
private:
    int mWidth = 0;
    int mHeight = 0;
    int mOffsetX = 0;
    int mOffsetY = 0;
    std::shared_ptr<eTexture> mFlipTex;
    SDL_Texture* mTex = nullptr;
};

#endif // ETEXTURE_H
