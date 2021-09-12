#include "ebuilding.h"

#include "engine/egameboard.h"
#include "engine/etile.h"
#include "eruins.h"

eBuilding::eBuilding(eGameBoard& board,
                     const eBuildingType type,
                     const int sw, const int sh) :
    eObject(board),
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {
    getBoard().registerBuilding(this);
}

eBuilding::~eBuilding() {
    getBoard().unregisterBuilding(this);
}

int eBuilding::provide(const eProvide p, const int n) {
    (void)n;
    if(p == eProvide::maintanance) {
        const int nn = 100 - mMaintance;
        mMaintance += nn;
        return nn;
    }
    return 0;
}

eTile* eBuilding::tileNeighbour(const eMoveDirection o,
                                const eTileValidator& v) const {
    if(!mTile) return nullptr;
    int dx = 0;
    int dy = 0;
    switch(o) {
    case eMoveDirection::topRight:
        dy--;
        break;
    case eMoveDirection::bottomRight:
        dx++;
        break;
    case eMoveDirection::bottomLeft:
        dy++;
        break;
    case eMoveDirection::topLeft:
        dx--;
        break;
    default:
        return nullptr;
    }
    for(const auto u : mUnderBuilding) {
        auto tt = static_cast<eTile*>(u->tileRel(dx, dy));
        if(!tt) continue;
        if(v(tt)) return tt;
    }
    return nullptr;
}

eTile* eBuilding::road(const eMoveDirection o) const {
    return tileNeighbour(o, [](eTile* const tile) {
        return tile->hasRoad();
    });
}

void eBuilding::incTime(const int by) {
    auto& b = getBoard();
    mTime += by;
    if(mTile && mTile->onFire()) {
        if(rand() % (10000/by) == 0) {
            if(rand() % 3) {
                const bool r = spreadFire();
                if(r) b.event(eEvent::fire, mTile);
            } else if(mType == eBuildingType::ruins) {
                mTile->setOnFire(false);
            } else {
                b.event(eEvent::collapse, mTile);
                collapse();
                return;
            }
        }
    } else if(rand() % (1000/by) == 0) {
        mMaintance = std::max(0, mMaintance - 1);
    } else {
        const int m4 = pow(mMaintance, 4);
        const auto diff = b.difficulty();
        const int fireRisk = eDifficultyHelpers::fireRisk(diff, mType);
        if(fireRisk) {
            const int firePeriod = m4/(by*fireRisk);
            if(firePeriod && rand() % firePeriod == 0) {
                catchOnFire();
                b.event(eEvent::fire, mTile);
            }
        }
        const int damageRisk = eDifficultyHelpers::damageRisk(diff, mType);
        if(damageRisk) {
            const int damagePeriod = m4/(by*damageRisk);
            if(damagePeriod && rand() % damagePeriod == 0) {
                b.event(eEvent::collapse, mTile);
                collapse();
                return;
            }
        }
    }
    timeChanged(by);
}

void eBuilding::setTile(eTile* const t) {
    mTile = t;
}

void eBuilding::draw(eTilePainter& p,
                     const double x, const double y) {
    p.drawTexture(x, y, getTexture(p.size()), eAlignment::top);
    if(mOverlayEnabled()) {
        const auto overlays = getOverlays(p.size());
        for(const auto& o : overlays) {
            if(o.fAlignTop) p.drawTexture(x + o.fX, y + o.fY, o.fTex,
                                          eAlignment::top);
            else p.drawTexture(x + o.fX, y + o.fY, o.fTex);
        }
    }
}

void eBuilding::addUnderBuilding(eTile* const t) {
    mUnderBuilding.push_back(t);
}

void eBuilding::erase() {
    deleteLater();
    for(const auto t : mUnderBuilding) {
        t->setUnderBuilding(nullptr);
    }
    mUnderBuilding.clear();
    if(mTile) {
        mTile->setBuilding(nullptr);
        mTile = nullptr;
    }
}

void eBuilding::collapse() {
    const auto tiles = mUnderBuilding;
    auto& b = getBoard();
    const auto tp = type();
    const bool noRuins = tp == eBuildingType::oliveTree ||
                         tp == eBuildingType::vine ||
                         tp == eBuildingType::orangeTree;
    if(mTile && noRuins) {
        mTile->setOnFire(false);
    }
    erase();
    if(noRuins) {
        return;
    }
    for(const auto t : tiles) {
        const auto ruins = e::make_shared<eRuins>(b);
        t->setBuilding(ruins);
        t->setUnderBuilding(ruins.get());
        ruins->addUnderBuilding(t);
    }
}

void eBuilding::catchOnFire() {
    for(const auto t : mUnderBuilding) {
        t->setOnFire(true);
    }
}

bool eBuilding::spreadFire() {
    auto dirs = gExtractDirections(eMoveDirection::allDirections);
    std::random_shuffle(dirs.begin(), dirs.end());
    eTile* t = nullptr;
    for(const auto dir : dirs) {
        t = tileNeighbour(dir, [this](eTile* const tile) {
            const auto ub = tile->underBuilding();
            if(!ub) return false;
            if(ub == this) return false;
            const auto t = ub->type();
            if(t == eBuildingType::road) return false;
            if(t == eBuildingType::sheep) return false;
            if(t == eBuildingType::goat) return false;
            if(t == eBuildingType::ruins) return false;
            return true;
        });
        if(t) break;
    }
    if(t) {
        const auto ub = t->underBuilding();
        if(ub) {
            ub->catchOnFire();
            return true;
        }
    }
    return false;
}

bool eBuilding::isOnFire() {
    for(const auto t : mUnderBuilding) {
        if(t->onFire()) return true;
    }
    return false;
}

void eBuilding::setEnabled(const bool e) {
    mEnabled = e;
}

void eBuilding::setOverlayEnabledFunc(const std::function<bool()>& e) {
    mOverlayEnabled = e;
}
