#include "eaestheticsbuilding.h"

#include "textures/egametextures.h"

eAestheticsBuilding::eAestheticsBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const eBuildingType type,
        const int sw, const int sh) :
    eBuilding(board, type, sw, sh),
    mTexture(baseTex) {
    setEnabled(true);
}

std::shared_ptr<eTexture> eAestheticsBuilding::getTexture(
        const eTileSize size) const {
    if(!mTexture) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].*mTexture;
}

eBench::eBench(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fBench,
                        eBuildingType::bench, 1, 1) {

}

eFlowerGarden::eFlowerGarden(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fFlowerGarden,
                        eBuildingType::flowerGarden, 2, 2) {

}

eGazebo::eGazebo(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fGazebo,
                        eBuildingType::gazebo, 2, 2) {

}

eHedgeMaze::eHedgeMaze(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fHedgeMaze,
                        eBuildingType::hedgeMaze, 3, 3) {

}

eFishPond::eFishPond(eGameBoard& board) :
    eOverlayAesthBuilding(board, &eBuildingTextures::fFishPond,
                          0.87, -3.10,
                          &eBuildingTextures::fFishPondOverlay,
                          eBuildingType::fishPond, 4, 4) {

}

eOverlayAesthBuilding::eOverlayAesthBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eBuildingType type,
        const int sw, const int sh) :
    eAestheticsBuilding(board, baseTex, type, sw, sh),
    mOverlays(overlays),
    mOverlayX(overlayX),
    mOverlayY(overlayY) {
    setEnabled(true);
}

std::vector<eOverlay> eOverlayAesthBuilding::getOverlays(
        const eTileSize size) const {
    if(!mOverlays) return {};
    const int sizeId = static_cast<int>(size);
    const auto& coll = eGameTextures::buildings()[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    return std::vector<eOverlay>({o});
}

eBirdBath::eBirdBath(eGameBoard& board) :
    eOverlayAesthBuilding(board, &eBuildingTextures::fBirdBath,
                          -1.35, -1.7,
                          &eBuildingTextures::fBirdBathOverlay,
                          eBuildingType::birdBath, 1, 1) {

}

eShortObelisk::eShortObelisk(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fShortObelisk,
                        eBuildingType::shortObelisk, 1, 1) {

}

eTallObelisk::eTallObelisk(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fTallObelisk,
                        eBuildingType::tallObelisk, 1, 1) {

}

eShellGarden::eShellGarden(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fShellGarden,
                        eBuildingType::shellGarden, 2, 2) {

}

eSundial::eSundial(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fSundial,
                        eBuildingType::sundial, 2, 2) {

}

eDolphinSculpture::eDolphinSculpture(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fDolphinSculpture,
                        eBuildingType::dolphinSculpture, 3, 3) {

}

eSpring::eSpring(eGameBoard& board) :
    eOverlayAesthBuilding(board, nullptr,
                          -3.0, -3.0,
                          &eBuildingTextures::fSpring,
                          eBuildingType::spring, 3, 3) {

}


eTopiary::eTopiary(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fTopiary,
                        eBuildingType::topiary, 3, 3) {

}

eBaths::eBaths(eGameBoard& board) :
    eOverlayAesthBuilding(board, &eBuildingTextures::fBaths,
                          -2.39, -3.20,
                          &eBuildingTextures::fBathsOverlay,
                          eBuildingType::baths, 4, 4) {

}

eStoneCircle::eStoneCircle(eGameBoard& board) :
    eOverlayAesthBuilding(board, &eBuildingTextures::fStoneCircle,
                          -0.5, -4.0,
                          &eBuildingTextures::fStoneCircleOverlay,
                          eBuildingType::stoneCircle, 4, 4) {

}


eWaterPark::eWaterPark(eGameBoard& board) :
    eBuilding(board, eBuildingType::waterPark, 2, 2) {
    setEnabled(true);
}

void eWaterPark::setId(const int i) {
    mId = i % 8;
}

std::shared_ptr<eTexture> eWaterPark::getTexture(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& colls = eGameTextures::buildings();
    const auto& texs = colls[sizeId];

    if(mId == 0) return texs.fWaterPark1;
    if(mId == 1) return texs.fWaterPark2;
    if(mId == 2) return texs.fWaterPark3;
    if(mId == 3) return texs.fWaterPark4;
    if(mId == 4) return texs.fWaterPark5;
    if(mId == 5) return texs.fWaterPark6;
    if(mId == 6) return texs.fWaterPark7;
    else         return texs.fWaterPark8;
}

const eOverlay waterParkOverlays[] = {{-1.27, -2.08, nullptr},
                                      {-1.20, -2.15, nullptr},
                                      {-1.28, -2.13, nullptr},
                                      {-1.27, -2.08, nullptr},
                                      {-1.39, -1.95, nullptr},
                                      {-1.24, -2.34, nullptr},
                                      {-1.25, -2.1, nullptr},
                                      {-1.07, -1.86, nullptr}};

std::vector<eOverlay> eWaterPark::getOverlays(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const eTextureCollection* coll = nullptr;
    if(mId == 0)      coll = &texs.fWaterPark1Overlay;
    else if(mId == 1) coll = &texs.fWaterPark2Overlay;
    else if(mId == 2) coll = &texs.fWaterPark3Overlay;
    else if(mId == 3) coll = &texs.fWaterPark4Overlay;
    else if(mId == 4) coll = &texs.fWaterPark5Overlay;
    else if(mId == 5) coll = &texs.fWaterPark6Overlay;
    else if(mId == 6) coll = &texs.fWaterPark7Overlay;
    else              coll = &texs.fWaterPark8Overlay;
    const int texId = textureTime() % coll->size();
    eOverlay o = waterParkOverlays[mId];
    o.fTex = coll->getTexture(texId);
    return std::vector<eOverlay>({o});
}

eCommemorative::eCommemorative(const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::commemorative, 3, 3),
    mId(id) {

}

std::shared_ptr<eTexture>
eCommemorative::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    return texs.fCommemorative.getTexture(mId);
}

eGodMonument::eGodMonument(const eGodType god, eGameBoard& board) :
    eBuilding(board, eBuildingType::godMonument, 2, 2),
    mGod(god) {}

void eGodMonument::erase() {
    for(const auto& t : mTiles) {
        t->eBuilding::erase();
    }
    eBuilding::erase();
}

#include "buildings/sanctuaries/etemplemonumentbuilding.h"

std::shared_ptr<eTexture> eGodMonument::getTexture(const eTileSize size) const {
    const auto coll = eTempleMonumentBuilding::sGodMonumentTextureCollection(size, mGod);
    return coll->getTexture(1);
}

void eGodMonument::addTile(eGodMonumentTile* const tile) {
    mTiles.push_back(tile);
}

eGodMonumentTile::eGodMonumentTile(eGameBoard& board) :
    eBuilding(board, eBuildingType::godMonumentTile, 1, 1) {}

void eGodMonumentTile::erase() {
    mMonument->erase();
}

std::shared_ptr<eTexture> eGodMonumentTile::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    const auto& coll = texs[sizeId].fPalaceTiles;
    return coll.getTexture(0);
}

void eGodMonumentTile::setMonument(eGodMonument *const mon) {
    mMonument = mon;
}
