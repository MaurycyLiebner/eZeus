#ifndef EGIFTDIALOG_H
#define EGIFTDIALOG_H

#include "eclosabledialog.h"

#include "engine/eworldcity.h"

class eGiftDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eRequestFunction = std::function<void(eResourceType)>;
    void initialize(const stdsptr<eWorldCity>& c,
                    const eRequestFunction& func,
                    const eGameBoard& board);
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EGIFTDIALOG_H
