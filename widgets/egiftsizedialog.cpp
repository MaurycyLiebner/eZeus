#include "egiftsizedialog.h"

#include "elanguage.h"
#include "estringhelpers.h"
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
    auto rof = eLanguage::zeusText(41, 0); // give to
    eStringHelpers::replace(rof, "[city_name]", name);
    const auto rofLabel = new eLabel(window());
    rofLabel->setTinyFontSize();
    rofLabel->setSmallPadding();
    rofLabel->setText(rof);
    rofLabel->fitContent();

    innerWid->addWidget(rofLabel);

    const int baseCount = eGiftHelpers::giftCount(type);
    const auto avCount = board.resourceCount(type);
    using gsType = std::vector<std::pair<int, int>>;
    gsType gs{{baseCount, 22}, // small
              {2*baseCount, 23}, // medium
              {3*baseCount, 24}}; // large
    const auto typeStr = eResourceTypeHelpers::typeLongName(type);
    for(const auto& g : gs) {
        const int count = g.first;
        if(count > avCount) break;
        const auto countStr = std::to_string(count);
        const int string = g.second;
        auto giftStr = eLanguage::zeusText(41, string);
        eStringHelpers::replace(giftStr, "[amount]", countStr);
        eStringHelpers::replace(giftStr, "[item]", typeStr);

        const auto b = new eFramedButtonWithIcon(window());
        b->setPressAction([type, count, func]() {
            func(type, count);
        });
        b->initialize(type, giftStr);
        innerWid->addWidget(b);
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}
