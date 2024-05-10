#include "ebuilding.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "engine/etile.h"
#include "eruins.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "buildings/eaestheticsbuilding.h"

#include "ebuildingrenderer.h"

#include "fileIO/ebuildingrendererwriter.h"
#include "fileIO/ebuildingrendererreader.h"

#include "evectorhelpers.h"

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

eTextureSpace eBuilding::getTextureSpace(const int tx, const int ty,
                                         const eTileSize size) const {
    const SDL_Point p{tx, ty};
    const auto r = tileRect();
    if(!SDL_PointInRect(&p, &r)) return {nullptr};
    const auto tex = getTexture(size);
    return eTextureSpace{tex, true, r};
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

bool eBuilding::sWalkableBuilding(const eBuildingType t) {
    if(t == eBuildingType::none) return true;
    if(t == eBuildingType::road) return true;
    if(t == eBuildingType::ruins) return true;
    if(t == eBuildingType::vine) return true;
    if(t == eBuildingType::park) return true;
    if(t == eBuildingType::oliveTree) return true;
    if(t == eBuildingType::orangeTree) return true;
    if(t == eBuildingType::sheep) return true;
    if(t == eBuildingType::goat) return true;
    if(t == eBuildingType::templeTile) return true;
    if(t == eBuildingType::palaceTile) return true;
    if(t == eBuildingType::godMonumentTile) return true;
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(t);
    if(bi >= min && bi <= max) return true;
    return false;
}

bool eBuilding::sFlatBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r ||
           bt == eBuildingType::none ||
           bt == eBuildingType::road ||
           bt == eBuildingType::templeTile ||
           bt == eBuildingType::vine ||
           bt == eBuildingType::park ||
           bt == eBuildingType::oliveTree ||
           bt == eBuildingType::orangeTree ||
           bt == eBuildingType::sheep ||
           bt == eBuildingType::goat ||
           bt == eBuildingType::ruins ||
           bt == eBuildingType::palaceTile ||
           bt == eBuildingType::godMonumentTile;
}

bool eBuilding::sSanctuaryBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeAltar);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r;
}

bool eBuilding::sAestheticsBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::park);
    const int max = static_cast<int>(eBuildingType::stoneCircle);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r;
}

bool eBuilding::sFlammable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::park) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::tower) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    return true;
}

bool eBuilding::sTimedBuilding(const eBuildingType bt) {
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::templeTile) return false;
    if(bt == eBuildingType::templeMonument) return false;
    if(bt == eBuildingType::templeStatue) return false;
    if(bt == eBuildingType::park) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    return true;
}

bool eBuilding::sBlessable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::park) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::tower) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    if(sAestheticsBuilding(bt)) return false;
    return true;
}

bool eBuilding::sAttackable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::park) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    return true;
}

std::string eBuilding::sNameForBuilding(eBuilding* const b) {
    if(!b) return "";
    switch(b->type()) {
    case eBuildingType::road:
        return "road";

    case eBuildingType::commonHouse:
        return "common_housing";
    case eBuildingType::eliteHousing:
        return "elite_housing";

    case eBuildingType::fountain:
        return "fountain";
    case eBuildingType::hospital:
        return "infirmary";
    case eBuildingType::maintenanceOffice:
        return "maintenance_office";
    case eBuildingType::watchPost:
        return "watchpost";

    case eBuildingType::palace:
        return "palace";
    case eBuildingType::taxOffice:
        return "tax_office";
    case eBuildingType::bridge:
        return "water_crossing";

    case eBuildingType::gymnasium:
        return "gymnasium";
    case eBuildingType::stadium:
        return "stadium";

    case eBuildingType::wheatFarm:
        return "wheat_farm";
    case eBuildingType::carrotsFarm:
        return "carrot_farm";
    case eBuildingType::onionsFarm:
        return "onion_farm";

    case eBuildingType::vine:
        return "vine";
    case eBuildingType::oliveTree:
        return "olive_tree";
    case eBuildingType::orangeTree:
        return "orange_tree";
    case eBuildingType::orangeTendersLodge:
        return "orange_tenders_lodge";
    case eBuildingType::growersLodge:
        return "growers_lodge";

    case eBuildingType::dairy:
        return "dairy";
    case eBuildingType::goat:
        return "goat";
    case eBuildingType::cardingShed:
        return "carding_shed";
    case eBuildingType::sheep:
        return "sheep";

    case eBuildingType::fishery:
        return "fishery";
    case eBuildingType::urchinQuay:
        return "urchin_quay";
    case eBuildingType::huntingLodge:
        return "hunting_lodge";

    case eBuildingType::mint:
        return "mint";
    case eBuildingType::foundry:
        return "foundry";
    case eBuildingType::timberMill:
        return "timber_mill";
    case eBuildingType::masonryShop:
        return "masonry_shop";

    case eBuildingType::winery:
        return "winery";
    case eBuildingType::olivePress:
        return "olive_press";
    case eBuildingType::sculptureStudio:
        return "sculpture_studio";

    case eBuildingType::commonAgora:
        return "common_agora";
    case eBuildingType::grandAgora:
        return "grand_agora";
    case eBuildingType::foodVendor:
        return "food_vendor";
    case eBuildingType::fleeceVendor:
        return "fleece_vendor";
    case eBuildingType::oilVendor:
        return "oil_vendor";
    case eBuildingType::wineVendor:
        return "wine_vendor";
    case eBuildingType::armsVendor:
        return "arms_vendor";
    case eBuildingType::horseTrainer:
        return "horse_trainer";

    case eBuildingType::podium:
        return "podium";
    case eBuildingType::college:
        return "college";
    case eBuildingType::theater:
        return "theater";
    case eBuildingType::dramaSchool:
        return "drama_school";

    case eBuildingType::templeZeus:
        return "zeus_stronghold";
    case eBuildingType::templePoseidon:
        return "promontery_of_poseidon";
    case eBuildingType::templeHades:
        return "gates_of_hades";
    case eBuildingType::templeHera:
        return "orchard_of_hera";
    case eBuildingType::templeDemeter:
        return "garden_of_demeter";
    case eBuildingType::templeAthena:
        return "arbor_of_athena";
    case eBuildingType::templeArtemis:
        return "artemis_menagerie";
    case eBuildingType::templeApollo:
        return "oracle_of_apollo";
    case eBuildingType::templeAtlas:
        return "pillar_of_atlas";
    case eBuildingType::templeAres:
        return "ares_fortress";
    case eBuildingType::templeHephaestus:
        return "forge_of_hephaestus";
    case eBuildingType::templeAphrodite:
        return "aphrodites_heaven";
    case eBuildingType::templeHermes:
        return "hermes_refuge";
    case eBuildingType::templeDionysus:
        return "grove_of_dionysus";

    case eBuildingType::wall:
        return "wall";
    case eBuildingType::tower:
        return "tower";
    case eBuildingType::gatehouse:
        return "gatehouse";

    case eBuildingType::armory:
        return "armory";
    case eBuildingType::horseRanch:
        return "horse_ranch";

    case eBuildingType::park:
        return "park";
    case eBuildingType::waterPark:
        return "water_park";
    case eBuildingType::doricColumn:
        return "doric_column";
    case eBuildingType::ionicColumn:
        return "ionic_column";
    case eBuildingType::corinthianColumn:
        return "corinthian_column";
    case eBuildingType::avenue:
        return "avenue";

    case eBuildingType::bench:
        return "bench";
    case eBuildingType::birdBath:
        return "bird_bath";
    case eBuildingType::shortObelisk:
        return "short_obelisk";
    case eBuildingType::tallObelisk:
        return "tall_obelisk";
    case eBuildingType::flowerGarden:
        return "flower_garden";
    case eBuildingType::gazebo:
        return "gazebo";
    case eBuildingType::shellGarden:
        return "shell_garden";
    case eBuildingType::sundial:
        return "sundial";
    case eBuildingType::hedgeMaze:
        return "hedge_maze";
    case eBuildingType::dolphinSculpture:
        return "dolphin_sculpture";
    case eBuildingType::spring:
        return "spring";
    case eBuildingType::topiary:
        return "topiary";
    case eBuildingType::fishPond:
        return "fish_pond";
    case eBuildingType::baths:
        return "baths";
    case eBuildingType::stoneCircle:
        return "stone_circle";

    case eBuildingType::commemorative:
        const auto c = static_cast<eCommemorative*>(b);
        const int id = c->id();
        if(id == 0) return "population_monument";
        else if(id == 1) return "victory_monument";
        else if(id == 2) return "colony_monument";
        else if(id == 3) return "athlete_monument";
        else if(id == 4) return "conquest_monument";
        else if(id == 5) return "happiness_monument";
        else if(id == 6) return "";
        else if(id == 7) return "";
        else if(id == 8) return "scholar_monument";
        break;

    }
    return "";
}

eTile* eBuilding::tileNeighbour(const eMoveDirection o,
                                const eTileValidator& v) const {
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

std::vector<eTile*> eBuilding::surroundingRoad(const bool diagonal) const {
    const auto& board = getBoard();
    const auto tr = tileRect();
    std::vector<eTile*> r;
    const int xMin = tr.x + (diagonal ? -1 : 0);
    const int xMax = tr.x + tr.w + (diagonal ? 1 : 0);
    for(int x = xMin; x < xMax; x++) {
        const auto t = board.tile(x, tr.y - 1);
        if(t && t->hasRoad()) r.push_back(t);
        const auto tt = board.tile(x, tr.y + tr.h);
        if(tt && tt->hasRoad()) r.push_back(tt);
    }
    for(int y = tr.y; y < tr.y + tr.h; y++) {
        const auto t = board.tile(tr.x - 1, y);
        if(t && t->hasRoad()) r.push_back(t);
        const auto tt = board.tile(tr.x + tr.w, y);
        if(tt && tt->hasRoad()) r.push_back(tt);
    }
    return r;
}

void eBuilding::incTime(const int by) {
    if(dead()) return;
    auto& b = getBoard();
    mTime += by;
    mTextureTime++;
    if(mBlessTime > 0) {
        mBlessTime -= by;
        if(mBlessTime <= 0) {
            mBlessed = 0;
        }
    }
    if(isOnFire()) {
        if(rand() % (10000/by) == 0) {
            if(rand() % 3) {
                const bool r = spreadFire();
                eEventData ed;
                ed.fTile = centerTile();
                if(r) b.event(eEvent::fire, ed);
            } else if(mType == eBuildingType::ruins) {
                setOnFire(false);
            } else {
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::collapse, ed);
                collapse();
                return;
            }
        }
    } else if(rand() % (2000/by) == 0) {
        bool lower = true;
        if(const auto sh = dynamic_cast<eSmallHouse*>(this)) {
            if(sh->people() <= 0) lower = false;
        } else if(const auto eh = dynamic_cast<eEliteHousing*>(this)) {
            if(eh->people() <= 0) lower = false;
        }
        if(lower) {
            mMaintance = std::max(0, mMaintance - 1);
        }
    } else {
        const int m4 = 10 + pow(mMaintance, 4);
        const auto diff = b.difficulty();
        const int fireRisk = eDifficultyHelpers::fireRisk(diff, mType);
        if(fireRisk && by) {
            const int firePeriod = m4/(by*fireRisk);
            if(firePeriod && rand() % firePeriod == 0) {
                setOnFire(true);
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::fire, ed);
            }
        }
        const int damageRisk = eDifficultyHelpers::damageRisk(diff, mType);
        if(damageRisk && by) {
            const int damagePeriod = m4/(by*damageRisk);
            if(damagePeriod && rand() % damagePeriod == 0) {
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::collapse, ed);
                collapse();
                return;
            }
        }
    }
    timeChanged(by);
}

void eBuilding::addUnderBuilding(eTile* const t) {
    mUnderBuilding.push_back(t);
}

void eBuilding::erase() {
    deleteLater();
    for(const auto t : mUnderBuilding) {
        t->setUnderBuilding(nullptr);
        t->setBuilding(nullptr);
    }
    mUnderBuilding.clear();
}

void eBuilding::collapse() {
    const auto tiles = mUnderBuilding;
    auto& b = getBoard();
    const auto tp = type();
    const bool noRuins = tp == eBuildingType::oliveTree ||
                         tp == eBuildingType::vine ||
                         tp == eBuildingType::orangeTree;
    const bool onFire = mOnFire;
    setOnFire(false);
    erase();
    if(noRuins) return;
    for(const auto t : tiles) {
        const auto ruins = e::make_shared<eRuins>(b);
        ruins->setOnFire(onFire);
        const auto renderer = e::make_shared<eBuildingRenderer>(ruins);
        t->setBuilding(renderer);
        ruins->setCenterTile(t);
        t->setUnderBuilding(ruins);
        ruins->addUnderBuilding(t);
        ruins->setTileRect({t->x(), t->y(), 1, 1});
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
            if(!sFlammable(t)) return false;
            return true;
        });
        if(t) break;
    }
    if(t) {
        const auto ub = t->underBuilding();
        if(ub) {
            ub->setOnFire(true);
            return true;
        }
    }
    return false;
}

bool eBuilding::isOnFire() {
    return mOnFire;
}

void eBuilding::setOnFire(const bool f) {
    mOnFire = f;
}

void eBuilding::setCenterTile(eTile* const ct) {
    mCenterTile = ct;
}

eTile* eBuilding::centerTile() const {
    return mCenterTile;
}

void eBuilding::addRenderer(eBuildingRenderer* const r) {
    mRenderers.push_back(r);
}

void eBuilding::removeRenderer(eBuildingRenderer* const r) {
    eVectorHelpers::remove(mRenderers, r);
}

void eBuilding::setEnabled(const bool e) {
    mEnabled = e;
}

void eBuilding::setOverlayEnabledFunc(const std::function<bool()>& e) {
    mOverlayEnabled = e;
}

bool eBuilding::defend(const double a) {
    if(mHp <= 0) return true;
    mHp -= a;
    if(mHp <= 0) {
        collapse();
        return true;
    } else {
        return false;
    }
}

bool eBuilding::dead() const {
    return mHp <= 0;
}

std::vector<eTile*> eBuilding::neighbours() const {
    std::vector<eTile*> result;

    const int left = mTileRect.x - 1;
    const int right = mTileRect.x + mTileRect.w + 1;
    const int top = mTileRect.y - 1;
    const int bottom = mTileRect.y + mTileRect.h + 1;

    const auto& brd = getBoard();

    int i;
    int j;

    const auto iiter = [&]() {
        for(i = left + 1; i <= right - 1; i++) {
            const auto t = brd.tile(i, j);
            if(!t) continue;
            result.push_back(t);
        }
    };

    const auto jiter = [&]() {
        for(j = top + 1; j <= bottom - 1; j++) {
            const auto t = brd.tile(i, j);
            if(!t) continue;
            result.push_back(t);
        }
    };

    j = top;
    iiter();
    j = bottom;
    iiter();

    i = left;
    jiter();
    i = right;
    jiter();

    return result;
}

void eBuilding::setBlessed(const double b) {
    mBlessTime = 30000;
    mBlessed = b;
}

void eBuilding::read(eReadStream& src) {
    src >> mIOID;
    src >> mTileRect;

    auto& board = getBoard();

    int ntiles;
    src >> ntiles;
    for(int i = 0; i < ntiles; i++) {
        const auto tile = src.readTile(board);
        mUnderBuilding.push_back(tile);
        bool setUnder;
        src >> setUnder;
        if(setUnder) {
            tile->setUnderBuilding(ref<eBuilding>());
        }
    }

    int nrend;
    src >> nrend;
    for(int i = 0; i < nrend; i++) {
        eBuildingRendererType type;
        src >> type;
        const auto r = eBuildingRendererReader::sRead(ref<eBuilding>(), type, src);
        const auto tile = src.readTile(board);
        tile->setBuilding(r);
    }

    mCenterTile = src.readTile(board);

    src >> mSeed;
    src >> mPlayerId;
    src >> mHp;
    src >> mMaintance;
    src >> mEnabled;
    src >> mBlessed;
    src >> mBlessTime;
    src >> mOnFire;
}

void eBuilding::write(eWriteStream& dst) const {
    dst << mIOID;
    dst << mTileRect;

    dst << mUnderBuilding.size();
    for(const auto t : mUnderBuilding) {
        dst.writeTile(t);
        dst << (t->underBuilding() == this);
    }

    dst << mRenderers.size();
    for(const auto r : mRenderers) {
        dst << r->type();
        eBuildingRendererWriter::sWrite(r, dst);
        dst.writeTile(r->tile());
    }

    dst.writeTile(mCenterTile);

    dst << mSeed;
    dst << mPlayerId;
    dst << mHp;
    dst << mMaintance;
    dst << mEnabled;
    dst << mBlessed;
    dst << mBlessTime;
    dst << mOnFire;
}

void eBuilding::setIOID(const int id) {
    mIOID = id;
}
