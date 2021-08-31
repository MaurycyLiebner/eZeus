#ifndef ESTORAGEINFOWIDGET_H
#define ESTORAGEINFOWIDGET_H

#include "einfowidget.h"

#include "../eswitchbutton.h"
#include "engine/eresourcetype.h"

class eStorageInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(const eResourceType all,
                    const eResourceType get,
                    const eResourceType empty,
                    const eResourceType accept);
    void get(eResourceType& get,
             eResourceType& empty,
             eResourceType& accept,
             eResourceType& dontaccept) const;
private:
    std::map<eResourceType, eSwitchButton*> mButtons;
};

#endif // ESTORAGEINFOWIDGET_H
