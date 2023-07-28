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
    if(s->finished() || true) {
        const auto gt = s->godType();
        const auto gn  = eGod::sGodName(gt);
        auto pbStr = eLanguage::text("pray_to");
        eStringHelpers::replace(pbStr, "%1", gn);
        const auto pb = new eFramedButton(pbStr, window());
        pb->setUnderline(false);
        pb->fitContent();
        cw->addWidget(pb);
        pb->align(eAlignment::center);
        pb->setPressAction([s]() {
            eHelpDenialReason reason;
            const bool r = s->askForHelp(reason);
        });
    } else {

    }
    addEmploymentWidget(s);
}
