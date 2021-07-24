#include "efonts.h"

std::map<eFont, TTF_Font*> eFonts::sFonts;
eFont eFonts::sDefaultFont;

TTF_Font* eFonts::requestFont(const eFont& font) {
    const auto it = sFonts.find(font);
    if(it != sFonts.end()) return it->second;
    const auto ttf = loadFont(font);
    if(ttf) sFonts.insert({font, ttf});
    return ttf;
}

TTF_Font* eFonts::defaultFont() {
    if(sDefaultFont.isNull()) {
        setDefaultFont({"fonts/FreeSans.ttf", 28});
    }
    return requestFont(sDefaultFont);
}

void eFonts::setDefaultFont(const eFont& font) {
    requestFont(font);
    sDefaultFont = font;
}

void eFonts::setDefaultFontSize(const int size) {
    defaultFont();
    sDefaultFont.fPtSize = size;
    defaultFont();
}

TTF_Font* eFonts::loadFont(const eFont& font) {
    const auto ttf = TTF_OpenFont(font.fPath.c_str(), font.fPtSize);
    if(!ttf) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return ttf;
}
