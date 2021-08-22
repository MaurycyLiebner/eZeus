#include "egameboard.h"

#include <random>

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "spawners/espawner.h"

eGameBoard::eGameBoard(eThreadPool* const tpool) :
    mThreadPool(tpool), mEmplData(mPopData) {}

eGameBoard::~eGameBoard() {
    clear();
}

void eGameBoard::initialize(const int w, const int h) {
    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        std::vector<eTile*> yArr;
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            const auto tile = new eTile(x, y);
            yArr.push_back(tile);
        }
        mTiles.push_back(yArr);
    }
    mWidth = w;
    mHeight = h;

    updateDiagonalArray();
    updateNeighbours();
}

void eGameBoard::clear() {
    for(const auto& x : mTiles) {
        for(const auto y : x) {
            delete y;
        }
    }
    mTiles.clear();
    mDiagTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

eTile* eGameBoard::tile(const int x, const int y) const {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return mTiles[x][y];
}

void eGameBoard::registerCharacter(eCharacter* const c) {
    mCharacters.push_back(c);
}

bool eGameBoard::unregisterCharacter(eCharacter* const c) {
    const auto it = std::find(mCharacters.begin(), mCharacters.end(), c);
    if(it == mCharacters.end()) return false;
    mCharacters.erase(it);
    return true;
}

void eGameBoard::registerBuilding(eBuilding* const b) {
    mBuildings.push_back(b);
}

bool eGameBoard::unregisterBuilding(eBuilding* const b) {
    const auto it = std::find(mBuildings.begin(), mBuildings.end(), b);
    if(it == mBuildings.end()) return false;
    mBuildings.erase(it);
    return true;
}

void eGameBoard::registerSpawner(eSpawner* const s) {
    mSpawners.push_back(s);
}

bool eGameBoard::unregisterSpawner(eSpawner* const s) {
    const auto it = std::find(mSpawners.begin(), mSpawners.end(), s);
    if(it == mSpawners.end()) return false;
    mSpawners.erase(it);
    return true;
}

void eGameBoard::incTime(const int by) {
    for(const auto c : mCharacters) {
        c->incTime(by);
    }
    for(const auto b : mBuildings) {
        b->incTime(by);
    }
    for(const auto s : mSpawners) {
        s->incTime(by);
    }
}

void eGameBoard::updateDiagonalArray() {
    for(int k = 0 ; k <= mWidth + mHeight - 2; k++) {
        std::vector<eTile*> diag;
        for(int j = k ; j >= 0 ; j--) {
            const int i = k - j;
            if(i < mWidth && j < mHeight) {
                diag.push_back(mTiles[i][j]);
            }
        }
        mDiagTiles.push_back(diag);
    }
}

void eGameBoard::updateNeighbours() {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            const auto t = mTiles[x][y];
            t->setTopLeft(tile(x - 1, y));
            t->setTopRight(tile(x, y - 1));
            t->setBottomRight(tile(x + 1, y));
            t->setBottomLeft(tile(x, y + 1));
        }
    }
}
