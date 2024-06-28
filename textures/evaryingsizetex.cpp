#include "evaryingsizetex.h"


bool hiddenByNeighbour(eTile* const tile,
                       const eWorldDirection dir) {
    for(int x = 0; x > -2; x--) {
        for(int y = 0; y > -2; y--) {
            if(x == 0 && y == 0) continue;
            const auto t = tile->tileRelRotated<eTile>(x, y, dir);
            if(!t) continue;
            const int d = t->futureDim();
            if(d > 1) return true;
        }
    }


    for(int x = 0; x > -3; x--) {
        for(int y = 0; y > -3; y--) {
            if(x == 0 && y == 0) continue;
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
    {
        const auto t = tile->topRightRotated<eTile>(dir);
        if(t) {
            if(t->futureDim() == 2) {
                futureDim = 0;
                drawDim = 2;
                return;
            }
            const auto tt = t->topRightRotated<eTile>(dir);
            if(tt && tt->futureDim() == 3) {
                futureDim = 0;
                drawDim = 3;
                return;
            }
        }
    }

    const bool hidden = hiddenByNeighbour(tile, dir);
    if(hidden) {
        futureDim = 0;
        drawDim = 0;
        return;
    }

    bool allFit = true;
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            if(x == 0 && y == 0) continue;
            const auto t = tile->tileRelRotated<eTile>(x, y, dir);
            if(!t || !checker(t) || hiddenByNeighbour(t, dir)) {
                allFit = false;
                break;
            }
        }
        if(!allFit) break;
    }
    if(allFit) {
        futureDim = 3;
        drawDim = 0;
        return;
    }

    allFit = true;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            if(x == 0 && y == 0) continue;
            const auto t = tile->tileRelRotated<eTile>(x, y, dir);
            if(!t || !checker(t) || hiddenByNeighbour(t, dir)) {
                allFit = false;
                break;
            }
        }
        if(!allFit) break;
    }
    if(allFit) {
        futureDim = 2;
        drawDim = 0;
        return;
    }

    futureDim = 1;
    drawDim = 1;
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
