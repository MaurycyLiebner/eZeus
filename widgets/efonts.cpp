#include "efonts.h"

std::map<eFont, TTF_Font*> eFonts::sFonts;

TTF_Font* eFonts::requestFont(const eFont& font) {
    const auto it = sFonts.find(font);
    if(it != sFonts.end()) return it->second;
    const auto ttf = loadFont(font);
    if(ttf) sFonts.insert({font, ttf});
    return ttf;
}

TTF_Font* eFonts::loadFont(const eFont& font) {
    const auto ttf = TTF_OpenFont(font.fPath.c_str(), font.fPtSize);
    if(!ttf) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return ttf;
}
