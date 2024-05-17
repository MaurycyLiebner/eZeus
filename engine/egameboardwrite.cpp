#include "egameboard.h"

#include "spawners/ebanner.h"
#include "fileIO/ebuildingwriter.h"
#include "einvasionhandler.h"
#include "missiles/emissile.h"
#include "gameEvents/egameevent.h"
#include "gameEvents/ereceiverequestevent.h"
#include "eplague.h"

void eGameBoard::write(eWriteStream& dst) const {
    dst << mWidth;
    dst << mHeight;

    dst << mDrachmas;
    dst << mDifficulty;
    dst << mWageRate;
    dst << mTaxRate;

    mDate.write(dst);
    dst << mTime;
    dst << mTotalTime;

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

    mWorldBoard.setIOIDs();

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
        const int ni = mInvasions.size();
        dst << ni;
        for(const auto i : mInvasions) {
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
        const int nms = mAttackingMonsters.size();
        dst << nms;
        for(const auto g : mAttackingMonsters) {
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

    mAvailableBuildings.write(dst);

    mWorldBoard.write(dst);
}
