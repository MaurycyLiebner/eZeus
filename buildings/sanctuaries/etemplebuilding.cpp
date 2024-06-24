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
    auto& board = getBoard();
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int id = p - 1;
    const int dirId = rotatedId();
    if(board.poseidonMode() && id == 2) {
        eGameTextures::loadPoseidonSanctuary();
        const auto& coll = blds.fPoseidonSanctuary;
        return coll.getTexture(dirId);
    } else {
        if(id == 2) {
            eGameTextures::loadZeusSanctuary();
        }
        const auto& coll = blds.fSanctuary[dirId];
        return coll.getTexture(id);
    }
}

std::vector<eOverlay> eTempleBuilding::getOverlays(const eTileSize size) const {
    const int p = progress();
    if(p < 3) {
        return {};
    }
    const int dirId = rotatedId();
    if(dirId != 0 && dirId != 1) {
        return {};
    }
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int tt = textureTime();
    eOverlay o;
    if(dirId == 0) {
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

int eTempleBuilding::rotatedId() const {
    auto& board = getBoard();
    const auto dir = board.direction();
    if(dir == eWorldDirection::N) {
        return mId;
    } else if(dir == eWorldDirection::E) {
        if(mId == 0) {
            return 3;
        } else if(mId == 1) {
            return 2;
        } else if(mId == 2) {
            return 1;
        } else { // if(mId == 3) {
            return 0;
        }
    } else if(dir == eWorldDirection::S) {
        if(mId == 0) {
            return 2;
        } else if(mId == 1) {
            return 3;
        } else if(mId == 2) {
            return 0;
        } else { // if(mId == 3) {
            return 1;
        }
    } else { // if(dir == eWorldDirection::W) {
        if(mId == 0) {
            return 1;
        } else if(mId == 1) {
            return 0;
        } else if(mId == 2) {
            return 3;
        } else { // if(mId == 3) {
            return 2;
        }
    }
}
