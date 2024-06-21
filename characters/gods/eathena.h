#ifndef EATHENA_H
#define EATHENA_H

#include "eextendedgod.h"

class eApollo : public eExtendedGod {
public:
    eApollo(eGameBoard& board);
};

class eArtemis : public eExtendedGod {
public:
    eArtemis(eGameBoard& board);
};

class eAthena : public eExtendedGod {
public:
    eAthena(eGameBoard& board);
};

class eAtlas : public eExtendedGod {
public:
    eAtlas(eGameBoard& board);
};

class eZeus : public eExtendedGod {
public:
    eZeus(eGameBoard& board);
};

#endif // EATHENA_H
