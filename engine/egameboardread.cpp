#include "egameboard.h"

#include "spawners/ebanner.h"
#include "fileIO/ebuildingreader.h"
#include "einvasionhandler.h"
#include "missiles/emissile.h"
#include "gameEvents/egameevent.h"
#include "gameEvents/ereceiverequestevent.h"
#include "gameEvents/etroopsrequestevent.h"
#include "eplague.h"

void eGameBoard::read(eReadStream& src) {
    int w;
    src >> w;
    int h;
    src >> h;
    initialize(w, h);

    src >> mPoseidonMode;

    src >> mEpisodeLost;

    src >> mImmigrationLimit;
    src >> mNoFood;
    mNoFoodSince.read(src);
    mInDebtSince.read(src);

    src >> mDrachmas;
    src >> mDifficulty;
    src >> mWageRate;
    src >> mWageMultiplier;
    src >> mTaxRate;
    src >> mTaxesPaidLastYear;
    src >> mTaxesPaidThisYear;
    src >> mPeoplePaidTaxesLastYear;
    src >> mPeoplePaidTaxesThisYear;

    for(auto& p : mPrices) {
        src >> p.second;
    }

    mDate.read(src);
    src >> mFrame;
    src >> mTime;
    src >> mTotalTime;

    mEmplDistributor.read(src);

    int ns;
    src >> ns;
    for(int i = 0; i < ns; i++) {
        eResourceType type;
        src >> type;
        mShutDown.push_back(type);
    }

    src >> mManTowers;

    src >> mShutdownLandTrade;
    src >> mShutdownSeaTrade;

    src >> mSoldiersUpdate;
    src >> mMaxRabble;
    src >> mMaxHoplites;
    src >> mMaxHorsemen;

    src >> mCoverageUpdate;
    src >> mAthleticsCoverage;
    src >> mPhilosophyCoverage;
    src >> mDramaCoverage;
    src >> mAllDiscCoverage;
    src >> mTaxesCoverage;
    src >> mUnrest;
    src >> mPopularity;
    src >> mHealth;
    src >> mExcessiveMilitaryServiceCount;
    src >> mMonthsOfMilitaryService;

    src >> mWonGames;

    mUpdateAppeal = true;

    for(const auto& ts : mTiles) {
        for(const auto& t : ts) {
            t->read(src);
            bool hasB;
            src >> hasB;
            if(!hasB) continue;
            eBannerTypeS type;
            src >> type;
            int id;
            src >> id;
            const auto b = eBanner::sCreate(id, t, *this, type);
            b->read(src);
        }
    }

    {
        int nq;
        src >> nq;
        for(int i = 0; i < nq; i++) {
            auto& q = mFulfilledQuests.emplace_back();
            q.read(src);
        }
    }

    {
        int nm;
        src >> nm;
        for(int i = 0; i < nm; i++) {
            auto& m = mSlayedMonsters.emplace_back();
            src >> m;
        }
    }

    {
        int nq;
        src >> nq;
        for(int i = 0; i < nq; i++) {
            src.readGameEvent(this, [this](eGameEvent* const e) {
                const auto ge = static_cast<eGodQuestEvent*>(e);
                mGodQuests.push_back(ge);
            });
        }
    }

    {
        int nq;
        src >> nq;
        for(int i = 0; i < nq; i++) {
            src.readGameEvent(this, [this](eGameEvent* const e) {
                const auto re = static_cast<eReceiveRequestEvent*>(e);
                mCityRequests.push_back(re);
            });
        }
    }

    {
        int nq;
        src >> nq;
        for(int i = 0; i < nq; i++) {
            src.readGameEvent(this, [this](eGameEvent* const e) {
                const auto re = static_cast<eTroopsRequestEvent*>(e);
                mCityTroopsRequests.push_back(re);
            });
        }
    }

    {
        int nbs;
        src >> nbs;
        for(int i = 0; i < nbs; i++) {
            eBuildingType type;
            src >> type;
            eBuildingReader::sRead(*this, type, src);
        }
    }


    {
        int ncs;
        src >> ncs;

        for(int i = 0; i < ncs; i++) {
            eCharacterType type;
            src >> type;
            const auto c = eCharacter::sCreate(type, *this);
            c->read(src);
        }
    }

    {
        int nb;
        src >> nb;

        for(int i = 0; i < nb; i++) {
            eBannerType type;
            src >> type;
            const auto b = e::make_shared<eSoldierBanner>(type, *this);
            b->read(src);
            registerSoldierBanner(b);
        }
    }

    {
        int ni;
        src >> ni;

        for(int i = 0; i < ni; i++) {
            const auto ii = new eInvasionHandler(*this, nullptr, nullptr);
            ii->read(src);
        }
    }

    {
        int n;
        src >> n;

        for(int i = 0; i < n; i++) {
            const auto p = std::make_shared<ePlague>(*this);
            p->read(src);
            mPlagues.push_back(p);
        }
    }

    {
        int ncs;
        src >> ncs;

        for(int i = 0; i < ncs; i++) {
            eMissileType type;
            src >> type;
            const auto c = eMissile::sCreate(*this, type);
            c->read(src);
        }
    }

    {
        int ngs;
        src >> ngs;
        for(int i = 0; i < ngs; i++) {
            src.readCharacter(this, [this](eCharacter* const c) {
                mAttackingGods.push_back(c);
            });
        }
    }

    {
        int nms;
        src >> nms;
        for(int i = 0; i < nms; i++) {
            src.readCharacter(this, [this](eCharacter* const c) {
                mMonsters.push_back(static_cast<eMonster*>(c));
            });
        }
    }

    int nfg;
    src >> nfg;
    for(int i = 0; i < nfg; i++) {
        eGodType type;
        src >> type;
        mFriendlyGods.push_back(type);
    }

    int nrg;
    src >> nrg;
    for(int i = 0; i < nrg; i++) {
        eGodType type;
        src >> type;
        mHostileGods.push_back(type);
    }

    int nevs;
    src >> nevs;
    for(int i = 0; i < nevs; i++) {
        eGameEventType type;
        src >> type;
        const auto branch = eGameEventBranch::root;
        const auto e = eGameEvent::sCreate(type, branch, this);
        e->setGameBoard(this);
        e->setWorldBoard(mWorldBoard);
        e->read(src);
        addRootGameEvent(e);
    }

    int ng;
    src >> ng;
    for(int i = 0; i < ng; i++) {
        const auto g = std::make_shared<eEpisodeGoal>();
        g->read(mWorldBoard, src);
        mGoals.push_back(g);
    }

    mAvailableBuildings.read(src);

    int na;
    src >> na;
    for(int i = 0; i < na; i++) {
        const auto ma = std::make_shared<eMilitaryAid>();
        ma->read(src, this);
        addMilitaryAid(ma);
    }

    src >> mProgressEarthquakes;
    int ne;
    src >> ne;
    for(int i = 0; i < ne; i++) {
        const auto e = std::make_shared<eEarthquake>();
        e->read(src, *this);
        mEarthquakes.push_back(e);
    }

    int nd;
    src >> nd;
    for(int i = 0; i < nd; i++) {
        src.readCity(this, [this](const stdsptr<eWorldCity>& c) {
            mDefeatedBy.push_back(c);
        });
    }

     src >> mPop100;
     src >> mPop500;
     src >> mPop1000;
     src >> mPop2000;
     src >> mPop3000;
     src >> mPop5000;
     src >> mPop10000;
     src >> mPop15000;
     src >> mPop20000;
     src >> mPop25000;

     int npa;
     src >> npa;
     for(int i = 0; i < npa; i++) {
         ePlannedActionType type;
         src >> type;
         const auto a = ePlannedAction::sCreate(type);
         a->read(src, *this);
         mPlannedActions.push_back(a);
     }

     int nh;
     src >> nh;
     for(int i = 0; i < nh; i++) {
         eHeroType h;
         src >> h;
         mSummonedHeroes.push_back(h);
     }

     updateMarbleTiles();
}
