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
            gw->updateTopBottomAltitude();
            gw->updateMinMaxAltitude();
            gw->updateMaps();
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
    generateButt->setPressAction([this, gw, boardPtr]() {
        const auto generateMenu = new eFramedWidget(window());
        generateMenu->setType(eFrameType::message);
        generateMenu->resize(width(), height());

        const auto res = resolution();
        const int p = res.largePadding();

        const auto iw = new eWidget(window());
        iw->setNoPadding();
        generateMenu->addWidget(iw);
        iw->move(p, p);

        const auto editW = new eWidget(window());
        editW->setNoPadding();
        iw->addWidget(editW);

        const auto col1 = new eWidget(window());
        col1->setNoPadding();
        editW->addWidget(col1);

        const auto col2 = new eWidget(window());
        col2->setNoPadding();
        editW->addWidget(col2);

        using eNumLineEditPtr = eNumLineEdit*;
        const auto createW = [&](const std::string& name,
                                 const int value,
                                 eNumLineEditPtr& numEdit) {
            const auto w = new eWidget(window());
            w->setNoPadding();

            const auto label = new eLabel(window());
            label->setText(eLanguage::text(name));
            label->fitContent();
            w->addWidget(label);

            numEdit = new eNumLineEdit(window());
            numEdit->setRenderBg(true);
            numEdit->setRange(0, 999);
            numEdit->setValue(value);
            numEdit->fitContent();
            w->addWidget(numEdit);

            w->stackHorizontally();
            w->fitContent();
            return w;
        };

        using eMGS = eMapGeneratorSettings;

        eNumLineEdit* waterE;
        const auto waterW = createW("water",
                                    eMGS::sLastWater,
                                    waterE);
        col1->addWidget(waterW);

        eNumLineEdit* forestE;
        const auto forestW = createW("forest",
                                     eMGS::sLastForest,
                                     forestE);
        col1->addWidget(forestW);

        eNumLineEdit* forestToFertileE;
        const auto forestToFertileW = createW("forest_to_fertile",
                                              eMGS::sLastForestToFertile,
                                              forestToFertileE);
        col1->addWidget(forestToFertileW);

        eNumLineEdit* fertileE;
        const auto fertileW = createW("fertile",
                                      eMGS::sLastFertile,
                                      fertileE);
        col1->addWidget(fertileW);

        eNumLineEdit* emptyDryE;
        const auto emptyDryW = createW("empty_dry",
                                       eMGS::sLastEmptyDry,
                                       emptyDryE);
        col1->addWidget(emptyDryW);

        eNumLineEdit* scrubDryE;
        const auto scrubDryW = createW("scrub_dry",
                                       eMGS::sLastScrubDry,
                                       scrubDryE);
        col2->addWidget(scrubDryW);

        eNumLineEdit* flatStonesE;
        const auto flatStonesW = createW("flat_stones",
                                         eMGS::sLastFlatStones,
                                         flatStonesE);
        col2->addWidget(flatStonesW);

        eNumLineEdit* tallStonesE;
        const auto tallStonesW = createW("tall_stones",
                                         eMGS::sLastTallStones,
                                         tallStonesE);
        col2->addWidget(tallStonesW);

        eNumLineEdit* elevationE;
        const auto elevationW = createW("elevation",
                                        eMGS::sLastElevation,
                                        elevationE);
        col2->addWidget(elevationW);

        col1->stackVertically();
        col1->fitContent();
        col2->stackVertically();
        col2->fitContent();

        editW->stackHorizontally();
        editW->fitContent();

        const auto buttonsW = new eWidget(window());
        buttonsW->setNoPadding();

        const auto accept = new eAcceptButton(window());
        const auto cancel = new eCancelButton(window());
        accept->setPressAction([generateMenu, boardPtr, gw,
                               waterE, forestE, forestToFertileE,
                               fertileE, emptyDryE, scrubDryE,
                               flatStonesE, tallStonesE,
                               elevationE]() {
            eMapGenerator g(*boardPtr);
            eMapGeneratorSettings sett;
            sett.fWater = waterE->value();
            sett.fForest = forestE->value();
            sett.fForestToFertile = forestToFertileE->value();
            sett.fFertile = fertileE->value();
            sett.fEmptyDry = emptyDryE->value();
            sett.fScrubDry = scrubDryE->value();
            sett.fFlatStones = flatStonesE->value();
            sett.fTallStones = tallStonesE->value();
            sett.fElevation = elevationE->value();
            g.generate(sett);
            gw->updateTopBottomAltitude();
            gw->updateMinMaxAltitude();
            gw->updateMaps();
            generateMenu->deleteLater();
        });
        cancel->setPressAction([generateMenu]() {
            generateMenu->deleteLater();
        });

        buttonsW->addWidget(accept);
        buttonsW->addWidget(cancel);
        buttonsW->fitHeight();
        buttonsW->setWidth(editW->width());
        buttonsW->layoutHorizontallyWithoutSpaces();
        iw->addWidget(buttonsW);

        iw->stackVertically();
        iw->fitContent();
        generateMenu->resize(2*p + iw->width(), 2*p + iw->height());

        window()->execDialog(generateMenu);
        generateMenu->align(eAlignment::center);
    });
    addWidget(generateButt);
    generateButt->align(eAlignment::hcenter);

    const auto clearButt = new eFramedButton(window());
    clearButt->setUnderline(false);
    clearButt->setText(eLanguage::text("clear"));
    clearButt->fitContent();
    clearButt->setPressAction([gw, boardPtr]() {
        boardPtr->initialize(boardPtr->width(), boardPtr->height());
        gw->updateTopBottomAltitude();
        gw->updateMaps();
    });
    addWidget(clearButt);
    clearButt->align(eAlignment::hcenter);

    layoutVertically();
}
