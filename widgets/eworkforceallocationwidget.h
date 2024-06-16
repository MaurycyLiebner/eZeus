#ifndef EWORKFORCEALLOCATIONWIDGET_H
#define EWORKFORCEALLOCATIONWIDGET_H

#include "infowidgets/einfowidget.h"

class eGameBoard;
enum class eSector;

class eWorkforceAllocationWidget : public eInfoWidget {
public:
    eWorkforceAllocationWidget(eMainWindow* const window);

    void initialize(eGameBoard& board);
private:
    void updateLabels();

    eGameBoard* mBoard = nullptr;
    std::map<eSector, eLabel*> mEmplLabels;
};

#endif // EWORKFORCEALLOCATIONWIDGET_H
