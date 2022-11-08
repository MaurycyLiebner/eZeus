#ifndef ELANDINVASIONPOINT_H
#define ELANDINVASIONPOINT_H

#include "ebanner.h"

class eLandInvasionPoint : public eBanner {
public:
    eLandInvasionPoint(const int id,
                       eTile* const tile,
                       eGameBoard& board);
    ~eLandInvasionPoint();

    int id() const { return mId; }
private:
    const int mId;
};

#endif // ELANDINVASIONPOINT_H
