#include "erequestdialog.h"

#include "elanguage.h"
#include "elabel.h"
#include "eframedbutton.h"

class eFramedButtonWithIcon : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    void initialize(const std::shared_ptr<eTexture>& icon,
                    const std::string& text) {
        const auto r = resolution();
        const double mult = r.multiplier();

        const int p = std::round(13*mult);
        const int w = r.centralWidgetSmallWidth();
        setWidth(w);
        setHeight(2*p);
        setNoPadding();

        const auto iconLabel = new eLabel(window());
        iconLabel->setNoPadding();
        iconLabel->setTexture(icon);
        iconLabel->fitContent();
        addWidget(iconLabel);

        const auto textLabel = new eLabel(window());
        textLabel->setNoPadding();
        textLabel->setTinyFontSize();
        textLabel->setText(text);
        textLabel->fitContent();
        addWidget(textLabel);

        iconLabel->setX(p);
        textLabel->setX(iconLabel->x() + iconLabel->width() + p);

        iconLabel->align(eAlignment::vcenter);
        textLabel->align(eAlignment::vcenter);
    }
};

void eRequestDialog::initialize(const stdsptr<eWorldCity>& c,
                                const eRequestFunction& func) {
    const auto r = resolution();
    const auto uiScale = r.uiScale();
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

    sells.push_back(eResourceType::drachmas);
    for(const auto s : sells) {
        const auto b = new eFramedButtonWithIcon(window());
        b->setPressAction([s, func]() {
            func(s);
        });
        const auto icon = eResourceTypeHelpers::icon(uiScale, s);
        std::string request;
        const auto rel = c->relationship();
        if(rel == eWorldCityRelationship::collony ||
           rel == eWorldCityRelationship::vassal) {
            request = eLanguage::text("order");
        } else {
            request = eLanguage::text("request");
        }
        const auto typeName = eResourceTypeHelpers::typeLongName(s);
        const auto text = request + " " + typeName;
        b->initialize(icon, text);
        innerWid->addWidget(b);
    }

    innerWid->stackVertically();
    innerWid->fitContent();

    fitContent();
    rofLabel->align(eAlignment::hcenter);
}

bool eRequestDialog::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        deleteLater();
    }
    return true;
}

bool eRequestDialog::mousePressEvent(const eMouseEvent& e) {
    const auto b = e.button();
    if(b == eMouseButton::right) {
        deleteLater();
    }
    return true;
}
