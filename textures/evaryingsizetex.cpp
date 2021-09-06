#include "evaryingsizetex.h"


bool hiddenByNeighbour(eTile* const tile) {
    if(const auto t = tile->top<eTile>()) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }

    if(const auto t = tile->topLeft<eTile>()) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }


    for(int x = 0; x > -3; x--) {
        for(int y = 0; y > -3; y--) {
            if(x == 0 && y == 0) continue;
            if(x == 0 && y == -2) continue;
            const auto t = tile->tileRel<eTile>(x, y);
            if(!t) continue;
            const int d = t->futureDim();
            if(d > 2) return true;
        }
    }


    return false;
}

void eVaryingSizeTex::get(eTile* const tile,
                          const eChecker& checker,
                          int& futureDim, int& drawDim) {
    const bool hidden = hiddenByNeighbour(tile);
    if(hidden) {
        futureDim = 0;
        drawDim = 0;
        return;
    }

    {
        const auto tr = tile->topRight<eTile>();
        if(tr) {
            if(tr->futureDim() == 2) {
                futureDim = 1;
                drawDim = 2;
                return;
            }
            const auto trtr = tr->topRight<eTile>();
            if(trtr && trtr->futureDim() == 3) {
                futureDim = 1;
                drawDim = 3;
                return;
            }
        }
    }

    futureDim = 1;
    drawDim = 1;

    {
        const auto t = tile->bottom<eTile>();
        if(!t || !checker(t)) return;
    }

    {
        const auto t = tile->bottomLeft<eTile>();
        if(!t || !checker(t)) return;
    }

    {
        const auto t = tile->bottomRight<eTile>();
        if(!t || !checker(t)) return;
    }
    {
        const auto t = tile->left<eTile>();
        if(t) {
            if(checker(t) && t->futureDim() > 1) {
                return;
            }
            const auto t1 = t->left<eTile>();
            if(t1 && checker(t1) && t1->futureDim() > 2) {
                return;
            }
            const auto t2 = t->topLeft<eTile>();
            if(t2 && checker(t2) && t2->futureDim() > 2) {
                return;
            }
            const auto t3 = t->bottomLeft<eTile>();
            if(t3 && checker(t3) && t3->futureDim() > 2) {
                return;
            }
        }
    }

    futureDim = 2;
    drawDim = 0;

    {
        const auto t0 = tile->bottom<eTile>();
        if(!t0 || !checker(t0)) return;
        const auto t1 = t0->bottom<eTile>();
        if(!t1 || !checker(t1)) return;

        const auto t2 = t1->topRight<eTile>();
        if(!t2 || !checker(t2)) return;
        const auto t3 = t2->topRight<eTile>();
        if(!t3 || !checker(t3)) return;

        const auto t4 = t1->topLeft<eTile>();
        if(!t4 || !checker(t4)) return;
        const auto t5 = t4->topLeft<eTile>();
        if(!t5 || !checker(t5)) return;

        const auto t = tile->left<eTile>();
        if(t) {
            const auto t3 = t->bottomLeft<eTile>();
            if(t3 && checker(t3) && t3->futureDim() > 1) {
                return;
            }
        }
    }

    futureDim = 3;
    drawDim = 0;
}

std::shared_ptr<eTexture> eVaryingSizeTex::getVaryingTexture(
        const eVaryingFunc& func,
        eTile* const tile,
        const eTextureCollection& small,
        const eTextureCollection& large,
        const eTextureCollection& huge,
        int& futureDim, int& drawDim) {
    func(tile, futureDim, drawDim);
    if(drawDim == 0) {
        return std::shared_ptr<eTexture>();
    } else if(drawDim == 1) {
        const auto& coll = small;
        const int texId = tile->seed() % coll.size();
        return coll.getTexture(texId);
    } else if(drawDim == 2) {
        const auto& coll = large;
        const int texId = tile->seed() % coll.size();
        return coll.getTexture(texId);
    } else if(drawDim == 3) {
        const auto& coll = huge;
        const int texId = tile->seed() % coll.size();
        return coll.getTexture(texId);
    }
    return std::shared_ptr<eTexture>();
}
