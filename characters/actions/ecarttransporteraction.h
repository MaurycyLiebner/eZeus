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
    void findTarget(const eCartTask& task);
    void findTarget(const std::vector<eCartTask>& tasks);
    void goBack();

    void targetResourceAction(const int bx, const int by);
    void targetResourceAction(eBuildingWithResource* const rb);
    bool targetProcessTask(eBuildingWithResource* const rb,
                           const eCartTask& task);

    void startResourceAction(const eCartTask& task);
    void finishResourceAction(const eCartTask& task);
private:
    void waitOutside();
    void clearTask();

    eBuildingWithResource* const mBuilding;

    eCartTask mTask;

    bool mNoTarget = false;
    bool mWaitOutside = false;
};

#endif // ECARTTRANSPORTERACTION_H
