#ifndef EPAINTER_H
#define EPAINTER_H

#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "etexture.h"

enum class eAlignment {
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

class ePainter {
    struct ePainterSave {
        int fX;
        int fY;
        TTF_Font* fFont;
    };
public:
    ePainter(SDL_Renderer* const renderer);

    SDL_Renderer* renderer() const { return mRenderer; }

    void save();
    void restore();

    void translate(const int x, const int y);

    void setFont(TTF_Font* const font);

    void drawTexturePortion(
            const int x, const int y,
            const int srcX, const int srcW,
            const std::shared_ptr<eTexture>& tex,
            const eAlignment align) const;
    void drawTexturePortion(
            const int dstX, const int dstY,
            const int srcX, const int srcW,
            const std::shared_ptr<eTexture>& tex) const;

    void drawTexture(const int x, const int y,
                     const std::shared_ptr<eTexture>& tex,
                     const eAlignment align) const;
    void drawTexture(const SDL_Rect& rect,
                     const std::shared_ptr<eTexture>& tex,
                     const eAlignment align) const;
    void drawTexture(const int x, const int y,
                     const std::shared_ptr<eTexture>& tex) const;
    void fillRect(const SDL_Rect& rect,
                  const SDL_Color& color) const;
    void drawRect(const SDL_Rect& rect,
                  const SDL_Color& color,
                  const int width);
    void drawText(const int x, const int y,
                  const std::string& text,
                  const eFontColor color,
                  const eAlignment align = eAlignment::bottom |
                                           eAlignment::right) const;
    void drawText(const SDL_Rect& rect,
                  const std::string& text,
                  const eFontColor color,
                  const eAlignment align = eAlignment::bottom |
                                           eAlignment::right) const;
    void drawPolygon(std::vector<SDL_Point> pts,
                     const SDL_Color& color) const;

    void setClipRect(const SDL_Rect* const rect);
private:
    std::vector<ePainterSave> mSaves;

    int mX = 0;
    int mY = 0;

    TTF_Font* mFont = nullptr;

    SDL_Renderer* mRenderer;
};

#endif // EPAINTER_H
