#ifndef EHEROSHALLINFOWIDGET_H
#define EHEROSHALLINFOWIDGET_H

#include "einfowidget.h"

class eHerosHall;

class eHerosHallInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(eHerosHall* const b);
};

#endif // EHEROSHALLINFOWIDGET_H
