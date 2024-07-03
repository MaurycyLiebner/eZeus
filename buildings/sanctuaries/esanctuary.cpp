#include "esanctuary.h"

#include "characters/ecarttransporter.h"
#include "engine/egameboard.h"
#include "characters/gods/egod.h"
#include "characters/actions/egodworshippedaction.h"
#include "etilehelper.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "gameEvents/eplayerconquesteventbase.h"

#include "characters/actions/godHelp/eaphroditehelpaction.h"
#include "characters/actions/godHelp/eapollohelpaction.h"
#include "characters/actions/godHelp/eareshelpaction.h"
#include "characters/actions/godHelp/eartemishelpaction.h"
#include "characters/actions/godHelp/eathenahelpaction.h"
#include "characters/actions/godHelp/eatlashelpaction.h"
#include "characters/actions/godHelp/edemeterhelpaction.h"
#include "characters/actions/godHelp/edionysushelpaction.h"
#include "characters/actions/godHelp/ehadeshelpaction.h"
#include "characters/actions/godHelp/eherahelpaction.h"
#include "characters/actions/godHelp/ehephaestushelpaction.h"
#include "characters/actions/godHelp/ehermeshelpaction.h"
#include "characters/actions/godHelp/eposeidonhelpaction.h"
#include "characters/actions/godHelp/ezeushelpaction.h"

#include "buildings/eresourcebuilding.h"
#include "buildings/eplaceholder.h"

#include "eartemissanctuary.h"
#include "ehephaestussanctuary.h"
#include "ezeussanctuary.h"

eSanctuary::eSanctuary(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees) {
    eGameTextures::loadSanctuary();
    switch(godType()) {
    case eGodType::aphrodite:
        eGameTextures::loadAphroditeMonuments();
        break;
    case eGodType::apollo:
        eGameTextures::loadApolloMonuments();
        break;
    case eGodType::ares:
        eGameTextures::loadAresMonuments();
        break;
    case eGodType::artemis:
        eGameTextures::loadArtemisMonuments();
        break;
    case eGodType::athena:
        eGameTextures::loadAthenaMonuments();
        break;
    case eGodType::atlas:
        eGameTextures::loadAtlasMonuments();
        break;
    case eGodType::demeter:
        eGameTextures::loadDemeterMonuments();
        break;
    case eGodType::dionysus:
        eGameTextures::loadDionysusMonuments();
        break;
    case eGodType::hades:
        eGameTextures::loadHadesMonuments();
        break;
    case eGodType::hephaestus:
        eGameTextures::loadHephaestusMonuments();
        break;
    case eGodType::hera:
        eGameTextures::loadHeraMonuments();
        break;
    case eGodType::hermes:
        eGameTextures::loadHermesMonuments();
        break;
    case eGodType::poseidon:
        eGameTextures::loadPoseidonMonuments();
        break;
    case eGodType::zeus:
        eGameTextures::loadZeusMonuments();
        break;
    }
    board.registerSanctuary(this);
}

eSanctuary::~eSanctuary() {
    if(mCart) mCart->kill();
    auto& board = getBoard();
    board.destroyed(type());
    board.unregisterSanctuary(this);
}

void eSanctuary::erase() {
    const auto& brd = getBoard();
    const auto rect = tileRect();
    for(int x = rect.x; x < rect.x + rect.w; x++) {
        for(int y = rect.y; y < rect.y + rect.h; y++) {
            const auto tile = brd.tile(x, y);
            tile->setAltitude(mAltitude);
            tile->setWalkableElev(false);
            const auto ub = tile->underBuilding();
            if(ub && ub != this && !dynamic_cast<eSanctBuilding*>(ub)) {
                ub->erase();
            }
            const auto t = tile->terrain();
            const bool r = static_cast<bool>(t & eTerrain::stones);
            if(r) tile->setTerrain(eTerrain::dry);
        }
    }
    for(const auto& e : mElements) {
        e->eBuilding::erase();
    }
    for(const auto s : mSpecialTiles) {
        const auto ub = s->underBuilding();
        if(!ub) continue;
        const auto ubt = ub->type();
        switch(ubt) {
        case eBuildingType::placeholder: {
            const auto p = static_cast<ePlaceholder*>(ub);
            p->sanctuaryErase();
        } break;
        case eBuildingType::oliveTree:
        case eBuildingType::vine:
        case eBuildingType::orangeTree: {
            const auto r = static_cast<eResourceBuilding*>(ub);
            r->sanctuaryErase();
        } break;
        default:
            break;
        }
    }
    eBuilding::erase();
}

eSanctCost eSanctuary::cost() const {
    eSanctCost c{0, 0, 0};
    for(const auto& e : mElements) {
        c += e->cost();
    }
    return c;
}

void eSanctuary::useResources(const eSanctCost& r) {
    mStored.fMarble -= r.fMarble;
    mStored.fWood -= r.fWood;
    mStored.fSculpture -= r.fSculpture;

    mUsed.fMarble += r.fMarble;
    mUsed.fWood += r.fWood;
    mUsed.fSculpture += r.fSculpture;
}

eGodType eSanctuary::godType() const {
    const auto bt = type();
    switch(bt) {
    case eBuildingType::templeAphrodite: return eGodType::aphrodite;
    case eBuildingType::templeApollo: return eGodType::apollo;
    case eBuildingType::templeAres: return eGodType::ares;
    case eBuildingType::templeArtemis: return eGodType::artemis;
    case eBuildingType::templeAthena: return eGodType::athena;
    case eBuildingType::templeAtlas: return eGodType::atlas;
    case eBuildingType::templeDemeter: return eGodType::demeter;
    case eBuildingType::templeDionysus: return eGodType::dionysus;
    case eBuildingType::templeHades: return eGodType::hades;
    case eBuildingType::templeHephaestus: return eGodType::hephaestus;
    case eBuildingType::templeHera: return eGodType::hera;
    case eBuildingType::templeHermes: return eGodType::hermes;
    case eBuildingType::templePoseidon: return eGodType::poseidon;
    case eBuildingType::templeZeus: return eGodType::zeus;
    default: return eGodType::aphrodite;
    }
}

eGod* eSanctuary::spawnGod() {
    auto& board = getBoard();
    const auto c = eGod::sCreateGod(godType(), board);
    mGod = c.get();
    const auto ct = centerTile();
    const int tx = ct->x();
    const int ty = ct->y();
    const auto cr = eTileHelper::closestRoad(tx, ty, board);
    if(!cr) return nullptr;
    mGod->changeTile(cr);
    return c.get();
}

void eSanctuary::spawnPatrolingGod() {
    const auto c = spawnGod();
    if(!c) return;
    const auto ha = e::make_shared<eGodWorshippedAction>(c);
    mGod->setAction(ha);
    mSpawnWait = 5000;
}

void eSanctuary::buildingProgressed() {
    const bool f = finished();
    if(f) {
        auto& board = getBoard();
        const auto g = godType();
        for(const auto s : mSpecialTiles) {
            const auto ub = s->underBuilding();
            if(ub) ub->erase();
            const auto build = [&](const eResourceBuildingType type) {
                const auto b = e::make_shared<eResourceBuilding>(
                            board, type);
                b->setSanctuary(true);
                b->setCenterTile(s);
                b->setTileRect({s->x(), s->y(), 1, 1});
                s->setUnderBuilding(b);
                b->addUnderBuilding(s);
            };
            switch(g) {
            case eGodType::hephaestus:
                s->setTerrain(eTerrain::copper);
                break;
            case eGodType::hades:
                s->setTerrain(eTerrain::silver);
                break;
            case eGodType::athena:
                build(eResourceBuildingType::oliveTree);
                break;
            case eGodType::dionysus:
                build(eResourceBuildingType::vine);
                break;
            case eGodType::hera:
                build(eResourceBuildingType::orangeTree);
                break;
            default:
                break;
            }
        }

        eEventData ed;
        ed.fGod = g;
        board.event(eEvent::sanctuaryComplete, ed);
    }
}

void eSanctuary::godComeback() {
    mGodAbroad = false;
}

void eSanctuary::setConstructionHalted(const bool h) {
    mHaltConstruction = h;
}

stdsptr<eSanctuary> eSanctuary::sCreate(
        const eBuildingType type,
        const int sw, const int sh,
        eGameBoard& board) {
    switch(type) {
    case eBuildingType::templeAphrodite:
        return e::make_shared<eAphroditeSanctuary>(sw, sh, board);
    case eBuildingType::templeApollo:
        return e::make_shared<eApolloSanctuary>(sw, sh, board);
    case eBuildingType::templeAres:
        return e::make_shared<eAresSanctuary>(sw, sh, board);
    case eBuildingType::templeArtemis:
        return e::make_shared<eArtemisSanctuary>(sw, sh, board);
    case eBuildingType::templeAthena:
        return e::make_shared<eAthenaSanctuary>(sw, sh, board);
    case eBuildingType::templeAtlas:
        return e::make_shared<eAtlasSanctuary>(sw, sh, board);
    case eBuildingType::templeDemeter:
        return e::make_shared<eDemeterSanctuary>(sw, sh, board);
    case eBuildingType::templeDionysus:
        return e::make_shared<eDionysusSanctuary>(sw, sh, board);
    case eBuildingType::templeHades:
        return e::make_shared<eHadesSanctuary>(sw, sh, board);
    case eBuildingType::templeHephaestus:
        return e::make_shared<eHephaestusSanctuary>(sw, sh, board);
    case eBuildingType::templeHera:
        return e::make_shared<eHeraSanctuary>(sw, sh, board);
    case eBuildingType::templeHermes:
        return e::make_shared<eHermesSanctuary>(sw, sh, board);
    case eBuildingType::templePoseidon:
        return e::make_shared<ePoseidonSanctuary>(sw, sh, board);
    case eBuildingType::templeZeus:
        return e::make_shared<eZeusSanctuary>(sw, sh, board);
    default:
        return nullptr;
    }
}

void eSanctuary::timeChanged(const int by) {
    mHelpTimer += by;
    if(!mCart) mCart = spawnCart(eCartActionTypeSupport::take);
    eEmployingBuilding::timeChanged(by);

    if(!mGod && !mGodAbroad && finished()) {
        mSpawnWait -= by;
        if(mSpawnWait <= 0) {
            spawnPatrolingGod();
        }
    }

    if(mAskedForHelp) {
        const int checkInterval = 1000;
        mCheckHelpNeeded += by;
        if(mCheckHelpNeeded > checkInterval) {
            mCheckHelpNeeded -= checkInterval;
            eHelpDenialReason r;
            askForHelp(r);
        }
    }
}

int eSanctuary::spaceLeft(const eResourceType type) const {
    const auto c = cost();
    if(type == eResourceType::marble) {
        return c.fMarble - mStored.fMarble - mUsed.fMarble;
    } else if(type == eResourceType::wood) {
        return c.fWood - mStored.fWood - mUsed.fWood;
    } else if(type == eResourceType::sculpture) {
        return c.fSculpture - mStored.fSculpture - mUsed.fSculpture;
    }
    return 0;
}

int eSanctuary::add(const eResourceType type, const int count) {
    const int space = spaceLeft(type);
    const int add = std::min(count, space);
    if(type == eResourceType::marble) {
        mStored.fMarble += add;
    } else if(type == eResourceType::wood) {
        mStored.fWood += add;
    } else if(type == eResourceType::sculpture) {
        mStored.fSculpture += add;
    }
    return add;
}


std::vector<eCartTask> eSanctuary::cartTasks() const {
    std::vector<eCartTask> tasks;

    const int m = spaceLeft(eResourceType::marble);
    const int w = spaceLeft(eResourceType::wood);
    const int s = spaceLeft(eResourceType::sculpture);

    if(m) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::marble;
        task.fMaxCount = m;
        tasks.push_back(task);
    }

    if(w) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wood;
        task.fMaxCount = w;
        tasks.push_back(task);
    }

    if(s) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::sculpture;
        task.fMaxCount = s;
        tasks.push_back(task);
    }

    return tasks;
}

void eSanctuary::registerElement(const stdsptr<eSanctBuilding>& e) {
    mElements.push_back(e);
}

int eSanctuary::progress() const {
    double did = 0;
    double max = 0;
    for(const auto& e : mElements) {
        did += e->progress();
        max += e->maxProgress();
    }
    return std::round(100*did/max);
}

bool eSanctuary::finished() const {
    return progress() >= 100;
}

void eSanctuary::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src >> mRotated;

    src >> mHaltConstruction;

    src >> mStored.fMarble;
    src >> mStored.fSculpture;
    src >> mStored.fWood;

    src >> mUsed.fMarble;
    src >> mUsed.fSculpture;
    src >> mUsed.fWood;

    src >> mAltitude;

    auto& board = getBoard();

    src.readCharacter(&board, [this](eCharacter* const c) {
        mCart = static_cast<eCartTransporter*>(c);
    });
    src.readCharacter(&board, [this](eCharacter* const c) {
        mGod = static_cast<eGod*>(c);
    });
    src >> mSpawnWait;
    src >> mGodAbroad;

    src >> mAskedForHelp;
    src >> mCheckHelpNeeded;
    src >> mHelpTimer;

    int nw;
    src >> nw;
    for(int i = 0; i < nw; i++) {
        const auto t = src.readTile(board);
        mWarriorTiles.push_back(t);
    }

    int ns;
    src >> ns;
    for(int i = 0; i < ns; i++) {
        const auto t = src.readTile(board);
        mSpecialTiles.push_back(t);
    }
}

void eSanctuary::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst << mRotated;

    dst << mHaltConstruction;

    dst << mStored.fMarble;
    dst << mStored.fSculpture;
    dst << mStored.fWood;

    dst << mUsed.fMarble;
    dst << mUsed.fSculpture;
    dst << mUsed.fWood;

    dst << mAltitude;

    dst.writeCharacter(mCart);
    dst.writeCharacter(mGod);
    dst << mSpawnWait;
    dst << mGodAbroad;

    dst << mAskedForHelp;
    dst << mCheckHelpNeeded;
    dst << mHelpTimer;

    dst << mWarriorTiles.size();
    for(const auto t : mWarriorTiles) {
        dst.writeTile(t);
    }

    dst << mSpecialTiles.size();
    for(const auto t : mSpecialTiles) {
        dst.writeTile(t);
    }
}

std::vector<eTile*> eSanctuary::warriorTiles() const {
    return mWarriorTiles;
}

void eSanctuary::addWarriorTile(eTile* const t) {
    mWarriorTiles.push_back(t);
}

void eSanctuary::addSpecialTile(eTile* const t) {
    mSpecialTiles.push_back(t);
}

bool eSanctuary::askForHelp(eHelpDenialReason& reason) {
    if(mGodAbroad || mHelpTimer < 250000) {
        reason = eHelpDenialReason::tooSoon;
        return false;
    }
    auto& board = getBoard();
    const auto type = godType();
    bool r = false;
    switch(type) {
    case eGodType::aphrodite: {
        r = eAphroditeHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::apollo: {
        r = eApolloHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::ares: {
        r = eAresHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::artemis: {
        r = eArtemisHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::athena: {
        r = eAthenaHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::atlas: {
        r = eAtlasHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::demeter: {
        r = eDemeterHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::dionysus: {
        r = eDionysusHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::hades: {
        r = eHadesHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::hera: {
        r = eHeraHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::hephaestus: {
        r = eHephaestusHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::hermes: {
        r = eHermesHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::poseidon: {
        r = ePoseidonHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::zeus: {
        r = eZeusHelpAction::sHelpNeeded(board);
    } break;
    }
    if(!r) {
        mAskedForHelp = true;
        reason = eHelpDenialReason::noTarget;
        return false;
    }
    stdsptr<eCharacterAction> a;
    eCharacter* c = nullptr;
    if(const auto g = god()) {
        const auto tile = g->tile();
        if(tile) {
            c = g;
        } else {
            c = spawnGod();
        }
    } else {
        c = spawnGod();
    }
    if(!c) {
        reason = eHelpDenialReason::error;
        return false;
    }
    switch(type) {
    case eGodType::aphrodite:
        a = e::make_shared<eAphroditeHelpAction>(c);
        break;
    case eGodType::apollo:
        a = e::make_shared<eApolloHelpAction>(c);
        break;
    case eGodType::ares:
        a = e::make_shared<eAresHelpAction>(c);
        break;
    case eGodType::artemis:
        a = e::make_shared<eArtemisHelpAction>(c);
        break;
    case eGodType::athena:
        a = e::make_shared<eAthenaHelpAction>(c);
        break;
    case eGodType::atlas:
        a = e::make_shared<eAtlasHelpAction>(c);
        break;
    case eGodType::demeter:
        a = e::make_shared<eDemeterHelpAction>(c);
        break;
    case eGodType::dionysus:
        a = e::make_shared<eDionysusHelpAction>(c);
        break;
    case eGodType::hades:
        a = e::make_shared<eHadesHelpAction>(c);
        break;
    case eGodType::hera:
        a = e::make_shared<eHeraHelpAction>(c);
        break;
    case eGodType::hephaestus:
        a = e::make_shared<eHephaestusHelpAction>(c);
        break;
    case eGodType::hermes:
        a = e::make_shared<eHermesHelpAction>(c);
        break;
    case eGodType::poseidon:
        a = e::make_shared<ePoseidonHelpAction>(c);
        break;
    case eGodType::zeus:
        a = e::make_shared<eZeusHelpAction>(c);
        break;
    }
    if(!a) {
        reason = eHelpDenialReason::error;
        return false;
    }
    mHelpTimer = 0;
    mAskedForHelp = false;
    c->setAction(a);
    eEventData ed;
    ed.fGod = type;
    ed.fChar = c;
    ed.fTile = c->tile();
    board.event(eEvent::godHelp, ed);
    if(type == eGodType::ares) {
        const auto& cs = board.conquests();
        if(cs.empty()) return true;
        cs[0]->addAres();
        mGodAbroad = true;
    }
    return true;
}
