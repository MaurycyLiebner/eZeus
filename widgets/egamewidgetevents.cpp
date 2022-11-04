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
        showMessage(tile, msgs.fWooing0);
    } else if(lm == 1) {
        eSounds::playGodSound(god, eGodSound::jealousy1);
        showMessage(tile, msgs.fJealousy1);
    } else if(lm == 2) {
        eSounds::playGodSound(god, eGodSound::jealousy2);
        showMessage(tile, msgs.fJealousy2);
    }
}

void eGameWidget::handleEvent(const eEvent e, eTile* const tile) {
    switch(e) {
    case eEvent::fire:
        eSounds::playFireSound();
        showMessage(tile, eMessages::instance.fFire);
        break;
    case eEvent::collapse:
        eSounds::playCollapseSound();
        showMessage(tile, eMessages::instance.fCollapse);
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
        eSounds::playGodSound(eGodType::artemis, eGodSound::monster);
        showMessage(tile, eMessages::instance.fArtemis.fMonster);
        break;
    case eEvent::cerberusInvasion:
        eSounds::playGodSound(eGodType::hades, eGodSound::monster);
        showMessage(tile, eMessages::instance.fHades.fMonster);
        break;
    case eEvent::chimeraInvasion:
        eSounds::playGodSound(eGodType::atlas, eGodSound::monster);
        showMessage(tile, eMessages::instance.fAtlas.fMonster);
        break;
    case eEvent::cyclopsInvasion:
        eSounds::playGodSound(eGodType::zeus, eGodSound::monster);
        showMessage(tile, eMessages::instance.fZeus.fMonster);
        break;
    case eEvent::dragonInvasion:
        eSounds::playGodSound(eGodType::ares, eGodSound::monster);
        showMessage(tile, eMessages::instance.fAres.fMonster);
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
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::monster);
        showMessage(tile, eMessages::instance.fAphrodite.fMonster);
        break;
    case eEvent::hydraInvasion:
        eSounds::playGodSound(eGodType::athena, eGodSound::monster);
        showMessage(tile, eMessages::instance.fAthena.fMonster);
        break;
    case eEvent::krakenInvasion:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::monster);
        showMessage(tile, eMessages::instance.fPoseidon.fMonster);
        break;
    case eEvent::maenadsInvasion:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::monster);
        showMessage(tile, eMessages::instance.fDionysus.fMonster);
        break;
    case eEvent::medusaInvasion:
        eSounds::playGodSound(eGodType::demeter, eGodSound::monster);
        showMessage(tile, eMessages::instance.fDemeter.fMonster);
        break;
    case eEvent::minotaurInvasion:
        eSounds::playGodSound(eGodType::hermes, eGodSound::monster);
        showMessage(tile, eMessages::instance.fHermes.fMonster);
        break;
    case eEvent::scyllaInvasion:
        eSounds::playGodSound(eGodType::apollo, eGodSound::monster);
        showMessage(tile, eMessages::instance.fApollo.fMonster);
        break;
    case eEvent::sphinxInvasion:
        eSounds::playGodSound(eGodType::hera, eGodSound::monster);
        showMessage(tile, eMessages::instance.fHera.fMonster);
        break;
    case eEvent::talosInvasion:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::monster);
        showMessage(tile, eMessages::instance.fHephaestus.fMonster);
        break;

    case eEvent::achillesArrival:
        eSounds::playHeroSound(eHeroType::achilles, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fAchilles.fArrival);
        break;
    case eEvent::atalantaArrival:
        eSounds::playHeroSound(eHeroType::atalanta, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fAtalanta.fArrival);
        break;
    case eEvent::bellerophonArrival:
        eSounds::playHeroSound(eHeroType::bellerophon, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fBellerophon.fArrival);
        break;
    case eEvent::herculesArrival:
        eSounds::playHeroSound(eHeroType::hercules, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fHercules.fArrival);
        break;
    case eEvent::jasonArrival:
        eSounds::playHeroSound(eHeroType::jason, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fJason.fArrival);
        break;
    case eEvent::odysseusArrival:
        eSounds::playHeroSound(eHeroType::odysseus, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fOdysseus.fArrival);
        break;
    case eEvent::perseusArrival:
        eSounds::playHeroSound(eHeroType::perseus, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fPerseus.fArrival);
        break;
    case eEvent::theseusArrival:
        eSounds::playHeroSound(eHeroType::theseus, eHeroSound::arrived);
        showMessage(tile, eMessages::instance.fTheseus.fArrival);
        break;
    }
    mGm->pushEvent(e, tile);
}
