#include "egamewidget.h"

#include "audio/esounds.h"
#include "emessages.h"

void eGameWidget::handleGodVisitEvent(eGodMessages& msgs,
                                      const eGodType god,
                                      eEventData& ed) {
    int& lm = msgs.fLastMessage;
    lm = lm > 2 ? 0 : (lm + 1);
    if(lm == 0) {
        eSounds::playGodSound(god, eGodSound::wooing0);
        showMessage(ed, msgs.fWooing0);
    } else if(lm == 1) {
        eSounds::playGodSound(god, eGodSound::jealousy1);
        showMessage(ed, msgs.fJealousy1);
    } else if(lm == 2) {
        eSounds::playGodSound(god, eGodSound::jealousy2);
        showMessage(ed, msgs.fJealousy2);
    }
}

void eGameWidget::handleMonsterInvasionEvent(eGodMessages& msgs,
                                             const eGodType god,
                                             eEventData& ed) {
    eSounds::playGodSound(god, eGodSound::monster);
    showMessage(ed, msgs.fMonster);
}

void eGameWidget::handleHeroArrivalEvent(eHeroMessages& msgs,
                                         const eHeroType hero,
                                         eEventData& ed) {
    eSounds::playHeroSound(hero, eHeroSound::arrived);
    showMessage(ed, msgs.fArrival);
}

void eGameWidget::handleEvent(const eEvent e, eEventData& ed) {
    auto& inst = eMessages::instance;
    switch(e) {
    case eEvent::fire: {
        eSounds::playFireSound();
        showMessage(ed, inst.fFire);
    } break;
    case eEvent::collapse: {
        eSounds::playCollapseSound();
        showMessage(ed, inst.fCollapse);
    } break;

    case eEvent::aphroditeVisit:
        handleGodVisitEvent(inst.fAphrodite,
                            eGodType::aphrodite, ed);
        break;
    case eEvent::aphroditeInvasion:
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::invade);
        break;

    case eEvent::apolloVisit:
        handleGodVisitEvent(inst.fApollo,
                            eGodType::apollo, ed);
        break;
    case eEvent::apolloInvasion:
        eSounds::playGodSound(eGodType::apollo, eGodSound::invade);
        break;

    case eEvent::aresVisit:
        handleGodVisitEvent(inst.fAres,
                            eGodType::ares, ed);
        break;
    case eEvent::aresInvasion:
        eSounds::playGodSound(eGodType::ares, eGodSound::invade);
        break;

    case eEvent::artemisVisit:
        handleGodVisitEvent(inst.fArtemis,
                            eGodType::artemis, ed);
        break;
    case eEvent::artemisInvasion:
        eSounds::playGodSound(eGodType::artemis, eGodSound::invade);
        break;

    case eEvent::athenaVisit:
        handleGodVisitEvent(inst.fAthena,
                            eGodType::athena, ed);
        break;
    case eEvent::athenaInvasion:
        eSounds::playGodSound(eGodType::athena, eGodSound::invade);
        break;

    case eEvent::atlasVisit:
        handleGodVisitEvent(inst.fAtlas,
                            eGodType::atlas, ed);
        break;
    case eEvent::atlasInvasion:
        eSounds::playGodSound(eGodType::atlas, eGodSound::invade);
        break;

    case eEvent::demeterVisit:
        handleGodVisitEvent(inst.fDemeter,
                            eGodType::demeter, ed);
        break;
    case eEvent::demeterInvasion:
        eSounds::playGodSound(eGodType::demeter, eGodSound::invade);
        break;

    case eEvent::dionysusVisit:
        handleGodVisitEvent(inst.fDionysus,
                            eGodType::dionysus, ed);
        break;
    case eEvent::dionysusInvasion:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::invade);
        break;

    case eEvent::hadesVisit:
        handleGodVisitEvent(inst.fHades,
                            eGodType::hades, ed);
        break;
    case eEvent::hadesInvasion:
        eSounds::playGodSound(eGodType::hades, eGodSound::invade);
        break;

    case eEvent::hephaestusVisit:
        handleGodVisitEvent(inst.fHephaestus,
                            eGodType::hephaestus, ed);
        break;
    case eEvent::hephaestusInvasion:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::invade);
        break;

    case eEvent::heraVisit:
        handleGodVisitEvent(inst.fHera,
                            eGodType::hera, ed);
        break;
    case eEvent::heraInvasion:
        eSounds::playGodSound(eGodType::hera, eGodSound::invade);
        break;

    case eEvent::hermesVisit:
        handleGodVisitEvent(inst.fHermes,
                            eGodType::hermes, ed);
        break;
    case eEvent::hermesInvasion:
        eSounds::playGodSound(eGodType::hermes, eGodSound::invade);
        break;

    case eEvent::poseidonVisit:
        handleGodVisitEvent(inst.fPoseidon,
                            eGodType::poseidon, ed);
        break;
    case eEvent::poseidonInvasion:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::invade);
        break;

    case eEvent::zeusVisit:
        handleGodVisitEvent(inst.fZeus,
                            eGodType::zeus, ed);
        break;
    case eEvent::zeusInvasion:
        eSounds::playGodSound(eGodType::zeus, eGodSound::invade);
        break;

    case eEvent::calydonianBoarInvasion:
        handleMonsterInvasionEvent(inst.fArtemis,
                                   eGodType::artemis, ed);
        break;
    case eEvent::cerberusInvasion:
        handleMonsterInvasionEvent(inst.fHades,
                                   eGodType::hades, ed);
        break;
    case eEvent::chimeraInvasion:
        handleMonsterInvasionEvent(inst.fAtlas,
                                   eGodType::atlas, ed);
        break;
    case eEvent::cyclopsInvasion:
        handleMonsterInvasionEvent(inst.fZeus,
                                   eGodType::zeus, ed);
        break;
    case eEvent::dragonInvasion:
        handleMonsterInvasionEvent(inst.fAres,
                                   eGodType::ares, ed);
        break;
    case eEvent::echidnaInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(ed, inst.fArtemis.fMonster);
        break;
    case eEvent::harpiesInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(ed, inst.fArtemis.fMonster);
        break;
    case eEvent::hectorInvasion:
        handleMonsterInvasionEvent(inst.fAphrodite,
                                   eGodType::aphrodite, ed);
        break;
    case eEvent::hydraInvasion:
        handleMonsterInvasionEvent(inst.fAthena,
                                   eGodType::athena, ed);
        break;
    case eEvent::krakenInvasion:
        handleMonsterInvasionEvent(inst.fPoseidon,
                                   eGodType::poseidon, ed);
        break;
    case eEvent::maenadsInvasion:
        handleMonsterInvasionEvent(inst.fDionysus,
                                   eGodType::dionysus, ed);
        break;
    case eEvent::medusaInvasion:
        handleMonsterInvasionEvent(inst.fDemeter,
                                   eGodType::demeter, ed);
        break;
    case eEvent::minotaurInvasion:
        handleMonsterInvasionEvent(inst.fHermes,
                                   eGodType::hermes, ed);
        break;
    case eEvent::scyllaInvasion:
        handleMonsterInvasionEvent(inst.fApollo,
                                   eGodType::apollo, ed);
        break;
    case eEvent::sphinxInvasion:
        handleMonsterInvasionEvent(inst.fHera,
                                   eGodType::hera, ed);
        break;
    case eEvent::talosInvasion:
        handleMonsterInvasionEvent(inst.fHephaestus,
                                   eGodType::hephaestus, ed);
        break;

    case eEvent::achillesArrival:
        handleHeroArrivalEvent(inst.fAchilles,
                               eHeroType::achilles, ed);
        break;
    case eEvent::atalantaArrival:
        handleHeroArrivalEvent(inst.fAtalanta,
                               eHeroType::atalanta, ed);
        break;
    case eEvent::bellerophonArrival:
        handleHeroArrivalEvent(inst.fBellerophon,
                               eHeroType::bellerophon, ed);
        break;
    case eEvent::herculesArrival:
        handleHeroArrivalEvent(inst.fHercules,
                               eHeroType::hercules, ed);
        break;
    case eEvent::jasonArrival:
        handleHeroArrivalEvent(inst.fJason,
                               eHeroType::jason, ed);
        break;
    case eEvent::odysseusArrival:
        handleHeroArrivalEvent(inst.fOdysseus,
                               eHeroType::odysseus, ed);
        break;
    case eEvent::perseusArrival:
        handleHeroArrivalEvent(inst.fPerseus,
                               eHeroType::perseus, ed);
        break;
    case eEvent::theseusArrival:
        handleHeroArrivalEvent(inst.fTheseus,
                               eHeroType::theseus, ed);
        break;

    case eEvent::invasion: {
        showMessage(ed, inst.fInvasion);
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
    case eEvent::generalRequestInitial: {
        showMessage(ed, inst.fGeneralRequestInitialS, true);
        return;
    } break;
    case eEvent::generalRequestReminder: {
        showMessage(ed, inst.fGeneralRequestReminderS, true);
        return;
    } break;
    case eEvent::generalRequestOverdue: {
        showMessage(ed, inst.fGeneralRequestOverdueS, true);
        return;
    } break;
    case eEvent::generalRequestWarning: {
        showMessage(ed, inst.fGeneralRequestWarningS, true);
        return;
    } break;
    case eEvent::generalRequestComply: {
        const auto m = eMessages::favorMessage(
                    inst.fGeneralRequestComplyS);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestTooLate: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestTooLateS);
        showMessage(ed, m, true);
        return;
    } break;
    case eEvent::generalRequestRefuse: {
        const auto m = eMessages::dfavorMessage(
                    inst.fGeneralRequestRefuseS);
        showMessage(ed, m, true);
        return;
    } break;
    }
    mGm->pushEvent(e, ed.fTile);
}
