#include "egameboard.h"

#include "spawners/ebanner.h"
#include "fileIO/ebuildingwriter.h"
#include "einvasionhandler.h"
#include "missiles/emissile.h"
#include "gameEvents/egameevent.h"
#include "gameEvents/ereceiverequestevent.h"
#include "gameEvents/etroopsrequestevent.h"
#include "eplague.h"

void eGameBoard::write(eWriteStream& dst) const {
    dst << mWidth;
    dst << mHeight;

    dst << mPoseidonMode;

    dst << mEpisodeLost;

    dst << mImmigrationLimit;
    dst << mNoFood;
    mNoFoodSince.write(dst);
    mInDebtSince.write(dst);

    dst << mDrachmas;
    dst << mDifficulty;
    dst << mWageRate;
    dst << mTaxRate;
    dst << mTaxesPaidLastYear;
    dst << mTaxesPaidThisYear;
    dst << mPeoplePaidTaxesLastYear;
    dst << mPeoplePaidTaxesThisYear;

    mDate.write(dst);
    dst << mFrame;
    dst << mTime;
    dst << mTotalTime;

    mEmplDistributor.write(dst);

    dst << mShutDown.size();
    for(const auto i : mShutDown) {
        dst << i;
    }

    dst << mManTowers;

    dst << mShutdownLandTrade;
    dst << mShutdownSeaTrade;

    dst << mSoldiersUpdate;
    dst << mMaxRabble;
    dst << mMaxHoplites;
    dst << mMaxHorsemen;

    dst << mCoverageUpdate;
    dst << mAthleticsCoverage;
    dst << mPhilosophyCoverage;
    dst << mDramaCoverage;
    dst << mAllDiscCoverage;
    dst << mTaxesCoverage;
    dst << mUnrest;
    dst << mPopularity;
    dst << mHealth;
    dst << mExcessiveMilitaryServiceCount;
    dst << mMonthsOfMilitaryService;

    dst << mWonGames;

    {
        int id = 0;
        for(const auto b : mAllBuildings) {
            b->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto c : mCharacters) {
            c->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto ca : mCharacterActions) {
            ca->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto b : mBanners) {
            b->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto b : mAllSoldierBanners) {
            b->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto e : mAllGameEvents) {
            e->setIOID(id++);
        }
    }

    for(const auto& ts : mTiles) {
        for(const auto& t : ts) {
            t->write(dst);
            const auto b = t->banner();
            const bool has = b != nullptr;
            dst << has;
            if(!has) continue;
            dst << b->type();
            dst << b->id();
            b->write(dst);
        }
    }

    {
        const int nq = mFulfilledQuests.size();
        dst << nq;
        for(const auto& q : mFulfilledQuests) {
            q.write(dst);
        }
    }

    {
        const int nm = mSlayedMonsters.size();
        dst << nm;
        for(const auto m : mSlayedMonsters) {
            dst << m;
        }
    }

    {
        const int nq = mGodQuests.size();
        dst << nq;
        for(const auto& q : mGodQuests) {
            dst.writeGameEvent(q);
        }
    }

    {
        const int nq = mCityRequests.size();
        dst << nq;
        for(const auto& q : mCityRequests) {
            dst.writeGameEvent(q);
        }
    }

    {
        const int nq = mCityTroopsRequests.size();
        dst << nq;
        for(const auto& q : mCityTroopsRequests) {
            dst.writeGameEvent(q);
        }
    }

    {
        const int nbs = mAllBuildings.size();
        dst << nbs;
        for(const auto b : mAllBuildings) {
            dst << b->type();
            eBuildingWriter::sWrite(b, dst);
        }
    }

    {
        const int ncs = mCharacters.size();
        dst << ncs;
        for(const auto c : mCharacters) {
            dst << c->type();
            c->write(dst);
        }
    }

    {
        const int nb = mSoldierBanners.size();
        dst << nb;
        for(const auto& b : mSoldierBanners) {
            dst << b->type();
            b->write(dst);
        }
    }

    {
        const int ni = mInvasionHandlers.size();
        dst << ni;
        for(const auto i : mInvasionHandlers) {
            i->write(dst);
        }
    }

    {
        dst << mPlagues.size();

        for(const auto& p : mPlagues) {
            p->write(dst);
        }
    }

    {
        const int ncs = mMissiles.size();
        dst << ncs;
        for(const auto c : mMissiles) {
            dst << c->type();
            c->write(dst);
        }
    }

    {
        const int ngs = mAttackingGods.size();
        dst << ngs;
        for(const auto g : mAttackingGods) {
            dst.writeCharacter(g);
        }
    }

    {
        const int nms = mMonsters.size();
        dst << nms;
        for(const auto g : mMonsters) {
            dst.writeCharacter(g);
        }
    }

    const int nfg = mFriendlyGods.size();
    dst << nfg;
    for(const auto g : mFriendlyGods) {
        dst << g;
    }

    const int nrg = mHostileGods.size();
    dst << nrg;
    for(const auto g : mHostileGods) {
        dst << g;
    }

    dst << mGameEvents.size();
    for(const auto& e : mGameEvents) {
        dst << e->type();
        e->write(dst);
    }

    dst << mGoals.size();
    for(const auto& g : mGoals) {
        g->write(dst);
    }

    mAvailableBuildings.write(dst);

    dst << mMilitaryAid.size();
    for(const auto& a : mMilitaryAid) {
        a->write(dst);
    }

    dst << mProgressEarthquakes;
    dst << mEarthquakes.size();
    for(const auto& e : mEarthquakes) {
        e->write(dst);
    }

    dst << mDefeatedBy.size();
    for(const auto& c : mDefeatedBy) {
        dst.writeCity(c.get());
    }

    dst << mPop100;
    dst << mPop500;
    dst << mPop1000;
    dst << mPop2000;
    dst << mPop3000;
    dst << mPop5000;
    dst << mPop10000;
    dst << mPop15000;
    dst << mPop20000;
    dst << mPop25000;

    dst << mPlannedActions.size();
    for(const auto a : mPlannedActions) {
        dst << a->type();
        a->write(dst);
    }

    dst << mSummonedHeroes.size();
    for(const auto h : mSummonedHeroes) {
        dst << h;
    }
}
