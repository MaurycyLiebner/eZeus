#include "ebanner.h"

eBanner::eBanner(eTile* const tile, eGameBoard& board) :
    mTile(tile), mBoard(board) {
    mTile->setBanner(this);
}

eBanner::~eBanner() {
    if(mTile) mTile->setBanner(nullptr);
}
