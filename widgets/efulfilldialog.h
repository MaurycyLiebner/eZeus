#ifndef EFULFILLDIALOG_H
#define EFULFILLDIALOG_H

#include "infowidgets/einfowidget.h"

class eGameBoard;
class eWorldCity;

class eFulfillDialog : public eInfoWidget {
public:
    eFulfillDialog(eMainWindow* const window);

    using eCity = std::shared_ptr<eWorldCity>;
    void initialize(eGameBoard* const board,
                    const eCity& city);
};

#endif // EFULFILLDIALOG_H
