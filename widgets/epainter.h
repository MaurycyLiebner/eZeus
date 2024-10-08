#ifndef EPAINTER_H
#define EPAINTER_H

#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "etexture.h"

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

    int x() const { return mX; }
    int y() const { return mY; }
private:
    std::vector<ePainterSave> mSaves;

    int mX = 0;
    int mY = 0;

    TTF_Font* mFont = nullptr;

    SDL_Renderer* mRenderer;
};

#endif // EPAINTER_H
