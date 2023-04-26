#include "ebuttonslistwidget.h"

#include "elabel.h"
#include "eframedbutton.h"
#include "ecancelbutton.h"

#include "elanguage.h"

void eListButton::initialize(const std::string& text, const int id,
                             const bool renderBg, const bool small) {
    setNoPadding();

    mIdLabel = new eLabel(std::to_string(id + 1), window());
    if(small) {
        mIdLabel->setSmallFontSize();
        mIdLabel->setSmallPadding();
    }
    mIdLabel->fitContent();
    mIdLabel->setWidth(mIdLabel->height());
    addWidget(mIdLabel);

    setId(id);

    mButton = new eFramedButton(text, window());
    if(small) {
        mButton->setSmallFontSize();
        mButton->setSmallPadding();
    }
    mButton->setUnderline(false);
    mButton->setRenderBg(renderBg);
    mButton->setPressAction([this]() {
        if(mPressAction) mPressAction(mId);
    });
    mButton->fitContent();
    addWidget(mButton);

    mCloseButton = new eCancelButton(window());
    mCloseButton->setPressAction([this]() {
        if(mCloseAction) mCloseAction(mId);
    });
    addWidget(mCloseButton);
    fitContent();
    mCloseButton->align(eAlignment::vcenter);
}

void eListButton::setId(const int id) {
    mId = id;
    mIdLabel->setText(std::to_string(id + 1));
}

void eListButton::setText(const std::string& text) {
    mButton->setText(text);
}

void eListButton::setCloseAction(const eCloseAction& ca) {
    mCloseAction = ca;
}

void eListButton::setPressAction(const ePressAction& pa) {
    mPressAction = pa;
}

void eListButton::fitToWidth(const int w) {
    setWidth(w);
    const int bw = w - mIdLabel->width() - mCloseButton->width();
    mButton->setWidth(bw);
    layoutHorizontallyWithoutSpaces();
}

void eButtonsListWidget::initialize(const bool newButton) {
    if(newButton) {
        const auto addStr = eLanguage::text("add");
        mNewButton = new eFramedButton(addStr, window());
        if(mSmallSize) {
            mNewButton->setSmallFontSize();
            mNewButton->setSmallPadding();
        }
        mNewButton->fitContent();
        mNewButton->setUnderline(false);
        mNewButton->setPressAction([this]() {
            if(mCreateE) mCreateE();
        });
    }

    updateButtons();
}

void eButtonsListWidget::setButtonPressEvent(const eButtonPressedEvent& e) {
    mPressE = e;
}

void eButtonsListWidget::setButtonCreateEvent(const eButtonCreateEvent& e) {
    mCreateE = e;
}

void eButtonsListWidget::setButtonRemoveEvent(const eButtonRemoveEvent& e) {
    mRemoveE = e;
}

void eButtonsListWidget::setText(const int id, const std::string& text) {
    mButtons[id]->setText(text);
}

int eButtonsListWidget::addButton(const std::string& text) {
    const int id = mButtons.size();
    const auto b = new eListButton(window());
    b->initialize(text, id, mRenderButtonBg, mSmallSize);
    b->setPressAction([this](const int id) {
        if(mPressE) mPressE(id);
    });
    b->setCloseAction([this](const int id) {
        removeButton(id);
        if(mRemoveE) mRemoveE(id);
    });
    mButtons.push_back(b);
    updateButtons();
    return id;
}

void eButtonsListWidget::removeButton(const int id) {
    mButtons.erase(mButtons.begin() + id);
    updateButtons();
}

void eButtonsListWidget::setSmallSize(const bool b) {
    mSmallSize = b;
}

void eButtonsListWidget::setRenderButtonBg(const bool b) {
    mRenderButtonBg = b;
}

void eButtonsListWidget::updateButtons() {
    removeAllWidgets();
    const int p = padding();
    int y = 0;
    int i = 0;
    for(const auto b : mButtons) {
        addWidget(b);
        b->fitToWidth(width());
        b->setY(y);
        b->setId(i++);
        y += b->height() + p;
    }
    if(mNewButton) {
        addWidget(mNewButton);
        mNewButton->setY(y);
        mNewButton->setWidth(width());
    }
}
