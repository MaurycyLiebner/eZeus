#include "egamewidget.h"

#include "esounds.h"
#include "emessages.h"

void eGameWidget::handleEvent(const eEvent e, eTile* const tile) {
    switch(e) {
    case eEvent::fire:
        eSounds::playFireSound();
        showMessage(tile, eMessages::sInstance.fFire);
        break;
    case eEvent::collapse:
        eSounds::playCollapseSound();
        showMessage(tile, eMessages::sInstance.fCollapse);
        break;

    case eEvent::aphroditeVisit:
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::visit);
        showMessage(tile, eMessages::sInstance.fAphroditeGreetings);
        break;
    case eEvent::aphroditeInvasion:
        eSounds::playGodSound(eGodType::aphrodite, eGodSound::invade);
        break;

    case eEvent::apolloVisit:
        eSounds::playGodSound(eGodType::apollo, eGodSound::visit);
        break;
    case eEvent::apolloInvasion:
        eSounds::playGodSound(eGodType::apollo, eGodSound::invade);
        break;

    case eEvent::aresVisit:
        eSounds::playGodSound(eGodType::ares, eGodSound::visit);
        break;
    case eEvent::aresInvasion:
        eSounds::playGodSound(eGodType::ares, eGodSound::invade);
        break;

    case eEvent::artemisVisit:
        eSounds::playGodSound(eGodType::artemis, eGodSound::visit);
        showMessage(tile, eMessages::sInstance.fArtemisGreetings);
        break;
    case eEvent::artemisInvasion:
        eSounds::playGodSound(eGodType::artemis, eGodSound::invade);
        break;

    case eEvent::athenaVisit:
        eSounds::playGodSound(eGodType::athena, eGodSound::visit);
        break;
    case eEvent::athenaInvasion:
        eSounds::playGodSound(eGodType::athena, eGodSound::invade);
        break;

    case eEvent::atlasVisit:
        eSounds::playGodSound(eGodType::atlas, eGodSound::visit);
        break;
    case eEvent::atlasInvasion:
        eSounds::playGodSound(eGodType::atlas, eGodSound::invade);
        break;

    case eEvent::demeterVisit:
        eSounds::playGodSound(eGodType::demeter, eGodSound::visit);
        showMessage(tile, eMessages::sInstance.fDemeterGreetings);
        break;
    case eEvent::demeterInvasion:
        eSounds::playGodSound(eGodType::demeter, eGodSound::invade);
        break;

    case eEvent::dionysusVisit:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::visit);
        break;
    case eEvent::dionysusInvasion:
        eSounds::playGodSound(eGodType::dionysus, eGodSound::invade);
        break;

    case eEvent::hadesVisit:
        eSounds::playGodSound(eGodType::hades, eGodSound::visit);
        showMessage(tile, eMessages::sInstance.fHadesGreetings);
        break;
    case eEvent::hadesInvasion:
        eSounds::playGodSound(eGodType::hades, eGodSound::invade);
        break;

    case eEvent::hephaestusVisit:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::visit);
        break;
    case eEvent::hephaestusInvasion:
        eSounds::playGodSound(eGodType::hephaestus, eGodSound::invade);
        break;

    case eEvent::heraVisit:
        eSounds::playGodSound(eGodType::hera, eGodSound::visit);
        break;
    case eEvent::heraInvasion:
        eSounds::playGodSound(eGodType::hera, eGodSound::invade);
        break;

    case eEvent::hermesVisit:
        eSounds::playGodSound(eGodType::hermes, eGodSound::visit);
        break;
    case eEvent::hermesInvasion:
        eSounds::playGodSound(eGodType::hermes, eGodSound::invade);
        break;

    case eEvent::poseidonVisit:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::visit);
        break;
    case eEvent::poseidonInvasion:
        eSounds::playGodSound(eGodType::poseidon, eGodSound::invade);
        break;

    case eEvent::zeusVisit:
        eSounds::playGodSound(eGodType::zeus, eGodSound::visit);
        showMessage(tile, eMessages::sInstance.fZeusGreetings);
        break;
    case eEvent::zeusInvasion:
        eSounds::playGodSound(eGodType::zeus, eGodSound::invade);
        break;
    }
    mGm->pushEvent(e, tile);
}
