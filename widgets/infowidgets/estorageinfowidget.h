#ifndef ESTORAGEINFOWIDGET_H
#define ESTORAGEINFOWIDGET_H

#include "eemployingbuildinginfowidget.h"

#include "../eswitchbutton.h"
#include "../espinbox.h"

#include "engine/eresourcetype.h"

#include "buildings/estoragebuilding.h"

class eStorageInfoWidget : public eEmployingBuildingInfoWidget {
public:
    eStorageInfoWidget(eMainWindow* const window);

    void initialize(eStorageBuilding* const stor);
    void get(eResourceType& get,
             eResourceType& empty,
             eResourceType& accept,
             eResourceType& dontaccept,
             std::map<eResourceType, int>& count) const;
private:
    std::map<eResourceType, eSwitchButton*> mButtons;
    std::map<eResourceType, eSpinBox*> mSpinBoxes;
};

#endif // ESTORAGEINFOWIDGET_H
