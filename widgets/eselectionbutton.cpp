#include "eselectionbutton.h"

#include "elabel.h"

void eSelectionButton::initialize(const int value, const int id) {
    mValue = value;
    setNoPadding();
    mIdLabel = new eLabel(std::to_string(id + 1), window());
    mIdLabel->fitContent();
    mIdLabel->setWidth(mIdLabel->height());
    addWidget(mIdLabel);
}

void eSelectionButton::setId(const int id) {
    mId = id;
    mIdLabel->setText(std::to_string(id + 1));
}
