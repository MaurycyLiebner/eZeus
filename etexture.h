#ifndef ETEXTURE_H
#define ETEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

#include "widgets/efonts.h"

#include "efontcolor.h"


enum class eAlignment {
    none = 0x0000,
    left = 0x0001,
    right = 0x0002,
    hcenter = 0x0004,

    top = 0x0020,
    bottom = 0x0040,
    vcenter = 0x0080,

    center = vcenter | hcenter
};

inline eAlignment operator|(const eAlignment a, const eAlignment b) {
    return static_cast<eAlignment>(static_cast<int>(a) | static_cast<int>(b));
}

inline eAlignment operator&(const eAlignment a, const eAlignment b) {
    return static_cast<eAlignment>(static_cast<int>(a) & static_cast<int>(b));
}

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
                  const int width = 0,
                  const eAlignment align = eAlignment::left);
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const eFontColor color,
                  const eFont& font,
                  const int width = 0,
                  const eAlignment align = eAlignment::left);

    void renderRelPortion(SDL_Renderer* const r,
                          const int dstX,
                          const int dstY,
                          const int srcX,
                          const int w,
                          const bool flipped) const;

    void render(SDL_Renderer* const r,
                const SDL_Rect& srcRect,
                const SDL_Rect& dstRect,
                const bool flipped = false) const;
    void render(SDL_Renderer* const r,
                const int x, const int y,
                const bool flipped = false) const;

    int x() const { return mX; }
    int y() const { return mY; }

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
    void setParentTexture(const SDL_Rect& rect,
                          const std::shared_ptr<eTexture>& tex);

    SDL_Texture* tex() const { return mTex; }
private:
    std::shared_ptr<eTexture> mParentTex;
    int mX = 0;
    int mY = 0;
    int mWidth = 0;
    int mHeight = 0;
    int mOffsetX = 0;
    int mOffsetY = 0;
    std::shared_ptr<eTexture> mFlipTex;
    SDL_Texture* mTex = nullptr;
};

#endif // ETEXTURE_H
