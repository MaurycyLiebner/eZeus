#include "emessages.h"

#include <fstream>

#include "egamedir.h"

#include "eloadtexthelper.h"
#include "estringhelpers.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"
#include "characters/monsters/emonster.h"

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

    god.fInvades.fFull.fTitle = fMessages["PHRASE_" + godName + "_invades_title"];
    god.fInvades.fFull.fText = fMessages["PHRASE_" + godName + "_invades_city_attacked_alert"];
    god.fInvades.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_invades_title"];
    god.fInvades.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_invades_initial_announcement"];

    god.fHelps.fFull.fTitle = fMessages["PHRASE_" + godName + "_help_title"];
    god.fHelps.fFull.fText = fMessages["PHRASE_" + godName + "_help_initial_announcement"];
    god.fHelps.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + godName + "_help_title"];
    god.fHelps.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_help_initial_announcement"];
    god.fHelps.fReason = fMessages["PHRASE_" + godName + "_help_reason"];

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

    god.fDisaster.fFull.fTitle = fMessages["PHRASE_" + godName + "_disaster_title"];
    god.fDisaster.fFull.fText = fMessages["PHRASE_" + godName + "_disaster_initial_announcement"];
    god.fDisaster.fCondensed.fTitle = fMessages["PHRASE_" + godName + "_disaster_title"];
    god.fDisaster.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_disaster_initial_announcement"];

    god.fDisasterEnds.fFull.fTitle = fMessages["PHRASE_" + godName + "_disaster_ends_title"];
    god.fDisasterEnds.fFull.fText = fMessages["PHRASE_" + godName + "_disaster_ends_initial_announcement"];
    god.fDisasterEnds.fCondensed.fTitle = fMessages["PHRASE_" + godName + "_disaster_ends_title"];
    god.fDisasterEnds.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + godName + "_disaster_ends_initial_announcement"];
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

void eMessages::load(eMonsterMessages& monster,
                     const std::string& monsterName1,
                     const std::string& monsterName2) {
    monster.fSlain.fFull.fTitle = fMessages["PHRASE_" + monsterName2 + "_slain_title"];
    monster.fSlain.fFull.fText = fMessages["PHRASE_" + monsterName2 + "_slain_initial_announcement"];
    monster.fSlain.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + monsterName2 + "_slain_title"];
    monster.fSlain.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + monsterName2 + "_slain_initial_announcement"];

    monster.fSlainReason = fMessages["PHRASE_" + monsterName1 + "_slain_reason"];

    monster.fPrediction.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fPrediction.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_oracle_prediction"];
    monster.fPrediction.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fPrediction.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_oracle_prediction"];

    monster.fInvasion36.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion36.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_initial_announcement"];
    monster.fInvasion36.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion36.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_initial_announcement"];

    monster.fInvasion24.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion24.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_2year_reminder"];
    monster.fInvasion24.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion24.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_2year_reminder"];

    monster.fInvasion12.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion12.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_1year_reminder"];
    monster.fInvasion12.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion12.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_1year_reminder"];

    monster.fInvasion6.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion6.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_6month_warning"];
    monster.fInvasion6.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion6.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_6month_warning"];

    monster.fInvasion1.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion1.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_1month_Warning"];
    monster.fInvasion1.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion1.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_1month_Warning"];

    monster.fInvasion.fFull.fTitle = fMessages["PHRASE_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion.fFull.fText = fMessages["PHRASE_independent_" + monsterName2 + "_invades_city_attacked_alert"];
    monster.fInvasion.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_title"];
    monster.fInvasion.fCondensed.fText = fMessages["PHRASE_CONDENSED_independent_" + monsterName2 + "_invades_city_attacked_alert"];

    monster.fToSlainReason = fMessages["PHRASE_independent_" + monsterName2 + "_invades_reason"];
    monster.fMonsterAttackReason = fMessages["PHRASE_independent_" + monsterName2 + "_invades_no_reason"];
}

void eMessages::loadGeneralRequest(
        eReceiveRequestMessages& request,
        const std::string& letter,
        const std::string& mid) {
    request.fInitial.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fInitial.fFull.fText = fMessages["PHRASE_" + mid + "_initial_announcement_" + letter];
    request.fInitial.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fInitial.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_initial_announcement_" + letter];

    request.fReminder.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fReminder.fFull.fText = fMessages["PHRASE_" + mid + "_reminder_" + letter];
    request.fReminder.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fReminder.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_reminder_" + letter];

    request.fOverdue.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fOverdue.fFull.fText = fMessages["PHRASE_" + mid + "_overdue_" + letter];
    request.fOverdue.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fOverdue.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_overdue_" + letter];

    request.fWarning.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fWarning.fFull.fText = fMessages["PHRASE_" + mid + "_warning_" + letter];
    request.fWarning.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fWarning.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_warning_" + letter];

    request.fComply.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fComply.fFull.fText = fMessages["PHRASE_" + mid + "_comply_reason_" + letter];
    request.fComply.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fComply.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_comply_reason_" + letter];

    request.fTooLate.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fTooLate.fFull.fText = fMessages["PHRASE_" + mid + "_too_late_reason_" + letter];
    request.fTooLate.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fTooLate.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_too_late_reason_" + letter];

    request.fRefuse.fFull.fTitle = fMessages["PHRASE_" + mid + "_title_" + letter];
    request.fRefuse.fFull.fText = fMessages["PHRASE_" + mid + "_refuse_reason_" + letter];
    request.fRefuse.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + mid + "_title_" + letter];
    request.fRefuse.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + mid + "_refuse_reason_" + letter];

    request.fEarlyReason.fFull = fMessages["PHRASE_" + mid + "_early_reason_" + letter];
    request.fComplyReason.fFull = fMessages["PHRASE_" + mid + "_comply_reason_" + letter];
    request.fTooLateReason.fFull = fMessages["PHRASE_" + mid + "_too_late_reason_" + letter];
    request.fRefuseReason.fFull = fMessages["PHRASE_" + mid + "_refuse_reason_" + letter];

    request.fEarlyReason.fCondensed = fMessages["PHRASE_CONDENSED_" + mid + "_early_reason_" + letter];
    request.fComplyReason.fCondensed = fMessages["PHRASE_CONDENSED_" + mid + "_comply_reason_" + letter];
    request.fTooLateReason.fCondensed = fMessages["PHRASE_CONDENSED_" + mid + "_too_late_reason_" + letter];
    request.fRefuseReason.fCondensed = fMessages["PHRASE_CONDENSED_" + mid + "_refuse_reason_" + letter];
}

void eMessages::loadResourceGranted(eResourceGrantedMessages& granted,
                                    const std::string& name) {
    granted.fGranted.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fGranted.fFull.fText = fMessages["PHRASE_" + name + "_granted"];
    granted.fGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_granted"];

    granted.fCashGranted.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fCashGranted.fFull.fText = fMessages["PHRASE_" + name + "_cash_granted"];
    granted.fCashGranted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fCashGranted.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_cash_granted"];

    granted.fPartialSpace.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fPartialSpace.fFull.fText = fMessages["PHRASE_" + name + "_partial_space"];
    granted.fPartialSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fPartialSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_partial_space"];

    granted.fInsufficientSpace.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fInsufficientSpace.fFull.fText = fMessages["PHRASE_" + name + "_insufficient_space"];
    granted.fInsufficientSpace.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fInsufficientSpace.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_insufficient_space"];

    granted.fLastChance.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fLastChance.fFull.fText = fMessages["PHRASE_" + name + "_last_chance"];
    granted.fLastChance.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fLastChance.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_last_chance"];

    granted.fForfeited.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fForfeited.fFull.fText = fMessages["PHRASE_" + name + "_forfeited"];
    granted.fForfeited.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fForfeited.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_forfeited"];

    granted.fAccepted.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fAccepted.fFull.fText = fMessages["PHRASE_" + name + "_accepted"];
    granted.fAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_accepted"];

    granted.fCashAccepted.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fCashAccepted.fFull.fText = fMessages["PHRASE_" + name + "_cash_accepted"];
    granted.fCashAccepted.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fCashAccepted.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_cash_accepted"];

    granted.fPostponed.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fPostponed.fFull.fText = fMessages["PHRASE_" + name + "_postponed"];
    granted.fPostponed.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fPostponed.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + name + "_postponed"];

    granted.fRefused.fFull.fTitle = fMessages["PHRASE_" + name + "_title"];
    granted.fRefused.fFull.fText = fMessages["PHRASE_" + name + "_refused"];
    granted.fRefused.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_" + name + "_title"];
    granted.fRefused.fCondensed.fText = fMessages["PHRASE_CONDENSED_gift_refused"];
}

void eMessages::loadMessage(eMessageType& m,
                            const std::string& titleKey,
                            const std::string& textKey) {
    m.fFull.fTitle = fMessages["PHRASE_" + titleKey];
    m.fFull.fText = fMessages["PHRASE_" + textKey];
    m.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + titleKey];
    m.fCondensed.fText = fMessages["PHRASE_CONDENSED_" + textKey];
}

void eMessages::loadReason(eReason& r,
                           const std::string& key) {
    r.fFull = fMessages["PHRASE_" + key];
    r.fCondensed = fMessages["PHRASE_CONDENSED_" + key];
}

void eMessages::load(eTroopsRequestedMessages& troops,
                     const std::string& name,
                     const std::string& letter) {
    loadMessage(troops.fInitialAnnouncement,
                name + "_under_attack_title_" + letter,
                name + "_under_attack_initial_announcement_" + letter);
    loadMessage(troops.fFirstReminder,
                name + "_under_attack_title_" + letter,
                name + "_under_attack_first_reminder_" + letter);
    loadMessage(troops.fLastReminder,
                name + "_under_attack_title_" + letter,
                name + "_under_attack_last_reminder_" + letter);

    loadReason(troops.fEarlyReason,
               name + "_under_attack_early_reason_" + letter);
    loadReason(troops.fComplyReason,
               name + "_under_attack_comply_reason_" + letter);
    loadReason(troops.fTooLateReason,
               name + "_under_attack_too_late_reason_" + letter);
    loadReason(troops.fRefuseReason,
               name + "_under_attack_refuse_reason_" + letter);
    loadReason(troops.fLostBattleReason,
               name + "_under_attack_lost_battle_reason_" + letter);

    if(name == "parentcity") {
        loadMessage(troops.fConquered,
                    "parent_city_falls_title",
                    "parent_city_falls_initial_announcement");
    } else {
        loadMessage(troops.fConquered,
                    name + "_conquered_by_rival_title",
                    name + "_conquered_by_rival_initial_announcement");
    }
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

    fZeusTradeResumes.fFull.fTitle = fMessages["PHRASE_zeus_invasion_trade_resumes_title"];
    fZeusTradeResumes.fFull.fText = fMessages["PHRASE_zeus_invasion_trade_resumes_initial_announcement"];
    fZeusTradeResumes.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_zeus_invasion_trade_resumes_title"];
    fZeusTradeResumes.fCondensed.fText = fMessages["PHRASE_CONDENSED_zeus_invasion_trade_resumes_initial_announcement"];

    fPoseidonTradeResumes.fFull.fTitle = fMessages["PHRASE_poseidon_invasion_trade_resumes_title"];
    fPoseidonTradeResumes.fFull.fText = fMessages["PHRASE_poseidon_invasion_trade_resumes_initial_announcement"];
    fPoseidonTradeResumes.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_poseidon_invasion_trade_resumes_title"];
    fPoseidonTradeResumes.fCondensed.fText = fMessages["PHRASE_CONDENSED_poseidon_invasion_trade_resumes_initial_announcement"];

    fHermesTradeResumes.fFull.fTitle = fMessages["PHRASE_hermes_invasion_trade_resumes_title"];
    fHermesTradeResumes.fFull.fText = fMessages["PHRASE_hermes_invasion_trade_resumes_initial_announcement"];
    fHermesTradeResumes.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_hermes_invasion_trade_resumes_title"];
    fHermesTradeResumes.fCondensed.fText = fMessages["PHRASE_CONDENSED_hermes_invasion_trade_resumes_initial_announcement"];

    load(fAchilles, "achilles");
    load(fAtalanta, "atalanta");
    load(fBellerophon, "bellerophon");
    load(fHercules, "hercules");
    load(fJason, "jason");
    load(fOdysseus, "odysseus");
    load(fPerseus, "perseus");
    load(fTheseus, "theseus");

    load(fCalydonianBoar, "calydonian_boar", "calydonianboar");
    load(fCerberus, "cerberus", "cerberus");
    load(fChimera, "chimera", "chimera");
    load(fCyclops, "cyclops", "cyclops");
    load(fDragon, "dragon", "dragon");
    load(fEchidna, "echidna", "echidna");
    load(fHarpies, "harpies", "harpies");
    load(fHector, "hector", "hector");
    load(fHydra, "hydra", "hydra");
    load(fKraken, "kraken", "kraken");
    load(fMaenads, "maenads", "maenads");
    load(fMedusa, "medusa", "medusa");
    load(fMinotaur, "minotaur", "minotaur");
    load(fScylla, "scylla", "scylla");
    load(fSphinx, "sphinx", "sphinx");
    load(fTalos, "talos", "talos");

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

    fInvasionVictoryMonument.fFull.fTitle = fMessages["PHRASE_players_city_saved_title"];
    fInvasionVictoryMonument.fFull.fText = fMessages["PHRASE_players_city_saved_init_announcment_comm_monument"];

    fInvasionVictoryMonument.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_players_city_saved_title"];
    fInvasionVictoryMonument.fCondensed.fText = fMessages["PHRASE_CONDENSED_players_city_saved_init_announcment_comm_monument"];

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

    loadGeneralRequest(fGeneralRequestAllyS, "S");
    loadGeneralRequest(fGeneralRequestRivalD, "D");
    loadGeneralRequest(fGeneralRequestSubjectP, "P");
    loadGeneralRequest(fGeneralRequestParentR, "R");

    loadGeneralRequest(fTributeRequest, "D", "tribute_due");

    loadResourceGranted(fGiftGranted, "gift");

    fSupportTroopsArrive.fFull.fTitle = fMessages["PHRASE_support_troops_arrive_title"];
    fSupportTroopsArrive.fFull.fText = fMessages["PHRASE_support_troops_arrive_initial_announcement"];
    fSupportTroopsArrive.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_support_troops_arrive_title"];
    fSupportTroopsArrive.fCondensed.fText = fMessages["PHRASE_CONDENSED_support_troops_arrive_initial_announcement"];

    fSupportTroopsDepart.fFull.fTitle = fMessages["PHRASE_support_troops_depart_title"];
    fSupportTroopsDepart.fFull.fText = fMessages["PHRASE_support_troops_depart_initial_announcement"];
    fSupportTroopsDepart.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_support_troops_depart_title"];
    fSupportTroopsDepart.fCondensed.fText = fMessages["PHRASE_CONDENSED_support_troops_depart_initial_announcement"];

    fSupportTroopsDefeated.fFull.fTitle = fMessages["PHRASE_support_troops_defeated_title"];
    fSupportTroopsDefeated.fFull.fText = fMessages["PHRASE_support_troops_defeated_initial_announcement"];
    fSupportTroopsDefeated.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_support_troops_defeated_title"];
    fSupportTroopsDefeated.fCondensed.fText = fMessages["PHRASE_CONDENSED_support_troops_defeated_initial_announcement"];

    fStrikeDepart.fFull.fTitle = fMessages["PHRASE_strike_force_sets_forth_title"];
    fStrikeDepart.fFull.fText = fMessages["PHRASE_strike_force_sets_forth_initial_announcement"];
    fStrikeDepart.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_strike_force_sets_forth_title"];
    fStrikeDepart.fCondensed.fText = fMessages["PHRASE_CONDENSED_strike_force_sets_forth_initial_announcement"];

    fStrikeSuccessful.fFull.fTitle = fMessages["PHRASE_strike_successful_title"];
    fStrikeSuccessful.fFull.fText = fMessages["PHRASE_strike_successful_initial_announcement"];
    fStrikeSuccessful.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_strike_successful_title"];
    fStrikeSuccessful.fCondensed.fText = fMessages["PHRASE_CONDENSED_strike_successful_initial_announcement"];

    fStrikeUnsuccessul.fFull.fTitle = fMessages["PHRASE_strike_unsuccessful_title"];
    fStrikeUnsuccessul.fFull.fText = fMessages["PHRASE_strike_unsuccessful_initial_announcement"];
    fStrikeUnsuccessul.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_strike_unsuccessful_title"];
    fStrikeUnsuccessul.fCondensed.fText = fMessages["PHRASE_CONDENSED_strike_unsuccessful_initial_announcement"];

    fRivalArmyAway.fFull.fTitle = fMessages["PHRASE_rival_away_title"];
    fRivalArmyAway.fFull.fText = fMessages["PHRASE_rival_away_initial_announcement"];
    fRivalArmyAway.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_rival_away_title"];
    fRivalArmyAway.fCondensed.fText = fMessages["PHRASE_CONDENSED_rival_away_initial_announcement"];

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

    fPlague.fFull.fTitle = fMessages["PHRASE_plague_title"];
    fPlague.fFull.fText = fMessages["PHRASE_plague_initial_announcement"];
    fPlague.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_plague_title"];
    fPlague.fCondensed.fText = fMessages["PHRASE_CONDENSED_plague_initial_announcement"];

    fCityConqueredByPlayer.fFull.fTitle = fMessages["PHRASE_city_conquered_by_player_title"];
    fCityConqueredByPlayer.fFull.fText = fMessages["PHRASE_city_conquered_by_player_initial_announcement"];
    fCityConqueredByPlayer.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_city_conquered_by_player_title"];
    fCityConqueredByPlayer.fCondensed.fText = fMessages["PHRASE_CONDENSED_city_conquered_by_player_initial_announcement"];

    fCityConquerFailedByPlayer.fFull.fTitle = fMessages["PHRASE_players_conquest_fails_title"];
    fCityConquerFailedByPlayer.fFull.fText = fMessages["PHRASE_players_conquest_fails_initial_announcement"];
    fCityConquerFailedByPlayer.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_players_conquest_fails_title"];
    fCityConquerFailedByPlayer.fCondensed.fText = fMessages["PHRASE_CONDENSED_players_conquest_fails_initial_announcement"];

    fCityRaidFailedByPlayer.fFull.fTitle = fMessages["PHRASE_raiding_party_wiped_out_title"];
    fCityRaidFailedByPlayer.fFull.fText = fMessages["PHRASE_raiding_party_wiped_out_initial_announcement"];
    fCityRaidFailedByPlayer.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_raiding_party_wiped_out_title"];
    fCityRaidFailedByPlayer.fCondensed.fText = fMessages["PHRASE_CONDENSED_raiding_party_wiped_out_initial_announcement"];

    loadResourceGranted(fRaidGranted, "raiding_party_returns");

    fAllyAttackedByPlayer.fFull.fTitle = fMessages["PHRASE_allies_hate_you_title"];
    fAllyAttackedByPlayer.fFull.fText = fMessages["PHRASE_allies_hate_you_initial_announcement"];
    fAllyAttackedByPlayer.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_allies_hate_you_title"];
    fAllyAttackedByPlayer.fCondensed.fText = fMessages["PHRASE_CONDENSED_allies_hate_you_initial_announcement"];

    fArmyReturns.fFull.fTitle = fMessages["PHRASE_army_returns_title"];
    fArmyReturns.fFull.fText = fMessages["PHRASE_army_returns_initial_announcement"];
    fArmyReturns.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_army_returns_title"];
    fArmyReturns.fCondensed.fText = fMessages["PHRASE_CONDENSED_army_returns_initial_announcement"];

    fMilitaryBuildup.fFull.fTitle = fMessages["PHRASE_military_change_title_I"];
    fMilitaryBuildup.fFull.fText = fMessages["PHRASE_military_change_initial_announcement_I"];
    fMilitaryBuildup.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_military_change_title_I"];
    fMilitaryBuildup.fCondensed.fText = fMessages["PHRASE_CONDENSED_military_change_initial_announcement_I"];

    fMilitaryDecline.fFull.fTitle = fMessages["PHRASE_military_change_title_D"];
    fMilitaryDecline.fFull.fText = fMessages["PHRASE_military_change_initial_announcement_D"];
    fMilitaryDecline.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_military_change_title_D"];
    fMilitaryDecline.fCondensed.fText = fMessages["PHRASE_CONDENSED_military_change_initial_announcement_D"];

    fEconomicProsperity.fFull.fTitle = fMessages["PHRASE_economic_change_title_I"];
    fEconomicProsperity.fFull.fText = fMessages["PHRASE_economic_change_initial_announcement_I"];
    fEconomicProsperity.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_economic_change_title_I"];
    fEconomicProsperity.fCondensed.fText = fMessages["PHRASE_CONDENSED_economic_change_initial_announcement_I"];

    fEconomicDecline.fFull.fTitle = fMessages["PHRASE_economic_change_title_D"];
    fEconomicDecline.fFull.fText = fMessages["PHRASE_economic_change_initial_announcement_D"];
    fEconomicDecline.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_economic_change_title_D"];
    fEconomicDecline.fCondensed.fText = fMessages["PHRASE_CONDENSED_economic_change_initial_announcement_D"];

    load(fAllyTroopsRequest, "ally", "S");
    load(fVassalTroopsRequest, "vassal", "P");
    load(fColonyTroopsRequest, "colony", "P");
    load(fParentCityTroopsRequest, "parentcity", "R");

    fEarthqauke.fFull.fTitle = fMessages["PHRASE_quake_title"];
    fEarthqauke.fFull.fText = fMessages["PHRASE_quake_phrase_by_god"];
    fEarthqauke.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_quake_title"];
    fEarthqauke.fCondensed.fText = fMessages["PHRASE_CONDENSED_quake_phrase_by_god"];

    fCityBecomesAlly.fFull.fTitle = fMessages["PHRASE_becomes_ally_title"];
    fCityBecomesAlly.fFull.fText = fMessages["PHRASE_becomes_ally_initial_announcement"];
    fCityBecomesAlly.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_becomes_ally_title"];
    fCityBecomesAlly.fCondensed.fText = fMessages["PHRASE_CONDENSED_becomes_ally_initial_announcement"];

    fCityBecomesRival.fFull.fTitle = fMessages["PHRASE_becomes_rival_title"];
    fCityBecomesRival.fFull.fText = fMessages["PHRASE_becomes_rival_initial_announcement"];
    fCityBecomesRival.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_becomes_rival_title"];
    fCityBecomesRival.fCondensed.fText = fMessages["PHRASE_CONDENSED_becomes_rival_initial_announcement"];

    fCityBecomesVassal.fFull.fTitle = fMessages["PHRASE_becomes_vassal_title"];
    fCityBecomesVassal.fFull.fText = fMessages["PHRASE_becomes_vassal_initial_announcement"];
    fCityBecomesVassal.fCondensed.fTitle = fMessages["PHRASE_CONDENSED_becomes_vassal_title"];
    fCityBecomesVassal.fCondensed.fText = fMessages["PHRASE_CONDENSED_becomes_vassal_initial_announcement"];

    loadMessage(fTroopsRequestAttackAverted,
                "attack_averted_title",
                "attack_averted_initial_announcement");

    loadMessage(fColonyRestored,
                "colony_restored_title",
                "colony_restored_initial_announcement");

    loadMessage(fDebtAnniversary,
                "still_in_debt_title",
                "still_in_debt_initial_announcement");

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

const eGodMessages* eMessages::godMessages(const eGodType godType) const {
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

const eMonsterMessages* eMessages::monsterMessages(const eMonsterType monsterType) const {
    switch(monsterType) {
    case eMonsterType::calydonianBoar:
        return &fCalydonianBoar;
    case eMonsterType::cerberus:
        return &fCerberus;
    case eMonsterType::chimera:
        return &fChimera;
    case eMonsterType::cyclops:
        return &fCyclops;
    case eMonsterType::dragon:
        return &fDragon;
    case eMonsterType::echidna:
        return &fEchidna;
    case eMonsterType::harpies:
        return &fHarpies;
    case eMonsterType::hector:
        return &fHector;
    case eMonsterType::hydra:
        return &fHydra;
    case eMonsterType::kraken:
        return &fKraken;
    case eMonsterType::maenads:
        return &fMaenads;
    case eMonsterType::medusa:
        return &fMedusa;
    case eMonsterType::minotaur:
        return &fMinotaur;
    case eMonsterType::scylla:
        return &fScylla;
    case eMonsterType::sphinx:
        return &fSphinx;
    case eMonsterType::talos:
        return &fTalos;
    }
    return nullptr;
}
