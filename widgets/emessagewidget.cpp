#include "emessagewidget.h"

#include "elabel.h"
#include "elanguage.h"

void eMessageWidget::initialize(const std::string& title,
                                const std::string& text) {
    setType(eFrameType::message);
    const auto res = resolution();
    const int p = 2*res.largePadding();
    const int width = 40*p;
    const auto cw = new eWidget(window());
    cw->setNoPadding();
    cw->setWidth(width);

    const auto titleLabel = new eLabel(window());
    titleLabel->setNoPadding();
    titleLabel->setHugeFontSize();
    titleLabel->setText(title);
    titleLabel->fitContent();
    cw->addWidget(titleLabel);

    const auto textLabel = new eLabel(window());
    textLabel->setNoPadding();
    textLabel->setSmallFontSize();
    textLabel->setWrapWidth(width);
    textLabel->setText(text);
    textLabel->fitContent();
    cw->addWidget(textLabel);

    const auto rightClickL = new eLabel(window());
    rightClickL->setNoPadding();
    rightClickL->setSmallFontSize();
    rightClickL->setText(eLanguage::zeusText(13, 1));
    rightClickL->fitContent();
    cw->addWidget(rightClickL);
    rightClickL->align(eAlignment::hcenter);

    cw->stackVertically(p);
    cw->fitContent();
    addWidget(cw);
    cw->move(p, p);
    resize(cw->width() + 2*p, cw->height() + 2*p);
    titleLabel->align(eAlignment::hcenter);
    rightClickL->align(eAlignment::hcenter);
}
