#include "eelitehousing.h"

#include "engine/egameboard.h"

#include "textures/egametextures.h"
#include "elanguage.h"

#include "buildings/epalace.h"

eEliteHousing::eEliteHousing(eGameBoard& board) :
    eHouseBase(board, eBuildingType::eliteHousing,
               4, 4, {6, 6, 10, 16, 20}) {}

eTextureSpace eEliteHousing::getTextureSpace(
        const int tx, const int ty,
        const eTileSize size) const {
    const SDL_Point p{tx, ty};
    const auto r = tileRect();
    if(!SDL_PointInRect(&p, &r)) return {nullptr};
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto& coll = getTextureCollection(size);
    const int rx = r.x;
    const int ry = r.y;
    const int dx = tx - rx;
    const int dy = ty - ry;
    if(dx < 2 && dy < 2) { // top
        if(dir == eWorldDirection::N) {
            const auto& tex = coll.getTexture(3);
            return {tex, true, {r.x, r.y, 2, 2}};
        } else if(dir == eWorldDirection::E) {
            const int id = seed() % 2;
            const auto& tex = coll.getTexture(id);
            return {tex, true, {r.x, r.y, 2, 2}};
        } else if(dir == eWorldDirection::S) {
            const auto& tex = coll.getTexture(2);
            return {tex, true, {r.x, r.y, 2, 2}};
        } else { // if(dir == eWorldDirection::W) {
            const auto& tex = coll.getTexture(4);
            return {tex, true, {r.x, r.y, 2, 2}};
        }
    } else if(dx < 2 && dy >= 2) { // left
        if(dir == eWorldDirection::N) {
            const int id = seed() % 2;
            const auto& tex = coll.getTexture(id);
            return {tex, false, {r.x, r.y + 2, 2, 2}};
        } else if(dir == eWorldDirection::E) {
            const auto& tex = coll.getTexture(2);
            return {tex, false, {r.x, r.y + 2, 2, 2}};
        } else if(dir == eWorldDirection::S) {
            const auto& tex = coll.getTexture(4);
            return {tex, false, {r.x, r.y + 2, 2, 2}};
        } else { // if(dir == eWorldDirection::W) {
            const auto& tex = coll.getTexture(3);
            return {tex, false, {r.x, r.y + 2, 2, 2}};
        }
    } else if(dx >= 2 && dy < 2) { // right
        if(dir == eWorldDirection::N) {
            const auto& tex = coll.getTexture(4);
            return {tex, false, {r.x + 2, r.y, 2, 2}};
        } else if(dir == eWorldDirection::E) {
            const auto& tex = coll.getTexture(3);
            return {tex, false, {r.x + 2, r.y, 2, 2}};
        } else if(dir == eWorldDirection::S) {
            const int id = seed() % 2;
            const auto& tex = coll.getTexture(id);
            return {tex, false, {r.x + 2, r.y, 2, 2}};
        } else { // if(dir == eWorldDirection::W) {
            const auto& tex = coll.getTexture(2);
            return {tex, false, {r.x + 2, r.y, 2, 2}};
        }
    } else { // bottom
        if(dir == eWorldDirection::N) {
            const auto& tex = coll.getTexture(2);
            return {tex, false, {r.x + 2, r.y + 2, 2, 2}};
        } else if(dir == eWorldDirection::E) {
            const auto& tex = coll.getTexture(4);
            return {tex, false, {r.x + 2, r.y + 2, 2, 2}};
        } else if(dir == eWorldDirection::S) {
            const auto& tex = coll.getTexture(3);
            return {tex, false, {r.x + 2, r.y + 2, 2, 2}};
        } else { // if(dir == eWorldDirection::W) {
            const int id = seed() % 2;
            const auto& tex = coll.getTexture(id);
            return {tex, false, {r.x + 2, r.y + 2, 2, 2}};
        }
    }
    return {};
}

std::vector<eOverlay> eEliteHousing::getOverlays(const eTileSize size) const {
//    auto& board = getBoard();
//    if(board.poseidonMode()) return {};
//    return getHorseOverlays(size);
    (void)size;
    return {};
}

std::shared_ptr<eTexture>
eEliteHousing::getLeftTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    const int id = seed() % 2;
    return coll.getTexture(id);
}

std::shared_ptr<eTexture>
eEliteHousing::getBottomTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(2);
}

std::shared_ptr<eTexture>
eEliteHousing::getTopTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(3);
}

std::shared_ptr<eTexture>
eEliteHousing::getRightTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(4);
}

std::vector<eOverlay>
eEliteHousing::getHorseOverlays(const eTileSize size) const {
    if(mLevel < 3 || mHorses < 1 || mPeople <= 0) {
        return {};
    }
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    eGameTextures::loadEliteHouse();
    const auto& coll = texs.fEliteHouseHorses;
    eOverlay h;
    h.fX = -2.0;
    h.fY = -2.5;
    h.fTex = coll.getTexture(mHorses - 1);
    return {h};
}

int eEliteHousing::provide(const eProvide p, const int n) {
    if(mPeople <= 0) return 0;
    int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::food:
        value = &mFood;
        max = 2*(16 + mPeople + mHorses);
        break;
    case eProvide::fleece:
        value = &mFleece;
        max = 16;
        break;
    case eProvide::oil:
        value = &mOil;
        max = 16;
        break;
    case eProvide::wine:
        value = &mWine;
        max = 16;
        break;
    case eProvide::arms:
        max = 4;
        value = &mArms;
        break;
    case eProvide::horses:
        max = 4;
        value = &mHorses;
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

void eEliteHousing::timeChanged(const int by) {
    const int lupdate = 1000;
    if(mUpdateLevel > lupdate) {
        mUpdateLevel -= lupdate;
        updateLevel();
    }
    eHouseBase::timeChanged(by);
}

void eEliteHousing::nextMonth() {
    mPaidTaxesLastMonth = mPaidTaxes;
    mPaidTaxes = 0;
    const int cfood = round((mPeople + mHorses)*0.25);
    const int cfleece = 2;
    const int coil = 2;
    const int cwine = mLevel > 1 ? 2 : 0;
    mFood = std::max(0, mFood - cfood);
    mFleece = std::max(0, mFleece - cfleece);
    mOil = std::max(0, mOil - coil);
    if(mLevel > 2) mWine = std::max(0, mWine - cwine);
}

bool eEliteHousing::lowFood() const {
    if(!mFood) return true;
    const int cfood = round((mPeople + mHorses)*0.25);
    return mFood < cfood;
}

void eEliteHousing::removeArmor() {
    mArms = std::max(0, mArms - 1);
    updateLevel();
}

void eEliteHousing::removeHorse() {
    mHorses = std::max(0, mHorses - 1);
    updateLevel();
}

eHouseMissing eEliteHousing::missing() const {
    const auto& b = getBoard();
    const auto t = centerTile();
    if(!t) return eHouseMissing::food;
    const int dx = t->dx();
    const int dy = t->dy();
    const double appeal = b.appeal(dx ,dy);
    int nVenues = 0;
    if(mPhilosophers > 0) nVenues++;
    if(mActors > 0) nVenues++;
    if(mAthletes > 0) nVenues++;
    if(mCompetitors > 0) nVenues++;
    if(mFood > 0) {
        if(mFleece > 0) {
            if(mOil > 0) {
                if(nVenues > 2) {
                    if(appeal > 5.0) {
                        if(mArms > 0) {
                            if(appeal > 7.0) {
                                if(mWine > 0) {
                                    if(appeal > 9.0) {
                                        if(mHorses > 0) {
                                            if(nVenues > 3) {
                                                if(appeal > 10.) {
                                                    return eHouseMissing::nothing;
                                                }
                                                return eHouseMissing::appeal;
                                            }
                                            return eHouseMissing::venues;
                                        }
                                        return eHouseMissing::horse;
                                    }
                                    return eHouseMissing::appeal;
                                }
                                return eHouseMissing::wine;
                            }
                            return eHouseMissing::appeal;
                        }
                        return eHouseMissing::arms;
                    }
                    return eHouseMissing::appeal;
                }
                return eHouseMissing::venues;
            }
            return eHouseMissing::oil;
        }
        return eHouseMissing::fleece;
    }
    return eHouseMissing::food;
}

void eEliteHousing::read(eReadStream& src) {
    eHouseBase::read(src);
    src >> mUpdateLevel;
    src >> mWine;
    src >> mArms;
    src >> mHorses;
}

void eEliteHousing::write(eWriteStream& dst) const {
    eHouseBase::write(dst);
    dst << mUpdateLevel;
    dst << mWine;
    dst << mArms;
    dst << mHorses;
}

std::string eEliteHousing::sName(const int level) {
    return eLanguage::zeusText(28, 10 + level);
}

const eTextureCollection& eEliteHousing::getTextureCollection(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    auto& board = getBoard();
    if(board.poseidonMode()) {
        eGameTextures::loadPoseidonEliteHouse();
        if(mPeople <= 0) return blds.fPoseidonEliteHouse[0];
        return blds.fPoseidonEliteHouse[mLevel + 1];
    } else {
        eGameTextures::loadEliteHouse();
        if(mPeople <= 0) return blds.fEliteHouse[0];
        return blds.fEliteHouse[mLevel + 1];
    }
}

void eEliteHousing::updateLevel() {
    const auto& b = getBoard();
    const auto t = centerTile();
    if(!t) return;
    const int dx = t->dx();
    const int dy = t->dy();
    const double appeal = b.appeal(dx ,dy);
    int nVenues = 0;
    if(mPhilosophers > 0) nVenues++;
    if(mActors > 0) nVenues++;
    if(mAthletes > 0) nVenues++;
    if(mCompetitors > 0) nVenues++;
    if(mFood > 0 && mFleece > 0 && mOil > 0 && nVenues > 2 && appeal > 5.0) {
        if(mArms > 0 && appeal > 7.0) {
            if(mWine > 0 && appeal > 9.0) {
                if(mHorses > 0 && nVenues > 3 && appeal > 10.0) {
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
