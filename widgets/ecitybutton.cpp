#include "ecitybutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"
#include "engine/egameboard.h"
#include "elanguage.h"

void eCityButton::initialize(eWorldBoard* const board,
                             const eCityAction& cact) {
    setUnderline(false);
    setPressAction([this, board, cact]() {
        const auto& cities = board->cities();
        std::vector<stdsptr<eWorldCity>> validCities;
        std::vector<std::string> cityNames;
        for(const auto& c : cities) {
            if(mValidator) {
                const bool v = mValidator(c);
                if(!v) continue;
            }
            cityNames.push_back(c->name());
            validCities.push_back(c);
        }
        if(cityNames.empty()) return;
        const auto choose = new eChooseButton(window());
        const auto act = [this, validCities, cact](const int val) {
            const auto c = validCities[val];
            setCity(c);
            if(cact) cact(c);
        };
        choose->initialize(8, cityNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setCity(nullptr);
}

void eCityButton::setValidator(const eCityValidator& v) {
    mValidator = v;
}

void eCityButton::setCity(const stdsptr<eWorldCity>& c) {
    const auto lcity = eLanguage::text("none");
    const auto ccname = c ? c->name() : lcity;
    setText(ccname);
    fitContent();
    mCity = c;
}
