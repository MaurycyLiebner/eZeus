#include "esettingsmenu.h"

#include "ecombobox.h"

eSettingsMenu::eSettingsMenu(const eSettings& iniSettings,
                             eMainWindow* const window) :
    eWidget(window),
    mIniSettings(iniSettings),
    mSettings(iniSettings) {

}

void eSettingsMenu::initialize(const eAction& backA,
                               const eApplyAction& settingsA) {
    const auto buttons = new eWidget(window());
    addWidget(buttons);

    const auto res = resolution();

    const int margin = eResolution::margin(res);

    const int cww = eResolution::centralWidgetWidth(res);
    const int cwh = eResolution::centralWidgetHeight(res);
    buttons->resize(cww, cwh);

    buttons->align(eAlignment::center);

    {
        const auto cw = new eWidget(window());

        const auto l = new eLabel("Resolution: ", window());
        l->fitContent();
        cw->addWidget(l);

        const auto b = new eComboBox(window());
        for(const auto& r : eResolution::sResolutions) {
            b->addAction(r.name());
        }
        const auto res = mSettings.fRes;
        const int id = static_cast<int>(res);
        b->setCurrentIndex(id);
        b->setCurrentChangedAction([this](const int id) {
            const auto& s = eResolution::sResolutions[id];
            mSettings.fRes = s.res();
        });
        cw->addWidget(b);
        b->fitContent();

        cw->fitContent();

        l->align(eAlignment::vcenter);
        b->align(eAlignment::vcenter);

        cw->setWidth(3*margin + l->width() + b->width());

        cw->layoutHorizontally();
        buttons->addWidget(cw);
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
