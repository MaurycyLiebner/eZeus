#ifndef ECARTTRANSPORTERACTION_H
#define ECARTTRANSPORTERACTION_H

#include "eactionwithcomeback.h"

#include "characters/ecarttransporter.h"

enum class eCartActionType {
    take, give
};

class eCartTransporterAction : public eActionWithComeback {
public:
    eCartTransporterAction(const SDL_Rect& buildingRect,
                           eCartTransporter* const c,
                           const eCartActionType aType,
                           const eResourceType resType,
                           const eAction& foundAction,
                           const eAction& failAction,
                           const eAction& finishAction);

    void increment(const int by);
protected:
    void findTarget();
    void goBack2();
    bool resourceAction();
private:
    const eCartActionType mActionType;
    const eResourceType mResource;
    const SDL_Rect mBuildingRect;
    const eAction mFoundAction;
    eOrientation mBuildingO;
};

#endif // ECARTTRANSPORTERACTION_H
