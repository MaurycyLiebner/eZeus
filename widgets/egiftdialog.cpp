#include "egiftdialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbuttonwithicon.h"
#include "engine/egameboard.h"

void eGiftDialog::initialize(const stdsptr<eWorldCity>& c,
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

    std::vector<eResourceType> gifts;
    auto all = eResourceTypeHelpers::extractResourceTypes(
                eResourceType::all);
    all.push_back(eResourceType::drachmas);
    for(const auto r : all) {
        const int count = giftCount(r);
        const int c = board.resourceCount(r);

        if(c >= count) gifts.push_back(r);
    }

    eWidget* ng = nullptr;
    if(gifts.empty()) {
        const auto rof = eLanguage::text("no_gifts_possible") + " " + name;
        const auto label = new eLabel(window());
        label->setTinyFontSize();
        label->setSmallPadding();
        label->setText(rof);
        label->fitContent();
        ng = label;

        innerWid->addWidget(label);
    } else {
        for(const auto s : gifts) {
            const auto b = new eFramedButtonWithIcon(window());
            b->setPressAction([s, func]() {
                func(s);
            });
            const auto typeName = eResourceTypeHelpers::typeLongName(s);
            const auto text = " " + typeName;
            b->initialize(s, text);
            innerWid->addWidget(b);
        }
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
    if(ng) ng->align(eAlignment::hcenter);
}

bool eGiftDialog::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        deleteLater();
    }
    return true;
}

bool eGiftDialog::mousePressEvent(const eMouseEvent& e) {
    const auto b = e.button();
    if(b == eMouseButton::right) {
        deleteLater();
    }
    return true;
}
