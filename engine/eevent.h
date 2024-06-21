#ifndef EEVENT_H
#define EEVENT_H

enum class eEvent {
    fire,
    collapse,

    godVisit,
    godInvasion,
    godHelp,
    godQuest,
    godQuestFulfilled,
    godMonsterUnleash,

    sanctuaryComplete,

    heroArrival,

    monsterInvasion36,
    monsterInvasion24,
    monsterInvasion12,
    monsterInvasion6,
    monsterInvasion1,
    monsterInvasion,
    monsterSlain,

    invasion36,
    invasion24,
    invasion12,
    invasion6,
    invasion1,
    invasion,
    invasionDefeat,
    invasionVictoryMonn,
    invasionVictory,
    invasionBribed,

    tributePaid,
    tributeAccepted,
    tributeDeclined,
    tributePostponed,

    requestGranted,
    requestPartialSpace,
    requestInsufficientSpace,
    requestLastChance,
    requestAccepted,
    requestPostponed,
    requestRefused,
    requestForfeited,

    demandRefused,

    giftReceivedDrachmas,
    giftReceivedNeeded,
    giftReceivedSells,
    giftReceivedNotNeeded,
    giftReceivedRefuse,

    generalRequestAllyInitial,
    generalRequestAllyReminder,
    generalRequestAllyOverdue,
    generalRequestAllyWarning,
    generalRequestAllyComply,
    generalRequestAllyTooLate,
    generalRequestAllyRefuse,

    generalRequestRivalInitial,
    generalRequestRivalReminder,
    generalRequestRivalOverdue,
    generalRequestRivalWarning,
    generalRequestRivalComply,
    generalRequestRivalTooLate,
    generalRequestRivalRefuse,

    generalRequestSubjectInitial,
    generalRequestSubjectReminder,
    generalRequestSubjectOverdue,
    generalRequestSubjectWarning,
    generalRequestSubjectComply,
    generalRequestSubjectTooLate,
    generalRequestSubjectRefuse,

    generalRequestParentInitial,
    generalRequestParentReminder,
    generalRequestParentOverdue,
    generalRequestParentWarning,
    generalRequestParentComply,
    generalRequestParentTooLate,
    generalRequestParentRefuse,

    giftGranted,
    giftCashGranted,
    giftPartialSpace,
    giftInsufficientSpace,
    giftLastChance,
    giftForfeited,
    giftAccepted,
    giftCashAccepted,
    giftPostponed,
    giftRefused,

    unemployment,
    employees,

    plague,

    cityConquered,
    cityConquerFailed,

    raidGranted,
    raidCashGranted,
    raidPartialSpace,
    raidInsufficientSpace,
    raidLastChance,
    raidForfeited,
    raidAccepted,
    raidCashAccepted,
    raidPostponed,
    raidRefused,

    allyAttackedByPlayer,

    cityRaidFailed,
    armyReturns,

    militaryBuildup,
    militaryDecline,
    economicProsperity,
    economicDecline,

    troopsRequestVassalInitial,
    troopsRequestVassalFirstReminder,
    troopsRequestVassalLastReminder,
    troopsRequestVassalConquered,

    troopsRequestColonyInitial,
    troopsRequestColonyFirstReminder,
    troopsRequestColonyLastReminder,
    troopsRequestColonyConquered,

    troopsRequestParentCityInitial,
    troopsRequestParentCityFirstReminder,
    troopsRequestParentCityLastReminder,
    troopsRequestParentCityConquered,

    troopsRequestAllyInitial,
    troopsRequestAllyFirstReminder,
    troopsRequestAllyLastReminder,
    troopsRequestAllyConquered,

    troopsRequestAttackAverted
};

#endif // EEVENT_H
