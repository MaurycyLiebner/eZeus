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

    const auto relationshipButton = new eFramedButton(window());
    relationshipButton->setUnderline(false);
    const auto rel = c->relationship();
    const auto relName = eWorldCity::sRelationshipName(rel, false);
    relationshipButton->setText(relName);
    relationshipButton->fitContent();
    relationshipButton->setPressAction([this, relationshipButton,
                                        nationalityButton, c, buttonsW]() {
        const std::vector<eWorldCityRelationship> relationships =
            {eWorldCityRelationship::mainCity,
             eWorldCityRelationship::collony,
             eWorldCityRelationship::vassal,
             eWorldCityRelationship::ally,
             eWorldCityRelationship::rival,
             eWorldCityRelationship::distantCity,
             eWorldCityRelationship::enchantedPlace,
             eWorldCityRelationship::destroyedCity};
        std::vector<std::string> relationshipNames;
        for(const auto r : relationships) {
            int group = 253;
            int string = -1;
            switch(r) {
            case eWorldCityRelationship::mainCity:
                group = 39;
                string = 0;
                break;
            case eWorldCityRelationship::collony:
                group = 39;
                string = 1;
                break;
            case eWorldCityRelationship::vassal:
                group = 253;
                string = 2;
                break;
            case eWorldCityRelationship::ally:
                group = 253;
                string = 0;
                break;
            case eWorldCityRelationship::rival:
                group = 253;
                string = 1;
                break;
            case eWorldCityRelationship::distantCity:
                group = 39;
                string = 4;
                break;
            case eWorldCityRelationship::enchantedPlace:
                group = 39;
                string = 5;
                break;
            case eWorldCityRelationship::destroyedCity:
                group = 39;
                string = 6;
                break;
            }
            const auto name = eLanguage::zeusText(group, string);
            relationshipNames.push_back(name);
        }
        const auto act = [nationalityButton, c, buttonsW,
                          relationships, relationshipNames,
                          relationshipButton](const int val) {
            const auto rel = relationships[val];
            c->setRelationship(rel);
            const auto name = relationshipNames[val];
            relationshipButton->setText(name);
            relationshipButton->fitContent();
            relationshipButton->align(eAlignment::hcenter);

            nationalityButton->setVisible(rel == eWorldCityRelationship::collony ||
                                          rel == eWorldCityRelationship::vassal ||
                                          rel == eWorldCityRelationship::ally ||
                                          rel == eWorldCityRelationship::rival);
            buttonsW->layoutVertically(true);
        };
        const auto d = new eChooseButton(window());
        d->initialize(4, relationshipNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(relationshipButton);
    relationshipButton->align(eAlignment::hcenter);

    nationalityButton->setUnderline(false);
    const auto nationality = c->nationality();
    nationalityButton->setText(nationality);
    nationalityButton->fitContent();
    nationalityButton->setPressAction([this, nationalityButton, c]() {
        const auto d = new eChooseButton(window());
        const std::vector<eWorldCityType> nationalities =
            {eWorldCityType::greekCity,
             eWorldCityType::trojanCity,
             eWorldCityType::persianCity,
             eWorldCityType::centaurCity,
             eWorldCityType::amazonCity,

             eWorldCityType::egyptianCity,
             eWorldCityType::mayanCity,
             eWorldCityType::phoenicianCity,
             eWorldCityType::oceanidCity,
             eWorldCityType::atlanteanCity};
        std::vector<std::string> nationalityNames;
        for(const auto r : nationalities) {
            const auto name = eWorldCity::sNationality(r);
            nationalityNames.push_back(name);
        }
        const auto act = [nationalities, nationalityNames,
                          c, nationalityButton](const int val) {
            const auto nat = nationalities[val];
            c->setType(nat);
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
