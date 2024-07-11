#include "enamewidget.h"

#include "emainwindow.h"
#include "elineedit.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "echoosebutton.h"
#include "eproceedbutton.h"

void eNameWidget::initialize(const std::string& ini,
                             const std::vector<std::string>& names,
                             const eNameChangeAction& nca,
                             const std::string& title,
                             const bool proceed) {
    setType(eFrameType::message);
    const auto innerWidget = new eWidget(window());
    innerWidget->setNoPadding();
    const int p = 2*padding();
    innerWidget->move(p, p);
    addWidget(innerWidget);

    if(!title.empty()) {
        const auto titleL = new eLabel(window());
        titleL->setHugeFontSize();
        titleL->setText(title);
        titleL->fitContent();
        innerWidget->addWidget(titleL);
    }

    const auto le = new eLineEdit(window());
    le->setRenderBg(true);
    le->setText(eLanguage::zeusText(21, 76));
    le->fitContent();
    le->setWidth(3*le->width()/2);
    le->setText(ini);
    le->grabKeyboard();
    if(!proceed) {
        le->setChangeAction([le, nca]() {
            const auto name = le->text();
            if(nca) nca(name);
        });
    }
    innerWidget->addWidget(le);

    const auto buttonsW = new eWidget(window());
    buttonsW->setNoPadding();

    const auto chooseButton = new eFramedButton(window());
    chooseButton->setUnderline(false);
    chooseButton->setSmallFontSize();
    chooseButton->setSmallPadding();
    chooseButton->setText(eLanguage::zeusText(13, 8)); // choose name:
    chooseButton->fitContent();
    buttonsW->addWidget(chooseButton);
    chooseButton->setPressAction([this, names, le, nca]() {
        const auto choose = new eChooseButton(window());
        const auto act = [names, le, nca](const int val) {
            const auto name = names[val];
            le->setText(name);
            if(nca) nca(name);
        };
        choose->initialize(16, names, act, true);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    if(proceed) {
        const auto pW = new eWidget(window());
        pW->setNoPadding();
        const auto continueL = new eLabel(window());
        continueL->setSmallFontSize();
        continueL->setSmallPadding();
        continueL->setText(eLanguage::zeusText(13, 5));
        continueL->fitContent();
        pW->addWidget(continueL);
        const auto pb = new eProceedButton(window());
        pb->setPressAction([le, nca]() {
            const auto text = le->text();
            if(nca) nca(text);
        });
        pW->addWidget(pb);
        pW->stackHorizontally();
        pW->fitContent();
        continueL->align(eAlignment::vcenter);
        buttonsW->addWidget(pW);
        buttonsW->stackHorizontally(2*p);
    }
    buttonsW->fitContent();
    innerWidget->addWidget(buttonsW);

    innerWidget->stackVertically(p);
    innerWidget->fitContent();
    buttonsW->setWidth(innerWidget->width());
    buttonsW->layoutHorizontallyWithoutSpaces();
    resize(innerWidget->x() + innerWidget->width() + p,
           innerWidget->y() + innerWidget->height() + p);
}
