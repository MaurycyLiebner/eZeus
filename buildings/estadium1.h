#ifndef ESTADIUM1_H
#define ESTADIUM1_H

#include "epatroltarget.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium1Base : public ePatrolTarget {
public:
    eStadium1Base(eGameBoard& board,
                  const eBaseTex baseTex);
    ~eStadium1Base();
};

class eStadium1W : public eStadium1Base {
public:
    eStadium1W(eGameBoard& board);
};

class eStadium1H : public eStadium1Base {
public:
    eStadium1H(eGameBoard& board);
};

#endif // ESTADIUM1_H
