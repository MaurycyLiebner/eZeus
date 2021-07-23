#ifndef EBUTTON_H
#define EBUTTON_H

#include "ewidget.h"
#include "efonts.h"

class eButton : public eWidget {
public:
    eButton(SDL_Renderer* const renderer);

    bool setFont(const eFont& font);
    bool setText(const std::string& text);
    bool setFontColor(const SDL_Color& color);
private:
    bool setFont(TTF_Font* const font);
    bool updateTextTexture();

    TTF_Font* mFont = nullptr;
    std::string mText;
    eTexture mTextTex;
    SDL_Color mFontColor{0, 0, 0, 255};

    eTexture mTexture;
    eTexture mHoverTexture;
    eTexture mPressedTexture;

    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);

    bool mPressed = false;
    bool mHover = false;
};

#endif // EBUTTON_H
