#ifndef EWALKABLEOBJECT_H
#define EWALKABLEOBJECT_H

#include "fileIO/estreams.h"
#include "pointers/estdpointer.h"
#include "engine/eorientation.h"

class eTileBase;

enum class eWalkableObjectType {
    ddefault,
    waterAndDefault,
    road,
    roadAvenue,
    roadblock,
    terrain,
    fertile,
    wall,
    rect,
    hasResource,
    deepWater,
    water,
    ranch,
    all
};

class eHasResourceObject;

class eWalkableObject {
public:
    eWalkableObject(const eWalkableObjectType t) :
        mType(t) {}

    virtual bool walkable(eTileBase* const t) const;

    virtual void read(eReadStream&) {}
    virtual void write(eWriteStream&) const {}

    virtual eWalkableObjectType rootType() const {
        return mType;
    }

    eWalkableObjectType type() const { return mType; }

    static stdsptr<eWalkableObject> sCreate(
            const eWalkableObjectType type);
    static stdsptr<eWalkableObject> sCreateDefault();
    static stdsptr<eWalkableObject> sCreateRoad();
    static stdsptr<eWalkableObject> sCreateRoadAvenue();
    static stdsptr<eWalkableObject> sCreateRoadblock();
    static stdsptr<eWalkableObject> sCreateTerrain();
    static stdsptr<eWalkableObject> sCreateFertile();
    static stdsptr<eWalkableObject> sCreateWall();
    static stdsptr<eWalkableObject> sCreateDeepWater();
    static stdsptr<eWalkableObject> sCreateWaterAndDefault();
    static stdsptr<eWalkableObject> sCreateAll();
    static stdsptr<eWalkableObject> sCreateRanch();
    static stdsptr<eWalkableObject> sCreateRect(const SDL_Rect& rect);
    static stdsptr<eWalkableObject> sCreateRect(eBuilding* const b);
    static stdsptr<eWalkableObject> sCreateRect(
            const SDL_Rect& rect,
            const stdsptr<eWalkableObject>& other);
    static stdsptr<eWalkableObject> sCreateRect(
            eBuilding* const b,
            const stdsptr<eWalkableObject>& other);
    static stdsptr<eWalkableObject> sCreateHasResource(
            const stdsptr<eHasResourceObject>& hr,
            const stdsptr<eWalkableObject>& w);
private:
    const eWalkableObjectType mType;
};

#endif // EWALKABLEOBJECT_H
