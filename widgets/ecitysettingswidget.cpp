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
    void initialize(const std::string& ini,
                    const std::vector<std::string>& names,
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
        le->setText(ini);
        le->grabKeyboard();
        le->setChangeAction([le, nca]() {
            const auto name = le->text();
            if(nca) nca(name);
        });
        innerWidget->addWidget(le);

        const auto chooseButton = new eFramedButton(window());
        chooseButton->setUnderline(false);
        chooseButton->setText(eLanguage::text("choose"));
        chooseButton->fitContent();
        innerWidget->addWidget(chooseButton);
        chooseButton->setPressAction([this, names, le, nca]() {
            const auto choose = new eChooseButton(window());
            const auto act = [names, le, nca](const int val) {
                const auto name = names[val];
                le->setText(name);
                if(nca) nca(name);
            };
            choose->initialize(16, names, act, true);

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
    const int h = res.centralWidgetLargeHeight();
    resize(w, h);

    const int p = 2*padding();

    const auto buttonsW = new eWidget(window());
    buttonsW->setNoPadding();
    addWidget(buttonsW);
    buttonsW->move(p, p);
    buttonsW->resize(w - 2*p, h - 2*p);

    const auto nameButton = new eFramedButton(window());
    nameButton->setUnderline(false);
    const auto n = c->name();
    nameButton->setText(n.empty() ? eLanguage::text("name") : n);
    nameButton->fitContent();
    nameButton->setPressAction([this, nameButton, c]() {
        const auto d = new eNameWidget(window());
        d->initialize(c->name(), eWorldCity::sNames(),
                      [c, nameButton](const std::string& name) {
            c->setName(name);
            nameButton->setText(name);
            nameButton->fitContent();
            nameButton->align(eAlignment::hcenter);
        });

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(nameButton);
    nameButton->align(eAlignment::hcenter);

    const auto leaderButton = new eFramedButton(window());
    leaderButton->setUnderline(false);
    const auto l = c->leader();
    leaderButton->setText(l.empty() ? eLanguage::text("leader") : l);
    leaderButton->fitContent();
    leaderButton->setPressAction([this, leaderButton, c]() {
        const auto d = new eNameWidget(window());
        d->initialize(c->leader(), eWorldCity::sLeaders(),
                      [c, leaderButton](const std::string& name) {
            c->setLeader(name);
            leaderButton->setText(name);
            leaderButton->fitContent();
            leaderButton->align(eAlignment::hcenter);
        });

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(leaderButton);
    leaderButton->align(eAlignment::hcenter);

    const auto relationshipButton = new eFramedButton(window());
    const auto nationalityButton = new eFramedButton(window());
    const auto stateButton = new eFramedButton(window());
    const auto attitudeButton = new eFramedButton(window());
    const auto directionButton = new eFramedButton(window());
    const auto type = c->type();
    relationshipButton->setVisible(type == eCityType::foreignCity);
    nationalityButton->setVisible(type == eCityType::foreignCity ||
                                  type == eCityType::colony);
    stateButton->setVisible(type == eCityType::colony);
    attitudeButton->setVisible(type == eCityType::foreignCity ||
                               type == eCityType::colony);
    directionButton->setVisible(type == eCityType::distantCity);

    const auto typeButton = new eFramedButton(window());
    typeButton->setUnderline(false);
    const auto rel = c->type();
    const auto relName = eWorldCity::sTypeName(rel);
    typeButton->setText(relName);
    typeButton->fitContent();
    typeButton->setPressAction([this, relationshipButton, typeButton,
                               directionButton, nationalityButton,
                               stateButton, attitudeButton,
                               c, buttonsW]() {
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
        const auto act = [relationshipButton, nationalityButton,
                          stateButton, directionButton,
                          attitudeButton, c, buttonsW,
                          types, typeNames, typeButton](const int val) {
            const auto type = types[val];
            c->setType(type);
            const auto name = typeNames[val];
            typeButton->setText(name);
            typeButton->fitContent();
            typeButton->align(eAlignment::hcenter);

            relationshipButton->setVisible(type == eCityType::foreignCity);
            nationalityButton->setVisible(type == eCityType::foreignCity ||
                                          type == eCityType::colony);
            stateButton->setVisible(type == eCityType::colony);
            attitudeButton->setVisible(type == eCityType::foreignCity ||
                                       type == eCityType::colony);
            directionButton->setVisible(type == eCityType::distantCity);
            buttonsW->layoutVertically(true);

            const auto attitude = c->attitudeClass();
            attitudeButton->setText(eWorldCity::sAttitudeName(attitude));
            attitudeButton->fitContent();
            attitudeButton->align(eAlignment::hcenter);
        };
        const auto d = new eChooseButton(window());
        d->initialize(3, typeNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(typeButton);
    typeButton->align(eAlignment::hcenter);

    relationshipButton->setUnderline(false);
    const auto relationship = c->relationship();
    relationshipButton->setText(eWorldCity::sRelationshipName(relationship));
    relationshipButton->fitContent();
    relationshipButton->setPressAction([this, attitudeButton,
                                       relationshipButton, c]() {
        const auto d = new eChooseButton(window());
        const std::vector<eForeignCityRelationship> relationships =
            {eForeignCityRelationship::vassal,
             eForeignCityRelationship::ally,
             eForeignCityRelationship::rival};
        std::vector<std::string> relationshipNames;
        for(const auto r : relationships) {
            const auto name = eWorldCity::sRelationshipName(r);
            relationshipNames.push_back(name);
        }
        const auto act = [attitudeButton,
                          relationships, relationshipNames,
                          c, relationshipButton](const int val) {
            const auto rel = relationships[val];
            c->setRelationship(rel);
            const auto name = relationshipNames[val];
            relationshipButton->setText(name);
            relationshipButton->fitContent();
            relationshipButton->align(eAlignment::hcenter);

            const auto attitude = c->attitudeClass();
            attitudeButton->setText(eWorldCity::sAttitudeName(attitude));
            attitudeButton->fitContent();
            attitudeButton->align(eAlignment::hcenter);
        };
        d->initialize(5, relationshipNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(relationshipButton);
    relationshipButton->align(eAlignment::hcenter);

    stateButton->setUnderline(false);
    const auto state = c->state();
    stateButton->setText(eWorldCity::sStateName(state));
    stateButton->fitContent();
    stateButton->setPressAction([this, stateButton, c]() {
        const auto d = new eChooseButton(window());
        const std::vector<eCityState> states =
            {eCityState::active, eCityState::inactive};
        std::vector<std::string> stateNames;
        for(const auto s : states) {
            const auto name = eWorldCity::sStateName(s);
            stateNames.push_back(name);
        }
        const auto act = [stateButton, states, stateNames, c](const int val) {
            const auto state = states[val];
            c->setState(state);
            const auto name = stateNames[val];
            stateButton->setText(name);
            stateButton->fitContent();
            stateButton->align(eAlignment::hcenter);
        };
        d->initialize(5, stateNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(stateButton);
    stateButton->align(eAlignment::hcenter);

    attitudeButton->setUnderline(false);
    const auto attitude = c->attitudeClass();
    attitudeButton->setText(eWorldCity::sAttitudeName(attitude));
    attitudeButton->fitContent();
    attitudeButton->setPressAction([this, attitudeButton, c]() {
        const auto d = new eChooseButton(window());
        std::vector<eCityAttitude> attitudes;
        if(c->isAlly()) {
            attitudes.push_back(eCityAttitude::annoyed);
            attitudes.push_back(eCityAttitude::apatheticA);
            attitudes.push_back(eCityAttitude::sympathetic);
            attitudes.push_back(eCityAttitude::congenial);
            attitudes.push_back(eCityAttitude::helpful);
        } else if(c->isVassal() || c->isColony()) {
            attitudes.push_back(eCityAttitude::angry);
            attitudes.push_back(eCityAttitude::bitter);
            attitudes.push_back(eCityAttitude::loyal);
            attitudes.push_back(eCityAttitude::dedicated);
            attitudes.push_back(eCityAttitude::devoted);
        } else { // rival
            attitudes.push_back(eCityAttitude::furious);
            attitudes.push_back(eCityAttitude::displeased);
            attitudes.push_back(eCityAttitude::apatheticR);
            attitudes.push_back(eCityAttitude::respectful);
            attitudes.push_back(eCityAttitude::admiring);
        }
        std::vector<std::string> attitudeNames;
        for(const auto r : attitudes) {
            const auto name = eWorldCity::sAttitudeName(r);
            attitudeNames.push_back(name);
        }
        const auto act = [attitudes, attitudeNames,
                          c, attitudeButton](const int val) {
            c->setAttitude(10 + val*20);
            const auto name = attitudeNames[val];
            attitudeButton->setText(name);
            attitudeButton->fitContent();
            attitudeButton->align(eAlignment::hcenter);
        };
        d->initialize(8, attitudeNames, act);

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    buttonsW->addWidget(attitudeButton);
    attitudeButton->align(eAlignment::hcenter);

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
