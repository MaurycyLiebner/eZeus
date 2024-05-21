#include "esanctuaryinfowidget.h"

#include "elanguage.h"
#include "widgets/eframedbutton.h"
#include "characters/gods/egod.h"
#include "estringhelpers.h"
#include "buildings/sanctuaries/esanctuary.h"

eSanctuaryInfoWidget::eSanctuaryInfoWidget(
        eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, true) {}

void eSanctuaryInfoWidget::initialize(eSanctuary* const s) {
    const auto titles = eBuilding::sNameForBuilding(s);
    const auto title = eLanguage::text(titles);
    eInfoWidget::initialize(title);
    const auto cw = addCentralWidget();
    addEmploymentWidget(s);
    if(s->finished() || true) {
        const auto gt = s->godType();
        const auto gn  = eGod::sGodName(gt);

        auto gnl = gn;
        const auto tolower = [](unsigned char c) {
            return std::tolower(c);
        };
        std::transform(gnl.begin(), gnl.end(), gnl.begin(), tolower);

        const int cww = cw->width();
        const auto descLabel = new eLabel(window());
        descLabel->setNoPadding();
        descLabel->setSmallFontSize();
        descLabel->setWrapWidth(cww);
        descLabel->setText(eLanguage::text(gnl + "_sanctuary_desc"));
        descLabel->fitContent();
        cw->addWidget(descLabel);

        const auto buttonReasonW = new eWidget(window());
        buttonReasonW->setNoPadding();
        cw->addWidget(buttonReasonW);
        buttonReasonW->setWidth(cww);

        const auto reasonLabel = new eLabel(window());
        reasonLabel->setNoPadding();
        reasonLabel->setWrapWidth(cww);
        buttonReasonW->addWidget(reasonLabel);

        auto pbStr = eLanguage::text("pray_to");
        eStringHelpers::replace(pbStr, "%1", gn);
        const auto pb = new eFramedButton(pbStr, window());
        pb->setUnderline(false);
        pb->fitContent();
        buttonReasonW->addWidget(pb);
        pb->align(eAlignment::hcenter);
        pb->setPressAction([s, gnl, buttonReasonW, reasonLabel]() {
            eHelpDenialReason reason;
            const bool r = s->askForHelp(reason);

            std::string txt;
            if(!r) {
                switch(reason) {
                case eHelpDenialReason::tooSoon:
                    txt = gnl + "_help_too_soon";
                    break;
                case eHelpDenialReason::noTarget:
                    txt = gnl + "_help_no_target";
                    break;
                case eHelpDenialReason::error:
                    break;
                }
                reasonLabel->setYellowFontColor();
            } else {
                reasonLabel->setLightFontColor();
            }
            reasonLabel->setText(eLanguage::text(txt));
            reasonLabel->fitContent();

            buttonReasonW->stackVertically();
            buttonReasonW->fitHeight();
            buttonReasonW->align(eAlignment::bottom);
        });

        buttonReasonW->stackVertically();
        buttonReasonW->fitHeight();
        buttonReasonW->align(eAlignment::bottom);
    } else {

    }
}
