#include "egamemenubase.h"

void eGameMenuBase::initialize() {
    int x;
    int y;
    switch(resolution().uiScale()) {
    case eUIScale::tiny:
        x = 5;
        y = 15;
        break;
    case eUIScale::small:
        x = 6;
        y = 21;
        break;
    case eUIScale::medium:
        x = 9;
        y = 31;
        break;
    default:
        x = 12;
        y = 42;
    }
    mButtonsWidget = new eWidget(window());
    mButtonsWidget->setX(x);
    mButtonsWidget->setY(y);
    mButtonsWidget->setPadding(0);
    addWidget(mButtonsWidget);
}

eCheckableButton* eGameMenuBase::addButton(
        const eTextureCollection& texs,
        eWidget* const w) {
    const auto b = createCheckableButton(texs, mButtonsWidget);
    mButtons.push_back(b);
    mWidgets.push_back(w);
    return b;
}

void eGameMenuBase::connectAndLayoutButtons() {
    double margin;
    switch(resolution().uiScale()) {
    case eUIScale::tiny:
        margin = 2;
        break;
    case eUIScale::small:
        margin = 2;
        break;
    case eUIScale::medium:
        margin = 2.1835;
        break;
    default:
        margin = 3;
    }
    const int n = mButtons.size();
    const int buttH = mButtons.front()->height();
    const int h = n*(buttH + margin);
    mButtonsWidget->setHeight(h);
    mButtonsWidget->layoutVertically();
    mButtonsWidget->fitContent();

    const int iMax = mButtons.size();
    for(int i = 0; i < iMax; i++) {
        const auto b = mButtons[i];
        b->setCheckAction([this, i, b](const bool c) {
            if(c) {
                const int jMax = mButtons.size();
                const int wSize = mWidgets.size();
                for(int j = 0; j < jMax; j++) {
                    if(j < wSize) {
                        const auto w = mWidgets[j];
                        w->setVisible(j == i);
                    }
                    if(j == i) continue;
                    const auto b = mButtons[j];
                    b->setChecked(false);
                }
            } else {
                b->setChecked(true);
            }
        });
    }
}

template <class T>
T* createButtonBase(const eTextureCollection& texs,
                    eWidget* const buttons,
                    eMainWindow* const window) {
    const auto b = new T(window);
    b->setTexture(texs.getTexture(0));
    b->setPadding(0);
    b->setHoverTexture(texs.getTexture(1));
    b->setDisabledTexture(texs.getTexture(3));
    b->fitContent();
    buttons->addWidget(b);
    return b;
}

eButton* eGameMenuBase::createButton(
        const eTextureCollection& texs,
        eWidget* const buttons) {
    const auto b = createButtonBase<eButton>(texs, buttons, window());
    b->setPressedTexture(texs.getTexture(2));
    return b;
}

eCheckableButton* eGameMenuBase::createCheckableButton(
        const eTextureCollection& texs,
        eWidget* const buttons) {
    const auto b = createButtonBase<eCheckableButton>(texs, buttons, window());
    b->setCheckedTexture(texs.getTexture(2));
    return b;
}
