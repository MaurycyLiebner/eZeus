#ifndef EREQUESTDIALOG_H
#define EREQUESTDIALOG_H

#include "eclosabledialog.h"

#include "engine/eworldcity.h"

class eRequestDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eRequestFunction = std::function<void(eResourceType)>;
    void initialize(const stdsptr<eWorldCity>& c,
                    const eRequestFunction& func,
                    const eAction& requestDefensiveAid,
                    const eAction& requestStrike);
};

#endif // EREQUESTDIALOG_H
