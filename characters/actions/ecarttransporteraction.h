#ifndef ECARTTRANSPORTERACTION_H
#define ECARTTRANSPORTERACTION_H

#include "eactionwithcomeback.h"

#include "characters/ecarttransporter.h"
#include "buildings/ebuildingwithresource.h"

class eCartTransporterAction : public eActionWithComeback {
public:
    eCartTransporterAction(eBuildingWithResource* const b,
                           eCartTransporter* const c,
                           const eAction& failAction,
                           const eAction& finishAction);

    bool decide();
protected:
    void findTarget();
    void goBack();

    void targetResourceAction(const int bx, const int by);
    void targetResourceAction(eBuildingWithResource* const rb);

    void startResourceAction(const eCartTask& task);
    void finishResourceAction(const eCartTask& task);
private:
    void clearTask();

    eBuildingWithResource* const mBuilding;

    eCartTask mTask;

    const eBuildingType mBuildingType;

    bool mNoTarget = false;
};

#endif // ECARTTRANSPORTERACTION_H
