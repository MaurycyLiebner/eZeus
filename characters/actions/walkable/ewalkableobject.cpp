#include "ewalkableobject.h"

#include "buildings/ebuilding.h"

#include "edefaultwalkableobject.h"
#include "eroadwalkableobject.h"
#include "eroadblockwalkableobject.h"
#include "eterrainwalkableobject.h"
#include "efertilewalkableobject.h"
#include "ewallwalkableobject.h"
#include "erectwalkableobject.h"
#include "ehasresourcewalkableobject.h"

stdsptr<eWalkableObject> eWalkableObject::sCreate(
        const eWalkableObjectType type) {
    switch(type) {
    case eWalkableObjectType::ddefault:
        return std::make_shared<eDefaultWalkableObject>();
    case eWalkableObjectType::road:
        return std::make_shared<eRoadWalkableObject>();
    case eWalkableObjectType::roadblock:
        return std::make_shared<eRoadblockWalkableObject>();
    case eWalkableObjectType::terrain:
        return std::make_shared<eTerrainWalkableObject>();
    case eWalkableObjectType::fertile:
        return std::make_shared<eFertileWalkableObject>();
    case eWalkableObjectType::wall:
        return std::make_shared<eWallWalkableObject>();
    case eWalkableObjectType::rect:
        return std::make_shared<eRectWalkableObject>();
    case eWalkableObjectType::hasResource:
        return std::make_shared<eHasResourceWalkableObject>();
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
