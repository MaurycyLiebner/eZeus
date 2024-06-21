#include "evaryingsizetex.h"


bool hiddenByNeighbour(eTile* const tile,
                       const eWorldDirection dir) {
    if(const auto t = tile->topRotated<eTile>(dir)) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }

    if(const auto t = tile->topLeftRotated<eTile>(dir)) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }


    for(int x = 0; x > -3; x--) {
        for(int y = 0; y > -3; y--) {
            if(x == 0 && y == 0) continue;
            if(x == 0 && y == -2) continue;
            const auto t = tile->tileRelRotated<eTile>(x, y, dir);
            if(!t) continue;
            const int d = t->futureDim();
            if(d > 2) return true;
        }
    }


    return false;
}

void eVaryingSizeTex::get(eTile* const tile,
                          const eChecker& checker,
                          int& futureDim, int& drawDim,
                          const eWorldDirection dir) {
    const bool hidden = hiddenByNeighbour(tile, dir);
    if(hidden) {
        futureDim = 0;
        drawDim = 0;
        return;
    }

    {
        const auto tr = tile->topRightRotated<eTile>(dir);
        if(tr) {
            if(tr->futureDim() == 2) {
                futureDim = 1;
                drawDim = 2;
                return;
            }
            const auto trtr = tr->topRightRotated<eTile>(dir);
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
        const auto t = tile->bottomRotated<eTile>(dir);
        if(!t || !checker(t)) return;
    }

    {
        const auto t = tile->bottomLeftRotated<eTile>(dir);
        if(!t || !checker(t)) return;
    }

    {
        const auto t = tile->bottomRightRotated<eTile>(dir);
        if(!t || !checker(t)) return;
    }
    {
        const auto t = tile->leftRotated<eTile>(dir);
        if(t) {
            if(checker(t) && t->futureDim() > 1) {
                return;
            }
            const auto t1 = t->leftRotated<eTile>(dir);
            if(t1 && checker(t1) && t1->futureDim() > 2) {
                return;
            }
            const auto t2 = t->topLeftRotated<eTile>(dir);
            if(t2 && checker(t2) && t2->futureDim() > 2) {
                return;
            }
            const auto t3 = t->bottomLeftRotated<eTile>(dir);
            if(t3 && checker(t3) && t3->futureDim() > 2) {
                return;
            }
        }
    }

    futureDim = 2;
    drawDim = 0;

    {
        const auto t0 = tile->bottomRotated<eTile>(dir);
        if(!t0 || !checker(t0)) return;
        const auto t1 = t0->bottomRotated<eTile>(dir);
        if(!t1 || !checker(t1)) return;

        const auto t2 = t1->topRightRotated<eTile>(dir);
        if(!t2 || !checker(t2)) return;
        const auto t3 = t2->topRightRotated<eTile>(dir);
        if(!t3 || !checker(t3)) return;

        const auto t4 = t1->topLeftRotated<eTile>(dir);
        if(!t4 || !checker(t4)) return;
        const auto t5 = t4->topLeftRotated<eTile>(dir);
        if(!t5 || !checker(t5)) return;

        const auto t = tile->leftRotated<eTile>(dir);
        if(t) {
            const auto t3 = t->bottomLeftRotated<eTile>(dir);
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
        int& futureDim, int& drawDim,
        const eWorldDirection dir) {
    func(tile, futureDim, drawDim, dir);
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
