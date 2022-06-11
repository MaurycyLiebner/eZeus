#ifndef ELABELBASE_H
#define ELABELBASE_H

#include "ewidget.h"
#include "efonts.h"

class eLabelBase {
public:
    eLabelBase(eMainWindow* const window);

    bool setTinyFontSize();
    bool setVerySmallFontSize();
    bool setSmallFontSize();
    bool setHugeFontSize();

    bool setFont(const eFont& font);
    bool setFontSize(const int s);
    bool setText(const std::string& text);
    bool setTexture(const std::shared_ptr<eTexture>& tex);
    bool setFontColor(const SDL_Color& color);

    SDL_Color fontColor() const
    { return mFontColor; }
    void setWhiteFontColor();
    void setDarkerFontColor();

    int fontSize() const;

    void setWrapWidth(const int w);
protected:
    const std::shared_ptr<eTexture>& texture() { return mTexture; }
    bool setFont(TTF_Font* const font);
private:
    bool updateTextTexture();
    eResolution res() const;

    int mWidth = 0;
    eMainWindow* const mWindow;
    TTF_Font* mFont = nullptr;
    std::string mText;
    std::shared_ptr<eTexture> mTexture;
    SDL_Color mFontColor{255, 255, 255, 255};
};

#endif // ELABELBASE_H
