#ifndef EDISASTERPOINT_H
#define EDISASTERPOINT_H

#include "ebanner.h"

class eDisasterPoint : public eBanner {
public:
    eDisasterPoint(const int id,
                   eTile* const tile,
                   eGameBoard& board);
};

#endif // EDISASTERPOINT_H
