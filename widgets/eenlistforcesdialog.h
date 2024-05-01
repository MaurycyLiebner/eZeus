#ifndef EENLISTFORCESDIALOG_H
#define EENLISTFORCESDIALOG_H

#include "eclosabledialog.h"

#include "characters/eenlistedforces.h"

class eEnlistForcesDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eEnlistAction = std::function<void(const eEnlistedForces&)>;
    void initialize(const eEnlistedForces& enlistable,
                    const eEnlistAction& action);
private:
    eEnlistedForces mSelected;
};

#endif // EENLISTFORCESDIALOG_H
