#ifndef EWORLDWIDGET_H
#define EWORLDWIDGET_H

#include "ewidget.h"
#include "engine/egameboard.h"

#include "widgets/eenlistforcesdialog.h"

class eWorldMenu;
class eWorldMapWidget;

class eWorldWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const board);
protected:
    bool keyPressEvent(const eKeyPressEvent& e);
private:
    using eEnlistAction = eEnlistForcesDialog::eEnlistAction;
    using ePlunderAction = eEnlistForcesDialog::ePlunderAction;
    void openEnlistForcesDialog(
            const eEnlistAction& a,
            const stdsptr<eWorldCity>& exclude,
            const std::vector<eResourceType>& plunderResources = {});
    void openRequestDialog();
    void openGiftDialog();

    stdsptr<eWorldCity> mCity;
    eWorldMenu* mWM = nullptr;
    eWorldMapWidget* mWMW = nullptr;
    eGameBoard* mBoard = nullptr;
};

#endif // EWORLDWIDGET_H
