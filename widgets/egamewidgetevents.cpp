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
    switch(e) {
    case eEvent::fire: {
        eSounds::playFireSound();
        showMessage(ed, eMessages::instance.fFire);
    } break;
    case eEvent::collapse: {
        eSounds::playCollapseSound();
        showMessage(ed, eMessages::instance.fCollapse);
    } break;

    case eEvent::aphroditeVisit:
        handleGodVisitEvent(eMessages::instance.fAphrodite,
                            eGodType::aphrodite, ed);
        break;
    case eEvent::aphroditeInvasion:
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::invade);
        break;

    case eEvent::apolloVisit:
        handleGodVisitEvent(eMessages::instance.fApollo,
                            eGodType::apollo, ed);
        break;
    case eEvent::apolloInvasion:
        eSounds::playGodSound(eGodType::apollo, eGodSound::invade);
        break;

    case eEvent::aresVisit:
        handleGodVisitEvent(eMessages::instance.fAres,
                            eGodType::ares, ed);
        break;
    case eEvent::aresInvasion:
        eSounds::playGodSound(eGodType::ares, eGodSound::invade);
        break;

    case eEvent::artemisVisit:
        handleGodVisitEvent(eMessages::instance.fArtemis,
                            eGodType::artemis, ed);
        break;
    case eEvent::artemisInvasion:
        eSounds::playGodSound(eGodType::artemis, eGodSound::invade);
        break;

    case eEvent::athenaVisit:
        handleGodVisitEvent(eMessages::instance.fAthena,
                            eGodType::athena, ed);
        break;
    case eEvent::athenaInvasion:
        eSounds::playGodSound(eGodType::athena, eGodSound::invade);
        break;

    case eEvent::atlasVisit:
        handleGodVisitEvent(eMessages::instance.fAtlas,
                            eGodType::atlas, ed);
        break;
    case eEvent::atlasInvasion:
        eSounds::playGodSound(eGodType::atlas, eGodSound::invade);
        break;

    case eEvent::demeterVisit:
        handleGodVisitEvent(eMessages::instance.fDemeter,
                            eGodType::demeter, ed);
        break;
    case eEvent::demeterInvasion:
        eSounds::playGodSound(eGodType::demeter, eGodSound::invade);
        break;

    case eEvent::dionysusVisit:
        handleGodVisitEvent(eMessages::instance.fDionysus,
                            eGodType::dionysus, ed);
        break;
    case eEvent::dionysusInvasion:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::invade);
        break;

    case eEvent::hadesVisit:
        handleGodVisitEvent(eMessages::instance.fHades,
                            eGodType::hades, ed);
        break;
    case eEvent::hadesInvasion:
        eSounds::playGodSound(eGodType::hades, eGodSound::invade);
        break;

    case eEvent::hephaestusVisit:
        handleGodVisitEvent(eMessages::instance.fHephaestus,
                            eGodType::hephaestus, ed);
        break;
    case eEvent::hephaestusInvasion:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::invade);
        break;

    case eEvent::heraVisit:
        handleGodVisitEvent(eMessages::instance.fHera,
                            eGodType::hera, ed);
        break;
    case eEvent::heraInvasion:
        eSounds::playGodSound(eGodType::hera, eGodSound::invade);
        break;

    case eEvent::hermesVisit:
        handleGodVisitEvent(eMessages::instance.fHermes,
                            eGodType::hermes, ed);
        break;
    case eEvent::hermesInvasion:
        eSounds::playGodSound(eGodType::hermes, eGodSound::invade);
        break;

    case eEvent::poseidonVisit:
        handleGodVisitEvent(eMessages::instance.fPoseidon,
                            eGodType::poseidon, ed);
        break;
    case eEvent::poseidonInvasion:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::invade);
        break;

    case eEvent::zeusVisit:
        handleGodVisitEvent(eMessages::instance.fZeus,
                            eGodType::zeus, ed);
        break;
    case eEvent::zeusInvasion:
        eSounds::playGodSound(eGodType::zeus, eGodSound::invade);
        break;

    case eEvent::calydonianBoarInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fArtemis,
                                   eGodType::artemis, ed);
        break;
    case eEvent::cerberusInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHades,
                                   eGodType::hades, ed);
        break;
    case eEvent::chimeraInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAtlas,
                                   eGodType::atlas, ed);
        break;
    case eEvent::cyclopsInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fZeus,
                                   eGodType::zeus, ed);
        break;
    case eEvent::dragonInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAres,
                                   eGodType::ares, ed);
        break;
    case eEvent::echidnaInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(ed, eMessages::instance.fArtemis.fMonster);
        break;
    case eEvent::harpiesInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(ed, eMessages::instance.fArtemis.fMonster);
        break;
    case eEvent::hectorInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAphrodite,
                                   eGodType::aphrodite, ed);
        break;
    case eEvent::hydraInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAthena,
                                   eGodType::athena, ed);
        break;
    case eEvent::krakenInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fPoseidon,
                                   eGodType::poseidon, ed);
        break;
    case eEvent::maenadsInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fDionysus,
                                   eGodType::dionysus, ed);
        break;
    case eEvent::medusaInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fDemeter,
                                   eGodType::demeter, ed);
        break;
    case eEvent::minotaurInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHermes,
                                   eGodType::hermes, ed);
        break;
    case eEvent::scyllaInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fApollo,
                                   eGodType::apollo, ed);
        break;
    case eEvent::sphinxInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHera,
                                   eGodType::hera, ed);
        break;
    case eEvent::talosInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHephaestus,
                                   eGodType::hephaestus, ed);
        break;

    case eEvent::achillesArrival:
        handleHeroArrivalEvent(eMessages::instance.fAchilles,
                               eHeroType::achilles, ed);
        break;
    case eEvent::atalantaArrival:
        handleHeroArrivalEvent(eMessages::instance.fAtalanta,
                               eHeroType::atalanta, ed);
        break;
    case eEvent::bellerophonArrival:
        handleHeroArrivalEvent(eMessages::instance.fBellerophon,
                               eHeroType::bellerophon, ed);
        break;
    case eEvent::herculesArrival:
        handleHeroArrivalEvent(eMessages::instance.fHercules,
                               eHeroType::hercules, ed);
        break;
    case eEvent::jasonArrival:
        handleHeroArrivalEvent(eMessages::instance.fJason,
                               eHeroType::jason, ed);
        break;
    case eEvent::odysseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fOdysseus,
                               eHeroType::odysseus, ed);
        break;
    case eEvent::perseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fPerseus,
                               eHeroType::perseus, ed);
        break;
    case eEvent::theseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fTheseus,
                               eHeroType::theseus, ed);
        break;

    case eEvent::invasion: {
        showMessage(ed, eMessages::instance.fInvasion);
    } break;
    }
    mGm->pushEvent(e, ed.fTile);
}
