#ifndef EFONTS_H
#define EFONTS_H

#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

struct eFont {
    std::string fPath;
    int fPtSize;

    bool isNull() const { return fPath.empty(); }
};

inline bool operator<(const eFont& p0, const eFont& p1) {
    if(p0.fPath == p1.fPath) return p0.fPtSize < p1.fPtSize;
    return p0.fPath < p1.fPath;
}

class eFonts {
public:
    static TTF_Font* requestFont(const eFont& font);
    static TTF_Font* defaultFont();

    static void setDefaultFont(const eFont& font);
    static void setDefaultFontSize(const int size);
private:
    static TTF_Font* loadFont(const eFont& font);

    static std::map<eFont, TTF_Font*> sFonts;
    static eFont sDefaultFont;
};

#endif // EFONTS_H
