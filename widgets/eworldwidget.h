#ifndef EWORLDWIDGET_H
#define EWORLDWIDGET_H

#include "ewidget.h"
#include "engine/egameboard.h"

#include "widgets/eenlistforcesdialog.h"

class eWorldMenu;
class eWorldMapWidget;
class eFramedButton;

class eWorldWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const board);
    void setWorldBoard(eWorldBoard* const board);

    void update();

    using eEnlistAction = eEnlistForcesDialog::eEnlistAction;
    void openEnlistForcesDialog(
            const eEnlistAction& a,
            const std::vector<stdsptr<eWorldCity>>& exclude,
            const std::vector<eResourceType>& plunderResources = {});
    void openEnlistForcesDialog(
            const eEnlistedForces& enlistable,
            const std::vector<bool>& heroesAbroad,
            const eEnlistAction& action,
            const std::vector<eResourceType>& plunderResources = {});

    void openDialog(eWidget* const d);
protected:
    bool keyPressEvent(const eKeyPressEvent& e);
private:
    void openRequestDialog();
    void openFulfillDialog();
    void openGiftDialog();
    void setMap(const eWorldMap map);

    stdsptr<eWorldCity> mCity;
    eWorldMenu* mWM = nullptr;
    eWorldMapWidget* mWMW = nullptr;
    eWorldBoard* mWorldBoard = nullptr;
    eGameBoard* mBoard = nullptr;
    eFramedButton* mMapButton = nullptr;
    eFramedButton* mAddCityButton = nullptr;
    eFramedButton* mSettingsButton = nullptr;
};

#endif // EWORLDWIDGET_H
