#ifndef EGIFTSIZEDIALOG_H
#define EGIFTSIZEDIALOG_H

#include "eclosabledialog.h"

#include "engine/eworldcity.h"

class eGiftSizeDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eRequestFunction = std::function<void(eResourceType,
                                                const int)>;
    void initialize(const eResourceType type,
                    const stdsptr<eWorldCity>& c,
                    const eRequestFunction& func,
                    const eGameBoard& board);
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EGIFTSIZEDIALOG_H
