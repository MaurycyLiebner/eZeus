#include "edemeter.h"

#include "engine/etile.h"

eDemeter::eDemeter(std::vector<eDemeterTextures>& texs) :
    mTextures(texs) {

}

eTexture eDemeter::getTexture(const eTileSize size) const {
    if(mAction == eDemeterAction::walk) {
        const int id = static_cast<int>(size);
        const auto& coll = mTextures[id].fWalk[0];
        return coll.getTexture(mTime % coll.size());
    }
    return eTexture();
}
