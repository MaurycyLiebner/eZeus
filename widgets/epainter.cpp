#include "epainter.h"

ePainter::ePainter(SDL_Renderer* const renderer) :
    mRenderer(renderer) {

}

void ePainter::save() {
    ePainterSave save;
    save.fX = mX;
    save.fY = mY;
    save.fFont = mFont;
    mSaves.emplace(save);
}

void ePainter::restore() {
    if(mSaves.empty()) return;
    const auto save = mSaves.front();
    mSaves.pop();
    mX = save.fX;
    mY = save.fY;
    mFont = save.fFont;
}

void ePainter::translate(const int x, const int y) {
    mX += x;
    mY += y;
}

void ePainter::setFont(TTF_Font* const font) {
    mFont = font;
}

void ePainter::drawTexture(const int x, const int y,
                           const eTexture& tex) const {
    tex.render(mRenderer, mX + x, mY + y);
}

void ePainter::fillRect(const SDL_Rect& rect,
                        const SDL_Color& color) const {
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(mRenderer, &rect);
}

void ePainter::drawText(const int x, const int y,
                        const std::string& text,
                        const SDL_Color& color) const {
    if(!mFont) return;
    eTexture tex;
    tex.loadText(mRenderer, text, color, *mFont);
    drawTexture(x, y, tex);
}
