#ifndef EMILITARYMOREINFOWIDGET_H
#define EMILITARYMOREINFOWIDGET_H

#include "infowidgets/einfowidget.h"

class eGameBoard;

class eMilitaryMoreInfoWidget : public eInfoWidget {
public:
    eMilitaryMoreInfoWidget(eMainWindow* const window);

    void initialize(eGameBoard& board);
private:
    eGameBoard* mBoard = nullptr;
};

#endif // EMILITARYMOREINFOWIDGET_H
