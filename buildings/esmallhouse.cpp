﻿#include "esmallhouse.h"

#include <algorithm>
#include "textures/egametextures.h"
#include "engine/egameboard.h"
#include "engine/eplague.h"

#include "characters/esick.h"
#include "characters/edisgruntled.h"
#include "characters/actions/esickdisgruntledaction.h"

#include "buildings/epalace.h"

#include "elanguage.h"

eSmallHouse::eSmallHouse(eGameBoard& board) :
    eHouseBase(board, eBuildingType::commonHouse, 2, 2,
               {8, 16, 24, 32, 40, 48, 60}) {
    eGameTextures::loadCommonHouse();
}

eSmallHouse::~eSmallHouse() {
    if(mSick) mSick->kill();
    if(mDisg) mDisg->kill();
    auto& board = getBoard();
    board.unregisterCommonHouse(this);
}

std::shared_ptr<eTexture> eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];

    if(mPeople == 0) return blds[sizeId].fHouseSpace;
    auto& board = getBoard();
    const eTextureCollection* coll = nullptr;
    if(board.poseidonMode()) {
        const int id = mLevel - 2;
        if(id < 0) {
            coll = &texs.fCommonHouse[mLevel];
        } else {
            eGameTextures::loadPoseidonCommonHouse();
            coll = &texs.fPoseidonCommonHouse[id];
        }
    } else {
        coll = &texs.fCommonHouse[mLevel];
    }
    const int texId = seed() % coll->size();
    return coll->getTexture(texId);
}

int eSmallHouse::provide(const eProvide p, const int n) {
    if(mPeople <= 0) return 0;
    int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::water:
        value = &mWater;
        break;
    case eProvide::hygiene:
        value = &mHygiene;
        max = 100;
        break;
    case eProvide::food:
        value = &mFood;
        max = 2*mPeople;
        break;
    case eProvide::fleece:
        value = &mFleece;
        break;
    case eProvide::oil:
        value = &mOil;
        break;

    case eProvide::philosopherInventor:
        value = &mPhilosophers;
        break;
    case eProvide::actorAstronomer:
        value = &mActors;
        break;
    case eProvide::gymnastScholar:
        value = &mAthletes;
        break;
    case eProvide::competitorCurator:
        value = &mCompetitors;
        break;

    case eProvide::taxes: {
        if(mPaidTaxes) return 0;
        auto& b = getBoard();
        const auto p = b.palace();
        if(!p || p->cursed()) return 0;
        const auto diff = b.difficulty();
        const int taxMult = eDifficultyHelpers::taxMultiplier(
                                diff, type(), mLevel);
        const double tax = mPeople * taxMult * b.taxRateF();
        const int iTax = std::round(tax);
        b.payTaxes(iTax, mPeople);
        mPaidTaxes = iTax;
        return iTax;
    }

    case eProvide::satisfaction: {
        if(mSatisfactionProvidedThisMonth) return 0;
        mSatisfactionProvidedThisMonth = true;
        mSatisfaction = std::clamp(mSatisfaction + 25, 0, 100);
        return 0;
    }
    default:
        return eBuilding::provide(p, n);
    }
    int add = 0;
    if(value) {
        add = std::clamp(n, 0, max - *value);
        *value += add;
    }
    updateLevel();
    return add;
}

void eSmallHouse::timeChanged(const int by) {
    if(mPeople <= 0) {
        mHygiene = 100;
        if(mPlague) {
            auto& board = getBoard();
            board.healHouse(this);
        }
        setDisgruntled(false);
        mSatisfaction = 100;
        mFoodSatisfaction = 100;
        mWaterSatisfaction = 100;
        mWorkSatisfaction = 100;
        mTaxSatisfaction = 100;
        eHouseBase::timeChanged(by);
        return;
    }
    mUpdateCulture += by;
    const int wupdate = 5000;
    if(mUpdateWater > wupdate) {
        mUpdateWater -= wupdate;
        mWater = std::max(0, mWater - 1);
    }
    mUpdateHygiene += by;
    const int hupdate = 25000;
    if(mUpdateHygiene > hupdate) {
        mUpdateHygiene -= hupdate;
        const int subWater = (100 - mWaterSatisfaction)/20;
        const int subFood = (100 - mFoodSatisfaction)/20;
        const int sub = 5 + subWater + subFood;
        mHygiene = std::max(0, mHygiene - sub);
    }

    auto& b = getBoard();
    if(mPlague) {
        if(mHygiene > 25) {
            const int m4 = 10*pow(10000./mHygiene, 4);
            if(by) {
                const int healPeriod = m4/by;
                if(healPeriod && rand() % healPeriod == 0) {
                    b.healHouse(this);
                }
            }
        }
    } else {
        const int m4 = 10*pow(10 + mHygiene, 4);
        const auto diff = b.difficulty();
        const int plagueRisk = eDifficultyHelpers::plagueRisk(diff);
        if(plagueRisk && by) {
            const int plaguePeriod = m4/(by*plagueRisk);
            if(plaguePeriod && rand() % plaguePeriod == 0) {
                b.startPlague(this);
            }
        }
    }

    const auto s = b.sanctuary(eGodType::dionysus);
    const bool dion = s && s->finished();
    if(mDisgruntled) {
        if(dion) {
            setDisgruntled(false);
         } else if(mSatisfaction > 30 && by > 0) {
            if(rand() % (500000/(mSatisfaction*by)) == 0) {
                setDisgruntled(false);
            }
        }
    } else if(!dion) {
        const int m4 = 10*pow(10 + mSatisfaction, 3);
        const auto diff = b.difficulty();
        const int crimeRisk = eDifficultyHelpers::crimeRisk(diff);
        if(crimeRisk && by) {
            const int crimePeriod = m4/(by*crimeRisk);
            if(crimePeriod && rand() % crimePeriod == 0) {
                setDisgruntled(true);
            }
        }
    }

    {
        const auto s = b.sanctuary(eGodType::aphrodite);
        const bool aphr = s && s->finished();
        if(!aphr) {
            const int m4 = 10*pow(10 + mSatisfaction, 3);
            const auto diff = b.difficulty();
            const int leaveRisk = eDifficultyHelpers::crimeRisk(diff);
            if(leaveRisk && by) {
                const int leavePeriod = m4/(by*leaveRisk);
                if(leavePeriod && rand() % leavePeriod == 0) {
                    leave();
                }
            }
        }
    }

    mUpdateLevel += by;
    const int lupdate = 1000;
    if(mUpdateLevel > lupdate) {
        mUpdateLevel -= lupdate;
        updateLevel();
    }
    mUpdateSatisfaction += by;
    const int supdate = 7500;
    if(mUpdateSatisfaction > supdate) {
        mUpdateSatisfaction -= supdate;
        updateSatisfaction();
    }

    if(mDisgruntled && !mDisg) {
        mSpawnDisg += by;
        const int d = 10000;
        if(mSpawnDisg > d) {
            mSpawnDisg -= d;
            spawnDisgruntled();
        }
    }
    if(mPlague && !mSick) {
        mSpawnSick += by;
        const int s = 10000;
        if(mSpawnSick > s) {
            mSpawnSick -= s;
            spawnSick();
        }
    }

    eHouseBase::timeChanged(by);
}

void eSmallHouse::nextMonth() {
    mPaidTaxesLastMonth = mPaidTaxes;
    mPaidTaxes = 0;
    mSatisfactionProvidedThisMonth = false;
    const int cfood = round(mPeople*0.25);
    const int cfleece = (mLevel > 2 && mPeople > 0) ? 2 : 0;
    const int coil = (mLevel > 4 && mPeople > 0) ? 2 : 0;
    mFood = std::max(0, mFood - cfood);
    mFleece = std::max(0, mFleece - cfleece);
    mOil = std::max(0, mOil - coil);
}

void eSmallHouse::setPlague(const bool p) {
    mPlague = p;
    mSpawnSick = rand() % 10000;
}

void eSmallHouse::setDisgruntled(const bool d) {
    mDisgruntled = d;
    mSpawnDisg = __INT_MAX__/2;
}

bool eSmallHouse::lowFood() const {
    if(!mFood) return true;
    const int cfood = round(mPeople*0.25);
    return mFood < cfood;
}

eHouseMissing eSmallHouse::missing() const {
    const auto& b = getBoard();
    const auto t = centerTile();
    if(!t) return eHouseMissing::food;
    const int dx = t->dx();
    const int dy = t->dy();
    const double appeal = b.appeal(dx, dy);
    int nVenues = 0;
    if(mPhilosophers > 0) nVenues++;
    if(mActors > 0) nVenues++;
    if(mAthletes > 0) nVenues++;
    if(mCompetitors > 0) nVenues++;
    if(mFood > 0) {
        if(mWater > 0) {
            if(nVenues > 0) {
                if(mFleece > 0) {
                    if(appeal > 2.0) {
                        if(nVenues > 1) {
                            if(mOil > 0) {
                                if(appeal > 5.0) {
                                    if(nVenues > 2) {
                                        if(appeal > 8.0) {
                                            return eHouseMissing::nothing;
                                        }
                                        return eHouseMissing::appeal;
                                    }
                                    return eHouseMissing::venues;
                                }
                                return eHouseMissing::appeal;
                            }
                            return eHouseMissing::oil;
                        }
                        return eHouseMissing::venues;
                    }
                    return eHouseMissing::appeal;
                }
                return eHouseMissing::fleece;
            }
            return eHouseMissing::venues;
        }
        return eHouseMissing::water;
    }
    return eHouseMissing::food;
}

void eSmallHouse::read(eReadStream& src) {
    eHouseBase::read(src);

    src >> mSatisfactionProvidedThisMonth;
    src >> mUpdateSatisfaction;
    src >> mSatisfaction;
    src >> mFoodSatisfaction;
    src >> mWaterSatisfaction;
    src >> mWorkSatisfaction;
    src >> mTaxSatisfaction;

    src >> mUpdateWater;
    src >> mUpdateHygiene;
    src >> mUpdateLevel;

    src >> mWater;
    src >> mHygiene;
    src >> mPlague;
    src >> mDisgruntled;

    src >> mSpawnSick;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mSick = static_cast<eSick*>(c);
    });
    src >> mSpawnDisg;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mDisg = static_cast<eDisgruntled*>(c);
    });
}

void eSmallHouse::write(eWriteStream& dst) const {
    eHouseBase::write(dst);

    dst << mSatisfactionProvidedThisMonth;
    dst << mUpdateSatisfaction;
    dst << mSatisfaction;
    dst << mFoodSatisfaction;
    dst << mWaterSatisfaction;
    dst << mWorkSatisfaction;
    dst << mTaxSatisfaction;

    dst << mUpdateWater;
    dst << mUpdateHygiene;
    dst << mUpdateLevel;

    dst << mWater;
    dst << mHygiene;
    dst << mPlague;
    dst << mDisgruntled;

    dst << mSpawnSick;
    dst.writeCharacter(mSick.get());
    dst << mSpawnDisg;
    dst.writeCharacter(mDisg.get());
}

std::string eSmallHouse::sName(const int level) {
    return eLanguage::zeusText(28, 2 + level);
}

void eSmallHouse::updateLevel() {
    const auto& b = getBoard();
    const auto t = centerTile();
    if(!t) return;
    const int dx = t->dx();
    const int dy = t->dy();
    const double appeal = b.appeal(dx, dy);
    int nVenues = 0;
    if(mPhilosophers > 0) nVenues++;
    if(mActors > 0) nVenues++;
    if(mAthletes > 0) nVenues++;
    if(mCompetitors > 0) nVenues++;
    if(mFood > 0) {
        if(mWater > 0 && nVenues > 0) {
            if(mFleece > 0 && appeal > 2.0) {
                if(nVenues > 1) {
                    if(mOil > 0 && appeal > 5.0) {
                        if(nVenues > 2 && appeal > 8.0) {
                            return setLevel(6);
                        }
                        return setLevel(5);
                    }
                    return setLevel(4);
                }
                return setLevel(3);
            }
            return setLevel(2);
        }
        return setLevel(1);
    }
    setLevel(0);
}

void eSmallHouse::updateSatisfaction() {
    const int weight = 9;
    const int div = weight + 1;

    const int foodSat = mFood == 0 ? 0 : 100;
    mFoodSatisfaction = (weight*mFoodSatisfaction + foodSat)/div;

    const int waterSat = mWater == 0 ? 0 : 100;
    mWaterSatisfaction = (weight*mWaterSatisfaction + waterSat)/div;

    auto& board = getBoard();
    const auto empData = board.employmentData();
    const int workSat = 100*std::pow(empData.employedFraction(), 4);
    mWorkSatisfaction = (weight*mWorkSatisfaction + workSat)/div;

    const auto taxRate = board.taxRate();
    const auto diff = board.difficulty();
    const int ts = eDifficultyHelpers::taxSentiment(diff, taxRate);
    const int taxSatIfPaid = std::round(100.*(ts + 7.)/14.);
    const int taxSat = mPaidTaxesLastMonth ? taxSatIfPaid : 100;
    mTaxSatisfaction = (weight*mTaxSatisfaction + taxSat)/div;

    const int m1 = std::min(mFoodSatisfaction, mWaterSatisfaction);
    const int m2 = std::min(m1, mWorkSatisfaction);
    const int satMin = mTaxSatisfaction - 50;
    const int satMax = 50 + mTaxSatisfaction;
    const int sat = std::clamp(m2, satMin, satMax);
    mSatisfaction = (weight*mSatisfaction + sat)/div;
}

void eSmallHouse::spawnCharacter(const stdsptr<eCharacter>& c) {
    auto ts = surroundingRoad(false, true);
    if(ts.empty()) {
        c->changeTile(centerTile());
    } else {
        const auto t = ts[rand() % ts.size()];
        c->changeTile(t);
    }
    const auto a = e::make_shared<eSickDisgruntledAction>(c.get(), this);
    c->setAction(a);
}

void eSmallHouse::spawnSick() {
    if(mSick) mSick->kill();
    const auto c = e::make_shared<eSick>(getBoard());
    mSick = c.get();
    spawnCharacter(c);
}

void eSmallHouse::spawnDisgruntled() {
    if(mDisg) mDisg->kill();
    const auto c = e::make_shared<eDisgruntled>(getBoard());
    mDisg = c.get();
    mDisg->setPlayerId(2);
    spawnCharacter(c);
}
