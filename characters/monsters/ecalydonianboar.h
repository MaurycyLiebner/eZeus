#ifndef ECALYDONIANBOAR_H
#define ECALYDONIANBOAR_H

#include "ebasicmonster.h"
#include "ewatermonster.h"

class eCalydonianBoar : public eBasicMonster {
public:
    eCalydonianBoar(eGameBoard& board);
};

class eCerberus : public eBasicMonster {
public:
    eCerberus(eGameBoard& board);
};

class eChimera : public eBasicMonster {
public:
    eChimera(eGameBoard& board);
};

class eCyclops : public eBasicMonster {
public:
    eCyclops(eGameBoard& board);
};

class eDragon : public eBasicMonster {
public:
    eDragon(eGameBoard& board);
};

class eEchidna : public eBasicMonster {
public:
    eEchidna(eGameBoard& board);
};

class eHarpies : public eBasicMonster {
public:
    eHarpies(eGameBoard& board);
};

class eHector : public eBasicMonster {
public:
    eHector(eGameBoard& board);
};

class eHydra : public eBasicMonster {
public:
    eHydra(eGameBoard& board);
};

class eKraken : public eWaterMonster {
public:
    eKraken(eGameBoard& board);
};

class eMaenads : public eBasicMonster {
public:
    eMaenads(eGameBoard& board);
};

class eMedusa : public eBasicMonster {
public:
    eMedusa(eGameBoard& board);
};

class eMinotaur : public eBasicMonster {
public:
    eMinotaur(eGameBoard& board);
};

class eScylla : public eWaterMonster {
public:
    eScylla(eGameBoard& board);
};

class eSphinx : public eBasicMonster {
public:
    eSphinx(eGameBoard& board);
};

class eTalos : public eBasicMonster {
public:
    eTalos(eGameBoard& board);
};

class eSatyr : public eBasicMonster {
public:
    eSatyr(eGameBoard& board);
};

#endif // ECALYDONIANBOAR_H
