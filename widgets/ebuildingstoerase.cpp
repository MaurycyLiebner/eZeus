#include "ebuildingstoerase.h"

#include "buildings/ebuilding.h"
#include "buildings/eagoraspace.h"
#include "buildings/evendor.h"
#include "buildings/eroad.h"
#include "buildings/eagorabase.h"
#include "buildings/epalacetile.h"
#include "buildings/epalace.h"
#include "buildings/epier.h"
#include "buildings/sanctuaries/esanctbuilding.h"
#include "buildings/sanctuaries/esanctuary.h"
#include "buildings/eaestheticsbuilding.h"
#include "engine/etile.h"

#include "characters/ehomeless.h"
#include "characters/actions/esettleraction.h"
#include "characters/actions/ekillcharacterfinishfail.h"
#include "buildings/ehousebase.h"

#include <algorithm>

#include "evectorhelpers.h"

bool isImportant(eBuilding* const b) {
    const auto t = b->type();
    if(t == eBuildingType::palace) return true;
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(t);
    if(bi >= min && bi <= max) return true;
    return false;
}

bool isNonEmptyAgora(eBuilding* const b) {
    const auto t = b->type();
    const auto isa = t == eBuildingType::commonAgora ||
                     t == eBuildingType::grandAgora;
    if(!isa) return false;
    const auto a = static_cast<eAgoraBase*>(b);
    return a->hasVendors();
}

void eBuildingsToErase::addBuilding(eBuilding* const b) {
    eBuilding* bb = b;
    const auto t = b->type();
    if(t == eBuildingType::agoraSpace) {
        const auto as = static_cast<eAgoraSpace*>(b);
        bb = as->agora();
    } else if(t == eBuildingType::road) {
        const auto r = static_cast<eRoad*>(b);
        const auto a = r->underAgora();
        if(a) bb = a;
    } else if(t == eBuildingType::palaceTile) {
        const auto pt = static_cast<ePalaceTile*>(b);
        const auto p = pt->palace();
        if(p) bb = p;
    } else if(t == eBuildingType::godMonumentTile) {
        const auto pt = static_cast<eGodMonumentTile*>(b);
        const auto p = pt->monument();
        if(p) bb = p;
    } else if(t == eBuildingType::pier) {
        const auto pt = static_cast<ePier*>(b);
        const auto p = pt->tradePost();
        if(p) bb = p;
    } else if(const auto sb = dynamic_cast<eSanctBuilding*>(b)) {
        const auto s = sb->sanctuary();
        if(s) bb = s;
    }
    if(isNonEmptyAgora(bb)) {
        mAgoBs.insert(bb);
    } else if(isImportant(bb)) {
        mImpBs.insert(bb);
    } else {
        mBs.insert(bb);
    }
}

void eBuildingsToErase::erase(eBuilding* const b) {
    switch(b->type()) {
    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::horseTrainer: {
        const auto v = static_cast<eVendor*>(b);
        v->deleteLater();
        const auto a = v->agora();
        a->setBuilding(v, nullptr);
        a->fillSpaces();
    } break;
    case eBuildingType::eliteHousing:
    case eBuildingType::commonHouse: {
        const auto hb = static_cast<eHouseBase*>(b);
        const int people = hb->people();
        if(people > 0) {
            auto& board = b->getBoard();
            const auto tile = b->centerTile();
            const auto h = e::make_shared<eHomeless>(board);
            h->changeTile(tile);
            const auto fa = std::make_shared<eKillCharacterFinishFail>(board);
            const auto a = e::make_shared<eSettlerAction>(h.get());
            a->setNumberPeople(people);
            a->setFailAction(fa);
            a->setFinishAction(fa);
            a->setDeleteFailAction(fa);
            h->setAction(a);
        }
        b->erase();
    } break;
    default:
        b->erase();
    }
}

int eBuildingsToErase::erase(const bool important) {
    int total = 0;
    for(const auto b : mBs) {
        erase(b);
    }
    total += mBs.size();
    mBs.clear();
    if(important) {
        for(const auto b : mImpBs) {
            erase(b);
        }
        total += mImpBs.size();
        mImpBs.clear();
        for(const auto b : mAgoBs) {
            erase(b);
        }
        total += mAgoBs.size();
        mAgoBs.clear();
    }
    return total;
}

bool eBuildingsToErase::hasImportantBuildings() const {
    return !mImpBs.empty();
}

bool eBuildingsToErase::hasNonEmptyAgoras() const {
    return !mAgoBs.empty();
}
