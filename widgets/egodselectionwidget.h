#ifndef EGODSELECTIONWIDGET_H
#define EGODSELECTIONWIDGET_H

#include "emultipleselectionwidget.h"

#include "characters/gods/egod.h"

class eGodSelectionWidget : public eMultipleSelectionWidget {
public:
    using eMultipleSelectionWidget::eMultipleSelectionWidget;

    using eGodSetAction = std::function<void(const std::vector<eGodType>&)>;
    void initialize(const eGodSetAction& godSetAct,
                    const std::vector<eGodType>& ini);
};

#endif // EGODSELECTIONWIDGET_H
