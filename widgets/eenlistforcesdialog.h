#ifndef EENLISTFORCESDIALOG_H
#define EENLISTFORCESDIALOG_H

#include "eclosabledialog.h"

#include "characters/eenlistedforces.h"

class eEnlistForcesDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eEnlistAction = std::function<void(const eEnlistedForces&, eResourceType)>;
    using ePlunderAction = std::function<void(eResourceType)>;
    void initialize(const eEnlistedForces& enlistable,
                    const std::vector<bool>& heroesAbroad,
                    const eEnlistAction& action,
                    const std::vector<eResourceType>& plunderResources = {});
private:
    eEnlistedForces mSelected;
    eResourceType mSelectedPlunder = eResourceType::none;
};

#endif // EENLISTFORCESDIALOG_H
