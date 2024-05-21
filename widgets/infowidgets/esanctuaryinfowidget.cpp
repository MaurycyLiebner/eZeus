#include "esanctuaryinfowidget.h"

#include "elanguage.h"
#include "widgets/eframedbutton.h"
#include "characters/gods/egod.h"
#include "estringhelpers.h"
#include "buildings/sanctuaries/esanctuary.h"

eSanctuaryInfoWidget::eSanctuaryInfoWidget(
        eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, false) {}

int sTextGodId(const eGodType god) {
    switch(god) {
    case eGodType::zeus:
        return 0;
    case eGodType::poseidon:
        return 1;
    case eGodType::demeter:
        return 2;
    case eGodType::apollo:
        return 3;
    case eGodType::artemis:
        return 4;
    case eGodType::ares:
        return 5;
    case eGodType::aphrodite:
        return 6;
    case eGodType::hermes:
        return 7;
    case eGodType::athena:
        return 8;
    case eGodType::hephaestus:
        return 9;
    case eGodType::dionysus:
        return 10;
    case eGodType::hades:
        return 11;
    case eGodType::hera:
        return 12;
    case eGodType::atlas:
        return 13;
    }
    return 0;
}

void eSanctuaryInfoWidget::initialize(eSanctuary* const s) {
    const auto titles = eBuilding::sNameForBuilding(s);
    const auto title = eLanguage::text(titles);
    eInfoWidget::initialize(title);
    const auto cw = addCentralWidget();
    addEmploymentWidget(s);
    if(s->finished() || true) {
        const auto gt = s->godType();

        const int cww = cw->width();
        const auto descLabel = new eLabel(window());
        descLabel->setNoPadding();
        descLabel->setSmallFontSize();
        descLabel->setWrapWidth(cww);
        const int godId = sTextGodId(gt);
        std::string desc;
        {
            const int string = 66 + godId;
            const auto txt = eLanguage::zeusText(132, string);
            desc = desc + " " + txt;
        }
        {
            const int string = 80 + godId;
            const auto txt = eLanguage::zeusText(132, string);
            desc = desc + " " + txt;
        }
        {
            const int string = 94 + godId;
            const auto txt = eLanguage::zeusText(132, string);
            desc = desc + " " + txt;
        }
        descLabel->setText(desc);
        descLabel->fitContent();
        cw->addWidget(descLabel);

        const auto buttonReasonW = new eWidget(window());
        buttonReasonW->setNoPadding();
        cw->addWidget(buttonReasonW);
        buttonReasonW->setWidth(cww);

        const auto reasonLabel = new eLabel(window());
        reasonLabel->setNoPadding();
        reasonLabel->setSmallFontSize();
        reasonLabel->setWrapWidth(cww);
        buttonReasonW->addWidget(reasonLabel);

        const int string = 10 + godId;
        const auto txt = eLanguage::zeusText(132, string);
        const auto pb = new eFramedButton(txt, window());
        pb->setUnderline(false);
        pb->fitContent();
        buttonReasonW->addWidget(pb);
        pb->align(eAlignment::hcenter);
        pb->setPressAction([s, godId, buttonReasonW, reasonLabel]() {
            eHelpDenialReason reason;
            const bool r = s->askForHelp(reason);
            int string;
            if(!r) {
                switch(reason) {
                case eHelpDenialReason::tooSoon:
                    string = 52 + godId;
                    break;
                case eHelpDenialReason::noTarget:
                    string = 38 + godId;
                    break;
                case eHelpDenialReason::error:
                    string = -1;
                    break;
                }
                reasonLabel->setYellowFontColor();
            } else {
                string = 24 + godId;
                reasonLabel->setLightFontColor();
            }
            const auto txt = eLanguage::zeusText(132, string);
            reasonLabel->setText(txt);
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
