#ifndef EDEMETER_H
#define EDEMETER_H

#include "ebasicgod.h"

class eAphrodite : public eBasicGod {
public:
    eAphrodite(eGameBoard& board);
};

class eAres : public eBasicGod {
public:
    eAres(eGameBoard& board);
};

class eDemeter : public eBasicGod {
public:
    eDemeter(eGameBoard& board);
};

class eHades : public eBasicGod {
public:
    eHades(eGameBoard& board);
};

class eHephaestus : public eBasicGod {
public:
    eHephaestus(eGameBoard& board);
};

class eHera : public eBasicGod {
public:
    eHera(eGameBoard& board);
};

class ePoseidon : public eBasicGod {
public:
    ePoseidon(eGameBoard& board);
};

#endif // EDEMETER_H
