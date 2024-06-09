#include "ebanner.h"

#include "engine/egameboard.h"

#include "eboarspawner.h"
#include "edeerspawner.h"
#include "elandinvasionpoint.h"
#include "eentrypoint.h"
#include "eexitpoint.h"

eBanner::eBanner(const eBannerTypeS type,
                 const int id,
                 eTile* const tile,
                 eGameBoard& board) :
    mType(type), mId(id), mTile(tile), mBoard(board) {
    board.registerBanner(this);
}

eBanner::~eBanner() {
    mBoard.unregisterBanner(this);
}

void eBanner::read(eReadStream& src) {
    src >> mIOID;
}

void eBanner::write(eWriteStream& dst) const {
    dst << mIOID;
}

eBanner* eBanner::sCreate(const int id,
                          eTile* const tile,
                          eGameBoard& board,
                          const eBannerTypeS type) {
    stdsptr<eBanner> b;
    switch(type) {
    case eBannerTypeS::boar:
        b = std::make_shared<eBoarSpawner>(id, tile, board);
    case eBannerTypeS::deer:
        b = std::make_shared<eDeerSpawner>(id, tile, board);
    case eBannerTypeS::landInvasion:
        b = std::make_shared<eLandInvasionPoint>(id, tile, board);
    case eBannerTypeS::entryPoint:
        b = std::make_shared<eEntryPoint>(id, tile, board);
    case eBannerTypeS::exitPoint:
        b = std::make_shared<eExitPoint>(id, tile, board);
    }
    tile->setBanner(b);
    return nullptr;
}
