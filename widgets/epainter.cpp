#include "epainter.h"

ePainter::ePainter(SDL_Renderer* const renderer) :
    mRenderer(renderer) {

}

void ePainter::save() {
    ePainterSave save;
    save.fX = mX;
    save.fY = mY;
    save.fFont = mFont;
    mSaves.emplace(mSaves.end(), save);
}

void ePainter::restore() {
    if(mSaves.empty()) return;
    const auto save = mSaves.back();
    mSaves.pop_back();
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
                           const eTexture& tex,
                           const eAlignment align) const {
    int xx = x;
    if(static_cast<bool>(align & eAlignment::left)) {
        xx -= tex.width();
    } else if(static_cast<bool>(align & eAlignment::hcenter)) {
        xx -= tex.width()/2;
    }

    int yy = y;
    if(static_cast<bool>(align & eAlignment::top)) {
        yy -= tex.height();
    } else if(static_cast<bool>(align & eAlignment::vcenter)) {
        yy -= tex.height()/2;
    }

    drawTexture(xx, yy, tex);
}

void ePainter::drawTexture(const SDL_Rect& rect,
                           const eTexture& tex,
                           const eAlignment align) const {
    int xx;
    if(static_cast<bool>(align & eAlignment::right)) {
        xx = rect.x + rect.w - tex.width();
    } else if(static_cast<bool>(align & eAlignment::hcenter)) {
        xx = rect.x + (rect.w - tex.width())/2;
    } else {
        xx = rect.x;
    }

    int yy;
    if(static_cast<bool>(align & eAlignment::bottom)) {
        yy = rect.y + rect.h - tex.height();
    } else if(static_cast<bool>(align & eAlignment::vcenter)) {
        yy = rect.y + (rect.h - tex.height())/2;
    } else {
        yy = rect.y;
    }

    drawTexture(xx, yy, tex);
}

void ePainter::drawTexture(const int x, const int y,
                           const eTexture& tex) const {
    tex.render(mRenderer, mX + x, mY + y);
}

void ePainter::fillRect(const SDL_Rect& rect,
                        const SDL_Color& color) const {
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    const SDL_Rect dRect{rect.x + mX, rect.y + mY, rect.w, rect.h};
    SDL_RenderFillRect(mRenderer, &dRect);
}

void ePainter::drawRect(const SDL_Rect& rect,
                        const SDL_Color& color,
                        const int width) {
    const SDL_Rect r1{rect.x,
                      rect.y,
                      rect.w,
                      width};
    const SDL_Rect r2{rect.x,
                      rect.y + rect.h - width,
                      rect.w,
                      width};
    const SDL_Rect r3{rect.x,
                      rect.y + width,
                      width,
                      rect.h - 2*width};
    const SDL_Rect r4{rect.x + rect.w - width,
                      rect.y + + width,
                      width,
                      rect.h - 2*width};
    fillRect(r1, color);
    fillRect(r2, color);
    fillRect(r3, color);
    fillRect(r4, color);
}

void ePainter::drawText(const int x, const int y,
                        const std::string& text,
                        const SDL_Color& color,
                        const eAlignment align) const {
    if(!mFont) return;

    eTexture tex;
    tex.loadText(mRenderer, text, color, *mFont);

    drawTexture(x, y, tex, align);
}

void ePainter::drawText(const SDL_Rect& rect,
                        const std::string& text,
                        const SDL_Color& color,
                        const eAlignment align) const {
    if(!mFont) return;

    eTexture tex;
    tex.loadText(mRenderer, text, color, *mFont);

    drawTexture(rect, tex, align);
}

void ePainter::drawPolygon(std::vector<SDL_Point> pts,
                           const SDL_Color& color) const {
    for(auto& pt : pts) {
        pt.x += mX;
        pt.y += mY;
    }
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(mRenderer, pts.data(), pts.size());
}
