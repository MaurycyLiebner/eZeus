#ifndef ETRADER_H
#define ETRADER_H

#include "ebasicpatroler.h"

class eTrader : public eBasicPatroler {
public:
    eTrader(eGameBoard& board);

    void createFollowers();

    void setActionType(const eCharacterActionType t);
private:
    std::vector<stdsptr<eCharacter>> mFollowers;
};

#endif // ETRADER_H
