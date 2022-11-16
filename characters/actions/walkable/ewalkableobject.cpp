#include "ewalkableobject.h"

#include "buildings/ebuilding.h"

#include "erectwalkableobject.h"
#include "ehasresourcewalkableobject.h"

bool eWalkableObject::walkable(eTileBase* const t) const {
    switch(mType) {
    case eWalkableObjectType::ddefault:
        return t->walkable();
    case eWalkableObjectType::road:
        return t->hasRoad();
    case eWalkableObjectType::roadblock: {
        const bool hr = t->hasRoad();
        if(!hr) return false;
        return !t->hasRoadblock();
    }
    case eWalkableObjectType::terrain: {
        const auto terr = t->terrain() & eTerrain::walkable;
        return static_cast<bool>(terr);
    }
    case eWalkableObjectType::fertile: {
        const bool r = t->walkable();
        if(!r) return false;
        return t->terrain() == eTerrain::fertile;
    }
    case eWalkableObjectType::wall: {
        const auto checker = [](eTileBase* const t) {
            if(!t) return false;
            const auto ubt = t->underBuildingType();
            return ubt == eBuildingType::wall ||
                   ubt == eBuildingType::tower;
        };
        if(!checker(t)) return false;
        const auto bl = t->tileRel(0, 1);
        if(!checker(bl)) return false;
        const auto br = t->tileRel(1, 0);
        if(!checker(br)) return false;
        const auto b = t->tileRel(1, 1);
        if(!checker(b)) return false;
        return true;
    }
    case eWalkableObjectType::water: {
        const bool r = t->terrain() == eTerrain::water;
        if(!r) return false;
        return !t->isShoreTile();
    }
    case eWalkableObjectType::ranch: {
        const auto tt = t->underBuildingType();
        if(tt != eBuildingType::horseRanchEnclosure) return false;

        const auto bl = t->bottomLeft();
        if(!bl) return false;
        const auto blt = bl->underBuildingType();
        if(blt != eBuildingType::horseRanchEnclosure) return false;

        const auto br = t->bottomRight();
        if(!br) return false;
        const auto brt = br->underBuildingType();
        if(brt != eBuildingType::horseRanchEnclosure) return false;

        return true;
    }
    default:
        return true;
    }
}

stdsptr<eWalkableObject> eWalkableObject::sCreate(
        const eWalkableObjectType type) {
    switch(type) {
    case eWalkableObjectType::rect:
        return std::make_shared<eRectWalkableObject>();
    case eWalkableObjectType::hasResource:
        return std::make_shared<eHasResourceWalkableObject>();
    default:
        return std::make_shared<eWalkableObject>(type);
    }
}

stdsptr<eWalkableObject> eWalkableObject::sCreateDefault() {
    return sCreate(eWalkableObjectType::ddefault);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRoad() {
    return sCreate(eWalkableObjectType::road);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRoadblock() {
    return sCreate(eWalkableObjectType::roadblock);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateTerrain() {
    return sCreate(eWalkableObjectType::terrain);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateFertile() {
    return sCreate(eWalkableObjectType::fertile);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateWall() {
    return sCreate(eWalkableObjectType::wall);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateWater() {
    return sCreate(eWalkableObjectType::water);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateAll() {
    return sCreate(eWalkableObjectType::all);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRanch() {
    return sCreate(eWalkableObjectType::ranch);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRect(const SDL_Rect& rect) {
    return std::make_shared<eRectWalkableObject>(rect);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRect(eBuilding* const b) {
    return sCreateRect(b->tileRect());
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRect(
        const SDL_Rect& rect,
        const stdsptr<eWalkableObject>& other) {
    return std::make_shared<eRectWalkableObject>(other, rect);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateRect(
        eBuilding* const b,
        const stdsptr<eWalkableObject>& other) {
    return sCreateRect(b->tileRect(), other);
}

stdsptr<eWalkableObject> eWalkableObject::sCreateHasResource(
        const stdsptr<eHasResourceObject>& hr,
        const stdsptr<eWalkableObject>& w) {
    return std::make_shared<eHasResourceWalkableObject>(hr, w);
}
