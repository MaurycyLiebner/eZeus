#include "eviewmodebutton.h"

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
    setSmallFontSize();
    setTinyPadding();
    setText(text);
    fitContent();
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
