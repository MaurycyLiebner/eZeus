#ifndef EACHILLES_H
#define EACHILLES_H

#include "ebasichero.h"

class eAchilles : public eBasicHero {
public:
    eAchilles(eGameBoard& board);
};

class eAtalanta : public eBasicHero {
public:
    eAtalanta(eGameBoard& board);
};

class eBellerophon : public eBasicHero {
public:
    eBellerophon(eGameBoard& board);
};

class eHercules : public eBasicHero {
public:
    eHercules(eGameBoard& board);
};

class eJason : public eBasicHero {
public:
    eJason(eGameBoard& board);
};

class eOdysseus : public eBasicHero {
public:
    eOdysseus(eGameBoard& board);
};

class ePerseus : public eBasicHero {
public:
    ePerseus(eGameBoard& board);
};

class eTheseus : public eBasicHero {
public:
    eTheseus(eGameBoard& board);
};

#endif // EACHILLES_H
