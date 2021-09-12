#include "eroad.h"

#include "textures/egametextures.h"

#include "engine/egameboard.h"

eRoad::eRoad(eGameBoard& board) :
    eBuilding(board, eBuildingType::road, 1, 1),
    mTextures(eGameTextures::buildings()) {

}

std::shared_ptr<eTexture> eRoad::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& sizeColl = mTextures[sizeId];
    const auto& tbcoll = sizeColl.fToBeachRoad;
    const auto& bcoll = sizeColl.fBeachRoad;

    const auto ti = tile();
    const auto tr = ti->topRight();
    const auto br = ti->bottomRight();
    const auto bl = ti->bottomLeft();
    const auto tl = ti->topLeft();

    const bool trRoad = !tr || tr->hasRoad();
    const bool brRoad = !br || br->hasRoad();
    const bool blRoad = !bl || bl->hasRoad();
    const bool tlRoad = !tl || tl->hasRoad();

    if(ti->terrain() == eTerrain::beach) {
        if(bl && bl->terrain() == eTerrain::dry) {
            return tbcoll.getTexture(0);
        } else if(tl && tl->terrain() == eTerrain::dry) {
            return tbcoll.getTexture(1);
        } else if(tr && tr->terrain() == eTerrain::dry) {
            return tbcoll.getTexture(2);
        } else if(br && br->terrain() == eTerrain::dry) {
            return tbcoll.getTexture(3);
        }


        if(tlRoad && blRoad && trRoad && brRoad) return bcoll.getTexture(17);
        if(trRoad && brRoad && blRoad) return bcoll.getTexture(13);
        if(tlRoad && blRoad && brRoad) return bcoll.getTexture(14);
        if(tlRoad && blRoad && trRoad) return bcoll.getTexture(15);
        if(tlRoad && brRoad && trRoad) return bcoll.getTexture(16);

        if(blRoad && trRoad) {
            if(seed() % 2) return bcoll.getTexture(0);
            else return bcoll.getTexture(2);
        }
        if(tlRoad && brRoad) {
            if(seed() % 2) return bcoll.getTexture(1);
            else return bcoll.getTexture(3);
        }

        if(trRoad && brRoad) return bcoll.getTexture(4);
        if(blRoad && brRoad) return bcoll.getTexture(5);
        if(blRoad && tlRoad) return bcoll.getTexture(6);
        if(tlRoad && trRoad) return bcoll.getTexture(7);
        if(trRoad) return bcoll.getTexture(8);
        if(brRoad) return bcoll.getTexture(9);
        if(blRoad) return bcoll.getTexture(10);
        if(tlRoad) return bcoll.getTexture(11);

        return bcoll.getTexture(12);

    } else {
        const auto& pcoll = sizeColl.fPrettyRoad;
        const auto& rcoll = sizeColl.fRoad;

        const auto& b = getBoard();
        const auto t = tile();
        const int tx = t->x();
        const int ty = t->y();
        const double a = b.appeal(tx, ty);

        const eTextureCollection* coll;
        if(a > 3) {
            coll = &pcoll;
        } else {
            coll = &rcoll;
        }

        if(tlRoad && blRoad && trRoad && brRoad) return coll->getTexture(17);
        if(trRoad && brRoad && blRoad) return coll->getTexture(13);
        if(tlRoad && blRoad && brRoad) return coll->getTexture(14);
        if(tlRoad && blRoad && trRoad) return coll->getTexture(15);
        if(tlRoad && brRoad && trRoad) return coll->getTexture(16);

        if(blRoad && trRoad) {
            if(seed() % 2) return coll->getTexture(0);
            else return coll->getTexture(2);
        }
        if(tlRoad && brRoad) {
            if(seed() % 2) return coll->getTexture(1);
            else return coll->getTexture(3);
        }

        if(trRoad && brRoad) return coll->getTexture(4);
        if(blRoad && brRoad) return coll->getTexture(5);
        if(blRoad && tlRoad) return coll->getTexture(6);
        if(tlRoad && trRoad) return coll->getTexture(7);
        if(trRoad) return coll->getTexture(8);
        if(brRoad) return coll->getTexture(9);
        if(blRoad) return coll->getTexture(10);
        if(tlRoad) return coll->getTexture(11);

        return coll->getTexture(12);
    }
    return std::shared_ptr<eTexture>();
}
