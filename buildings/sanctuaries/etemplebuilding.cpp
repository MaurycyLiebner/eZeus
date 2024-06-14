#include "etemplebuilding.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

eTempleBuilding::eTempleBuilding(eGameBoard& board) :
    eSanctBuilding({5, 5, 0}, 3, board,
                   eBuildingType::temple, 4, 4) {}

eTempleBuilding::eTempleBuilding(
        const int id, eGameBoard& board) :
    eTempleBuilding(board) {
    mId = id;
    setEnabled(true);
}

std::shared_ptr<eTexture>
eTempleBuilding::getTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int id = p - 1;
    auto& board = getBoard();
    if(board.poseidonMode() && id == 2) {
        eGameTextures::loadPoseidonSanctuary();
        const auto& coll = blds.fPoseidonSanctuary;
        return coll.getTexture(mId);
    } else {
        if(id == 2) {
            eGameTextures::loadZeusSanctuary();
        }
        const auto& coll = blds.fSanctuary[mId];
        return coll.getTexture(id);
    }
}

std::vector<eOverlay> eTempleBuilding::getOverlays(const eTileSize size) const {
    const int p = progress();
    if(p < 3) {
        return {};
    }
    if(mId != 0 && mId != 1) {
        return {};
    }
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int tt = textureTime();
    eOverlay o;
    if(mId == 0) {
        o.fX = -0.45;
        o.fY = -2.75;
        const auto& coll = blds.fSanctuaryHOverlay;
        o.fTex = coll.getTexture(tt % coll.size());
    } else {
        o.fX = 1.45;
        o.fY = -4.65;
        const auto& coll = blds.fSanctuaryWOverlay;
        o.fTex = coll.getTexture(tt % coll.size());
    }
    return {o};
}

void eTempleBuilding::read(eReadStream& src) {
    eSanctBuilding::read(src);

    src >> mId;
}

void eTempleBuilding::write(eWriteStream& dst) const {
    eSanctBuilding::write(dst);

    dst << mId;
}
