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
    mTile->setBanner(this);
}

eBanner::~eBanner() {
    mBoard.unregisterBanner(this);
    if(mTile) mTile->setBanner(nullptr);
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
    switch(type) {
    case eBannerTypeS::boar:
        return new eBoarSpawner(id, tile, board);
    case eBannerTypeS::deer:
        return new eDeerSpawner(id, tile, board);
    case eBannerTypeS::landInvasion:
        return new eLandInvasionPoint(id, tile, board);
    case eBannerTypeS::entryPoint:
        return new eEntryPoint(id, tile, board);
    case eBannerTypeS::exitPoint:
        return new eExitPoint(id, tile, board);
    }
    return nullptr;
}
