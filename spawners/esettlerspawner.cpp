#include "esettlerspawner.h"

#include "characters/esettler.h"
#include "characters/actions/esettleraction.h"

eSettlerSpawner::eSettlerSpawner(eTile* const tile, eGameBoard& board) :
    eSpawner(tile, __INT_MAX__, 500, board) {

}

void eSettlerSpawner::spawn(eTile* const tile) {
    auto& popData = board().populationData();
    const int v = popData.vacancies();
    const int s = popData.settlers();
    if(s >= v) return;
    popData.incSettlers(8);
    const auto b = e::make_shared<eSettler>(board());
    b->changeTile(tile);
    const auto fa = [this]() {
        auto& popData = board().populationData();
        popData.incSettlers(-8);
    };
    b->setAction(e::make_shared<eSettlerAction>(b.get(), fa, fa));
}
