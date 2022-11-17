#include "elandinvasionpoint.h"

eLandInvasionPoint::eLandInvasionPoint(const int id,
                                       eTile* const tile,
                                       eGameBoard& board) :
    eBanner(eBannerTypeS::landInvasion, id, tile, board) {
    board.addLandInvasionPoint(this);
}

eLandInvasionPoint::~eLandInvasionPoint() {
    board().removeLandInvasionPoint(id());
}
