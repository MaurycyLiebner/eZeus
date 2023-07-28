#include "esanctuary.h"

#include "characters/ecarttransporter.h"
#include "engine/egameboard.h"
#include "characters/gods/egod.h"
#include "characters/actions/egodworshippedaction.h"
#include "etilehelper.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"

#include "characters/actions/godHelp/eartemishelpaction.h"
#include "characters/actions/godHelp/eathenahelpaction.h"
#include "characters/actions/godHelp/eatlashelpaction.h"
#include "characters/actions/godHelp/edemeterhelpaction.h"
#include "characters/actions/godHelp/edionysushelpaction.h"
#include "characters/actions/godHelp/ehadeshelpaction.h"
#include "characters/actions/godHelp/eherahelpaction.h"
#include "characters/actions/godHelp/eposeidonhelpaction.h"
#include "characters/actions/godHelp/ezeushelpaction.h"

eSanctuary::eSanctuary(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees) {
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
        eEventData ed;
        ed.fGod = godType();
        auto& board = getBoard();
        board.event(eEvent::sanctuaryComplete, ed);
    }
}

void eSanctuary::timeChanged(const int by) {
    mHelpTimer += by;
    if(!mCart) mCart = spawnCart(eCartActionTypeSupport::take);
    eEmployingBuilding::timeChanged(by);

    if(!mGod && finished()) {
        mSpawnWait -= by;
        if(mSpawnWait <= 0) {
            spawnPatrolingGod();
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

    src >> mStored.fMarble;
    src >> mStored.fSculpture;
    src >> mStored.fWood;

    src >> mUsed.fMarble;
    src >> mUsed.fSculpture;
    src >> mUsed.fWood;

    src >> mAltitude;

    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mCart = static_cast<eCartTransporter*>(c);
    });
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mGod = static_cast<eGod*>(c);
    });
    src >> mSpawnWait;

    src >> mHelpTimer;
}

void eSanctuary::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

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

    dst << mHelpTimer;
}

bool eSanctuary::askForHelp(eHelpDenialReason& reason) {
    if(mHelpTimer < 10000) {
        reason = eHelpDenialReason::tooSoon;
        return false;
    }
    auto& board = getBoard();
    const auto type = godType();
    bool r = false;
    switch(type) {
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
    case eGodType::poseidon: {
        r = ePoseidonHelpAction::sHelpNeeded(board);
    } break;
    case eGodType::zeus: {
        r = eZeusHelpAction::sHelpNeeded(board);
    } break;
    }
    if(!r) {
        reason = eHelpDenialReason::noTarget;
        return false;
    }
    stdsptr<eCharacterAction> a;
    eCharacter* c = nullptr;
    if(const auto g = god()) {
        c = g;
    } else {
        c = spawnGod();
    }
    if(!c) {
        reason = eHelpDenialReason::error;
        return false;
    }
    switch(type) {
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
    c->setAction(a);
    eEventData ed;
    ed.fGod = type;
    board.event(eEvent::godHelp, ed);
    return true;
}
