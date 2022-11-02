#include "epeddler.h"

#include "buildings/eagorabase.h"

ePeddler::ePeddler(eGameBoard& board, eAgoraBase* const agora) :
    eBasicPatroler(board, &eCharacterTextures::fPeddler,
                   eCharacterType::peddler),
    mAgora(agora) {
    setProvide(eProvide::peddler, 10000);
}

void ePeddler::provideToBuilding(eBuilding* const b) {
    if(!mAgora) return;
    mAgora->agoraProvide(b);
}
