#include "eentrypoint.h"

#include "engine/egameboard.h"
#include "characters/esettler.h"
#include "characters/actions/esettleraction.h"

eEntryPoint::eEntryPoint(const int id,
                         eTile* const tile,
                         eGameBoard& board) :
    eSpawner(eBannerTypeS::entryPoint, id, tile,
             __INT_MAX__, 500, board) {}

void eEntryPoint::incTime(const int by) {
    auto& board = eEntryPoint::board();
    const int pop = board.popularity();
    setSpawnPeriod(500*(115 - pop)/15);
    eSpawner::incTime(by);
}

void eEntryPoint::spawn(eTile* const tile) {
    auto& board = eEntryPoint::board();
    const auto& ivs = board.invasionHandlers();
    if(!ivs.empty()) return;
    const auto limit = board.immigrationLimit();
    if(limit != eImmigrationLimitedBy::none &&
       limit != eImmigrationLimitedBy::lackOfVacancies) {
        return;
    }
    auto& popData = board.populationData();
    const int v = popData.vacancies();
    const int s = popData.settlers();
    if(s >= v) return;
    const auto b = e::make_shared<eSettler>(board);
    b->setVisible(false);
    b->changeTile(tile);
    const auto a = e::make_shared<eSettlerAction>(b.get());
    a->setNumberPeople(std::min(8, v - s));
    b->setAction(a);
}

void eSS_spawnFinish::call() {}
