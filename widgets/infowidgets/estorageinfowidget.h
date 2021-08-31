#ifndef ESTORAGEINFOWIDGET_H
#define ESTORAGEINFOWIDGET_H

#include "einfowidget.h"

#include "../eswitchbutton.h"
#include "../espinbox.h"

#include "engine/eresourcetype.h"

class eStorageInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(const eResourceType all,
                    const eResourceType get,
                    const eResourceType empty,
                    const eResourceType accept,
                    const std::map<eResourceType, int>& count);
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
