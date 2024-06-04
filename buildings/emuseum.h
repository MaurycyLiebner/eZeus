#ifndef EMUSEUM_H
#define EMUSEUM_H

#include "epatroltarget.h"

class eMuseum : public ePatrolTarget {
public:
    eMuseum(eGameBoard& board);
    ~eMuseum();
};

#endif // EMUSEUM_H
