#include "esettlerspawner.h"

#include "characters/esettler.h"
#include "characters/actions/esettleraction.h"

eSettlerSpawner::eSettlerSpawner(eTile* const tile, eGameBoard& board) :
    eSpawner(tile, __INT_MAX__, 500, board) {

}

void eSettlerSpawner::spawn(eTile* const tile) {
    const auto& popData = board().populationData();
    const int v = popData.vacancies();
    if(mPop >= v) return;
    mPop += 8;
    const auto b = new eSettler(board());
    b->setTile(tile);
    tile->addCharacter(b);
    b->setActionType(eCharacterActionType::walk);
    const auto fa = [this, b]() {
        mPop -= 8;
        delete b;
    };
    b->setAction(new eSettlerAction(b, fa, fa));
}
