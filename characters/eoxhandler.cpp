#include "eoxhandler.h"

#include "characters/actions/efollowaction.h"
#include "etrailer.h"
#include "eox.h"

eOxHandler::eOxHandler(eGameBoard& board) :
    eTransporterBase(board, &eCharacterTextures::fOxHandler,
                     eCharacterType::oxHandler) {}

eOxTransporter eOxHandler::sCreate(
        eGameBoard& board, eTile* const t) {
    const auto h = e::make_shared<eOxHandler>(board);
    h->changeTile(t);
    const auto ox = e::make_shared<eOx>(board);
    const auto aox = e::make_shared<eFollowAction>(
                       h.get(), ox.get(),
                       []() {}, []() {});
    ox->setAction(aox);
    ox->changeTile(t);
    const auto tr = e::make_shared<eTrailer>(h.get(), board);
    const auto atr = e::make_shared<eFollowAction>(
                       ox.get(), tr.get(),
                       []() {}, []() {});
    tr->setAction(atr);
    tr->changeTile(t);

    return {h, ox, tr};
}
