#include "esettingsmenu.h"

#include "ecombobox.h"

eSettingsMenu::eSettingsMenu(const eSettings& iniSettings,
                             SDL_Renderer* const renderer) :
    eWidget(renderer),
    mIniSettings(iniSettings),
    mSettings(iniSettings) {

}

void eSettingsMenu::initialize(const eAction& backA,
                               const eApplyAction& settingsA) {
    const auto buttons = new eWidget(renderer());
    addWidget(buttons);
    buttons->resize(500, 500);
    buttons->align(eAlignment::center);

    {
        const auto cw = new eWidget(renderer());

        const auto l = new eLabel("Resolution: ", renderer());
        l->fitContent();
        cw->addWidget(l);

        const auto b = new eComboBox(renderer());
        for(const auto& r : eResolution::sResolutions) {
            b->addAction(r.name());
        }
        const auto res = mSettings.fRes.res();
        const int id = static_cast<int>(res);
        b->setCurrentIndex(id);
        b->setCurrentChangedAction([this](const int id) {
            const auto& s = eResolution::sResolutions[id];
            mSettings.fRes = s;
        });
        cw->addWidget(b);
        b->fitContent();
        b->align(eAlignment::hcenter);

        cw->resize(l->width() + b->width() + 50, 50);
        cw->layoutHorizontally();
        buttons->addWidget(cw);
    }

    buttons->layoutVertically();

    {
        const auto b = new eButton(renderer());
        b->setPressAction(backA);
        buttons->addWidget(b);
        b->setText("Back");
        b->fitContent();
        b->align(eAlignment::left | eAlignment::bottom);
    }

    {
        const auto b = new eButton(renderer());
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
