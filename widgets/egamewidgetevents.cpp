#include "egamewidget.h"

#include "audio/esounds.h"
#include "emessages.h"

void eGameWidget::handleGodVisitEvent(eGodMessages& msgs,
                                      const eGodType god,
                                      eTile* const tile) {
    int& lm = msgs.fLastMessage;
    lm = lm > 2 ? 0 : (lm + 1);
    if(lm == 0) {
        eSounds::playGodSound(god, eGodSound::wooing0);
        showMessage(eMessageEventType::common, tile, msgs.fWooing0);
    } else if(lm == 1) {
        eSounds::playGodSound(god, eGodSound::jealousy1);
        showMessage(eMessageEventType::common, tile, msgs.fJealousy1);
    } else if(lm == 2) {
        eSounds::playGodSound(god, eGodSound::jealousy2);
        showMessage(eMessageEventType::common, tile, msgs.fJealousy2);
    }
}

void eGameWidget::handleMonsterInvasionEvent(eGodMessages& msgs,
                                             const eGodType god,
                                             eTile* const tile) {
    eSounds::playGodSound(god, eGodSound::monster);
    showMessage(eMessageEventType::common, tile, msgs.fMonster);
}

void eGameWidget::handleHeroArrivalEvent(eHeroMessages& msgs,
                                         const eHeroType hero,
                                         eTile* const tile) {
    eSounds::playHeroSound(hero, eHeroSound::arrived);
    showMessage(eMessageEventType::common, tile, msgs.fArrival);
}

void eGameWidget::handleEvent(const eEvent e, eTile* const tile,
                              eWorldCity* const city,
                              const int bribe) {
    switch(e) {
    case eEvent::fire:
        eSounds::playFireSound();
        showMessage(eMessageEventType::common, tile,
                    eMessages::instance.fFire);
        break;
    case eEvent::collapse:
        eSounds::playCollapseSound();
        showMessage(eMessageEventType::common, tile,
                    eMessages::instance.fCollapse);
        break;

    case eEvent::aphroditeVisit:
        handleGodVisitEvent(eMessages::instance.fAphrodite,
                            eGodType::aphrodite, tile);
        break;
    case eEvent::aphroditeInvasion:
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::invade);
        break;

    case eEvent::apolloVisit:
        handleGodVisitEvent(eMessages::instance.fApollo,
                            eGodType::apollo, tile);
        break;
    case eEvent::apolloInvasion:
        eSounds::playGodSound(eGodType::apollo, eGodSound::invade);
        break;

    case eEvent::aresVisit:
        handleGodVisitEvent(eMessages::instance.fAres,
                            eGodType::ares, tile);
        break;
    case eEvent::aresInvasion:
        eSounds::playGodSound(eGodType::ares, eGodSound::invade);
        break;

    case eEvent::artemisVisit:
        handleGodVisitEvent(eMessages::instance.fArtemis,
                            eGodType::artemis, tile);
        break;
    case eEvent::artemisInvasion:
        eSounds::playGodSound(eGodType::artemis, eGodSound::invade);
        break;

    case eEvent::athenaVisit:
        handleGodVisitEvent(eMessages::instance.fAthena,
                            eGodType::athena, tile);
        break;
    case eEvent::athenaInvasion:
        eSounds::playGodSound(eGodType::athena, eGodSound::invade);
        break;

    case eEvent::atlasVisit:
        handleGodVisitEvent(eMessages::instance.fAtlas,
                            eGodType::atlas, tile);
        break;
    case eEvent::atlasInvasion:
        eSounds::playGodSound(eGodType::atlas, eGodSound::invade);
        break;

    case eEvent::demeterVisit:
        handleGodVisitEvent(eMessages::instance.fDemeter,
                            eGodType::demeter, tile);
        break;
    case eEvent::demeterInvasion:
        eSounds::playGodSound(eGodType::demeter, eGodSound::invade);
        break;

    case eEvent::dionysusVisit:
        handleGodVisitEvent(eMessages::instance.fDionysus,
                            eGodType::dionysus, tile);
        break;
    case eEvent::dionysusInvasion:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::invade);
        break;

    case eEvent::hadesVisit:
        handleGodVisitEvent(eMessages::instance.fHades,
                            eGodType::hades, tile);
        break;
    case eEvent::hadesInvasion:
        eSounds::playGodSound(eGodType::hades, eGodSound::invade);
        break;

    case eEvent::hephaestusVisit:
        handleGodVisitEvent(eMessages::instance.fHephaestus,
                            eGodType::hephaestus, tile);
        break;
    case eEvent::hephaestusInvasion:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::invade);
        break;

    case eEvent::heraVisit:
        handleGodVisitEvent(eMessages::instance.fHera,
                            eGodType::hera, tile);
        break;
    case eEvent::heraInvasion:
        eSounds::playGodSound(eGodType::hera, eGodSound::invade);
        break;

    case eEvent::hermesVisit:
        handleGodVisitEvent(eMessages::instance.fHermes,
                            eGodType::hermes, tile);
        break;
    case eEvent::hermesInvasion:
        eSounds::playGodSound(eGodType::hermes, eGodSound::invade);
        break;

    case eEvent::poseidonVisit:
        handleGodVisitEvent(eMessages::instance.fPoseidon,
                            eGodType::poseidon, tile);
        break;
    case eEvent::poseidonInvasion:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::invade);
        break;

    case eEvent::zeusVisit:
        handleGodVisitEvent(eMessages::instance.fZeus,
                            eGodType::zeus, tile);
        break;
    case eEvent::zeusInvasion:
        eSounds::playGodSound(eGodType::zeus, eGodSound::invade);
        break;

    case eEvent::calydonianBoarInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fArtemis,
                                   eGodType::artemis, tile);
        break;
    case eEvent::cerberusInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHades,
                                   eGodType::hades, tile);
        break;
    case eEvent::chimeraInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAtlas,
                                   eGodType::atlas, tile);
        break;
    case eEvent::cyclopsInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fZeus,
                                   eGodType::zeus, tile);
        break;
    case eEvent::dragonInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAres,
                                   eGodType::ares, tile);
        break;
    case eEvent::echidnaInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(tile, eMessages::instance.fArtemis.fMonster);
        break;
    case eEvent::harpiesInvasion:
//        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
//        showMessage(tile, eMessages::instance.fArtemis.fMonster);
        break;
    case eEvent::hectorInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAphrodite,
                                   eGodType::aphrodite, tile);
        break;
    case eEvent::hydraInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fAthena,
                                   eGodType::athena, tile);
        break;
    case eEvent::krakenInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fPoseidon,
                                   eGodType::poseidon, tile);
        break;
    case eEvent::maenadsInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fDionysus,
                                   eGodType::dionysus, tile);
        break;
    case eEvent::medusaInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fDemeter,
                                   eGodType::demeter, tile);
        break;
    case eEvent::minotaurInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHermes,
                                   eGodType::hermes, tile);
        break;
    case eEvent::scyllaInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fApollo,
                                   eGodType::apollo, tile);
        break;
    case eEvent::sphinxInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHera,
                                   eGodType::hera, tile);
        break;
    case eEvent::talosInvasion:
        handleMonsterInvasionEvent(eMessages::instance.fHephaestus,
                                   eGodType::hephaestus, tile);
        break;

    case eEvent::achillesArrival:
        handleHeroArrivalEvent(eMessages::instance.fAchilles,
                               eHeroType::achilles, tile);
        break;
    case eEvent::atalantaArrival:
        handleHeroArrivalEvent(eMessages::instance.fAtalanta,
                               eHeroType::atalanta, tile);
        break;
    case eEvent::bellerophonArrival:
        handleHeroArrivalEvent(eMessages::instance.fBellerophon,
                               eHeroType::bellerophon, tile);
        break;
    case eEvent::herculesArrival:
        handleHeroArrivalEvent(eMessages::instance.fHercules,
                               eHeroType::hercules, tile);
        break;
    case eEvent::jasonArrival:
        handleHeroArrivalEvent(eMessages::instance.fJason,
                               eHeroType::jason, tile);
        break;
    case eEvent::odysseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fOdysseus,
                               eHeroType::odysseus, tile);
        break;
    case eEvent::perseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fPerseus,
                               eHeroType::perseus, tile);
        break;
    case eEvent::theseusArrival:
        handleHeroArrivalEvent(eMessages::instance.fTheseus,
                               eHeroType::theseus, tile);
        break;

    case eEvent::invasion:
        showMessage(eMessageEventType::invasion,
                    tile, eMessages::instance.fInvasion,
                    city, bribe);
        break;
    }
    mGm->pushEvent(e, tile);
}
