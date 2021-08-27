#ifndef EGOATHERD_H
#define EGOATHERD_H

#include "eresourcecollector.h"

class eGoatherd : public eResourceCollector {
public:
    eGoatherd(eGameBoard& board);
};

#endif // EGOATHERD_H
