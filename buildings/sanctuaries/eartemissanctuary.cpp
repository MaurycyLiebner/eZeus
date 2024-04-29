#include "eartemissanctuary.h"

#include "engine/egameboard.h"

eArtemisSanctuary::eArtemisSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuaryWithWarriors(board, eBuildingType::templeArtemis,
                           sw, sh, 60) {}

eAresSanctuary::eAresSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuaryWithWarriors(board, eBuildingType::templeAres,
                           sw, sh, 60) {}

void eSanctuaryWithWarriors::timeChanged(const int by) {
    if(finished()) {
        while(mSoldierBanners.size() < 2) {
            auto& board = getBoard();
            const auto gt = godType();
            eBannerType bt;
            if(gt == eGodType::artemis) {
                bt = eBannerType::amazon;
            } else if(gt == eGodType::ares) {
                bt = eBannerType::aresWarrior;
            } else {
                return;
            }
            const auto b = e::make_shared<eSoldierBanner>(bt, board);
            mSoldierBanners.push_back(b);
            b->setPlayerId(1);
            board.registerSoldierBanner(b);
            b->moveToDefault();
        }
        mSoldierSpawn += by;
        const int ssr = 20000;
        if(mSoldierSpawn > ssr) {
            mSoldierSpawn -= ssr;
            for(const auto& b : mSoldierBanners) {
                const int count = b->count();
                if(count >= 8) continue;
                b->incCount();
                break;
            }
        }
    }
    eSanctuary::timeChanged(by);
}
