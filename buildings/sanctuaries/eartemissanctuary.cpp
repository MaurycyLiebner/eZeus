#include "eartemissanctuary.h"

#include "engine/egameboard.h"
#include "elanguage.h"

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
        int id = 0;
        while(mSoldierBanners.size() < 2) {
            auto& board = getBoard();
            const auto gt = godType();
            std::string namet;
            eBannerType bt;
            if(gt == eGodType::artemis) {
                bt = eBannerType::amazon;
                namet = "amazon_banner_name_";
            } else if(gt == eGodType::ares) {
                bt = eBannerType::aresWarrior;
                namet = "ares_warrior_banner_name_";
            } else {
                return;
            }
            namet = namet + std::to_string(id);
            const auto name = eLanguage::text(namet);
            const auto b = e::make_shared<eSoldierBanner>(bt, board);
            for(int i = 0; i < 8; i++) {
                b->incCount();
            }
            b->setName(name);
            mSoldierBanners.push_back(b);
            b->setPlayerId(1);
            board.registerSoldierBanner(b);
            b->moveToDefault();
            id++;
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
