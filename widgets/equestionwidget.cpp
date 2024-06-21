#include "equestionwidget.h"

#include "elabel.h"
#include "eacceptbutton.h"
#include "ecancelbutton.h"

void eQuestionWidget::initialize(const std::string& title,
                                 const std::string& text,
                                 const eAction& acceptA,
                                 const eAction& cancelA) {
    setType(eFrameType::message);
    const int p = padding();
    const int width = 40*p;
    const auto cw = new eWidget(window());
    cw->setNoPadding();
    cw->setWidth(width);

    const auto titleLabel = new eLabel(window());
    titleLabel->setHugeFontSize();
    titleLabel->setText(title);
    titleLabel->fitContent();
    cw->addWidget(titleLabel);

    const auto textLabel = new eLabel(window());
    textLabel->setSmallFontSize();
    textLabel->setWrapWidth(width);
    textLabel->setText(text);
    textLabel->fitContent();
    cw->addWidget(textLabel);
    const int tly = titleLabel->y() + titleLabel->height();
    textLabel->setY(tly);

    const auto buttons = new eWidget(window());

    const auto accept = new eAcceptButton(window());
    const auto cancel = new eCancelButton(window());
    accept->setPressAction([this, acceptA]() {
        if(acceptA) acceptA();
        deleteLater();
    });
    cancel->setPressAction([this, cancelA]() {
        if(cancelA) cancelA();
        deleteLater();
    });
    buttons->addWidget(cancel);
    buttons->addWidget(accept);

    buttons->setNoPadding();
    accept->setX(width/5);
    buttons->fitContent();

    cw->addWidget(buttons);
    const int by = textLabel->y() + textLabel->height() + p;
    buttons->setY(by);

    cw->fitContent();
    cw->setHeight(cw->height() + p);
    addWidget(cw);
    cw->move(p, p);
    resize(cw->width() + 2*p, cw->height() + 2*p);
    titleLabel->align(eAlignment::hcenter);
    buttons->align(eAlignment::hcenter);
}
