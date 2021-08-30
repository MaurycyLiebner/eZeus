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

std::shared_ptr<eTexture> eTextureCollection::loadTexture(
        const std::string& path) {
    const auto t = std::make_shared<eTexture>();
    const bool r = t->load(mRenderer, path);
    if(!r) return nullptr;
    mTexs.push_back(t);
    return mTexs.back();
}

std::shared_ptr<eTexture> eTextureCollection::getTexture(const int id) const {
    return mTexs[id];
}

int eTextureCollection::size() const {
    return mTexs.size();
}
