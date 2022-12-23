#ifndef EZEUSSANCTUARY_H
#define EZEUSSANCTUARY_H

#include "esanctuary.h"

class eZeusSanctuary: public eSanctuary  {
public:
    eZeusSanctuary(const int sw, const int sh,
                   eGameBoard& board);
};

#endif // EZEUSSANCTUARY_H
