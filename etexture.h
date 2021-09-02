#ifndef ETEXTURE_H
#define ETEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

#include "widgets/efonts.h"

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
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const SDL_Color& color,
                  TTF_Font& font);
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const SDL_Color& color,
                  const eFont& font);

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
    void setColorMod(const Uint8 r, const Uint8 g, const Uint8 b);
    void clearColorMod();
private:
    int mWidth = 0;
    int mHeight = 0;
    int mOffsetX = 0;
    int mOffsetY = 0;
    SDL_Texture* mTex = nullptr;
};

#endif // ETEXTURE_H
