#ifndef ESHEPHERD_H
#define ESHEPHERD_H

#include "eresourcecollector.h"

class eShepherd : public eResourceCollector {
public:
    eShepherd(eGameBoard& board);
};

#endif // ESHEPHERD_H
