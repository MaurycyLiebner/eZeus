#include "edemeter.h"

#include "engine/etile.h"

eDemeter::eDemeter(std::vector<eDemeterTextures>& texs) :
    mTextures(texs) {

}

eTexture eDemeter::getTexture(const eTileSize size) const {
    if(mAction == eDemeterAction::walk) {
        const int id = static_cast<int>(size);
        const int oid = static_cast<int>(orientation());
        const auto& coll = mTextures[id].fWalk[oid];
        return coll.getTexture((time()/4) % coll.size());
    }
    return eTexture();
}
