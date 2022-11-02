#include "esettingsmenu.h"

#include "ecombobox.h"
#include "echeckbox.h"
#include "elabeledwidget.h"
#include "eframedwidget.h"

#include "elanguage.h"

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
    buttons->setType(eFrameType::message);
    addWidget(buttons);

    const auto res = resolution();

    const int cww = res.centralWidgetLargeWidth();
    const int cwh = res.centralWidgetLargeHeight();
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

        lw->setup(eLanguage::text("resolution"), b);
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

        lw->setup(eLanguage::text("fullscreen"), b);
        buttons->addWidget(lw);
    }

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eCheckBox(window());
        b->setChecked(mSettings.fTinyTextures);
        b->setCheckAction([this](const bool c) {
            mSettings.fTinyTextures = c;
        });
        b->fitContent();

        lw->setup(eLanguage::text("tiny_textures"), b);
        buttons->addWidget(lw);
    }

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eCheckBox(window());
        b->setChecked(mSettings.fSmallTextures);
        b->setCheckAction([this](const bool c) {
            mSettings.fSmallTextures = c;
        });
        b->fitContent();

        lw->setup(eLanguage::text("small_textures"), b);
        buttons->addWidget(lw);
    }

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eCheckBox(window());
        b->setChecked(mSettings.fMediumTextures);
        b->setCheckAction([this](const bool c) {
            mSettings.fMediumTextures = c;
        });
        b->fitContent();

        lw->setup(eLanguage::text("medium_textures"), b);
        buttons->addWidget(lw);
    }

    {
        const auto lw = new eLabeledWidget(window());

        const auto b = new eCheckBox(window());
        b->setChecked(mSettings.fLargeTextures);
        b->setCheckAction([this](const bool c) {
            mSettings.fLargeTextures = c;
        });
        b->fitContent();

        lw->setup(eLanguage::text("large_textures"), b);
        buttons->addWidget(lw);
    }

    buttons->layoutVertically();

    {
        const auto b = new eButton(window());
        b->setPressAction(backA);
        buttons->addWidget(b);
        b->setText(eLanguage::text("back"));
        b->fitContent();
        b->align(eAlignment::left | eAlignment::bottom);
    }

    {
        const auto b = new eButton(window());
        b->setPressAction([this, backA, settingsA]() {
            settingsA(mSettings);
        });
        buttons->addWidget(b);
        b->setText(eLanguage::text("apply"));
        b->fitContent();
        b->align(eAlignment::right | eAlignment::bottom);
    }
}
