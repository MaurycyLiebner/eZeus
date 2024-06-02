#include "ecitysettingswidget.h"

#include "eframedbutton.h"
#include "elanguage.h"
#include "etradeeditwidget.h"
#include "emainwindow.h"
#include "eresourcebutton.h"
#include "evaluebutton.h"
#include "elineedit.h"
#include "echoosebutton.h"

class eTributeSettingsWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const stdsptr<eWorldCity>& c) {
        setType(eFrameType::message);
        const auto innerWidget = new eWidget(window());
        innerWidget->setNoPadding();
        const int p = 2*padding();
        innerWidget->move(p, p);
        addWidget(innerWidget);

        const auto countButton = new eValueButton(window());
        countButton->initialize(1, 9999);
        countButton->setValue(c->tributeCount());
        countButton->setValueChangeAction([c](const int v) {
            c->setTributeCount(v);
        });
        innerWidget->addWidget(countButton);

        const auto resButton = new eResourceButton(window());
        resButton->initialize([this, p, innerWidget, c](
                              const eResourceType r) {
            c->setTributeType(r);
            innerWidget->fitContent();
            resize(innerWidget->x() + innerWidget->width() + p,
                   innerWidget->y() + innerWidget->height() + p);
        }, true);
        resButton->setResource(c->tributeType());
        innerWidget->addWidget(resButton);

        innerWidget->stackHorizontally();
        innerWidget->fitContent();
        resize(innerWidget->x() + innerWidget->width() + p,
               innerWidget->y() + innerWidget->height() + p);
    }
};

class eNameWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eNameChangeAction = std::function<void(const std::string&)>;
    void initialize(const stdsptr<eWorldCity>& c,
                    const eNameChangeAction& nca) {
        setType(eFrameType::message);
        const auto innerWidget = new eWidget(window());
        innerWidget->setNoPadding();
        const int p = 2*padding();
        innerWidget->move(p, p);
        addWidget(innerWidget);

        const auto le = new eLineEdit(window());
        le->setRenderBg(true);
        le->setText(eLanguage::zeusText(21, 76));
        le->fitContent();
        le->setWidth(3*le->width()/2);
        le->setText(c->name());
        le->grabKeyboard();
        le->setChangeAction([c, le, nca]() {
            const auto name = le->text();
            c->setName(name);
            if(nca) nca(name);
        });
        innerWidget->addWidget(le);

        const auto chooseButton = new eFramedButton(window());
        chooseButton->setUnderline(false);
        chooseButton->setText(eLanguage::text("choose"));
        chooseButton->fitContent();
        innerWidget->addWidget(chooseButton);
        chooseButton->setPressAction([this, le, c, nca]() {
            const auto cityNames = eWorldCity::sNames();
            const auto choose = new eChooseButton(window());
            const auto act = [cityNames, le, c, nca](const int val) {
                const auto name = cityNames[val];
                le->setText(name);
                c->setName(name);
                if(nca) nca(name);
            };
            choose->initialize(16, cityNames, act, true);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        });

        innerWidget->stackHorizontally();
        innerWidget->fitContent();
        resize(innerWidget->x() + innerWidget->width() + p,
               innerWidget->y() + innerWidget->height() + p);
    }
};

void eCitySettingsWidget::initialize(const stdsptr<eWorldCity>& c) {
    if(!c) return;
    setType(eFrameType::message);
    const auto res = resolution();
    const int w = res.centralWidgetSmallWidth();
    const int h = res.centralWidgetSmallHeight();
    resize(w, h);

    const int p = 2*padding();

    const auto buttonsW = new eWidget(window());
    buttonsW->setNoPadding();
    addWidget(buttonsW);
    buttonsW->move(p, p);
    buttonsW->resize(w - 2*p, h - 2*p);

    const auto nameButton = new eFramedButton(window());
    nameButton->setText(c->name());
    nameButton->fitContent();
    nameButton->setPressAction([this, nameButton, c]() {
        const auto d = new eNameWidget(window());
        d->initialize(c, [nameButton](const std::string& name) {
            nameButton->setText(name);
            nameButton->fitContent();
            nameButton->align(eAlignment::hcenter);
        });

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(nameButton);
    nameButton->align(eAlignment::hcenter);

    const auto nationalityButton = new eFramedButton(window());
    const auto directionButton = new eFramedButton(window());
    const auto type = c->type();
    nationalityButton->setVisible(type == eCityType::foreignCity ||
                                  type == eCityType::colony);
    directionButton->setVisible(type == eCityType::distantCity);

    const auto typeButton = new eFramedButton(window());
    typeButton->setUnderline(false);
    const auto rel = c->type();
    const auto relName = eWorldCity::sTypeName(rel);
    typeButton->setText(relName);
    typeButton->fitContent();
    typeButton->setPressAction([this, typeButton, directionButton,
                                nationalityButton, c, buttonsW]() {
        const std::vector<eCityType> types =
            {eCityType::parentCity,
             eCityType::colony,
             eCityType::foreignCity,
             eCityType::distantCity,
             eCityType::enchantedPlace,
             eCityType::destroyedCity};
        std::vector<std::string> typeNames;
        for(const auto t : types) {
            const auto name = eWorldCity::sTypeName(t);
            typeNames.push_back(name);
        }
        const auto act = [nationalityButton, directionButton,
                          c, buttonsW, types, typeNames,
                          typeButton](const int val) {
            const auto type = types[val];
            c->setType(type);
            const auto name = typeNames[val];
            typeButton->setText(name);
            typeButton->fitContent();
            typeButton->align(eAlignment::hcenter);

            nationalityButton->setVisible(type == eCityType::foreignCity ||
                                          type == eCityType::colony);
            directionButton->setVisible(type == eCityType::distantCity);
            buttonsW->layoutVertically(true);
        };
        const auto d = new eChooseButton(window());
        d->initialize(3, typeNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(typeButton);
    typeButton->align(eAlignment::hcenter);

    nationalityButton->setUnderline(false);
    const auto nationality = c->nationality();
    nationalityButton->setText(eWorldCity::sNationalityName(nationality));
    nationalityButton->fitContent();
    nationalityButton->setPressAction([this, nationalityButton, c]() {
        const auto d = new eChooseButton(window());
        const std::vector<eNationality> nationalities =
            {eNationality::greek,
             eNationality::trojan,
             eNationality::persian,
             eNationality::centaur,
             eNationality::amazon,

             eNationality::egyptian,
             eNationality::mayan,
             eNationality::phoenician,
             eNationality::oceanid,
             eNationality::atlantean};
        std::vector<std::string> nationalityNames;
        for(const auto r : nationalities) {
            const auto name = eWorldCity::sNationalityName(r);
            nationalityNames.push_back(name);
        }
        const auto act = [nationalities, nationalityNames,
                          c, nationalityButton](const int val) {
            const auto nat = nationalities[val];
            c->setNationality(nat);
            const auto name = nationalityNames[val];
            nationalityButton->setText(name);
            nationalityButton->fitContent();
            nationalityButton->align(eAlignment::hcenter);
        };
        d->initialize(5, nationalityNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(nationalityButton);
    nationalityButton->align(eAlignment::hcenter);

    directionButton->setUnderline(false);
    const auto dir = c->direction();
    directionButton->setText(eWorldCity::sDirectionName(dir));
    directionButton->fitContent();
    directionButton->setPressAction([this, directionButton, c]() {
        const auto d = new eChooseButton(window());
        const std::vector<eDistantDirection> directions =
            {eDistantDirection::none,
             eDistantDirection::N,
             eDistantDirection::NE,
             eDistantDirection::E,
             eDistantDirection::SE,
             eDistantDirection::S,
             eDistantDirection::SW,
             eDistantDirection::W,
             eDistantDirection::NW};
        std::vector<std::string> directionNames;
        for(const auto r : directions) {
            const auto name = eWorldCity::sDirectionName(r);
            directionNames.push_back(name);
        }
        const auto act = [directions, directionNames,
                          c, directionButton](const int val) {
            const auto dir = directions[val];
            c->setDirection(dir);
            const auto name = directionNames[val];
            directionButton->setText(name);
            directionButton->fitContent();
            directionButton->align(eAlignment::hcenter);
        };
        d->initialize(5, directionNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(directionButton);
    directionButton->align(eAlignment::hcenter);

    const auto buysButton = new eFramedButton(window());
    buysButton->setUnderline(false);
    buysButton->setText(eLanguage::zeusText(47, 1));
    buysButton->fitContent();
    buysButton->setPressAction([this, c]() {
        const auto d = new eTradeEditWidget(window());
        const auto res = resolution();
        const int w = res.centralWidgetSmallWidth();
        const int h = res.centralWidgetSmallHeight();
        d->resize(w, h);
        d->initialize(&c->buys());

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(buysButton);
    buysButton->align(eAlignment::hcenter);

    const auto sellsButton = new eFramedButton(window());
    sellsButton->setUnderline(false);
    sellsButton->setText(eLanguage::zeusText(47, 2));
    sellsButton->fitContent();
    sellsButton->setPressAction([this, c]() {
        const auto d = new eTradeEditWidget(window());
        const auto res = resolution();
        const int w = res.centralWidgetSmallWidth();
        const int h = res.centralWidgetSmallHeight();
        d->resize(w, h);
        d->initialize(&c->sells());

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(sellsButton);
    sellsButton->align(eAlignment::hcenter);

    const auto tributeButton = new eFramedButton(window());
    tributeButton->setUnderline(false);
    tributeButton->setText(eLanguage::text("tribute"));
    tributeButton->fitContent();
    tributeButton->setPressAction([this, c]() {
        const auto d = new eTributeSettingsWidget(window());
        d->initialize(c);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(tributeButton);
    tributeButton->align(eAlignment::hcenter);

    buttonsW->layoutVertically(true);
}
