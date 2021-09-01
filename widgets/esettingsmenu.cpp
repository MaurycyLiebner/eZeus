#include "esettingsmenu.h"

#include "ecombobox.h"
#include "echeckbox.h"
#include "elabeledwidget.h"
#include "eframedwidget.h"

eSettingsMenu::eSettingsMenu(const eSettings& iniSettings,
                             eMainWindow* const window) :
    eMainMenuBase(window),
    mIniSettings(iniSettings),
    mSettings(iniSettings) {

}

void eSettingsMenu::initialize(const eAction& backA,
                               const eApplyAction& settingsA) {
    eMainMenuBase::initialize();

    const auto buttons = new eFramedWidget(window());
    addWidget(buttons);

    const auto res = resolution();

    const int cww = res.centralWidgetWidth();
    const int cwh = res.centralWidgetHeight();
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eComboBox(window());
        const auto res = mSettings.fRes;
        int id = 0;
        const int iMax = eResolution::sResolutions.size();
        for(int i = 0; i < iMax; i++) {
            const auto& r = eResolution::sResolutions[i];
            if(r == res) id = i;
            b->addAction(r.name());
        }
        b->setCurrentIndex(id);
        b->setCurrentChangedAction([this](const int id) {
            mSettings.fRes = eResolution::sResolutions[id];
        });
        b->fitContent();

        lw->setup("Resolution: ", b);
        buttons->addWidget(lw);
    }

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eCheckBox(window());
        b->setChecked(mSettings.fFullscreen);
        b->setCheckAction([this](const bool c) {
            mSettings.fFullscreen = c;
        });
        b->fitContent();

        lw->setup("Fullscreen: ", b);
        buttons->addWidget(lw);
    }

    buttons->layoutVertically();

    {
        const auto b = new eButton(window());
        b->setPressAction(backA);
        buttons->addWidget(b);
        b->setText("Back");
        b->fitContent();
        b->align(eAlignment::left | eAlignment::bottom);
    }

    {
        const auto b = new eButton(window());
        b->setPressAction([this, backA, settingsA]() {
            if(mSettings == mIniSettings) {
                return;
            }
            settingsA(mSettings);
        });
        buttons->addWidget(b);
        b->setText("Apply");
        b->fitContent();
        b->align(eAlignment::right | eAlignment::bottom);
    }
}
