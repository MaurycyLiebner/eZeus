#ifndef ELABELBASE_H
#define ELABELBASE_H

#include "ewidget.h"
#include "efonts.h"

class eLabelBase {
public:
    eLabelBase(SDL_Renderer* const renderer);

    bool setFont(const eFont& font);
    bool setFontSize(const int s);
    bool setText(const std::string& text);
    bool setTexture(const std::shared_ptr<eTexture>& tex);
    bool setFontColor(const SDL_Color& color);

    SDL_Color fontColor() const
    { return mFontColor; }
protected:
    const std::shared_ptr<eTexture>& texture() { return mTexture; }
    bool setFont(TTF_Font* const font);
private:
    bool updateTextTexture();

    SDL_Renderer* const mRenderer;
    TTF_Font* mFont = nullptr;
    std::string mText;
    std::shared_ptr<eTexture> mTexture;
    SDL_Color mFontColor{255, 255, 255, 255};
};

#endif // ELABELBASE_H
