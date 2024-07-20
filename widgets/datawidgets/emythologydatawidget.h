#ifndef EMYTHOLOGYDATAWIDGET_H
#define EMYTHOLOGYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eTitledWidget;

class eSanctuary;
class eCharacter;
class eMonster;

class eMythologyDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize() override;
protected:
    void paintEvent(ePainter& p) override;
private:
    eViewModeButton* mSeeImmortals = nullptr;

    struct eSanctuaryState {
        eSanctuary* fPtr = nullptr;
        bool fFinished = false;
        bool fSacrificing = false;
    };

    bool mSanctuariesF = true;
    std::vector<eSanctuaryState> mSanctuariesV;
    eTitledWidget* mSanctuaries = nullptr;
    bool mGodsAttackingF = true;
    std::vector<eCharacter*> mGodsAttackingV;
    eTitledWidget* mGodsAttacking = nullptr;
    bool mMonstersAttackingF = true;
    std::vector<eMonster*> mMonstersAttackingV;
    eTitledWidget* mMonstersAttacking = nullptr;
};

#endif // EMYTHOLOGYDATAWIDGET_H
