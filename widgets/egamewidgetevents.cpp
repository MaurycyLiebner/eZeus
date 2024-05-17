#include "egamewidget.h"

#include "audio/esounds.h"
#include "emessages.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "engine/egameboard.h"

void eGameWidget::handleGodQuestEvent(eEventData& ed,
                                      const bool fulfilled) {
    const auto hero = ed.fHero;
    const auto id = ed.fQuestId;
    const auto god = ed.fGod;
    if(fulfilled) {
        eSounds::playGodSound(god, eGodSound::questFinished);
    } else {
        eSounds::playGodSound(god, eGodSound::quest);
    }
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(god);
    if(!gm) return;
    const eQuestMessages* qm = nullptr;
    switch(id) {
    case eGodQuestId::godQuest1:
        qm = &gm->fQuest1;
        break;
    case eGodQuestId::godQuest2:
        qm = &gm->fQuest2;
        break;
    }
    const eEventMessageType* emt = nullptr;
    if(fulfilled) {
        emt = &qm->fFulfilled;
    } else {
        emt = &qm->fQuest;
    }
    auto msg = emt->fFull;
    const auto hm = eHero::sHeroName(hero);
    eStringHelpers::replaceAll(msg.fTitle, "[hero_needed]", hm);
    eStringHelpers::replaceAll(msg.fText, "[hero_needed]", hm);
    showMessage(ed, msg);
}

void eGameWidget::handleGodVisitEvent(const eGodType god) {
    const auto& inst = eMessages::instance;
    const auto msgs = inst.godMessages(god);
    int& lm = msgs->fLastMessage;
    lm = lm > 2 ? 0 : (lm + 1);
    eEventData ed;
    if(lm == 0) {
        eSounds::playGodSound(god, eGodSound::wooing0);
        showMessage(ed, msgs->fWooing0);
    } else if(lm == 1) {
        eSounds::playGodSound(god, eGodSound::jealousy1);
        showMessage(ed, msgs->fJealousy1);
    } else if(lm == 2) {
        eSounds::playGodSound(god, eGodSound::jealousy2);
        showMessage(ed, msgs->fJealousy2);
    }
}

void eGameWidget::handleGodInvasionEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto msgs = inst.godMessages(ed.fGod);
    showMessage(ed, msgs->fInvades);
    eSounds::playGodSound(ed.fGod, eGodSound::invade);
}

void eGameWidget::handleGodHelpEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto msgs = inst.godMessages(ed.fGod);
    showMessage(ed, msgs->fHelps);
    eSounds::playGodSound(ed.fGod, eGodSound::help);
}

void eGameWidget::handleSanctuaryComplete(const eGodType god) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(god);
    if(!gm) return;
    eEventData ed;
    showMessage(ed, gm->fSanctuaryComplete);
}

void eGameWidget::handleMonsterInvasionEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(ed.fGod);
    if(!gm) return;
    eSounds::playGodSound(ed.fGod, eGodSound::monster);
    showMessage(ed, gm->fMonster);
}

void eGameWidget::handleHeroArrivalEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.heroMessages(ed.fHero);
    if(!gm) return;
    eSounds::playHeroSound(ed.fHero, eHeroSound::arrived);
    showMessage(ed, gm->fArrival);
}

void eGameWidget::handleEvent(const eEvent e, eEventData& ed) {
    const auto& inst = eMessages::instance;
    switch(e) {
    case eEvent::fire: {
        eSounds::playFireSound();
        showMessage(ed, inst.fFire);
    } break;
    case eEvent::collapse: {
        eSounds::playCollapseSound();
        showMessage(ed, inst.fCollapse);
    } break;

    case eEvent::godVisit:
        handleGodVisitEvent(ed.fGod);
        break;
    case eEvent::godInvasion:
        handleGodInvasionEvent(ed);
        break;
    case eEvent::godHelp:
        handleGodHelpEvent(ed);
        break;

    case eEvent::godMonsterUnleash:
        handleMonsterInvasionEvent(ed);
        break;

    case eEvent::godQuest:
    case eEvent::godQuestFulfilled: {
        handleGodQuestEvent(ed, e == eEvent::godQuestFulfilled);
        return;
    } break;
    case eEvent::sanctuaryComplete: {
        handleSanctuaryComplete(ed.fGod);
        return;
    } break;

    case eEvent::heroArrival:
        handleHeroArrivalEvent(ed);
        break;

    case eEvent::invasion36: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion36, ed.fReason, 36));
    } break;
    case eEvent::invasion24: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion24, ed.fReason, 24));
    } break;
    case eEvent::invasion12: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion12, ed.fReason, 12));
    } break;
    case eEvent::invasion6: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion6, ed.fReason, 6));
    } break;
    case eEvent::invasion1: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion1, ed.fReason, 1));
    } break;
    case eEvent::invasion: {
        showMessage(ed, eMessages::invasionMessage(inst.fInvasion, ed.fReason, 0));
    } break;
    case eEvent::invasionBribed: {
        showMessage(ed, inst.fInvasionBribed);
        return;
    } break;
    case eEvent::invasionDefeat: {
        showMessage(ed, inst.fInvasionDefeat);
        return;
    } break;
    case eEvent::invasionVictory: {
        showMessage(ed, inst.fInvasionVictory);
        return;
    } break;
    case eEvent::tributePaid: {
        showMessage(ed, inst.fTributePaidGranted);
        return;
    } break;
    case eEvent::tributeAccepted: {
        showMessage(ed, inst.fTributePaidAccepted, true);
        return;
    } break;
    case eEvent::tributeDeclined: {
        showMessage(ed, inst.fTributePaidRefused, true);
        return;
    } break;
    case eEvent::tributePostponed: {
        showMessage(ed, inst.fTributePostponed, true);
        return;
    } break;
    case eEvent::requestGranted: {
        showMessage(ed, inst.fRequestGranted);
        return;
    } break;
    case eEvent::requestPartialSpace: {
        showMessage(ed, inst.fRequestPartialSpace);
        return;
    } break;
    case eEvent::requestInsufficientSpace: {
        showMessage(ed, inst.fRequestInsufficientSpace);
        return;
    } break;
    case eEvent::requestLastChance: {
        showMessage(ed, inst.fRequestLastChance);
        return;
    } break;
    case eEvent::requestAccepted: {
        showMessage(ed, inst.fRequestAccepted, true);
        return;
    } break;
    case eEvent::requestPostponed: {
        showMessage(ed, inst.fRequestPostponed, true);
        return;
    } break;
    case eEvent::requestRefused: {
        showMessage(ed, inst.fRequestRefused, true);
        return;
    } break;
    case eEvent::requestForfeited: {
        showMessage(ed, inst.fRequestForfeited, true);
        return;
    } break;
    case eEvent::giftGranted: {
        showMessage(ed, inst.fGiftGranted);
        return;
    } break;
    case eEvent::giftPartialSpace: {
        showMessage(ed, inst.fGiftPartialSpace);
        return;
    } break;
    case eEvent::giftInsufficientSpace: {
        showMessage(ed, inst.fGiftInsufficientSpace);
        return;
    } break;
    case eEvent::giftLastChance: {
        showMessage(ed, inst.fGiftLastChance);
        return;
    } break;
    case eEvent::giftAccepted: {
        showMessage(ed, inst.fGiftAccepted, true);
        return;
    } break;
    case eEvent::giftPostponed: {
        showMessage(ed, inst.fGiftPostponed, true);
        return;
    } break;
    case eEvent::giftRefused: {
        showMessage(ed, inst.fGiftRefused, true);
        return;
    } break;
    case eEvent::giftForfeited: {
        showMessage(ed, inst.fGiftForfeited, true);
        return;
    } break;
    case eEvent::giftCashGranted: {
        showMessage(ed, inst.fGiftCashGranted, true);
        return;
    } break;
    case eEvent::giftCashAccepted: {
        showMessage(ed, inst.fGiftCashAccepted, true);
        return;
    } break;
    case eEvent::demandRefused: {
        showMessage(ed, inst.fDemandRefused, true);
        return;
    } break;
    case eEvent::giftReceivedDrachmas: {
        showMessage(ed, inst.fGiftReceivedDrachmas, true);
        return;
    } break;
    case eEvent::giftReceivedNeeded: {
        showMessage(ed, inst.fGiftReceivedNeeded, true);
        return;
    } break;
    case eEvent::giftReceivedSells: {
        showMessage(ed, inst.fGiftReceivedSells, true);
        return;
    } break;
    case eEvent::giftReceivedNotNeeded: {
        showMessage(ed, inst.fGiftReceivedNotNeeded, true);
        return;
    } break;
    case eEvent::giftReceivedRefuse: {
        showMessage(ed, inst.fGiftReceivedRefuse, true);
        return;
    } break;

    case eEvent::generalRequestAllyInitial: {
        showMessage(ed, inst.fGeneralRequestAllyS.fInitial, true);
        return;
    } break;
    case eEvent::generalRequestAllyReminder: {
        showMessage(ed, inst.fGeneralRequestAllyS.fReminder, true);
        return;
    } break;
    case eEvent::generalRequestAllyOverdue: {
        showMessage(ed, inst.fGeneralRequestAllyS.fOverdue, true);
        return;
    } break;
    case eEvent::generalRequestAllyWarning: {
        showMessage(ed, inst.fGeneralRequestAllyS.fWarning, true);
        return;
    } break;
    case eEvent::generalRequestAllyComply: {
        const auto m = eMessages::favorMessage(
                    inst.fGeneralRequestAllyS.fComply);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestAllyTooLate: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestAllyS.fTooLate);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestAllyRefuse: {
        const auto m = eMessages::dfavorMessage(
                           inst.fGeneralRequestAllyS.fRefuse);
        showMessage(ed, m, true);
        return;
    } break;

    case eEvent::generalRequestRivalInitial: {
        showMessage(ed, inst.fGeneralRequestRivalD.fInitial, true);
        return;
    } break;
    case eEvent::generalRequestRivalReminder: {
        showMessage(ed, inst.fGeneralRequestRivalD.fReminder, true);
        return;
    } break;
    case eEvent::generalRequestRivalOverdue: {
        showMessage(ed, inst.fGeneralRequestRivalD.fOverdue, true);
        return;
    } break;
    case eEvent::generalRequestRivalWarning: {
        showMessage(ed, inst.fGeneralRequestRivalD.fWarning, true);
        return;
    } break;
    case eEvent::generalRequestRivalComply: {
        const auto m = eMessages::favorMessage(
                    inst.fGeneralRequestRivalD.fComply);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestRivalTooLate: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestRivalD.fTooLate);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestRivalRefuse: {
        const auto m = eMessages::dfavorMessage(
                           inst.fGeneralRequestRivalD.fRefuse);
        showMessage(ed, m, true);
        return;
    } break;

    case eEvent::generalRequestSubjectInitial: {
        showMessage(ed, inst.fGeneralRequestSubjectP.fInitial, true);
        return;
    } break;
    case eEvent::generalRequestSubjectReminder: {
        showMessage(ed, inst.fGeneralRequestSubjectP.fReminder, true);
        return;
    } break;
    case eEvent::generalRequestSubjectOverdue: {
        showMessage(ed, inst.fGeneralRequestSubjectP.fOverdue, true);
        return;
    } break;
    case eEvent::generalRequestSubjectWarning: {
        showMessage(ed, inst.fGeneralRequestSubjectP.fWarning, true);
        return;
    } break;
    case eEvent::generalRequestSubjectComply: {
        const auto m = eMessages::favorMessage(
                    inst.fGeneralRequestSubjectP.fComply);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestSubjectTooLate: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestSubjectP.fTooLate);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestSubjectRefuse: {
        const auto m = eMessages::dfavorMessage(
                           inst.fGeneralRequestSubjectP.fRefuse);
        showMessage(ed, m, true);
        return;
    } break;

    case eEvent::generalRequestParentInitial: {
        showMessage(ed, inst.fGeneralRequestParentR.fInitial, true);
        return;
    } break;
    case eEvent::generalRequestParentReminder: {
        showMessage(ed, inst.fGeneralRequestParentR.fReminder, true);
        return;
    } break;
    case eEvent::generalRequestParentOverdue: {
        showMessage(ed, inst.fGeneralRequestParentR.fOverdue, true);
        return;
    } break;
    case eEvent::generalRequestParentWarning: {
        showMessage(ed, inst.fGeneralRequestParentR.fWarning, true);
        return;
    } break;
    case eEvent::generalRequestParentComply: {
        const auto m = eMessages::favorMessage(
                    inst.fGeneralRequestParentR.fComply);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestParentTooLate: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestParentR.fTooLate);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestParentRefuse: {
        const auto m = eMessages::dfavorMessage(
                           inst.fGeneralRequestParentR.fRefuse);
        showMessage(ed, m, true);
        return;
    } break;

    case eEvent::unemployment: {
        showMessage(ed, inst.fUnemployment, true);
        return;
    } break;
    case eEvent::employees: {
        showMessage(ed, inst.fEmployees, true);
        return;
    } break;
    case eEvent::plague: {
        showMessage(ed, inst.fPlague, true);
    } break;
    }
    mGm->pushEvent(e, ed.fTile);
}
