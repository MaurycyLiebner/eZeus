#ifndef EGODATTACKEVENTWIDGET_H
#define EGODATTACKEVENTWIDGET_H

#include "../ewidget.h"

#include "characters/gods/egod.h"

class eSwitchButton;

class eGodAttackEvent;

class eGodAttackEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void load(const eGodAttackEvent& e);
    void save(eGodAttackEvent& e) const;
private:
    std::vector<eGodType> mTypes;
    bool mRandom = false;

    eSwitchButton* mRandomButton = nullptr;
};

#endif // EGODATTACKEVENTWIDGET_H
