#include "edatalabel.h"

void eDataLabel::initialize(const std::string& text) {
    setNoPadding();
    const auto p = new eLabel(text, window());
    p->setVerySmallFontSize();
    p->setSmallPadding();
    p->fitContent();
    mLabel = new eLabel("-", window());
    mLabel->setVerySmallFontSize();
    mLabel->setSmallPadding();
    mLabel->fitContent();

    addWidget(p);
    addWidget(mLabel);

    stackHorizontally();
    fitContent();
}
