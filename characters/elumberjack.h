#ifndef ELUMBERJACK_H
#define ELUMBERJACK_H

#include "eresourcecollector.h"

class eLumberjack : public eResourceCollector {
public:
    eLumberjack(eGameBoard& board);
};

#endif // ELUMBERJACK_H
