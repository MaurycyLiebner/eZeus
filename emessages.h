#ifndef EMESSAGES_H
#define EMESSAGES_H

#include "emessage.h"

#include <memory>

struct eGameMessages {
    std::shared_ptr<eMessage> fNoPart;
    std::shared_ptr<eMessage> fBegin;
    std::shared_ptr<eMessage> fLost;
    std::shared_ptr<eMessage> fSecond;
    std::shared_ptr<eMessage> fWin;
};

class eMessages {
public:
    eMessages() {}

    void load();

    static eMessages sInstance;

    std::shared_ptr<eMessage> fPop100;
    std::shared_ptr<eMessage> fPop500;
    std::shared_ptr<eMessage> fPop1000;
    std::shared_ptr<eMessage> fPop2000;
    std::shared_ptr<eMessage> fPop3000;

    std::shared_ptr<eMessage> fHappinessMonument;

    std::shared_ptr<eMessage> fEmployeesNeeded;

    std::shared_ptr<eMessage> fFire;
    std::shared_ptr<eMessage> fCollapse;
    std::shared_ptr<eMessage> fPlagueStrikes;

    std::shared_ptr<eMessage> fAphroditeGreetings;
    std::shared_ptr<eMessage> fArtemisGreetings;
    std::shared_ptr<eMessage> fDemeterGreetings;
    std::shared_ptr<eMessage> fHadesGreetings;
    std::shared_ptr<eMessage> fZeusGreetings;

    eGameMessages fHomeGames;
    eGameMessages fIsthmianGames;
    eGameMessages fNemeanGames;
    eGameMessages fOlympianGames;
    eGameMessages fPythianGames;
};

#endif // EMESSAGES_H
