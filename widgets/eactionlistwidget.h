#ifndef EACTIONLISTWIDGET_H
#define EACTIONLISTWIDGET_H

#include "ewidget.h"

class eActionListWidget : public eWidget {
public:
    using eWidget::eWidget;

    using eStateChecker = std::function<bool()>;
    void addAction(const std::string& text, const eAction& a,
                   const eStateChecker& stateChecker = nullptr);
};

#endif // EACTIONLISTWIDGET_H
