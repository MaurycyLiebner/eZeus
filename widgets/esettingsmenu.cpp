#include "esettingsmenu.h"

#include "echeckbox.h"
#include "elabeledwidget.h"
#include "eframedwidget.h"
#include "eframedbutton.h"
#include "eokbutton.h"

#include "elanguage.h"

eSettingsMenu::eSettingsMenu(const eSettings& iniSettings,
                             eMainWindow* const window) :
    eMainMenuBase(window),
    mIniSettings(iniSettings),
    mSettings(iniSettings) {

}

eWidget* createTextureBox(eMainWindow* const window,
                          const bool checked,
                          const eCheckAction& checkA,
                          const std::string& text,
                          const int p) {
    const auto w = new eWidget(window);
    w->setNoPadding();

    const auto b = new eCheckBox(window);
    b->setNoPadding();
    b->setChecked(checked);
    b->setCheckAction(checkA);
    b->fitContent();

    const auto l = new eLabel(window);
    l->setNoPadding();
    l->setSmallFontSize();
    l->setText(text);
    l->fitContent();

    w->addWidget(b);
    w->addWidget(l);
    l->setX(b->width() + p);
    w->fitContent();

    return w;
}

void eSettingsMenu::initialize(const eApplyAction& settingsA,
                               const eFullscreenA& fullscreenA) {
    eMainMenuBase::initialize();

    const auto frame = new eFramedWidget(window());
    frame->setType(eFrameType::message);
    addWidget(frame);

    const auto res = resolution();

    const int p = res.largePadding();
    const int cww = res.centralWidgetLargeWidth();
    const int cwh = res.centralWidgetLargeHeight();
    frame->resize(cww, cwh);

    frame->align(eAlignment::center);

    const auto inner = new eWidget(window());
    inner->setNoPadding();
    frame->addWidget(inner);
    inner->move(2*p, 2*p);
    inner->resize(frame->width() - 4*p, frame->height() - 4*p);

    const int colm = 2*p;
    const int colw = (inner->width() - 2*colm)/3;
    const int colh = inner->height();

    const auto col1 = new eWidget(window());
    col1->setNoPadding();
    col1->setWidth(colw + 2*p);
    col1->setHeight(colh);
    inner->addWidget(col1);

    const auto col2 = new eWidget(window());
    col2->setNoPadding();
    col2->setWidth(colw - p);
    col2->setHeight(colh);
    inner->addWidget(col2);
    col2->setX(colw + 2*p + colm);

    const auto col3 = new eWidget(window());
    col3->setNoPadding();
    col3->setWidth(colw - p);
    col3->setHeight(colh);
    inner->addWidget(col3);
    col3->setX(2*colw + 2*p + 2*colm);

    {
        const auto res = mSettings.fRes;
        const auto& ress = eResolution::sResolutions;
        int y = 0;
        eWidget* col = col2;
        const auto currentButton = std::make_shared<eFramedButton*>();
        const int iMax = ress.size();
        for(int i = 0; i < iMax; i++) {
            const auto& r = ress[i];
            const auto b = new eFramedButton(window());
            b->setSmallPadding();
            b->setUnderline(false);
            b->setText(r.name());
            b->fitContent();
            b->setWidth(col->width() - 2*p);
            if(r == res) {
                *currentButton = b;
                b->setYellowFontColor();
            }
            col->addWidget(b);
            b->setY(y);
            b->align(eAlignment::hcenter);
            b->setPressAction([this, currentButton, b, r]() {
                if(currentButton) {
                    (*currentButton)->setLightFontColor();
                }
                *currentButton = b;
                b->setYellowFontColor();
                mSettings.fRes = r;
            });
            y += b->height() + p;
            if(col->height() - y < b->height()) {
                col = col3;
                y = 0;
            }
        }
    }

    {
        const auto fs = new eFramedButton(window());
        fs->setUnderline(false);
        fs->setText(mSettings.fFullscreen ?
                        eLanguage::zeusText(42, 2) : // windowed screen
                        eLanguage::zeusText(42, 1)); // full screen
        fs->fitContent();
        col1->addWidget(fs);

        fs->setPressAction([this, fs, fullscreenA]() {
            const bool f = !mSettings.fFullscreen;
            mSettings.fFullscreen = f;
            fullscreenA(f);
            fs->setText(f ? eLanguage::zeusText(42, 2) : // windowed screen
                            eLanguage::zeusText(42, 1)); // full screen
            fs->fitContent();
            fs->align(eAlignment::hcenter);
        });
        fs->align(eAlignment::hcenter);
    }

    {
        const auto texsFrame = new eFramedWidget(window());
        texsFrame->setType(eFrameType::inner);
        texsFrame->setNoPadding();

        const auto texsWid = new eWidget(window());

        {
            const auto checkA = [this](const bool c) {
                mSettings.fTinyTextures = c;
            };
            const bool checked = mSettings.fTinyTextures;
            const auto text = eLanguage::text("tiny_textures");
            const auto w = createTextureBox(window(), checked, checkA, text, p);
            texsWid->addWidget(w);
        }

        {
            const auto checkA = [this](const bool c) {
                mSettings.fSmallTextures = c;
            };
            const bool checked = mSettings.fSmallTextures;
            const auto text = eLanguage::text("small_textures");
            const auto w = createTextureBox(window(), checked, checkA, text, p);
            texsWid->addWidget(w);
        }

        {
            const auto checkA = [this](const bool c) {
                mSettings.fMediumTextures = c;
            };
            const bool checked = mSettings.fMediumTextures;
            const auto text = eLanguage::text("medium_textures");
            const auto w = createTextureBox(window(), checked, checkA, text, p);
            texsWid->addWidget(w);
        }

        {
            const auto checkA = [this](const bool c) {
                mSettings.fLargeTextures = c;
            };
            const bool checked = mSettings.fLargeTextures;
            const auto text = eLanguage::text("large_textures");
            const auto w = createTextureBox(window(), checked, checkA, text, p);
            texsWid->addWidget(w);
        }

        texsWid->stackVertically();
        texsWid->fitContent();
        texsFrame->addWidget(texsWid);
        texsFrame->resize(texsWid->width() + 2*p,
                          texsWid->height() + 2*p);
        texsWid->move(2*p, 2*p);
        col1->addWidget(texsFrame);
    }

    col1->layoutVertically();

    {
        const auto b = new eOkButton(window());
        frame->addWidget(b);
        b->setPressAction([this, settingsA]() {
            settingsA(mSettings);
        });
        b->align(eAlignment::bottom | eAlignment::right);
        b->move(b->x() - 2*p, b->y() - 2*p);
    }
}
