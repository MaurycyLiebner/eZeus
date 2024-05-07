#include "egameboard.h"

#include "spawners/ebanner.h"
#include "fileIO/ebuildingreader.h"
#include "einvasionhandler.h"
#include "missiles/emissile.h"
#include "gameEvents/egameevent.h"

void eGameBoard::read(eReadStream& src) {
    int w;
    src >> w;
    int h;
    src >> h;
    initialize(w, h);

    src >> mDrachmas;
    src >> mDifficulty;
    src >> mWageRate;
    src >> mTaxRate;

    mDate.read(src);
    src >> mTime;
    src >> mTotalTime;

    src >> mSoldiersUpdate;
    src >> mMaxRockThrowers;
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
            eGodQuest q;
            q.read(src);
            mGodQuests.push_back(q);
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
            const auto ii = new eInvasionHandler(*this, nullptr);
            ii->read(src);
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
        const auto e = eGameEvent::sCreate(type, *this);
        e->read(src);
        mGameEvents.push_back(e);
    }

    mAvailableBuildings.read(src);

    mWorldBoard.read(src);

    src.handlePostFuncs();
}