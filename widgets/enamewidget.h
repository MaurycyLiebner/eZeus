#ifndef ENAMEWIDGET_H
#define ENAMEWIDGET_H

#include "eframedwidget.h"

class eNameWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eNameChangeAction = std::function<void(const std::string&)>;
    void initialize(const std::string& ini,
                    const std::vector<std::string>& names,
                    const eNameChangeAction& nca,
                    const std::string& title = "",
                    const bool proceed = false);
};

#endif // ENAMEWIDGET_H
