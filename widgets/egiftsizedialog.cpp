#include "egiftsizedialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbuttonwithicon.h"
#include "engine/egameboard.h"
#include "engine/egifthelpers.h"

void eGiftSizeDialog::initialize(const eResourceType type,
                                 const stdsptr<eWorldCity>& c,
                                 const eRequestFunction& func,
                                 const eGameBoard& board) {
    const auto r = resolution();
    const double mult = r.multiplier();

    setType(eFrameType::message);

    const auto innerWid = new eWidget(window());
    addWidget(innerWid);
    const int p = std::round(20*mult);
    innerWid->setNoPadding();
    innerWid->move(p, p/2);

    const auto name = c->name();
    const auto rof = eLanguage::text("give_to") + " " + name;
    const auto rofLabel = new eLabel(window());
    rofLabel->setTinyFontSize();
    rofLabel->setSmallPadding();
    rofLabel->setText(rof);
    rofLabel->fitContent();

    innerWid->addWidget(rofLabel);

    const int baseCount = eGiftHelpers::giftCount(type);
    const auto avCount = board.resourceCount(type);
    using gsType = std::vector<std::pair<int, std::string>>;
    gsType gs{{baseCount, "small"},
              {2*baseCount, "medium"},
              {3*baseCount, "large"}};
    const auto typeStr = eResourceTypeHelpers::typeLongName(type);
    for(const auto& g : gs) {
        const int count = g.first;
        if(count > avCount) break;
        const auto countStr = std::to_string(count);
        const auto key = g.second + "_gift_of";
        const auto giftStr = eLanguage::text(key);
        const auto text = giftStr + " " + countStr + " " + typeStr;

        const auto b = new eFramedButtonWithIcon(window());
        b->setPressAction([type, count, func]() {
            func(type, count);
        });
        b->initialize(type, text);
        innerWid->addWidget(b);
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}
