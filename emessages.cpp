#include "emessages.h"

#include <fstream>
#include <SDL2/SDL_log.h>

#include "egamedir.h"

#include "eloadtexthelper.h"

eMessages eMessages::instance;

bool eMessages::loadImpl() {
    if(mLoaded) return false;
    mLoaded = true;

    const std::string path = eGameDir::path("Model/Zeus eventmsg.txt");
    eLoadTextHelper::load(path, fMessages);

    fPop100.fFull.fTitle = fMessages["PHRASE_population_100_title"];
    fPop100.fFull.fText = fMessages["PHRASE_population_100_initial_announcement"];
    fPop100.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_100_initial_announcement"];

    fPop500.fFull.fTitle = fMessages["PHRASE_population_500_title"];
    fPop500.fFull.fText = fMessages["PHRASE_population_500_initial_announcement"];
    fPop500.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_500_initial_announcement"];

    fPop1000.fFull.fTitle = fMessages["PHRASE_population_1000_title"];
    fPop1000.fFull.fText = fMessages["PHRASE_population_1000_initial_announcement"];
    fPop1000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_1000_initial_announcement"];

    fPop2000.fFull.fTitle = fMessages["PHRASE_population_2000_title"];
    fPop2000.fFull.fText = fMessages["PHRASE_population_2000_initial_announcement"];
    fPop2000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_2000_initial_announcement"];

    fPop3000.fFull.fTitle = fMessages["PHRASE_population_3000_title"];
    fPop3000.fFull.fText = fMessages["PHRASE_population_3000_initial_announcement"];
    fPop3000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_3000_initial_announcement"];

    fPop5000.fFull.fTitle = fMessages["PHRASE_population_5000_title"];
    fPop5000.fFull.fText = fMessages["PHRASE_population_5000_initial_announcement"];
    fPop5000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_5000_initial_announcement"];

    fPop10000.fFull.fTitle = fMessages["PHRASE_population_10000_title"];
    fPop10000.fFull.fText = fMessages["PHRASE_population_10000_initial_announcement"];
    fPop10000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_10000_initial_announcement"];

    fPop15000.fFull.fTitle = fMessages["PHRASE_population_15000_title"];
    fPop15000.fFull.fText = fMessages["PHRASE_population_15000_initial_announcement"];
    fPop15000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_15000_initial_announcement"];

    fPop20000.fFull.fTitle = fMessages["PHRASE_population_20000_title"];
    fPop20000.fFull.fText = fMessages["PHRASE_population_20000_initial_announcement"];
    fPop20000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_20000_initial_announcement"];

    fPop25000.fFull.fTitle = fMessages["PHRASE_population_25000_title"];
    fPop25000.fFull.fText = fMessages["PHRASE_population_25000_initial_announcement"];
    fPop25000.fCondensed.fText = fMessages["PHRASE_CONDENSED_population_25000_initial_announcement"];

    fHappinessMonument.fFull.fTitle = fMessages["PHRASE_happiness_monument_title"];
    fHappinessMonument.fFull.fText = fMessages["PHRASE_happiness_monument_initial_announcement"];
    fHappinessMonument.fCondensed.fText = fMessages["PHRASE_CONDENSED_happiness_monument_initial_announcement"];

    fEmployeesNeeded.fFull.fTitle = fMessages["PHRASE_employees_needed_title"];
    fEmployeesNeeded.fFull.fText = fMessages["PHRASE_employees_needed_initial_announcement"];
    fEmployeesNeeded.fCondensed.fText = fMessages["PHRASE_CONDENSED_employees_needed_initial_announcement"];

    fFire.fFull.fTitle = fMessages["PHRASE_fire_title"];
    fFire.fFull.fText = fMessages["PHRASE_fire_initial_announcement"];
    fFire.fCondensed.fText = fMessages["PHRASE_CONDENSED_fire_initial_announcement"];

    fCollapse.fFull.fTitle = fMessages["PHRASE_collapsed_building_title"];
    fCollapse.fFull.fText = fMessages["PHRASE_collapsed_building_initial_announcement"];
    fCollapse.fCondensed.fText = fMessages["PHRASE_CONDENSED_collapsed_building_initial_announcement"];

    fPlagueStrikes.fFull.fTitle = fMessages["PHRASE_plague_title"];
    fPlagueStrikes.fFull.fText = fMessages["PHRASE_plague_initial_announcement"];
    fPlagueStrikes.fCondensed.fText = fMessages["PHRASE_CONDENSED_plague_initial_announcement"];

    fAphroditeWooing.fFull.fTitle = fMessages["PHRASE_aphrodite_wooing0_title"];
    fAphroditeWooing.fFull.fText = fMessages["PHRASE_aphrodite_wooing0_initial_announcement"];
    fAphroditeWooing.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_aphrodite_wooing0_title"];
    fAphroditeWooing.fCondensed.fText = fMessages["PHRASE_CONDENSED_aphrodite_wooing0_initial_announcement"];

    fArtemisWooing.fFull.fTitle = fMessages["PHRASE_artemis_wooing0_title"];
    fArtemisWooing.fFull.fText = fMessages["PHRASE_artemis_wooing0_initial_announcement"];
    fArtemisWooing.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_artemis_wooing0_title"];
    fArtemisWooing.fCondensed.fText = fMessages["PHRASE_CONDENSED_artemis_wooing0_initial_announcement"];

    fDemeterWooing.fFull.fTitle = fMessages["PHRASE_demeter_wooing0_title"];
    fDemeterWooing.fFull.fText = fMessages["PHRASE_demeter_wooing0_initial_announcement"];
    fDemeterWooing.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_demeter_wooing0_title"];
    fDemeterWooing.fCondensed.fText = fMessages["PHRASE_CONDENSED_demeter_wooing0_initial_announcement"];

    fHadesWooing.fFull.fTitle = fMessages["PHRASE_hades_wooing0_title"];
    fHadesWooing.fFull.fText = fMessages["PHRASE_hades_wooing0_initial_announcement"];
    fHadesWooing.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_hades_wooing0_title"];
    fHadesWooing.fCondensed.fText = fMessages["PHRASE_CONDENSED_hades_wooing0_initial_announcement"];

    fZeusWooing.fFull.fTitle = fMessages["PHRASE_zeus_wooing0_title"];
    fZeusWooing.fFull.fText = fMessages["PHRASE_zeus_wooing0_initial_announcement"];
    fZeusWooing.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_zeus_wooing0_title"];
    fZeusWooing.fCondensed.fText = fMessages["PHRASE_CONDENSED_zeus_wooing0_initial_announcement"];

    fHomeGames.fBegin.fFull.fTitle = fMessages["PHRASE_home_games_begin_title"];
    fHomeGames.fBegin.fFull.fText = fMessages["PHRASE_home_games_begin_initial_announcement"];
    fHomeGames.fBegin.fCondensed.fText = fMessages["PHRASE_CONDENSED_home_games_begin_initial_announcement"];
    fHomeGames.fNoPart.fFull.fTitle = fMessages["PHRASE_home_games_cancelled_title"];
    fHomeGames.fNoPart.fFull.fText = fMessages["PHRASE_home_games_cancelled_initial_announcement"];
    fHomeGames.fNoPart.fCondensed.fText = fMessages["PHRASE_CONDENSED_home_games_cancelled_initial_announcement"];
    fHomeGames.fWon.fFull.fTitle = fMessages["PHRASE_home_games_conclude_title"];
    fHomeGames.fWon.fFull.fText = fMessages["PHRASE_home_games_conclude_initial_announcement_won"];
    fHomeGames.fWon.fCondensed.fText = fMessages["PHRASE_CONDENSED_home_games_conclude_initial_announcement_won"];
    fHomeGames.fSecond.fFull.fTitle = fMessages["PHRASE_home_games_conclude_title"];
    fHomeGames.fSecond.fFull.fText = fMessages["PHRASE_home_games_conclude_initial_announcement_second"];
    fHomeGames.fSecond.fCondensed.fText = fMessages["PHRASE_CONDENSED_home_games_conclude_initial_announcement_second"];
    fHomeGames.fLost.fFull.fTitle = fMessages["PHRASE_home_games_conclude_title"];
    fHomeGames.fLost.fFull.fText = fMessages["PHRASE_home_games_conclude_initial_announcement_lost"];
    fHomeGames.fLost.fCondensed.fText = fMessages["PHRASE_CONDENSED_home_games_conclude_initial_announcement_lost"];

    fOlympianGames.fBegin.fFull.fTitle = fMessages["PHRASE_olympian_games_begin_title"];
    fOlympianGames.fBegin.fFull.fText = fMessages["PHRASE_olympian_games_begin_initial_announcement_go"];
    fOlympianGames.fBegin.fCondensed.fText = fMessages["PHRASE_CONDENSED_olympian_games_begin_initial_announcement_go"];
    fOlympianGames.fNoPart.fFull.fTitle = fMessages["PHRASE_olympian_games_cant_participate_title"];
    fOlympianGames.fNoPart.fFull.fText = fMessages["PHRASE_olympian_games_cant_participate_initial_announcement"];
    fOlympianGames.fNoPart.fCondensed.fText = fMessages["PHRASE_CONDENSED_olympian_games_cant_participate_initial_announcement"];
    fOlympianGames.fWon.fFull.fTitle = fMessages["PHRASE_olympian_games_conclude_title"];
    fOlympianGames.fWon.fFull.fText = fMessages["PHRASE_olympian_games_conclude_initial_announcement_won"];
    fOlympianGames.fWon.fCondensed.fText = fMessages["PHRASE_CONDENSED_olympian_games_conclude_initial_announcement_won"];
    fOlympianGames.fSecond.fFull.fTitle = fMessages["PHRASE_olympian_games_conclude_title"];
    fOlympianGames.fSecond.fFull.fText = fMessages["PHRASE_olympian_games_conclude_initial_announcement_second"];
    fOlympianGames.fSecond.fCondensed.fText = fMessages["PHRASE_CONDENSED_olympian_games_conclude_initial_announcement_second"];
    fOlympianGames.fLost.fFull.fTitle = fMessages["PHRASE_olympian_games_conclude_title"];
    fOlympianGames.fLost.fFull.fText = fMessages["PHRASE_olympian_games_conclude_initial_announcement_lost"];
    fOlympianGames.fLost.fCondensed.fText = fMessages["PHRASE_CONDENSED_olympian_games_conclude_initial_announcement_lost"];

    fPythianGames.fBegin.fFull.fTitle = fMessages["PHRASE_pythian_games_begin_title"];
    fPythianGames.fBegin.fFull.fText = fMessages["PHRASE_pythian_games_begin_initial_announcement_go"];
    fPythianGames.fBegin.fCondensed.fText = fMessages["PHRASE_CONDENSED_pythian_games_begin_initial_announcement_go"];
    fPythianGames.fNoPart.fFull.fTitle = fMessages["PHRASE_pythian_games_cant_participate_title"];
    fPythianGames.fNoPart.fFull.fText = fMessages["PHRASE_pythian_games_cant_participate_initial_announcement"];
    fPythianGames.fNoPart.fCondensed.fText = fMessages["PHRASE_CONDENSED_pythian_games_cant_participate_initial_announcement"];
    fPythianGames.fWon.fFull.fTitle = fMessages["PHRASE_pythian_games_conclude_title"];
    fPythianGames.fWon.fFull.fText = fMessages["PHRASE_pythian_games_conclude_initial_announcement_won"];
    fPythianGames.fWon.fCondensed.fText = fMessages["PHRASE_CONDENSED_pythian_games_conclude_initial_announcement_won"];
    fPythianGames.fSecond.fFull.fTitle = fMessages["PHRASE_pythian_games_conclude_title"];
    fPythianGames.fSecond.fFull.fText = fMessages["PHRASE_pythian_games_conclude_initial_announcement_second"];
    fPythianGames.fSecond.fCondensed.fText = fMessages["PHRASE_CONDENSED_pythian_games_conclude_initial_announcement_second"];
    fPythianGames.fLost.fFull.fTitle = fMessages["PHRASE_pythian_games_conclude_title"];
    fPythianGames.fLost.fFull.fText = fMessages["PHRASE_pythian_games_conclude_initial_announcement_lost"];
    fPythianGames.fLost.fCondensed.fText = fMessages["PHRASE_CONDENSED_pythian_games_conclude_initial_announcement_lost"];

    fIsthmianGames.fBegin.fFull.fTitle = fMessages["PHRASE_isthmian_games_begin_title"];
    fIsthmianGames.fBegin.fFull.fText = fMessages["PHRASE_isthmian_games_begin_initial_announcement_go"];
    fIsthmianGames.fBegin.fCondensed.fText = fMessages["PHRASE_CONDENSED_isthmian_games_begin_initial_announcement_go"];
    fIsthmianGames.fNoPart.fFull.fTitle = fMessages["PHRASE_isthmian_games_cant_participate_title"];
    fIsthmianGames.fNoPart.fFull.fText = fMessages["PHRASE_isthmian_games_cant_participate_initial_announcement"];
    fIsthmianGames.fNoPart.fCondensed.fText = fMessages["PHRASE_CONDENSED_isthmian_games_cant_participate_initial_announcement"];
    fIsthmianGames.fWon.fFull.fTitle = fMessages["PHRASE_isthmian_games_conclude_title"];
    fIsthmianGames.fWon.fFull.fText = fMessages["PHRASE_isthmian_games_conclude_initial_announcement_won"];
    fIsthmianGames.fWon.fCondensed.fText = fMessages["PHRASE_CONDENSED_isthmian_games_conclude_initial_announcement_won"];
    fIsthmianGames.fSecond.fFull.fTitle = fMessages["PHRASE_isthmian_games_conclude_title"];
    fIsthmianGames.fSecond.fFull.fText = fMessages["PHRASE_isthmian_games_conclude_initial_announcement_second"];
    fIsthmianGames.fSecond.fCondensed.fText = fMessages["PHRASE_CONDENSED_isthmian_games_conclude_initial_announcement_second"];
    fIsthmianGames.fLost.fFull.fTitle = fMessages["PHRASE_isthmian_games_conclude_title"];
    fIsthmianGames.fLost.fFull.fText = fMessages["PHRASE_isthmian_games_conclude_initial_announcement_lost"];
    fIsthmianGames.fLost.fCondensed.fText = fMessages["PHRASE_CONDENSED_isthmian_games_conclude_initial_announcement_lost"];

    fNemeanGames.fBegin.fFull.fTitle = fMessages["PHRASE_nemean_games_begin_title"];
    fNemeanGames.fBegin.fFull.fText = fMessages["PHRASE_nemean_games_begin_initial_announcement_go"];
    fNemeanGames.fBegin.fCondensed.fText = fMessages["PHRASE_CONDENSED_nemean_games_begin_initial_announcement_go"];
    fNemeanGames.fNoPart.fFull.fTitle = fMessages["PHRASE_nemean_games_cant_participate_title"];
    fNemeanGames.fNoPart.fFull.fText = fMessages["PHRASE_nemean_games_cant_participate_initial_announcement"];
    fNemeanGames.fNoPart.fCondensed.fText = fMessages["PHRASE_CONDENSED_nemean_games_cant_participate_initial_announcement"];
    fNemeanGames.fWon.fFull.fTitle = fMessages["PHRASE_nemean_games_conclude_title"];
    fNemeanGames.fWon.fFull.fText = fMessages["PHRASE_nemean_games_conclude_initial_announcement_won"];
    fNemeanGames.fWon.fCondensed.fText = fMessages["PHRASE_CONDENSED_nemean_games_conclude_initial_announcement_won"];
    fNemeanGames.fSecond.fFull.fTitle = fMessages["PHRASE_nemean_games_conclude_title"];
    fNemeanGames.fSecond.fFull.fText = fMessages["PHRASE_nemean_games_conclude_initial_announcement_second"];
    fNemeanGames.fSecond.fCondensed.fText = fMessages["PHRASE_CONDENSED_nemean_games_conclude_initial_announcement_second"];
    fNemeanGames.fLost.fFull.fTitle = fMessages["PHRASE_nemean_games_conclude_title"];
    fNemeanGames.fLost.fFull.fText = fMessages["PHRASE_nemean_games_conclude_initial_announcement_lost"];
    fNemeanGames.fLost.fCondensed.fText = fMessages["PHRASE_CONDENSED_nemean_games_conclude_initial_announcement_lost"];

    return true;
}

bool eMessages::load() {
    return instance.loadImpl();
}

bool eMessages::loaded() {
    return instance.mLoaded;
}

const std::string& eMessages::message(const std::string& key) {
    return instance.fMessages[key];
}
