#ifndef EHUNTER_H
#define EHUNTER_H

#include "eresourcecollector.h"

class eHunter : public eResourceCollector {
public:
    eHunter(eGameBoard& board);
};

#endif // EHUNTER_H
