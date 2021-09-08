#include "ebuilding.h"

#include "engine/egameboard.h"
#include "engine/etile.h"

eBuilding::eBuilding(eGameBoard& board,
                     const eBuildingType type,
                     const int sw, const int sh) :
    mBoard(board),
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {
    mBoard.registerBuilding(this);
}

eBuilding::~eBuilding() {
    mBoard.unregisterBuilding(this);
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
    mTime += by;
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
    for(const auto t : mUnderBuilding) {
        t->setUnderBuilding(nullptr);
    }
    mUnderBuilding.clear();
    if(mTile) {
        mTile->setBuilding(nullptr);
        mTile = nullptr;
    }
}

void eBuilding::setEnabled(const bool e) {
    mEnabled = e;
}

void eBuilding::setOverlayEnabledFunc(const std::function<bool()>& e) {
    mOverlayEnabled = e;
}

eAppeal eBuilding::appeal() const {
    switch(mType) {
    case eBuildingType::wheatFarm: return {-3, 3};
    case eBuildingType::carrotsFarm: return {-4, 3};
    case eBuildingType::onionsFarm: return {-2, 2};
    case eBuildingType::growersLodge: return {-3, 2};
    case eBuildingType::oliveTree:
    case eBuildingType::vine: return {1, 1};
    case eBuildingType::orangeTree: return {1, 2};
    case eBuildingType::cardingShed: return {-5, 3};
    case eBuildingType::dairy: return {-5, 3};
    case eBuildingType::urchinQuay:
    case eBuildingType::fishery: return {-15, 4};
    case eBuildingType::huntingLodge: return {-6, 4};
    case eBuildingType::orangeTendersLodge: return {2, 2};

    case eBuildingType::timberMill: return {-5, 4};
    case eBuildingType::masonryShop: return {-6, 4};
    case eBuildingType::mint:
    case eBuildingType::foundry: return {-10, 6};
    case eBuildingType::sculptureStudio: return {-2, 2};
    case eBuildingType::olivePress: return {-4, 4};
    case eBuildingType::winery: return {4, 4};

    case eBuildingType::granary: return {-12, 4};
    case eBuildingType::warehouse: return {-2, 4};
    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::wineVendor: return {2, 2};
    case eBuildingType::horseTrainer: return {-2, 2};

    case eBuildingType::fountain: return {4, 4};
    case eBuildingType::hospital: return {-2, 4};
    case eBuildingType::maintenanceOffice: return {0, 0};
    case eBuildingType::watchPost: return {-2, 2};
    case eBuildingType::palace1:
    case eBuildingType::palace2: return {18, 6};
    case eBuildingType::taxOffice: return {-4, 2};

    case eBuildingType::college: return {-5, 2};
    case eBuildingType::podium: return {3, 3};
    case eBuildingType::gymnasium: return {0, 0};
    case eBuildingType::dramaSchool: return {0, 0};
    case eBuildingType::theater: return {6, 3};
    case eBuildingType::stadium1:
    case eBuildingType::stadium2: return {0, 0};

    case eBuildingType::doricColumn:
    case eBuildingType::ionicColumn:
    case eBuildingType::corinthianColumn: return {4, 3};
    case eBuildingType::park: return {3, 3};

    case eBuildingType::bench: return {2, 4};
    case eBuildingType::flowerGarden: return {8, 3};
    case eBuildingType::gazebo: return {6, 6};
    case eBuildingType::hedgeMaze: return {12, 4};
    case eBuildingType::fishPond: return {18, 6};

    case eBuildingType::waterPark: return {5, 4};

    case eBuildingType::birdBath: return {3, 3};
    case eBuildingType::shortObelisk: return {6, 2};
    case eBuildingType::tallObelisk: return {8, 2};
    case eBuildingType::shellGarden: return {5, 5};
    case eBuildingType::sundial: return {7, 4};
    case eBuildingType::dolphinSculpture: return {12, 4};
    case eBuildingType::spring: return {10, 5};
    case eBuildingType::topiary: return {15, 3};
    case eBuildingType::baths: return {15, 6};
    case eBuildingType::stoneCircle: return {24, 4};

    default: return {0, 0};
    }
}
