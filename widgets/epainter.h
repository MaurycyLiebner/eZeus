#ifndef EPAINTER_H
#define EPAINTER_H

#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "etexture.h"

struct ePainterSave {
    int fX;
    int fY;
    TTF_Font* fFont;
};

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
public:
    ePainter(SDL_Renderer* const renderer);

    void save();
    void restore();

    void translate(const int x, const int y);

    void setFont(TTF_Font* const font);

    void drawTexture(const int x, const int y,
                     const eTexture& tex,
                     const eAlignment align) const;
    void drawTexture(const SDL_Rect& rect,
                     const eTexture& tex,
                     const eAlignment align) const;
    void drawTexture(const int x, const int y,
                     const eTexture& tex) const;
    void fillRect(const SDL_Rect& rect,
                  const SDL_Color& color) const;
    void drawRect(const SDL_Rect& rect,
                  const SDL_Color& color,
                  const int width);
    void drawText(const int x, const int y,
                  const std::string& text,
                  const SDL_Color& color,
                  const eAlignment align = eAlignment::bottom |
                                           eAlignment::right) const;
    void drawText(const SDL_Rect& rect,
                  const std::string& text,
                  const SDL_Color& color,
                  const eAlignment align = eAlignment::bottom |
                                           eAlignment::right) const;
    void drawPolygon(std::vector<SDL_Point> pts,
                     const SDL_Color& color) const;
private:
    std::vector<ePainterSave> mSaves;

    int mX = 0;
    int mY = 0;

    TTF_Font* mFont = nullptr;

    SDL_Renderer* mRenderer;
};

#endif // EPAINTER_H
