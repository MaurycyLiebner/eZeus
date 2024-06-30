#include "elandinvasionpoint.h"

#include "engine/egameboard.h"

eLandInvasionPoint::eLandInvasionPoint(const int id,
                                       eTile* const tile,
                                       eGameBoard& board) :
    eBanner(eBannerTypeS::landInvasion, id, tile, board) {}
