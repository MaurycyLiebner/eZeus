#include "emessages.h"

#include <fstream>

#include "egamedir.h"

#include "eloadtexthelper.h"
#include "estringhelpers.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

eMessages eMessages::instance;

void eMessages::load(eGodMessages& god, const std::string& godName) {
    god.fWooing0.fFull.fTitle = fMessages["PHRASE_" + godName + "_wooing0_title"];
    god.fWooing0.fFull.fText = fMessages["PHRASE_" + godName + "_wooing0_initial_announcement"];
    god.fWooing0.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_wooing0_title"];
    god.fWooing0.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_wooing0_initial_announcement"];

    god.fJealousy1.fFull.fTitle = fMessages["PHRASE_" + godName + "_jealousy1_title"];
    god.fJealousy1.fFull.fText = fMessages["PHRASE_" + godName + "_jealousy1_initial_announcement"];
    god.fJealousy1.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_jealousy1_title"];
    god.fJealousy1.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_jealousy1_initial_announcement"];

    god.fJealousy2.fFull.fTitle = fMessages["PHRASE_" + godName + "_jealousy2_title"];
    god.fJealousy2.fFull.fText = fMessages["PHRASE_" + godName + "_jealousy2_initial_announcement"];
    god.fJealousy2.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_jealousy2_title"];
    god.fJealousy2.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_jealousy2_initial_announcement"];

    god.fMonster.fFull.fTitle = fMessages["PHRASE_" + godName + "_unleashes_monster_title"];
    god.fMonster.fFull.fText = fMessages["PHRASE_" + godName + "_unleashes_monster_city_attacked_alert"];
    god.fMonster.fNoReason = fMessages["PHRASE_" + godName + "_unleashes_monster_no_reason"];
    eStringHelpers::replaceAll(god.fMonster.fFull.fText, "[reason_phrase]", god.fMonster.fNoReason);
    god.fMonster.fReason = fMessages["PHRASE_" + godName + "_unleashes_monster_reason"];
    god.fMonster.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_unleashes_monster_title"];
    god.fMonster.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_unleashes_monster_city_attacked_alert"];

    god.fQuest1.fQuest.fFull.fTitle = fMessages["PHRASE_" + godName + "_quest_title"];
    god.fQuest1.fQuest.fFull.fText = fMessages["PHRASE_" + godName + "_quest_initial_announcement"];
    god.fQuest1.fQuest.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_quest_title"];
    god.fQuest1.fQuest.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_quest_initial_announcement"];
    god.fQuest1.fQuest.fNoReason = fMessages["PHRASE_" + godName + "_quest_no_reason"];
    god.fQuest1.fQuest.fReason = fMessages["PHRASE_" + godName + "_quest_reason"];

    god.fQuest1.fFulfilled.fFull.fTitle = fMessages["PHRASE_" + godName + "_quest_fulfilled_title"];
    god.fQuest1.fFulfilled.fFull.fText = fMessages["PHRASE_" + godName + "_quest_fulfilled_initial_announcement"];
    god.fQuest1.fFulfilled.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_quest_fulfilled_title"];
    god.fQuest1.fFulfilled.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_quest_fulfilled_initial_announcement"];
    god.fQuest1.fFulfilled.fNoReason = fMessages["PHRASE_" + godName + "_quest_fulfilled_no_reason"];
    god.fQuest1.fFulfilled.fReason = fMessages["PHRASE_" + godName + "_quest_fulfilled_reason"];

    god.fQuest2.fQuest.fFull.fTitle = fMessages["PHRASE_" + godName + "_quest2_title"];
    god.fQuest2.fQuest.fFull.fText = fMessages["PHRASE_" + godName + "_quest2_initial_announcement"];
    god.fQuest2.fQuest.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_quest2_title"];
    god.fQuest2.fQuest.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_quest2_initial_announcement"];
    god.fQuest2.fQuest.fNoReason = fMessages["PHRASE_" + godName + "_quest2_no_reason"];
    god.fQuest2.fQuest.fReason = fMessages["PHRASE_" + godName + "_quest2_reason"];

    god.fQuest2.fFulfilled.fFull.fTitle = fMessages["PHRASE_" + godName + "_quest2_fulfilled_title"];
    god.fQuest2.fFulfilled.fFull.fText = fMessages["PHRASE_" + godName + "_quest2_fulfilled_initial_announcement"];
    god.fQuest2.fFulfilled.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_quest2_fulfilled_title"];
    god.fQuest2.fFulfilled.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_quest2_fulfilled_initial_announcement"];
    god.fQuest2.fFulfilled.fNoReason = fMessages["PHRASE_" + godName + "_quest2_fulfilled_no_reason"];
    god.fQuest2.fFulfilled.fReason = fMessages["PHRASE_" + godName + "_quest2_fulfilled_reason"];

    god.fSanctuaryComplete.fFull.fTitle = fMessages["PHRASE_" + godName + "_sanctuary_complete_title"];
    god.fSanctuaryComplete.fFull.fText = fMessages["PHRASE_" + godName + "_sanctuary_complete_initial_announcement"];
    god.fSanctuaryComplete.fCondensed.fTitle = fMessages["PHRASE_" + godName + "_sanctuary_complete_title"];
    god.fSanctuaryComplete.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_sanctuary_complete_initial_announcement"];
}

void eMessages::load(eHeroMessages& hero, const std::string& heroName) {
    hero.fArrival.fFull.fTitle = fMessages["PHRASE_" + heroName + "_arrives_title"];
    hero.fArrival.fFull.fText = fMessages["PHRASE_" + heroName + "_arrives_initial_announcement"];
    hero.fArrival.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + heroName + "_arrives_title"];
    hero.fArrival.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + heroName + "_arrives_initial_announcement"];

    hero.fHallAvailable.fFull.fTitle = fMessages["PHRASE_" + heroName + "_hall_available_title"];
    hero.fHallAvailable.fNoReason = fMessages["PHRASE_" + heroName + "_hall_available_no_reason"];
    hero.fHallAvailable.fFull.fText = fMessages["PHRASE_" + heroName + "_hall_available_initial_announcement"];
    hero.fHallAvailable.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + heroName + "_hall_available_title"];
    hero.fHallAvailable.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + heroName + "_hall_available_initial_announcement"];
}

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

    fFire.fFull.fTitle = fMessages["PHRASE_fire_title"];
    fFire.fFull.fText = fMessages["PHRASE_fire_initial_announcement"];
    fFire.fCondensed.fText = fMessages["PHRASE_CONDENSED_fire_initial_announcement"];

    fCollapse.fFull.fTitle = fMessages["PHRASE_collapsed_building_title"];
    fCollapse.fFull.fText = fMessages["PHRASE_collapsed_building_initial_announcement"];
    fCollapse.fCondensed.fText = fMessages["PHRASE_CONDENSED_collapsed_building_initial_announcement"];

    fPlagueStrikes.fFull.fTitle = fMessages["PHRASE_plague_title"];
    fPlagueStrikes.fFull.fText = fMessages["PHRASE_plague_initial_announcement"];
    fPlagueStrikes.fCondensed.fText = fMessages["PHRASE_CONDENSED_plague_initial_announcement"];

    load(fAphrodite, "aphrodite");
    load(fApollo, "apollo");
    load(fAres, "ares");
    load(fArtemis, "artemis");
    load(fAthena, "athena");
    load(fAtlas, "atlas");
    load(fDemeter, "demeter");
    load(fDionysus, "dionysus");
    load(fHades, "hades");
    load(fHephaestus, "hephaestus");
    load(fHera, "hera");
    load(fHermes, "hermes");
    load(fPoseidon, "poseidon");
    load(fZeus, "zeus");

    load(fAchilles, "achilles");
    load(fAtalanta, "atalanta");
    load(fBellerophon, "bellerophon");
    load(fHercules, "hercules");
    load(fJason, "jason");
    load(fOdysseus, "odysseus");
    load(fPerseus, "perseus");
    load(fTheseus, "theseus");

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

    fInvasion36.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion36.fFull.fText = fMessages["PHRASE_invasion_initial_announcement"];
    fInvasion36.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion36.fCondensed.fText = fMessages["PHRASE_CONDENSED_invasion_initial_announcement"];

    fInvasion24.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion24.fFull.fText = fMessages["PHRASE_invasion_2year_reminder"];
    fInvasion24.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion24.fCondensed.fText = fMessages["PHRASE_CONDENSED_invasion_2year_reminder"];

    fInvasion12.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion12.fFull.fText = fMessages["PHRASE_invasion_1year_reminder"];
    fInvasion12.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion12.fCondensed.fText = fMessages["PHRASE_CONDENSED_invasion_1year_reminder"];

    fInvasion6.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion6.fFull.fText = fMessages["PHRASE_invasion_6month_warning"];
    fInvasion6.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion6.fCondensed.fText = fMessages["PHRASE_CONDENSED_invasion_6month_warning"];

    fInvasion1.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion1.fFull.fText = fMessages["PHRASE_invasion_1month_Warning"];
    fInvasion1.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion1.fCondensed.fText = fMessages["PHRASE_invasion_1month_Warning"];

    fInvasion.fFull.fTitle = fMessages["PHRASE_invasion_title"];
    fInvasion.fFull.fText = fMessages["PHRASE_invasion_city_attacked_alert"];
    fInvasion.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_invasion_title"];
    fInvasion.fCondensed.fText = fMessages["PHRASE_CONDENSED_invasion_city_attacked_alert"];

    fInvasionBribed.fFull.fTitle = fMessages["PHRASE_players_city_saved_bribery_title"];
    fInvasionBribed.fFull.fText = fMessages["PHRASE_players_city_saved_bribery_initial_announcement"];

    fInvasionBribed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_players_city_saved_bribery_title"];
    fInvasionBribed.fCondensed.fText = fMessages["PHRASE_CONDENSED_players_city_saved_bribery_initial_announcement"];

    fInvasionBribed.fFull.fTitle = fMessages["PHRASE_players_city_saved_bribery_title"];
    fInvasionBribed.fFull.fText = fMessages["PHRASE_players_city_saved_bribery_initial_announcement"];

    fInvasionBribed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_players_city_saved_bribery_title"];
    fInvasionBribed.fCondensed.fText = fMessages["PHRASE_CONDENSED_players_city_saved_bribery_initial_announcement"];

    fInvasionDefeat.fFull.fTitle = fMessages["PHRASE_enemy_victorious_title"];
    fInvasionDefeat.fFull.fText = fMessages["PHRASE_enemy_victorious_initial_announcement"];

    fInvasionDefeat.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_enemy_victorious_title"];
    fInvasionDefeat.fCondensed.fText = fMessages["PHRASE_CONDENSED_enemy_victorious_initial_announcement"];

    fInvasionVictory.fFull.fTitle = fMessages["PHRASE_players_city_saved_title"];
    fInvasionVictory.fFull.fText = fMessages["PHRASE_players_city_saved_initial_announcement"];

    fInvasionVictory.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_players_city_saved_title"];
    fInvasionVictory.fCondensed.fText = fMessages["PHRASE_CONDENSED_players_city_saved_initial_announcement"];

    fTributePaidGranted.fFull.fTitle = fMessages["PHRASE_tribute_paid_title"];
    fTributePaidGranted.fFull.fText = fMessages["PHRASE_tribute_paid_granted"];
    fTributePaidGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_tribute_paid_title"];
    fTributePaidGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_tribute_paid_granted"];

    fTributePaidAccepted.fFull.fTitle = fMessages["PHRASE_tribute_paid_title"];
    fTributePaidAccepted.fFull.fText = fMessages["PHRASE_tribute_paid_accepted"];
    fTributePaidAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_tribute_paid_title"];
    fTributePaidAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_tribute_paid_accepted"];

    fTributePaidRefused.fFull.fTitle = fMessages["PHRASE_tribute_paid_title"];
    fTributePaidRefused.fFull.fText = fMessages["PHRASE_tribute_paid_refused"];
    fTributePaidRefused.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_tribute_paid_title"];
    fTributePaidRefused.fCondensed.fText = fMessages["PHRASE_CONDENSED_tribute_paid_refused"];

    fTributePostponed.fFull.fTitle = fMessages["PHRASE_tribute_paid_title"];
    fTributePostponed.fFull.fText = fMessages["PHRASE_tribute_paid_postponed"];
    fTributePostponed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_tribute_paid_title"];
    fTributePostponed.fCondensed.fText = fMessages["PHRASE_CONDENSED_tribute_paid_postponed"];

    fRequestGranted.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestGranted.fFull.fText = fMessages["PHRASE_request_granted_granted"];
    fRequestGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_granted"];

    fRequestPartialSpace.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestPartialSpace.fFull.fText = fMessages["PHRASE_request_granted_partial_space"];
    fRequestPartialSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestPartialSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_partial_space"];

    fRequestInsufficientSpace.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestInsufficientSpace.fFull.fText = fMessages["PHRASE_request_granted_insufficient_space"];
    fRequestInsufficientSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestInsufficientSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_insufficient_space"];

    fRequestLastChance.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestLastChance.fFull.fText = fMessages["PHRASE_request_granted_last_chance"];
    fRequestLastChance.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestLastChance.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_last_chance"];

    fRequestAccepted.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestAccepted.fFull.fText = fMessages["PHRASE_request_granted_accepted"];
    fRequestAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_accepted"];

    fRequestPostponed.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestPostponed.fFull.fText = fMessages["PHRASE_request_granted_postponed"];
    fRequestPostponed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestPostponed.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_postponed"];

    fRequestRefused.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestRefused.fFull.fText = fMessages["PHRASE_request_granted_refused"];
    fRequestRefused.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestRefused.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_refused"];

    fRequestForfeited.fFull.fTitle = fMessages["PHRASE_request_granted_title"];
    fRequestForfeited.fFull.fText = fMessages["PHRASE_request_granted_forfeited"];
    fRequestForfeited.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_request_granted_title"];
    fRequestForfeited.fCondensed.fText = fMessages["PHRASE_CONDENSED_request_granted_forfeited"];

    fDemandRefused.fFull.fTitle = fMessages["PHRASE_demand_refused_title"];
    fDemandRefused.fFull.fText = fMessages["PHRASE_demand_refused_initial_announcement"];
    fDemandRefused.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_demand_refused_title"];
    fDemandRefused.fCondensed.fText = fMessages["PHRASE_CONDENSED_demand_refused_initial_announcement"];

    fGiftReceivedDrachmas.fFull.fTitle = fMessages["PHRASE_gift_received_money_title"];
    fGiftReceivedDrachmas.fFull.fText = fMessages["PHRASE_gift_received_money_initial_announcement"];
    fGiftReceivedDrachmas.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_received_money_title"];
    fGiftReceivedDrachmas.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_received_money_initial_announcement"];

    fGiftReceivedNeeded.fFull.fTitle = fMessages["PHRASE_gift_received_needs_title"];
    fGiftReceivedNeeded.fFull.fText = fMessages["PHRASE_gift_received_needs_initial_announcement"];
    fGiftReceivedNeeded.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_received_needs_title"];
    fGiftReceivedNeeded.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_received_needs_initial_announcement"];

    fGiftReceivedSells.fFull.fTitle = fMessages["PHRASE_gift_received_produces_title"];
    fGiftReceivedSells.fFull.fText = fMessages["PHRASE_gift_received_produces_initial_announcement"];
    fGiftReceivedSells.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_received_produces_title"];
    fGiftReceivedSells.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_received_produces_initial_announcement"];

    fGiftReceivedNotNeeded.fFull.fTitle = fMessages["PHRASE_gift_received_doesnt_need_title"];
    fGiftReceivedNotNeeded.fFull.fText = fMessages["PHRASE_gift_received_doesnt_need_initial_announcement"];
    fGiftReceivedNotNeeded.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_received_doesnt_need_title"];
    fGiftReceivedNotNeeded.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_received_doesnt_need_initial_announcement"];

    fGiftReceivedRefuse.fFull.fTitle = fMessages["PHRASE_gift_refused_title"];
    fGiftReceivedRefuse.fFull.fText = fMessages["PHRASE_gift_refused_initial_announcement"];
    fGiftReceivedRefuse.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_refused_title"];
    fGiftReceivedRefuse.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_refused_initial_announcement"];

    fGeneralRequestInitialS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestInitialS.fFull.fText = fMessages["PHRASE_general_request_initial_announcement_S"];
    fGeneralRequestInitialS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestInitialS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_initial_announcement_S"];

    fGeneralRequestReminderS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestReminderS.fFull.fText = fMessages["PHRASE_general_request_reminder_S"];
    fGeneralRequestReminderS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestReminderS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_reminder_S"];

    fGeneralRequestOverdueS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestOverdueS.fFull.fText = fMessages["PHRASE_general_request_overdue_S"];
    fGeneralRequestOverdueS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestOverdueS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_overdue_S"];

    fGeneralRequestWarningS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestWarningS.fFull.fText = fMessages["PHRASE_general_request_warning_S"];
    fGeneralRequestWarningS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestWarningS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_warning_S"];

    fGeneralRequestComplyS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestComplyS.fFull.fText = fMessages["PHRASE_general_request_comply_reason_S"];
    fGeneralRequestComplyS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestComplyS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_comply_reason_S"];

    fGeneralRequestTooLateS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestTooLateS.fFull.fText = fMessages["PHRASE_general_request_too_late_reason_S"];
    fGeneralRequestTooLateS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestTooLateS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_too_late_reason_S"];

    fGeneralRequestRefuseS.fFull.fTitle = fMessages["PHRASE_general_request_title_S"];
    fGeneralRequestRefuseS.fFull.fText = fMessages["PHRASE_general_request_refuse_reason_S"];
    fGeneralRequestRefuseS.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_general_request_title_S"];
    fGeneralRequestRefuseS.fCondensed.fText = fMessages["PHRASE_CONDENSED_general_request_refuse_reason_S"];

    fGeneralRequestEarlyReasonS.fFull = fMessages["PHRASE_general_request_early_reason_S"];
    fGeneralRequestComplyReasonS.fFull = fMessages["PHRASE_general_request_comply_reason_S"];
    fGeneralRequestTooLateReasonS.fFull = fMessages["PHRASE_general_request_too_late_reason_S"];
    fGeneralRequestRefuseReasonS.fFull = fMessages["PHRASE_general_request_refuse_reason_S"];

    fGeneralRequestEarlyReasonS.fCondensed = fMessages["PHRASE_CONDENSED_general_request_early_reason_S"];
    fGeneralRequestComplyReasonS.fCondensed = fMessages["PHRASE_CONDENSED_general_request_comply_reason_S"];
    fGeneralRequestTooLateReasonS.fCondensed = fMessages["PHRASE_CONDENSED_general_request_too_late_reason_S"];
    fGeneralRequestRefuseReasonS.fCondensed = fMessages["PHRASE_CONDENSED_general_request_refuse_reason_S"];

    fGiftGranted.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftGranted.fFull.fText = fMessages["PHRASE_gift_granted"];
    fGiftGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_granted"];

    fGiftCashGranted.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftCashGranted.fFull.fText = fMessages["PHRASE_gift_cash_granted"];
    fGiftCashGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftCashGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_cash_granted"];

    fGiftPartialSpace.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftPartialSpace.fFull.fText = fMessages["PHRASE_gift_partial_space"];
    fGiftPartialSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftPartialSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_partial_space"];

    fGiftInsufficientSpace.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftInsufficientSpace.fFull.fText = fMessages["PHRASE_gift_insufficient_space"];
    fGiftInsufficientSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftInsufficientSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_insufficient_space"];

    fGiftLastChance.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftLastChance.fFull.fText = fMessages["PHRASE_gift_last_chance"];
    fGiftLastChance.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftLastChance.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_last_chance"];

    fGiftForfeited.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftForfeited.fFull.fText = fMessages["PHRASE_gift_forfeited"];
    fGiftForfeited.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftForfeited.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_forfeited"];

    fGiftAccepted.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftAccepted.fFull.fText = fMessages["PHRASE_gift_accepted"];
    fGiftAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_accepted"];

    fGiftCashAccepted.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftCashAccepted.fFull.fText = fMessages["PHRASE_gift_cash_accepted"];
    fGiftCashAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftCashAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_cash_accepted"];

    fGiftPostponed.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftPostponed.fFull.fText = fMessages["PHRASE_gift_postponed"];
    fGiftPostponed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftPostponed.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_postponed"];

    fGiftRefused.fFull.fTitle = fMessages["PHRASE_gift_title"];
    fGiftRefused.fFull.fText = fMessages["PHRASE_gift_refused"];
    fGiftRefused.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_gift_title"];
    fGiftRefused.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_refused"];

    fIncreasedFavor.fFull.fTitle = fMessages["PHRASE_favor_change_title_I"];
    fIncreasedFavor.fFull.fText = fMessages["PHRASE_favor_change_initial_announcement_I"];
    fIncreasedFavor.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_favor_change_title_I"];
    fIncreasedFavor.fCondensed.fText = fMessages["PHRASE_CONDENSED_favor_change_initial_announcement_I"];

    fDecreasedFavor.fFull.fTitle = fMessages["PHRASE_favor_change_title_D"];
    fDecreasedFavor.fFull.fText = fMessages["PHRASE_favor_change_initial_announcement_D"];
    fDecreasedFavor.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_favor_change_title_D"];
    fDecreasedFavor.fCondensed.fText = fMessages["PHRASE_CONDENSED_favor_change_initial_announcement_D"];

    fUnemployment.fFull.fTitle = fMessages[";PHRASE_unemployment_title"];
    fUnemployment.fFull.fText = fMessages[";PHRASE_unemployment_initial_announcement"];
    fUnemployment.fCondensed.fTitle = fMessages[";PHRASE_CONDENSED_unemployment_title"];
    fUnemployment.fCondensed.fText = fMessages[";PHRASE_CONDENSED_unemployment_initial_announcement"];

    fEmployees.fFull.fTitle = fMessages["PHRASE_employees_needed_title"];
    fEmployees.fFull.fText = fMessages["PHRASE_employees_needed_initial_announcement"];
    fEmployees.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_employees_needed_title"];
    fEmployees.fCondensed.fText = fMessages["PHRASE_CONDENSED_employees_needed_initial_announcement"];

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

eMessageType eMessages::favorMessage(const eMessageType& reason) {
    const auto& ifavor = instance.fIncreasedFavor;
    eMessageType msg = ifavor;
    auto& text = msg.fFull.fText;
    eStringHelpers::replaceAll(text, "[reason_phrase]",
                               reason.fFull.fText);
    return msg;
}

eMessageType eMessages::dfavorMessage(const eMessageType& reason) {
    const auto& ifavor = instance.fDecreasedFavor;
    eMessageType msg = ifavor;
    auto& text = msg.fFull.fText;
    eStringHelpers::replaceAll(text, "[reason_phrase]",
                               reason.fFull.fText);
    return msg;
}

eMessageType eMessages::invasionMessage(const eMessageType& baseMsg,
                                        const std::string& reason,
                                        const int months) {
    eMessageType msg = baseMsg;
    auto& text = msg.fFull.fText;
    if(reason.empty()) {
        const auto& inst = eMessages::instance;
        eStringHelpers::replaceAll(text, "[reason_phrase]",
                                   inst.fInvasionNoReason);
    } else {
        eStringHelpers::replaceAll(text, "[reason_phrase]",
                                   reason);
    }
    eStringHelpers::replaceAll(text, "[time_until_attack]",
                               std::to_string(months));
    return msg;
}

eGodMessages* eMessages::godMessages(const eGodType godType) {
    switch(godType) {
    case eGodType::aphrodite:
        return &fAphrodite;
    case eGodType::apollo:
        return &fApollo;
    case eGodType::ares:
        return &fAres;
    case eGodType::artemis:
        return &fArtemis;
    case eGodType::athena:
        return &fAthena;
    case eGodType::atlas:
        return &fAtlas;
    case eGodType::demeter:
        return &fDemeter;
    case eGodType::dionysus:
        return &fDionysus;
    case eGodType::hades:
        return &fHades;
    case eGodType::hephaestus:
        return &fHephaestus;
    case eGodType::hera:
        return &fHera;
    case eGodType::hermes:
        return &fHermes;
    case eGodType::poseidon:
        return &fPoseidon;
    case eGodType::zeus:
        return &fZeus;
    }
    return nullptr;
}

const eHeroMessages* eMessages::heroMessages(const eHeroType heroType) const {
    switch(heroType) {
    case eHeroType::achilles:
        return &fAchilles;
    case eHeroType::atalanta:
        return &fAtalanta;
    case eHeroType::bellerophon:
        return &fBellerophon;
    case eHeroType::hercules:
        return &fHercules;
    case eHeroType::jason:
        return &fJason;
    case eHeroType::odysseus:
        return &fOdysseus;
    case eHeroType::perseus:
        return &fPerseus;
    case eHeroType::theseus:
        return &fTheseus;
    }
    return nullptr;
}
