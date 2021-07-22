#ifndef EPAINTER_H
#define EPAINTER_H

#include <SDL2/SDL_ttf.h>

#include <string>
#include <queue>

#include "etexture.h"

struct ePainterSave {
    int fX;
    int fY;
    TTF_Font* fFont;
};

class ePainter {
public:
    ePainter(SDL_Renderer* const renderer);

    void save();
    void restore();

    void translate(const int x, const int y);

    void setFont(TTF_Font* const font);

    void drawTexture(const int x, const int y,
                     const eTexture& tex) const;
    void fillRect(const SDL_Rect& rect,
                  const SDL_Color& color) const;
    void drawText(const int x, const int y,
                  const std::string& text,
                  const SDL_Color& color) const;
private:
    std::queue<ePainterSave> mSaves;

    int mX = 0;
    int mY = 0;

    TTF_Font* mFont = nullptr;

    SDL_Renderer* mRenderer;
};

#endif // EPAINTER_H
