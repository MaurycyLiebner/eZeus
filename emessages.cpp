#include "emessages.h"

#include <fstream>

eMessages eMessages::sInstance;

bool loadMsg(std::shared_ptr<eMessage>& msg,
             const std::string& path) {
    std::ifstream file(path);
    if(!file.good()) {
        printf("File missing %s\n", path.c_str());
        return false;
    }
    std::string str;
    eMessage msg0;
    int i = 0;
    while(std::getline(file, str)) {
        if(i == 0) {
            msg0.fTitle = str;
        } else {
            msg0.fText = str;
            break;
        }
        i++;
    }
    msg = std::make_shared<eMessage>(msg0);
    return true;
}

void loadGames(const std::string& dir,
               const std::string& name,
               eGameMessages& gms) {
    loadMsg(gms.fNoPart, dir + name + "_games_no_part.txt");
    loadMsg(gms.fBegin, dir + name + "_games_begin.txt");
    loadMsg(gms.fLost, dir + name + "_games_lost.txt");
    loadMsg(gms.fSecond, dir + name + "_games_second.txt");
    loadMsg(gms.fWin, dir + name + "_games_win.txt");
}

void eMessages::load() {
    const std::string dir{"../Text/"};

    loadMsg(fPop100, dir + "population_100.txt");
    loadMsg(fPop500, dir + "population_500.txt");
    loadMsg(fPop1000, dir + "population_1000.txt");
    loadMsg(fPop2000, dir + "population_2000.txt");
    loadMsg(fPop3000, dir + "population_3000.txt");

    loadMsg(fHappinessMonument, dir + "happiness_monument.txt");

    loadMsg(fEmployeesNeeded, dir + "employees_needed.txt");

    loadMsg(fFire, dir + "fire.txt");
    loadMsg(fCollapse, dir + "collapsed_building.txt");
    loadMsg(fPlagueStrikes, dir + "plague_strikes.txt");

    loadMsg(fAphroditeGreetings, dir + "aphrodite_greetings.txt");
    loadMsg(fArtemisGreetings, dir + "artemis_greetings.txt");
    loadMsg(fDemeterGreetings, dir + "demeter_greetings.txt");
    loadMsg(fHadesGreetings, dir + "hades_greetings.txt");
    loadMsg(fZeusGreetings, dir + "zeus_greetings.txt");

    loadGames(dir, "home", fHomeGames);
    loadGames(dir, "isthmian", fIsthmianGames);
    loadGames(dir, "nemean", fNemeanGames);
    loadGames(dir, "olympian", fOlympianGames);
    loadGames(dir, "pythian", fPythianGames);
}
