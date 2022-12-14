#include "erequestdialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbuttonwithicon.h"

void eRequestDialog::initialize(const stdsptr<eWorldCity>& c,
                                const eRequestFunction& func) {
    const auto r = resolution();
    const double mult = r.multiplier();

    setType(eFrameType::message);

    const auto innerWid = new eWidget(window());
    addWidget(innerWid);
    const int p = std::round(20*mult);
    innerWid->setNoPadding();
    innerWid->move(p, p/2);

    const auto name = c->name();
    const auto rof = eLanguage::text("request_of") + " " + name;
    const auto rofLabel = new eLabel(window());
    rofLabel->setTinyFontSize();
    rofLabel->setSmallPadding();
    rofLabel->setText(rof);
    rofLabel->fitContent();

    innerWid->addWidget(rofLabel);

    const auto tradeSells = c->sells();
    std::vector<eResourceType> sells;
    for(const auto& ts : tradeSells) {
        sells.push_back(ts.fType);
    }
    const int att = c->attitude();
    const auto rel = c->relationship();
    sells.push_back(eResourceType::drachmas);
    if(att <= 50 && rel != eWorldCityRelationship::rival) {
        const auto notReg = eLanguage::text("not_regarded_enough");
        const int p = std::round(13*mult);
        const int h = 2*p;
        for(const auto s : sells) {
            const auto typeName = eResourceTypeHelpers::typeLongName(s);
            const auto text = notReg + " " + typeName;
            const auto l = new eLabel(window());
            l->setTinyFontSize();
            l->setText(text);
            l->fitContent();
            l->setHeight(h);
            l->setTextAlignment(eAlignment::vcenter);
            innerWid->addWidget(l);
        }
    } else {
        for(const auto s : sells) {
            const auto b = new eFramedButtonWithIcon(window());
            b->setPressAction([s, func]() {
                func(s);
            });
            std::string request;
            const auto rel = c->relationship();
            if(rel == eWorldCityRelationship::collony ||
               rel == eWorldCityRelationship::vassal) {
                request = eLanguage::text("order");
            } else if(rel == eWorldCityRelationship::rival) {
                request = eLanguage::text("demand");
            } else {
                request = eLanguage::text("request");
            }
            const auto typeName = eResourceTypeHelpers::typeLongName(s);
            const auto text = request + " " + typeName;
            b->initialize(s, text);
            innerWid->addWidget(b);
        }
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}
