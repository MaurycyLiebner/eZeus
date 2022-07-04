#ifndef EMESSAGES_H
#define EMESSAGES_H

#include "emessage.h"

#include <map>

class eMessages {
public:
    eMessages() {}

    static eMessages instance;

    static bool load();
    static bool loaded();

    static const std::string& message(const std::string& key);

    std::map<std::string, std::string> fMessages;

    eMessageType fPop100;
    eMessageType fPop500;
    eMessageType fPop1000;
    eMessageType fPop2000;
    eMessageType fPop3000;
    eMessageType fPop5000;
    eMessageType fPop10000;
    eMessageType fPop15000;
    eMessageType fPop20000;
    eMessageType fPop25000;

    eMessageType fHappinessMonument;

    eMessageType fEmployeesNeeded;

    eMessageType fFire;
    eMessageType fCollapse;
    eMessageType fPlagueStrikes;

    eMessageType fAphroditeWooing;
    eMessageType fArtemisWooing;
    eMessageType fDemeterWooing;
    eMessageType fHadesWooing;
    eMessageType fZeusWooing;

    eGameMessages fHomeGames;
    eGameMessages fIsthmianGames;
    eGameMessages fNemeanGames;
    eGameMessages fPythianGames;
    eGameMessages fOlympianGames;
private:
    bool loadImpl();
    bool mLoaded = false;
};

#endif // EMESSAGES_H
