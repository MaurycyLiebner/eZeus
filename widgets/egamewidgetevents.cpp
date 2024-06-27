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

void eGameWidget::handleMonsterUnleashEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(ed.fGod);
    if(!gm) return;
    eSounds::playGodSound(ed.fGod, eGodSound::monster);
    showMessage(ed, gm->fMonster, true);
}

void eGameWidget::handleMonsterInvasion36Event(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    eMessageType msg = gm->fInvasion36;
    std::string reason = ed.fReason;
    if(reason.empty()) {
        reason = gm->fMonsterAttackReason;
    }
    eStringHelpers::replace(msg.fFull.fText, "[reason_phrase]", reason);
    eStringHelpers::replace(msg.fFull.fText, "[time_until_attack]", "36");
    eStringHelpers::replace(msg.fCondensed.fText, "[time_until_attack]", "36");
    showMessage(ed, msg);
}

void eGameWidget::handleMonsterInvasion24Event(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fInvasion24);
}

void eGameWidget::handleMonsterInvasion12Event(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fInvasion12);
}

void eGameWidget::handleMonsterInvasion6Event(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fInvasion6);
}

void eGameWidget::handleMonsterInvasion1Event(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fInvasion1);
}

void eGameWidget::handleMonsterInvasionEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fInvasion, true);
}

void eGameWidget::handleMonsterSlainEvent(eEventData& ed) {
    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(ed.fMonster);
    if(!gm) return;
    showMessage(ed, gm->fSlain);
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
        handleMonsterUnleashEvent(ed);
        break;

    case eEvent::monsterInvasion36:
        handleMonsterInvasion36Event(ed);
        return;
    case eEvent::monsterInvasion24:
        handleMonsterInvasion24Event(ed);
        return;
    case eEvent::monsterInvasion12:
        handleMonsterInvasion12Event(ed);
        return;
    case eEvent::monsterInvasion6:
        handleMonsterInvasion6Event(ed);
        return;
    case eEvent::monsterInvasion1:
        handleMonsterInvasion1Event(ed);
        return;
    case eEvent::monsterInvasion:
        handleMonsterInvasionEvent(ed);
        break;
    case eEvent::monsterSlain:
        handleMonsterSlainEvent(ed);
        return;

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
    case eEvent::invasionVictoryMonn: {
        showMessage(ed, inst.fInvasionVictoryMonument);
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
        showMessage(ed, inst.fGiftGranted.fGranted);
        return;
    } break;
    case eEvent::giftPartialSpace: {
        showMessage(ed, inst.fGiftGranted.fPartialSpace);
        return;
    } break;
    case eEvent::giftInsufficientSpace: {
        showMessage(ed, inst.fGiftGranted.fInsufficientSpace);
        return;
    } break;
    case eEvent::giftLastChance: {
        showMessage(ed, inst.fGiftGranted.fLastChance);
        return;
    } break;
    case eEvent::giftAccepted: {
        showMessage(ed, inst.fGiftGranted.fAccepted, true);
        return;
    } break;
    case eEvent::giftPostponed: {
        showMessage(ed, inst.fGiftGranted.fPostponed, true);
        return;
    } break;
    case eEvent::giftRefused: {
        showMessage(ed, inst.fGiftGranted.fRefused, true);
        return;
    } break;
    case eEvent::giftForfeited: {
        showMessage(ed, inst.fGiftGranted.fForfeited, true);
        return;
    } break;
    case eEvent::giftCashGranted: {
        showMessage(ed, inst.fGiftGranted.fCashGranted, true);
        return;
    } break;
    case eEvent::giftCashAccepted: {
        showMessage(ed, inst.fGiftGranted.fCashAccepted, true);
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

    case eEvent::cityConquered: {
        showMessage(ed, inst.fCityConqueredByPlayer, true);
        return;
    } break;
    case eEvent::cityConquerFailed: {
        showMessage(ed, inst.fCityConquerFailedByPlayer, true);
        return;
    } break;


    case eEvent::raidGranted: {
        showMessage(ed, inst.fRaidGranted.fGranted);
        return;
    } break;
    case eEvent::raidPartialSpace: {
        showMessage(ed, inst.fRaidGranted.fPartialSpace);
        return;
    } break;
    case eEvent::raidInsufficientSpace: {
        showMessage(ed, inst.fRaidGranted.fInsufficientSpace);
        return;
    } break;
    case eEvent::raidLastChance: {
        showMessage(ed, inst.fRaidGranted.fLastChance);
        return;
    } break;
    case eEvent::raidAccepted: {
        showMessage(ed, inst.fRaidGranted.fAccepted, true);
        return;
    } break;
    case eEvent::raidPostponed: {
        showMessage(ed, inst.fRaidGranted.fPostponed, true);
        return;
    } break;
    case eEvent::raidRefused: {
        showMessage(ed, inst.fRaidGranted.fRefused, true);
        return;
    } break;
    case eEvent::raidForfeited: {
        showMessage(ed, inst.fRaidGranted.fForfeited, true);
        return;
    } break;
    case eEvent::raidCashGranted: {
        showMessage(ed, inst.fRaidGranted.fCashGranted, true);
        return;
    } break;
    case eEvent::raidCashAccepted: {
        showMessage(ed, inst.fRaidGranted.fCashAccepted, true);
        return;
    } break;

    case eEvent::cityRaidFailed: {
        showMessage(ed, inst.fCityRaidFailedByPlayer, true);
        return;
    } break;

    case eEvent::allyAttackedByPlayer: {
        showMessage(ed, inst.fAllyAttackedByPlayer, true);
        return;
    } break;

    case eEvent::armyReturns: {
        showMessage(ed, inst.fArmyReturns, true);
    } break;

    case eEvent::militaryBuildup: {
        showMessage(ed, inst.fMilitaryBuildup, true);
        return;
    } break;
    case eEvent::militaryDecline: {
        showMessage(ed, inst.fMilitaryDecline, true);
        return;
    } break;
    case eEvent::economicProsperity: {
        showMessage(ed, inst.fEconomicProsperity, true);
        return;
    } break;
    case eEvent::economicDecline: {
        showMessage(ed, inst.fEconomicDecline, true);
        return;
    } break;

    case eEvent::troopsRequestVassalInitial: {
        showMessage(ed, inst.fVassalTroopsRequest.fInitialAnnouncement, true);
        return;
    } break;
    case eEvent::troopsRequestColonyInitial: {
        showMessage(ed, inst.fColonyTroopsRequest.fInitialAnnouncement, true);
        return;
    } break;
    case eEvent::troopsRequestParentCityInitial: {
        showMessage(ed, inst.fParentCityTroopsRequest.fInitialAnnouncement, true);
        return;
    } break;
    case eEvent::troopsRequestAllyInitial: {
        showMessage(ed, inst.fAllyTroopsRequest.fInitialAnnouncement, true);
        return;
    } break;

    case eEvent::troopsRequestVassalFirstReminder: {
        showMessage(ed, inst.fVassalTroopsRequest.fFirstReminder, true);
        return;
    } break;
    case eEvent::troopsRequestColonyFirstReminder: {
        showMessage(ed, inst.fColonyTroopsRequest.fFirstReminder, true);
        return;
    } break;
    case eEvent::troopsRequestParentCityFirstReminder: {
        showMessage(ed, inst.fParentCityTroopsRequest.fFirstReminder, true);
        return;
    } break;
    case eEvent::troopsRequestAllyFirstReminder: {
        showMessage(ed, inst.fAllyTroopsRequest.fFirstReminder, true);
        return;
    } break;

    case eEvent::troopsRequestVassalLastReminder: {
        showMessage(ed, inst.fVassalTroopsRequest.fLastReminder, true);
        return;
    } break;
    case eEvent::troopsRequestColonyLastReminder: {
        showMessage(ed, inst.fColonyTroopsRequest.fLastReminder, true);
        return;
    } break;
    case eEvent::troopsRequestParentCityLastReminder: {
        showMessage(ed, inst.fParentCityTroopsRequest.fLastReminder, true);
        return;
    } break;
    case eEvent::troopsRequestAllyLastReminder: {
        showMessage(ed, inst.fAllyTroopsRequest.fLastReminder, true);
        return;
    } break;

    case eEvent::troopsRequestVassalConquered: {
        showMessage(ed, inst.fVassalTroopsRequest.fConquered, true);
        return;
    } break;
    case eEvent::troopsRequestColonyConquered: {
        showMessage(ed, inst.fColonyTroopsRequest.fConquered, true);
        return;
    } break;
    case eEvent::troopsRequestParentCityConquered: {
        showMessage(ed, inst.fParentCityTroopsRequest.fConquered, true);
        return;
    } break;
    case eEvent::troopsRequestAllyConquered: {
        showMessage(ed, inst.fAllyTroopsRequest.fConquered, true);
        return;
    } break;

    case eEvent::troopsRequestAttackAverted: {
        showMessage(ed, inst.fTroopsRequestAttackAverted, true);
        return;
    } break;

    case eEvent::godDisaster: {
        const auto msgs = inst.godMessages(ed.fGod);
        showMessage(ed, msgs->fDisaster);
        return;
    } break;
    case eEvent::godDisasterEnds: {
        const auto msgs = inst.godMessages(ed.fGod);
        showMessage(ed, msgs->fDisasterEnds);
        return;
    } break;
    case eEvent::godTradeResumes: {
        if(ed.fGod == eGodType::zeus) {
            showMessage(ed, inst.fZeusTradeResumes);
        } else if(ed.fGod == eGodType::poseidon) {
            showMessage(ed, inst.fPoseidonTradeResumes);
        } else if(ed.fGod == eGodType::hermes) {
            showMessage(ed, inst.fHermesTradeResumes);
        }
        return;
    } break;
    case eEvent::aidArrives: {
        showMessage(ed, inst.fSupportTroopsArrive);
    } break;
    case eEvent::aidDeparts: {
        showMessage(ed, inst.fSupportTroopsDepart);
        return;
    } break;
    case eEvent::aidDefeated: {
        showMessage(ed, inst.fSupportTroopsDefeated);
        return;
    } break;
    }
    mGm->pushEvent(e, ed);
}
