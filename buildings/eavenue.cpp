#include "eavenue.h"

#include "textures/egametextures.h"

eAvenue::eAvenue(eGameBoard& board) :
    eBuilding(board, eBuildingType::avenue, 1, 1) {

}

int eAvenue::provide(const eProvide p, const int n) {
    const auto t = centerTile();
    if(!t) return eBuilding::provide(p, n);
    int rem = n;
    for(const int x : {-1, 0, 1}) {
        for(const int y : {-1, 0, 1}) {
            const auto tt = t->tileRel<eTile>(x, y);
            if(!tt) continue;
            if(const auto b = tt->underBuilding()) {
                const auto tp = b->type();
                if(tp == eBuildingType::avenue) continue;
                const int r = b->provide(p, rem);
                rem -= r;
                if(rem <= 0) return n;
            }
        }
    }
    return n - rem;
}

bool isSingle(eTile* const t) {
    if(!t) return true;
    const int tx = t->x();
    const int ty = t->y();
    const auto tl = t->topLeft<eTile>();
    const auto br = t->bottomRight<eTile>();
    const bool tlb = tl && tl->underBuildingType() == eBuildingType::avenue;
    const bool brb = br && br->underBuildingType() == eBuildingType::avenue;
    bool single = true;
    if(tlb && brb) {
        bool s = false;
        if(tl) {
            if(const auto tltl = tl->topLeft<eTile>()) {
                s = tltl->underBuildingType() != eBuildingType::avenue;
            }
        }
        if(br && !s) {
            if(const auto brbr = br->bottomRight<eTile>()) {
                s = brbr->underBuildingType() != eBuildingType::avenue;
            }
        }
        single = s;
    }
    if(!single) {
        const int id = tx + ty;
        single = id % 5 > 0;
    }
    return single;
}

std::shared_ptr<eTexture>
eAvenue::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& avn = blds.fAvenue;
    const auto t = centerTile();
    const auto tl = t->topLeft<eTile>();
    const auto br = t->bottomRight<eTile>();
    const bool tlb = tl && tl->underBuildingType() == eBuildingType::avenue;
    const bool brb = br && br->underBuildingType() == eBuildingType::avenue;
    if(tlb && brb) {
        const bool s = isSingle(t);
        const bool tls = isSingle(tl);
        const bool brs = isSingle(br);
        int id = 0;
        if(s && !tls) {
            id = 3;
        } else if(s && !brs) {
            id = 5;
        } else if(!s) {
            const int ids[] = {4, 6, 7};
            id = ids[seed() % 3];
        } else {
            const int ids[] = {0, 1, 2, 8};
            id = ids[seed() % 4];
        }
        const auto& coll = avn[0];
        return coll.getTexture(id);
    }
    return avn[0].getTexture(0);
}
