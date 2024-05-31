#ifndef EENLISTFORCESDIALOG_H
#define EENLISTFORCESDIALOG_H

#include "eclosabledialog.h"

#include "characters/eenlistedforces.h"

#include <deque>

class eEnlistForcesDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eEnlistAction = std::function<void(const eEnlistedForces&, eResourceType)>;
    void initialize(const eEnlistedForces& enlistable,
                    const std::vector<bool>& heroesAbroad,
                    const eEnlistAction& action,
                    const std::vector<eResourceType>& plunderResources = {});
protected:
    void paintEvent(ePainter& p) override;
private:
    void updateTipPositions();

    int mFrame = 0;

    struct eTip {
        eWidget* fWid = nullptr;
        int fLastFrame = 0;
    };

    std::deque<eTip> mTips;

    eEnlistedForces mSelected;
    eResourceType mSelectedPlunder = eResourceType::none;
};

#endif // EENLISTFORCESDIALOG_H
