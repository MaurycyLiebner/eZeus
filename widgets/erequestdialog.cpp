#include "erequestdialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbuttonwithicon.h"
#include "estringhelpers.h"

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
    auto rof = eLanguage::zeusText(41, 1); // request of
    eStringHelpers::replace(rof, "[city_name]", name);
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
        const auto notReg = eLanguage::zeusText(41, 11); // not regarded
        const int p = std::round(13*mult);
        const int h = 2*p;
        for(const auto s : sells) {
            const auto typeName = eResourceTypeHelpers::typeLongName(s);
            auto text = notReg;
            eStringHelpers::replace(text, "[item]", typeName);
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
                request = eLanguage::zeusText(41, 5); // order
            } else if(rel == eWorldCityRelationship::rival) {
                request = eLanguage::zeusText(41, 4); // demand
            } else {
                request = eLanguage::zeusText(41, 3); // request
            }
            const auto typeName = eResourceTypeHelpers::typeLongName(s);
            eStringHelpers::replace(request, "[item]", typeName);
            b->initialize(s, request);
            innerWid->addWidget(b);
        }
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}
