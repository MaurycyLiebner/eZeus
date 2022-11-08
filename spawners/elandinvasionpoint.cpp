#include "elandinvasionpoint.h"

eLandInvasionPoint::eLandInvasionPoint(const int id,
                                       eTile* const tile,
                                       eGameBoard& board) :
    eBanner(tile, board), mId(id) {
    board.addLandInvasionPoint(this);
}

eLandInvasionPoint::~eLandInvasionPoint() {
    board().removeLandInvasionPoint(mId);
}
