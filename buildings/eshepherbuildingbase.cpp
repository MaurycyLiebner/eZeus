#include "eshepherbuildingbase.h"

#include "textures/egametextures.h"
#include "characters/actions/eshepherdaction.h"

eShepherBuildingBase::eShepherBuildingBase(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const eResourceType resType,
        const eCharacterType animalType,
        const int sw, const int sh,
        const int maxEmployees) :
    eResourceBuildingBase(board, type, sw, sh,
                          maxEmployees, resType),
    mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mAnimalType(animalType) {

}

eShepherBuildingBase::~eShepherBuildingBase() {
    if(mShepherd) mShepherd->kill();
}

std::shared_ptr<eTexture> eShepherBuildingBase::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eShepherBuildingBase::getOverlays(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    return std::vector<eOverlay>({o});
}

void eShepherBuildingBase::timeChanged(const int by) {
    eResourceBuildingBase::timeChanged(by);
    if(!mShepherd) {
        mSpawnTime += by;
        const int period = eNumbers::sShepherdGoatherdWaitTime;
        const int wait = period/effectiveness();
        if(mSpawnTime > wait) {
            mSpawnTime = 0;
            spawn();
        }
    }
}

void eShepherBuildingBase::read(eReadStream& src) {
    eResourceBuildingBase::read(src);
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mShepherd = static_cast<eResourceCollectorBase*>(c);
    });
    src >> mSpawnTime;
}

void eShepherBuildingBase::write(eWriteStream& dst) const {
    eResourceBuildingBase::write(dst);
    dst.writeCharacter(mShepherd.get());
    dst << mSpawnTime;
}

bool eShepherBuildingBase::spawn() {
    if(resource() >= maxResource()) return false;
    const auto t = centerTile();
    const auto s = mCharGenerator(getBoard());
    mShepherd = s.get();
    s->changeTile(t);
    const auto a = e::make_shared<eShepherdAction>(
                       this, s.get(),
                       mAnimalType);
    s->setAction(a);
    return true;
}
