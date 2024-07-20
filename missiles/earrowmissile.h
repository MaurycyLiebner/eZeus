#ifndef EARROWMISSILE_H
#define EARROWMISSILE_H

#include "earrowspearbase.h"

class eArrowMissile : public eArrowSpearBase {
public:
    eArrowMissile(eGameBoard& board,
                  const std::vector<ePathPoint>& path = {});
};

#endif // EARROWMISSILE_H
