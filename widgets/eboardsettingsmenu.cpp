#include "eboardsettingsmenu.h"

#include "eframedbutton.h"
#include "elanguage.h"

#include "engine/emapgenerator.h"

#include "eacceptbutton.h"
#include "ecancelbutton.h"
#include "enumlineedit.h"

#include "engine/egameboard.h"
#include "emainwindow.h"
#include "egamewidget.h"

void eBoardSettingsMenu::initialize(
        eGameWidget* const gw, eGameBoard& board) {
    setType(eFrameType::message);

    const auto boardPtr = &board;

    const auto resizeButt = new eFramedButton(window());
    resizeButt->setUnderline(false);
    resizeButt->setText(eLanguage::text("resize"));
    resizeButt->fitContent();
    resizeButt->setPressAction([this, gw, boardPtr]() {
        const auto resizeMenu = new eFramedWidget(window());
        resizeMenu->setType(eFrameType::message);
        resizeMenu->resize(width(), height());

        const auto res = resolution();
        const int p = res.largePadding();

        const auto iw = new eWidget(window());
        iw->setNoPadding();
        resizeMenu->addWidget(iw);
        iw->move(p, p);

        const auto editW = new eWidget(window());
        editW->setNoPadding();
        iw->addWidget(editW);

        const auto widthL = new eLabel(window());
        widthL->setText(eLanguage::text("width"));
        widthL->fitContent();
        editW->addWidget(widthL);

        const auto width = new eNumLineEdit(window());
        width->setRenderBg(true);
        width->setRange(10, 999);
        width->setValue(999);
        width->fitContent();
        width->setValue(boardPtr->width());
        editW->addWidget(width);

        const auto heightL = new eLabel(window());
        heightL->setText(eLanguage::text("height"));
        heightL->fitContent();
        editW->addWidget(heightL);

        const auto height = new eNumLineEdit(window());
        height->setRenderBg(true);
        height->setRange(10, 999);
        height->setValue(999);
        height->fitContent();
        height->setValue(boardPtr->height());
        editW->addWidget(height);

        editW->stackHorizontally();
        editW->fitContent();

        widthL->align(eAlignment::vcenter);
        width->align(eAlignment::vcenter);
        heightL->align(eAlignment::vcenter);
        height->align(eAlignment::vcenter);

        const auto buttonsW = new eWidget(window());
        buttonsW->setNoPadding();

        const auto accept = new eAcceptButton(window());
        const auto cancel = new eCancelButton(window());
        accept->setPressAction([resizeMenu, width, height, boardPtr, gw]() {
            const int w = width->value();
            const int h = height->value();
            boardPtr->resize(w, h);
            gw->updateViewBoxSize();
            resizeMenu->deleteLater();
        });
        cancel->setPressAction([resizeMenu]() {
            resizeMenu->deleteLater();
        });

        buttonsW->addWidget(accept);
        buttonsW->addWidget(cancel);
        buttonsW->fitHeight();
        buttonsW->setWidth(editW->width());
        buttonsW->layoutHorizontallyWithoutSpaces();
        iw->addWidget(buttonsW);

        iw->stackVertically();
        iw->fitContent();
        resizeMenu->resize(2*p + iw->width(), 2*p + iw->height());

        window()->execDialog(resizeMenu);
        resizeMenu->align(eAlignment::center);
    });
    addWidget(resizeButt);
    resizeButt->align(eAlignment::hcenter);

    const auto generateButt = new eFramedButton(window());
    generateButt->setUnderline(false);
    generateButt->setText(eLanguage::text("generate"));
    generateButt->fitContent();
    generateButt->setPressAction([boardPtr]() {
        eMapGenerator g(*boardPtr);
        eMapGeneratorSettings sett;

        g.generate(sett);
    });
    addWidget(generateButt);
    generateButt->align(eAlignment::hcenter);

    layoutVertically();
}
