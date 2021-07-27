#include "etexturecollection.h"

eTextureCollection::eTextureCollection(SDL_Renderer* const r) :
    mRenderer(r) {

}

void eTextureCollection::draw(ePainter& p,
                              const int x, const int y,
                              const int id) const {
    p.drawTexture(x, y, mTexs[id]);
}

void eTextureCollection::draw(ePainter& p,
                              const int x, const int y,
                              const int id,
                              const eAlignment align) const {
    p.drawTexture(x, y, mTexs[id], align);
}

bool eTextureCollection::loadTexture(
        const std::string& path) {
    eTexture t;
    const bool r = t.load(mRenderer, path);
    if(!r) return false;
    mTexs.push_back(t);
    return true;
}

eTexture eTextureCollection::getTexture(const int id) const {
    return mTexs[id];
}

int eTextureCollection::size() const {
    return mTexs.size();
}
