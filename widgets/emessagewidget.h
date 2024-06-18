#ifndef EMESSAGEWIDGET_H
#define EMESSAGEWIDGET_H

#include "eframedwidget.h"

class eMessageWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const std::string& title,
                    const std::string& text);
};

#endif // EMESSAGEWIDGET_H
