#include "etemplealtarbuilding.h"

#include "textures/egametextures.h"

#include "esanctuary.h"
#include "engine/egameboard.h"

eTempleAltarBuilding::eTempleAltarBuilding(eGameBoard& board) :
    eSanctBuilding({0, 4, 0}, 1, board,
                   eBuildingType::templeAltar, 2, 2) {
    setOverlayEnabledFunc([this]() {
        const auto s = sanctuary();
        return s->finished();
    });
}

std::shared_ptr<eTexture>
eTempleAltarBuilding::getTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    return blds.fSanctuaryAltar;
}

std::vector<eOverlay> eTempleAltarBuilding::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const eTextureCollection* coll = nullptr;
    if(mSacrifice == eSacrifice::sheep) {
        eGameTextures::loadAltarSheepOverlay();
        coll = &blds.fAltarSheepOverlay;
    } else if(mSacrifice == eSacrifice::goods) {
        eGameTextures::loadAltarGoodsOverlay();
        coll = &blds.fAltarGoodsOverlay;
    } else if(mSacrifice == eSacrifice::bull) {
        eGameTextures::loadAltarBullOverlay();
        coll = &blds.fAltarBullOverlay;
    } else {
        return {};
    }
    std::vector<eOverlay> result;
    const int frame = textureTime();
    const auto& tex = coll->getTexture(frame % coll->size());
    result.emplace_back(eOverlay{-1.7, -3.4, tex, false});
    return result;
}

void eTempleAltarBuilding::timeChanged(const int by) {
    mSacrificeTime += by;
    if(mSacrificeTime > 25000) {
        mSacrifice = eSacrifice::none;
        if(mSacrificeTime > 100000) {
            eSacrifice s = eSacrifice::goods;
            auto& board = getBoard();
            const auto hasChar = [&](const eCharacterType type) {
                const auto& chars = board.characters();
                for(const auto c : chars) {
                    const auto t = c->type();
                    if(t == type) return true;
                }
                return false;
            };
            if(hasChar(eCharacterType::bull)) {
                s = eSacrifice::bull;
            } else if(hasChar(eCharacterType::sheep)) {
                s = eSacrifice::sheep;
            }
            startSacrifice(s);
        }
    }
}

void eTempleAltarBuilding::read(eReadStream& src) {
    eSanctBuilding::read(src);
    src >> mSacrifice;
    src >> mSacrificeTime;
}

void eTempleAltarBuilding::write(eWriteStream& dst) const {
    eSanctBuilding::write(dst);
    dst << mSacrifice;
    dst << mSacrificeTime;
}

void eTempleAltarBuilding::startSacrifice(const eSacrifice s) {
    mSacrifice = s;
    mSacrificeTime = 0;
}
