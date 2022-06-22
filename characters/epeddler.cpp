#include "epeddler.h"

#include "buildings/eagorabase.h"

ePeddler::ePeddler(eGameBoard& board, eAgoraBase* const agora) :
    eBasicPatroler(board, &eCharacterTextures::fPeddler,
                   eCharacterType::peddler),
    mAgora(agora) {}

void ePeddler::provideToBuilding(eBuilding* const b) {
    if(!mAgora) return;
    mAgora->provide(b);
}
