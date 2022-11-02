#include "esmallhouse.h"

#include <algorithm>
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eSmallHouse::eSmallHouse(eGameBoard& board) :
    eHouseBase(board, eBuildingType::commonHouse, 2, 2,
               {8, 16, 24, 32, 40, 48, 60}) {}

std::shared_ptr<eTexture> eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    if(mPeople == 0) return blds[sizeId].fHouseSpace;
    const auto& coll = blds[sizeId].fCommonHouse[mLevel];
    const int texId = seed() % coll.size();
    return coll.getTexture(texId);
}

int eSmallHouse::provide(const eProvide p, const int n) {
    if(mPeople <= 0) return 0;
    int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::water:
        value = &mWater;
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

    case eProvide::philosopher:
        value = &mPhilosophers;
        break;
    case eProvide::actor:
        value = &mActors;
        break;
    case eProvide::gymnast:
        value = &mAthletes;
        break;

    case eProvide::taxes: {
        if(mPaidTaxes) return 0;
        mPaidTaxes = true;
        auto& b = getBoard();
        const auto diff = b.difficulty();
        const int taxMult = eDifficultyHelpers::taxMultiplier(
                                diff, type(), mLevel);
        const double tax = mPeople * taxMult * b.taxRateF();
        const int iTax = std::round(tax);
        b.incDrachmas(iTax);
        return iTax;
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
    mUpdateCulture += by;
    const int wupdate = 5000;
    if(mUpdateWater > wupdate) {
        mUpdateWater -= wupdate;
        mWater = std::max(0, mWater - 1);
    }
    const int lupdate = 1000;
    if(mUpdateLevel > lupdate) {
        mUpdateLevel -= lupdate;
        updateLevel();
    }
    eHouseBase::timeChanged(by);
}

void eSmallHouse::nextMonth() {
    mPaidTaxes = false;
    const int cfood = round(mPeople*0.25);
    const int cfleece = mLevel > 2 ? 2 : 0;
    const int coil = mLevel > 4 ? 2 : 0;
    mFood = std::max(0, mFood - cfood);
    mFleece = std::max(0, mFleece - cfleece);
    mOil = std::max(0, mOil - coil);
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
    const int stadium = b.hasStadium() ? 1 : 0;
    const int nVenues = mPhilosophers + mActors +
                        mAthletes + stadium;
    if(mFood > 0) {
        if(mWater > 0) {
            if(nVenues > 0) {
                if(mFleece > 0) {
                    if(appeal > 2.0) {
                        if(nVenues > 1) {
                            if(mOil > 0 && appeal > 5.0) {
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
    src >> mWater;
}

void eSmallHouse::write(eWriteStream& dst) const {
    eHouseBase::write(dst);
    dst << mWater;
}

void eSmallHouse::updateLevel() {
    const auto& b = getBoard();
    const auto t = centerTile();
    if(!t) return;
    const int dx = t->dx();
    const int dy = t->dy();
    const double appeal = b.appeal(dx, dy);
    const int stadium = b.hasStadium() ? 1 : 0;
    const int nVenues = mPhilosophers + mActors +
                        mAthletes + stadium;
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
