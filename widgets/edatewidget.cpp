#include "edatewidget.h"

#include "echoosebutton.h"
#include "eframedbutton.h"
#include "enumlineedit.h"

#include "emainwindow.h"

void eDateWidget::initialize(const eDateAction& a) {
    setType(eFrameType::message);

    mDayEdit = new eNumLineEdit(window());
    mDayEdit->setRange(1, eMonthHelper::days(mMonth));
    mDayEdit->setValue(10);
    mDayEdit->fitContent();
    mDayEdit->setChangeAction([this, a]() {
        if(a) a(date());
    });

    mMonthEdit = new eFramedButton(window());
    mMonthEdit->fitContent();
    std::vector<std::string> monthStrs;
    int w = 0;
    for(int i = 0; i < 12; i++) {
        const auto m = static_cast<eMonth>(i);
        const auto str = eMonthHelper::name(m);
        mMonthEdit->setText(str);
        mMonthEdit->fitContent();
        const int mw = mMonthEdit->width();
        if(mw > w) w = mw;
        monthStrs.push_back(str);
    }
    mMonthEdit->setText(eMonthHelper::name(mMonth));
    mMonthEdit->setWidth(w);
    mMonthEdit->setPressAction([this, monthStrs, a]() {
        const auto choose = new eChooseButton(window());
        choose->initialize(4, monthStrs, [this, a](const int i) {
            mMonth = static_cast<eMonth>(i);
            const int days = eMonthHelper::days(mMonth);
            mDayEdit->setRange(1, days);
            mMonthEdit->setText(eMonthHelper::name(mMonth));
            if(a) a(date());
        });
        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });

    mYearEdit = new eNumLineEdit(window());
    mYearEdit->setRange(-9999, 9999);
    mYearEdit->setValue(-1500);
    mYearEdit->fitContent();
    mYearEdit->setChangeAction([this, a]() {
        if(a) a(date());
    });

    addWidget(mDayEdit);
    addWidget(mMonthEdit);
    addWidget(mYearEdit);

    const int p = padding();
    int x = 2*p;
    mDayEdit->setX(x);
    mDayEdit->setY(2*p);
    x += mDayEdit->width() + p;
    mMonthEdit->setX(x);
    mMonthEdit->setY(2*p);
    x += mMonthEdit->width() + p;
    mYearEdit->setX(x);
    mYearEdit->setY(2*p);

    fitContent();
}

eDate eDateWidget::date() const {
    const int d = mDayEdit->value();
    const int y = mYearEdit->value();
    return eDate(d, mMonth, y);
}

void eDateWidget::setDate(const eDate& date) {
    mMonth = date.month();
    mMonthEdit->setText(eMonthHelper::name(mMonth));
    const int days = eMonthHelper::days(mMonth);
    mDayEdit->setRange(1, days);
    mDayEdit->setValue(date.day());
    mYearEdit->setValue(date.year());
}
