#include "emessagebox.h"

#include "elabel.h"

void eMessageBox::initialize(const std::shared_ptr<eMessage>& msg) {
    setType(eFrameType::message);

    const auto title = new eLabel(msg->fTitle, window());
    title->setHugeFontSize();
    title->fitContent();
    addWidget(title);

    const auto text = new eLabel(window());
    text->setWrapWidth(width());
    text->setText(msg->fText);
    text->fitContent();
    addWidget(text);

    stackVertically();
}
