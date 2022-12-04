#ifndef EMESSAGES_H
#define EMESSAGES_H

#include "emessage.h"

#include <map>

struct eGodMessages {
    int fLastMessage = -1;

    eMessageType fWooing0;
    eMessageType fJealousy1;
    eMessageType fJealousy2;

    eMessageType fMonster;
};

struct eHeroMessages {
    eMessageType fArrival;
    eMessageType fHallAvailable;
};

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

    eGodMessages fAphrodite;
    eGodMessages fApollo;
    eGodMessages fAres;
    eGodMessages fArtemis;
    eGodMessages fAthena;
    eGodMessages fAtlas;
    eGodMessages fDemeter;
    eGodMessages fDionysus;
    eGodMessages fHades;
    eGodMessages fHephaestus;
    eGodMessages fHera;
    eGodMessages fHermes;
    eGodMessages fPoseidon;
    eGodMessages fZeus;

    eHeroMessages fAchilles;
    eHeroMessages fAtalanta;
    eHeroMessages fBellerophon;
    eHeroMessages fHercules;
    eHeroMessages fJason;
    eHeroMessages fOdysseus;
    eHeroMessages fPerseus;
    eHeroMessages fTheseus;

    eGameMessages fHomeGames;
    eGameMessages fIsthmianGames;
    eGameMessages fNemeanGames;
    eGameMessages fPythianGames;
    eGameMessages fOlympianGames;

    eMessageType fInvasion;
    eMessageType fInvasionBribed;
    eMessageType fInvasionDefeat;
    eMessageType fInvasionVictory;

    eMessageType fTributePaidGranted;
    eMessageType fTributePaidAccepted;
    eMessageType fTributePaidRefused;
private:
    bool loadImpl();
    void load(eGodMessages& god, const std::string& godName);
    void load(eHeroMessages& hero, const std::string& heroName);
    bool mLoaded = false;
};

#endif // EMESSAGES_H
