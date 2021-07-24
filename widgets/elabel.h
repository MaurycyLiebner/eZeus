#ifndef ELABEL_H
#define ELABEL_H

#include "ewidget.h"
#include "efonts.h"

class eLabel : public eWidget {
public:
    eLabel(eMainWindow* const window);
    eLabel(const std::string& text,
           eMainWindow* const window);

    bool setFont(const eFont& font);
    bool setText(const std::string& text);
    bool setFontColor(const SDL_Color& color);
protected:
    void sizeHint(int& w, int& h);
    void paintEvent(ePainter& p);
private:
    bool setFont(TTF_Font* const font);
    bool updateTextTexture();

    TTF_Font* mFont = nullptr;
    std::string mText;
    eTexture mTextTex;
    SDL_Color mFontColor{0, 0, 0, 255};
};

#endif // ELABEL_H
