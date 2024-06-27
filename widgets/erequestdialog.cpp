#include "erequestdialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbuttonwithicon.h"
#include "estringhelpers.h"
#include "textures/egametextures.h"
#include "emessagewidget.h"

void eRequestDialog::initialize(const stdsptr<eWorldCity>& c,
                                const eRequestFunction& func,
                                const eAction& requestDefensiveAid,
                                const eAction& requestStrike) {
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
    sells.push_back(eResourceType::drachmas);
    if(att <= 50 && !c->isRival()) {
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
            if(c->isVassal() || c->isColony()) {
                request = eLanguage::zeusText(41, 5); // order
            } else if(c->isRival()) {
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

    if(!c->isRival()) {
        if(att <= 65) {
            const int p = std::round(13*mult);
            const int h = 2*p;

            {
                const auto text = eLanguage::zeusText(41, 9); // not regarded defensive aid
                const auto l = new eLabel(window());
                l->setTinyFontSize();
                l->setText(text);
                l->fitContent();
                l->setHeight(h);
                l->setTextAlignment(eAlignment::vcenter);
                innerWid->addWidget(l);
            }

            {
                const auto text = eLanguage::zeusText(41, 10); // not regarded strike
                const auto l = new eLabel(window());
                l->setTinyFontSize();
                l->setText(text);
                l->fitContent();
                l->setHeight(h);
                l->setTextAlignment(eAlignment::vcenter);
                innerWid->addWidget(l);
            }
        } else if(c->army() < 2) {
            const int p = std::round(13*mult);
            const int h = 2*p;

            {
                const auto text = eLanguage::zeusText(41, 17); // can't spare defensive aid
                const auto l = new eLabel(window());
                l->setTinyFontSize();
                l->setText(text);
                l->fitContent();
                l->setHeight(h);
                l->setTextAlignment(eAlignment::vcenter);
                innerWid->addWidget(l);
            }

            {
                const auto text = eLanguage::zeusText(41, 18); // can't spare strike
                const auto l = new eLabel(window());
                l->setTinyFontSize();
                l->setText(text);
                l->fitContent();
                l->setHeight(h);
                l->setTextAlignment(eAlignment::vcenter);
                innerWid->addWidget(l);
            }
        } else {
            const auto r = resolution();
            const auto uiScale = r.uiScale();
            const int icoll = static_cast<int>(uiScale);
            const auto& intrfc = eGameTextures::interface();
            const auto& coll = intrfc[icoll];

            {
                const auto b = new eFramedButtonWithIcon(window());
                b->setPressAction(requestDefensiveAid);
                const auto request = eLanguage::zeusText(41, 7); // request defensive aid
                b->initialize(coll.fTroopsRequestIcon, request);
                innerWid->addWidget(b);
            }

            {
                const auto b = new eFramedButtonWithIcon(window());
                b->setPressAction(requestStrike);
                const auto request = eLanguage::zeusText(41, 8); // request military strike
                b->initialize(coll.fTroopsRequestIcon, request);
                innerWid->addWidget(b);
            }
        }
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}
