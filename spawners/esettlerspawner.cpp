#include "esettlerspawner.h"

#include "engine/egameboard.h"
#include "characters/esettler.h"
#include "characters/actions/esettleraction.h"

eSettlerSpawner::eSettlerSpawner(
        const int id,
        eTile* const tile,
        eGameBoard& board) :
    eSpawner(eBannerTypeS::settler, id, tile,
             __INT_MAX__, 500, board) {}

void eSettlerSpawner::incTime(const int by) {
    auto& board = eSettlerSpawner::board();
    const int pop = board.popularity();
    setSpawnPeriod(500*(115 - pop)/15);
    eSpawner::incTime(by);
}

void eSettlerSpawner::spawn(eTile* const tile) {
    auto& board = eSettlerSpawner::board();
    const int pop = board.popularity();
    if(pop < 50) {
        const auto& husbData = board.husbandryData();
        const int food = husbData.storedFood();
        if(food < 1) return;
    }
    auto& popData = board.populationData();
    const int v = popData.vacancies();
    const int s = popData.settlers();
    if(s >= v) return;
    popData.incSettlers(8);
    const auto b = e::make_shared<eSettler>(board);
    b->setVisible(false);
    b->changeTile(tile);
    const auto fa = std::make_shared<eSS_spawnFinish>(board);
    const auto a = e::make_shared<eSettlerAction>(b.get());
    a->setFailAction(fa);
    a->setFinishAction(fa);
    a->setDeleteFailAction(fa);
    b->setAction(a);
}

void eSS_spawnFinish::call() {
    auto& popData = board().populationData();
    popData.incSettlers(-8);
}
