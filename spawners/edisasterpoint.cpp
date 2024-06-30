#include "edisasterpoint.h"

#include "engine/egameboard.h"

eDisasterPoint::eDisasterPoint(const int id,
                              eTile* const tile,
                              eGameBoard& board) :
    eBanner(eBannerTypeS::disasterPoint, id, tile, board) {}
