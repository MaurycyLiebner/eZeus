#ifndef EMONSTERSELECTIONWIDGET_H
#define EMONSTERSELECTIONWIDGET_H

#include "emultipleselectionwidget.h"

#include "characters/monsters/emonster.h"

class eMonsterSelectionWidget : public eMultipleSelectionWidget {
public:
    using eMultipleSelectionWidget::eMultipleSelectionWidget;

    using eMonsterSetAction = std::function<void(const std::vector<eMonsterType>&)>;
    void initialize(const eMonsterSetAction& monsterSetAct,
                    const std::vector<eMonsterType>& ini);
};

#endif // EMONSTERSELECTIONWIDGET_H
