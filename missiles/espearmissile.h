#ifndef ESPEARMISSILE_H
#define ESPEARMISSILE_H

#include "earrowspearbase.h"

class eSpearMissile : public eArrowSpearBase {
public:
    eSpearMissile(eGameBoard& board,
                  const std::vector<ePathPoint>& path = {});
};

#endif // ESPEARMISSILE_H
