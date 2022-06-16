#include "eviewmodebutton.h"

#include "textures/egametextures.h"

eViewModeButton::eViewModeButton(const std::string& text,
                                 const eViewMode vm,
                                 eMainWindow* const window) :
    eCheckableButton(window), mVM(vm) {
    setCheckAction([this](const bool) {
        if(!mGW) return;
        const auto gwvm = mGW->viewMode();
        if(gwvm == mVM) {
            mGW->setViewMode(eViewMode::defaultView);
        } else {
            mGW->setViewMode(mVM);
        }
    });

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes].fSeeButton;

    setTexture(texs.getTexture(0));
    setHoverTexture(texs.getTexture(1));
    setCheckedTexture(texs.getTexture(2));
    setVeryVeryTinyPadding();
    fitContent();

    const auto label = new eLabel(text, window);
    label->setVerySmallFontSize();
    label->setNoPadding();
    label->fitContent();
    addWidget(label);
    label->align(eAlignment::center);
}

void eViewModeButton::setGameWidget(eGameWidget* const gw) {
    mGW = gw;
}

void eViewModeButton::paintEvent(ePainter& p) {
    if(mGW) {
        const auto vm = mGW->viewMode();
        setChecked(vm == mVM);
    }
    eCheckableButton::paintEvent(p);
}
