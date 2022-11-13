#include "epeddler.h"

#include "buildings/eagorabase.h"

ePeddler::ePeddler(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fPeddler,
                   eCharacterType::peddler) {
    setProvide(eProvide::peddler, 10000);
}

void ePeddler::provideToBuilding(eBuilding* const b) {
    if(!mAgora) return;
    mAgora->agoraProvide(b);
}

void ePeddler::setAgora(eAgoraBase* const a) {
    mAgora = a;
}
