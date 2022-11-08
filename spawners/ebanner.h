#ifndef EBANNER_H
#define EBANNER_H

#include "engine/egameboard.h"

class eTile;

class eBanner {
public:
    eBanner(eTile* const tile, eGameBoard& board);
    virtual ~eBanner();

    eTile* tile() const { return mTile; }
    eGameBoard& board() { return mBoard; }
private:
    eTile* const mTile;
    eGameBoard& mBoard;
};

#endif // EBANNER_H
