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
            int string = -1;
            eBannerType bt;
            if(gt == eGodType::artemis) {
                bt = eBannerType::amazon;
                string = 30 + id;
            } else if(gt == eGodType::ares) {
                bt = eBannerType::aresWarrior;
                string = 32 + id;
            } else {
                return;
            }
            const auto name = eLanguage::zeusText(138, string);
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

void eSanctuaryWithWarriors::read(eReadStream& src) {
    eSanctuary::read(src);

    auto& board = getBoard();
    int nb;
    src >> nb;
    for(int i = 0; i < nb; i++) {
        src.readSoldierBanner(&board, [this, i](const stdsptr<eSoldierBanner>& b) {
            const auto gt = godType();
            int string = -1;
            if(gt == eGodType::artemis) {
                string = 30 + i;
            } else if(gt == eGodType::ares) {
                string = 32 + i;
            } else {
                return;
            }
            const auto name = eLanguage::zeusText(138, string);
            b->setName(name);
            mSoldierBanners.push_back(b);
        });
    }
}

void eSanctuaryWithWarriors::write(eWriteStream& dst) const {
    eSanctuary::write(dst);

    dst << mSoldierBanners.size();
    for(const auto& b: mSoldierBanners) {
        dst.writeSoldierBanner(b.get());
    }
}
