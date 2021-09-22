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

using eTileGetter = eTile* (eTile::*)() const;
bool isSingle(eTile* const t,
              eTileGetter tg1,
              eTileGetter tg2) {
    if(!t) return true;
    const int tx = t->x();
    const int ty = t->y();
    const auto tl = (t->*tg1)();
    const auto br = (t->*tg2)();
    const bool tlb = tl && tl->underBuildingType() == eBuildingType::avenue;
    const bool brb = br && br->underBuildingType() == eBuildingType::avenue;
    bool single = true;
    if(tlb && brb) {
        bool s = false;
        if(tl) {
            if(const auto tltl = (tl->*tg1)()) {
                s = tltl->underBuildingType() != eBuildingType::avenue;
            }
        }
        if(br && !s) {
            if(const auto brbr = (br->*tg2)()) {
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
    const auto bl = t->bottomLeft<eTile>();
    const auto tr = t->topRight<eTile>();

    const auto tlt = tl ? tl->underBuildingType() : eBuildingType::none;
    const auto brt = br ? br->underBuildingType() : eBuildingType::none;
    const auto blt = bl ? bl->underBuildingType() : eBuildingType::none;
    const auto trt = tr ? tr->underBuildingType() : eBuildingType::none;

    const auto tt = tl ? tl->underBuildingType() : eBuildingType::none;
    const auto bt = br ? br->underBuildingType() : eBuildingType::none;
    const auto lt = bl ? bl->underBuildingType() : eBuildingType::none;
    const auto rt = tr ? tr->underBuildingType() : eBuildingType::none;

    const bool tlb = tlt == eBuildingType::avenue ||
                     tlt == eBuildingType::road;
    const bool brb = brt == eBuildingType::avenue ||
                     brt == eBuildingType::road;
    const bool blb = blt == eBuildingType::avenue ||
                     blt == eBuildingType::road;
    const bool trb = trt == eBuildingType::avenue ||
                     trt == eBuildingType::road;

    const bool lb = bt == eBuildingType::avenue ||
                    bt == eBuildingType::road;
    const bool bb = lt == eBuildingType::avenue ||
                    lt == eBuildingType::road;
    const bool rb = rt == eBuildingType::avenue ||
                    rt == eBuildingType::road;
    eTileGetter tg1 = nullptr;
    eTileGetter tg2 = nullptr;
    int collId = 0;
    int id = 0;
    if(tlb && brb && blb && trb) {
        collId = 4;
        if(!bb) {
            id = 0;
        } else if(!rb) {
            id = 1;
        } else if(!lb) {
            id = 2;
        } else {
            id = 3;
        }
    } else if(trb && brb && !tlb && !blb) {
        collId = 4;
        id = 4;
    } else if(blb && brb && !tlb && !trb) {
        collId = 4;
        id = 5;
    } else if(blb && tlb && !brb && !trb) {
        collId = 4;
        id = 6;
    } else if(tlb && trb && !brb && !blb) {
        collId = 4;
        id = 7;
    } else if(tlb && brb) {
        tg1 = &eTile::topLeft<eTile>;
        tg2 = &eTile::bottomRight<eTile>;
        if(trb) {
            collId = 0;
        } else {
            collId = 1;
        }
    } else if(blb && trb) {
        tg2 = &eTile::bottomLeft<eTile>;
        tg1 = &eTile::topRight<eTile>;
        if(tlb) {
            collId = 2;
        } else {
            collId = 3;
        }
    }
    if(tg1 && tg2) {
        const bool s = isSingle(t, tg1, tg2);
        const bool tls = isSingle((t->*tg1)(), tg1, tg2);
        const bool brs = isSingle((t->*tg2)(), tg1, tg2);
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
    }
    const auto& coll = avn[collId];
    return coll.getTexture(id);
}
