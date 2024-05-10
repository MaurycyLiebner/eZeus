#include "eplague.h"

#include "buildings/esmallhouse.h"
#include "egameboard.h"
#include "evectorhelpers.h"

ePlague::ePlague(eGameBoard& board) :
    mBoard(board) {}

void ePlague::randomSpread() {
    if(mHouses.empty()) return;
    std::random_shuffle(mHouses.begin(), mHouses.end());
    spreadFrom(mHouses[0]);
}

void ePlague::spreadFrom(eSmallHouse* const h) {
    const auto hRect = h->tileRect();
    const int range = 5;
    const SDL_Rect contRect{hRect.x - range, hRect.y - range,
                            hRect.w + 2*range, hRect.h + 2*range};
    for(int x = contRect.x; x < contRect.x + contRect.w; x++) {
        for(int y = contRect.y; y < contRect.y + contRect.h; y++) {
            const auto t = mBoard.tile(x, y);
            if(!t) continue;
            const auto b = t->underBuilding();
            if(!b) continue;
            if(b->centerTile() != t) continue;
            const auto bt = b->type();
            if(bt != eBuildingType::commonHouse) continue;
            const auto ch = static_cast<eSmallHouse*>(b);
            if(ch->plague()) continue;
            if(ch != h && rand() % 2) continue;
            mHouses.push_back(ch);
            ch->setPlague(true);
        }
    }
}

void ePlague::healAll() {
    for(const auto& h : mHouses) {
        h->setPlague(false);
    }
    mHouses.clear();
}

void ePlague::healHouse(eSmallHouse* const h) {
    if(!h) return;
    h->setPlague(false);
    eVectorHelpers::remove(mHouses, h);
}

bool ePlague::hasHouse(eSmallHouse* const h) const {
    return eVectorHelpers::contains(mHouses, h);
}

void ePlague::removeHouse(eSmallHouse* const h) {
    eVectorHelpers::remove(mHouses, h);
}

void ePlague::read(eReadStream& src) {
    int n;
    src >> n;
    for(int i = 0 ; i < n; i++) {
        src.readBuilding(&mBoard, [this](eBuilding* const b) {
            const auto ch = static_cast<eSmallHouse*>(b);
            mHouses.push_back(ch);
        });
    }
}

void ePlague::write(eWriteStream& dst) const {
    dst << mHouses.size();
    for(const auto& ch : mHouses) {
        dst.writeBuilding(ch);
    }
}
