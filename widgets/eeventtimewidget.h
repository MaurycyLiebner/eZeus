#ifndef EEVENTTIMEWIDGET_H
#define EEVENTTIMEWIDGET_H

#include "ewidget.h"

#include "engine/eeventtime.h"

class eEventTimeWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const eAction& act);

    void setEventTime(const eEventTime et);
    eEventTime eventTime() const;
private:
    eAction mChangeAction;
};

#endif // EEVENTTIMEWIDGET_H
