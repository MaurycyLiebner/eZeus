#ifndef ECARTTRANSPORTERACTION_H
#define ECARTTRANSPORTERACTION_H

#include "eactionwithcomeback.h"

#include "characters/ecarttransporter.h"

enum class eCartActionType {
    take, give
};

class eCartTransporterAction : public eActionWithComeback {
public:
    eCartTransporterAction(eBuilding* const b,
                           eTransporterBase* const c,
                           const eCartActionType aType,
                           const eResourceType resType,
                           const eAction& failAction,
                           const eAction& finishAction);
    eCartTransporterAction(eBuilding* const b,
                           eTransporterBase* const c,
                           const eCartActionType aType,
                           const eResourceType resType,
                           const eAction& foundAction,
                           const eAction& failAction,
                           const eAction& finishAction);

    void increment(const int by);
protected:
    void findTarget();
    void goBack2();
    bool resourceAction(const int bx, const int by);
private:
    eBuilding* const mBuilding;
    const eBuildingType mBuildingType;
    const SDL_Rect mBuildingRect;
    const eCartActionType mActionType;
    const eResourceType mResource;
    const eAction mFoundAction;
    eOrientation mBuildingO;
};

#endif // ECARTTRANSPORTERACTION_H
