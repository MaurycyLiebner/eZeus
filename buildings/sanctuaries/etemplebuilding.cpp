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

bool eTempleBuilding::hasNeighbour() const {
    const auto& board = getBoard();
    const auto tr = tileRect();
    const int xMin = tr.x;
    const int xMax = tr.x + tr.w;
    const auto has = [](eTile* const t) {
        if(!t) return false;
        const auto ub = t->underBuilding();
        const auto temple = dynamic_cast<eTempleBuilding*>(ub);
        return static_cast<bool>(temple);
    };
    for(int x = xMin; x < xMax; x++) {
        const auto t = board.tile(x, tr.y - 1);
        if(has(t)) return true;
        const auto tt = board.tile(x, tr.y + tr.h);
        if(has(tt)) return true;
    }
    for(int y = tr.y; y < tr.y + tr.h; y++) {
        const auto t = board.tile(tr.x - 1, y);
        if(has(t)) return true;
        const auto tt = board.tile(tr.x + tr.w, y);
        if(has(tt)) return true;
    }
    return false;
}

int eTempleBuilding::rotatedId() const {
    const auto s = sanctuary();
    const bool rotated = s->rotated();
    auto& board = getBoard();
    const auto dir = board.direction();
    if(mUpdateHasNeighbour) {
        mUpdateHasNeighbour = false;
        mHasNeighbour = hasNeighbour();
    }
    if(dir == eWorldDirection::N) {
        return mId;
    } else if(dir == eWorldDirection::E) {
        if(mId == 0) {
            if(mHasNeighbour) {
                return rotated ? 1 : 3;
            } else {
                return 1;
            }
        } else if(mId == 1) {
            if(mHasNeighbour) {
                return rotated ? 0 : 2;
            } else {
                return 0;
            }
        } else if(mId == 2) {
            return rotated ? 3 : 1;
        } else { // if(mId == 3) {
            return rotated ? 2 : 0;
        }
    } else if(dir == eWorldDirection::S) {
        if(mId == 0) {
            if(mHasNeighbour) {
                return 2;
            } else {
                return 0;
            }
        } else if(mId == 1) {
            if(mHasNeighbour) {
                return 3;
            } else {
                return 1;
            }
        } else if(mId == 2) {
            return 0;
        } else { // if(mId == 3) {
            return 1;
        }
    } else { // if(dir == eWorldDirection::W) {
        if(mId == 0) {
            if(mHasNeighbour) {
                return rotated ? 3 : 1;
            } else {
                return 1;
            }
        } else if(mId == 1) {
            if(mHasNeighbour) {
                return rotated ? 2 : 0;
            } else {
                return 0;
            }
        } else if(mId == 2) {
            return rotated ? 1 : 3;
        } else { // if(mId == 3) {
            return rotated ? 0 : 2;
        }
    }
}
