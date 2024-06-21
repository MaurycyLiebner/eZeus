#ifndef EDATEWIDGET_H
#define EDATEWIDGET_H

#include "eframedwidget.h"

#include "engine/edate.h"

class eNumLineEdit;
class eFramedButton;

class eDateWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eDateAction = std::function<void(const eDate&)>;
    void initialize(const eDateAction& a,
                    const bool actOnChange);

    eDate date() const;
    void setDate(const eDate& date);
private:
    bool mActOnChange = false;
    eNumLineEdit* mDayEdit = nullptr;
    eFramedButton* mMonthEdit = nullptr;
    eMonth mMonth = eMonth::january;
    eNumLineEdit* mYearEdit = nullptr;
};

#endif // EDATEWIDGET_H
