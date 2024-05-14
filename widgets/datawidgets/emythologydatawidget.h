#ifndef EMYTHOLOGYDATAWIDGET_H
#define EMYTHOLOGYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eTitledWidget;

class eSanctuary;
class eCharacter;

class eMythologyDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeImmortals = nullptr;

    bool mSanctuariesF = true;
    std::vector<eSanctuary*> mSanctuariesV;
    eTitledWidget* mSanctuaries = nullptr;
    bool mGodsAttackingF = true;
    std::vector<eCharacter*> mGodsAttackingV;
    eTitledWidget* mGodsAttacking = nullptr;
    bool mMonstersAttackingF = true;
    std::vector<eCharacter*> mMonstersAttackingV;
    eTitledWidget* mMonstersAttacking = nullptr;

    int mTime{0};
};

#endif // EMYTHOLOGYDATAWIDGET_H
