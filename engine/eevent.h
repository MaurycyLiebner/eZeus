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

    invasion36,
    invasion24,
    invasion12,
    invasion6,
    invasion1,
    invasion,
    invasionDefeat,
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

    plague
};

#endif // EEVENT_H
