#include "erequestaidevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eRequestAidEvent::eRequestAidEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::requestAid, branch) {}

void eRequestAidEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;

   const auto date = board->date();

    if(mEnd) {
        const auto ma = board->militaryAid(mCity);
        if(ma->allDead()) {
            board->event(eEvent::aidDefeated, ed);
        } else {
            const auto& ivhs = board->invasionHandlers();
            const auto& ivs = board->invasions();
            const bool needed = !ivhs.empty() || !ivs.empty();
            const int days = date - mArrivalDate;
            if(!needed || (ivhs.empty() && days > 600)) {
                if(ma) {
                    ma->goBack();
                    const int t = mCity->troops();
                    mCity->setTroops(t + ma->count());
                    board->removeMilitaryAid(mCity);
                }
                board->event(eEvent::aidDeparts, ed);
            }
        }
        return;
    } else {
        const int t = mCity->troops();
        const int arrived = t/3;
        mCity->setTroops(t - arrived);

        mArrivalDate = date;
        const auto entryPoint = board->entryPoint();
        if(!entryPoint) return;

        const auto ma = std::make_shared<eMilitaryAid>();
        ma->fCity = mCity;
        ed.fTile = entryPoint;

        int rem = arrived;
        int nHorsemen = 0;
        if(arrived >= 28) {
            nHorsemen = (arrived - 12)/4;
        }
        rem -= nHorsemen;
        const int nRabble = rem/2;
        rem -= nRabble;
        const int nHoplites = rem;

        int remRabble = nRabble;
        while(remRabble > 0) {
            const auto b = e::make_shared<eSoldierBanner>(
                               eBannerType::rockThrower, *board);
            b->setMilitaryAid(true);
            b->backFromHome();
            for(int i = 0; i < 8 && i < remRabble; i++) {
                b->createSoldier(entryPoint);
                b->incCount();
            }
            ma->fSoldiers.push_back(b);
            remRabble -= b->count();
        }

        int remHoplites = nHoplites;
        while(remHoplites > 0) {
            const auto b = e::make_shared<eSoldierBanner>(
                               eBannerType::hoplite, *board);
            b->setMilitaryAid(true);
            b->backFromHome();
            for(int i = 0; i < 8 && i < remHoplites; i++) {
                b->createSoldier(entryPoint);
                b->incCount();
            }
            ma->fSoldiers.push_back(b);
            remHoplites -= b->count();
        }

        int remHorsemen = nHorsemen;
        while(remHorsemen > 0) {
            const auto b = e::make_shared<eSoldierBanner>(
                               eBannerType::horseman, *board);
            b->setMilitaryAid(true);
            b->backFromHome();
            for(int i = 0; i < 8 && i < remHorsemen; i++) {
                b->createSoldier(entryPoint);
                b->incCount();
            }
            ma->fSoldiers.push_back(b);
            remHorsemen -= b->count();
        }

        std::vector<eSoldierBanner*> banners;
        for(const auto& b : ma->fSoldiers) {
            banners.push_back(b.get());
        }

        const int ctx = entryPoint->x();
        const int cty = entryPoint->y();
        eSoldierBanner::sPlace(banners, ctx, cty, *board, 3, 3);
        board->addMilitaryAid(ma);
    }

    const auto e = e::make_shared<eRequestAidEvent>(
                       eGameEventBranch::child);
    e->setCity(mCity);
    e->setEnd(true);
    e->setArrivalDate(mArrivalDate);
    e->initializeDate(date + 150);
    addConsequence(e);
    board->event(eEvent::aidArrives, ed);
}

std::string eRequestAidEvent::longName() const {
    return eLanguage::text("request_aid_long_name");
}

void eRequestAidEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());
    mArrivalDate.write(dst);
    dst << mEnd;
}

void eRequestAidEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    mArrivalDate.read(src);
    src >> mEnd;
}
