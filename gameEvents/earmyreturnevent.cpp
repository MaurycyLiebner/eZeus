#include "earmyreturnevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "buildings/eheroshall.h"
#include "characters/actions/eheroaction.h"
#include "characters/actions/egodworshippedaction.h"

eArmyReturnEvent::eArmyReturnEvent(
        const eGameEventBranch branch,
        eGameBoard* const board) :
    eArmyEventBase(eGameEventType::armyReturnEvent, branch, board) {}

void eArmyReturnEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city) {
    mForces = forces;
    mCity = city;
}

void eArmyReturnEvent::trigger() {
    removeArmyEvent();
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    const auto entryPoint = board->entryPoint();

    int wait = 0;
    for(const auto& s : mForces.fSoldiers) {
        s->backFromAbroad(wait);
    }

    for(const auto h : mForces.fHeroes) {
        const auto hh = board->heroHall(h);
        if(!hh) continue;
        hh->setHeroOnQuest(false);
        if(!entryPoint) continue;
        const auto hero = hh->spawnHero();
        const auto a = hero->action();
        const auto ha = dynamic_cast<eHeroAction*>(a);
        if(!ha) continue;
        hero->changeTile(entryPoint);
        ha->goBackToHall();
    }

    for(const auto& a : mForces.fAllies) {
        a->setAbroad(false);
    }

    if(mForces.fAres) {
        const auto as = board->sanctuary(eGodType::ares);
        if(as) {
            as->godComeback();
            if(entryPoint) {
                const auto god = as->spawnGod();
                if(god) {
                    const auto ga = e::make_shared<eGodWorshippedAction>(god);
                    god->setAction(ga);
                    god->changeTile(entryPoint);
                    ga->goBackToSanctuary();
                }
            }
        }
    }

    eEventData ed;
    ed.fTile = entryPoint;
    ed.fCity = mCity;
    board->event(eEvent::armyReturns, ed);
}

std::string eArmyReturnEvent::longName() const {
    return eLanguage::text("army_returns_event_long_name");
}

stdsptr<eGameEvent> eArmyReturnEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eArmyReturnEvent>(branch(), gameBoard());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->setReason(reason);
    return c;
}
