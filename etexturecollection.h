#ifndef ETEXTURECOLLECTION_H
#define ETEXTURECOLLECTION_H

#include "etexture.h"
#include "widgets/epainter.h"

class eTextureCollection {
public:
    eTextureCollection(SDL_Renderer* const r);

    void draw(ePainter& p,
              const int x, const int y,
              const int id) const;
    void draw(ePainter& p,
              const int x, const int y,
              const int id,
              const eAlignment align) const;
    eTexture* loadTexture(const std::string& path);
    eTexture getTexture(const int id) const;
    int size() const;
private:
    SDL_Renderer* const mRenderer;
    std::vector<eTexture> mTexs;
};

#endif // ETEXTURECOLLECTION_H
