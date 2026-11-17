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

    src >> mFogOfWar;

    src >> mEpisodeLost;

    src >> mWageMultiplier;

    for(auto& p : mPrices) {
        src >> p.second;
    }

    mDate.read(src);
    src >> mFrame;
    src >> mTime;
    src >> mTotalTime;

    src >> mSoldiersUpdate;

    {
        int nc;
        src >> nc;
        for(int i = 0; i < nc; i++) {
            eCityId cid;
            src >> cid;
            const auto c = addCityToBoard(cid);
            c->read(src);
            scheduleAppealMapUpdate(cid);
        }
    }

    {
        int np;
        src >> np;
        for(int i = 0; i < np; i++) {
            ePlayerId pid;
            src >> pid;
            const auto p = std::make_shared<eBoardPlayer>(pid, *this);
            p->read(src);
            mPlayersOnBoard.push_back(p);
        }
    }

    for(const auto& ts : mTiles) {
        for(const auto& t : ts) {
            t->read(src);
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
        int ncs;
        src >> ncs;

        for(int i = 0; i < ncs; i++) {
            eMissileType type;
            src >> type;
            const auto c = eMissile::sCreate(*this, type);
            c->read(src);
        }
    }

    int ng;
    src >> ng;
    for(int i = 0; i < ng; i++) {
        const auto g = std::make_shared<eEpisodeGoal>();
        g->read(src);
        mGoals.push_back(g);
    }
    src >> mGoalsFulfilled;

    src >> mProgressEarthquakes;
    int ne;
    src >> ne;
    for(int i = 0; i < ne; i++) {
        const auto e = std::make_shared<eEarthquake>();
        e->read(src, *this);
        mEarthquakes.push_back(e);
    }

    src >> mProgressWaves;
    int nw;
    src >> nw;
    for(int i = 0; i < nw; i++) {
        const auto w = std::make_shared<eTidalWave>();
        w->read(src, *this);
        mTidalWaves.push_back(w);
    }

    src >> mProgressLavaFlows;
    int nl;
    src >> nl;
    for(int i = 0; i < nl; i++) {
        const auto w = std::make_shared<eLavaFlow>();
        w->read(src, *this);
        mLavaFlows.push_back(w);
    }

    src >> mProgressLandSlides;
    int ns;
    src >> ns;
    for(int i = 0; i < ns; i++) {
        const auto w = std::make_shared<eLandSlide>();
        w->read(src, *this);
        mLandSlides.push_back(w);
    }

    int nd;
    src >> nd;
    for(int i = 0; i < nd; i++) {
        eCityId cid;
        src >> cid;
        int nc;
        src >> nc;
        for(int j = 0; j < nc; j++) {
            src.readCity(this, [this, cid](const stdsptr<eWorldCity>& c) {
                mDefeatedBy[cid].push_back(c);
            });
        }
    }

    int npa;
    src >> npa;
    for(int i = 0; i < npa; i++) {
        ePlannedActionType type;
        src >> type;
        const auto a = ePlannedAction::sCreate(type);
        a->read(src, *this);
        mPlannedActions.push_back(a);
    }

    int np;
    src >> np;
    for(int i = 0; i < np; i++) {
        eResourceType type;
        src >> type;
        auto& y = mYearlyProduction[type];
        src >> y.fBest;
        src >> y.fLastYear;
        src >> y.fThisYear;
    }

    src >> mSavedYear;

    updateMarbleTiles();
    updateBlackMarbleTiles();
    updateTerritoryBorders();
    for(const auto& c : mCitiesOnBoard) {
        c->updateResources();
    }
}
