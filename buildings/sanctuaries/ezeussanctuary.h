#ifndef EZEUSSANCTUARY_H
#define EZEUSSANCTUARY_H

#include "esanctuary.h"

class eZeusSanctuary: public eSanctuary  {
public:
    eZeusSanctuary(const int sw, const int sh,
                   eGameBoard& board);
};

class eAphroditeSanctuary: public eSanctuary  {
public:
    eAphroditeSanctuary(const int sw, const int sh,
                   eGameBoard& board);
};

class eApolloSanctuary: public eSanctuary  {
public:
    eApolloSanctuary(const int sw, const int sh,
                    eGameBoard& board);
};

class eAthenaSanctuary: public eSanctuary  {
public:
    eAthenaSanctuary(const int sw, const int sh,
                     eGameBoard& board);
};

class eDionysusSanctuary: public eSanctuary  {
public:
    eDionysusSanctuary(const int sw, const int sh,
                       eGameBoard& board);
};

class eHeraSanctuary: public eSanctuary  {
public:
    eHeraSanctuary(const int sw, const int sh,
                   eGameBoard& board);
};

#endif // EZEUSSANCTUARY_H
