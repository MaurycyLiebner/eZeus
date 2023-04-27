#ifndef ENUMLINEEDITWIDGET_H
#define ENUMLINEEDITWIDGET_H

#include "eframedwidget.h"

class eNumLineEdit;

class eNumLineEditWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eValueAction = std::function<void(const int)>;
    void initialize(const eValueAction& a,
                    const bool actOnChange,
                    const int min,
                    const int max);

    int value() const;
    void setValue(const int v);
private:
    bool mActOnChange = false;
    eNumLineEdit* mEdit = nullptr;
};

#endif // ENUMLINEEDITWIDGET_H
