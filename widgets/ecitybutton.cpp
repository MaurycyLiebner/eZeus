#include "ecitybutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"
#include "engine/egameboard.h"
#include "elanguage.h"

void eCityButton::initialize(eGameBoard& board,
                             const eCityAction& cact) {
    setUnderline(false);
    const auto boardPtr = &board;
    setPressAction([this, boardPtr, cact]() {
        auto& world = boardPtr->getWorldBoard();
        const auto& cities = world.cities();
        std::vector<std::string> cityNames;
        for(const auto& c : cities) {
            cityNames.push_back(c->name());
        }
        const auto choose = new eChooseButton(window());
        const auto act = [this, cities, cact](const int val) {
            const auto c = cities[val];
            setCity(c);
            if(cact) cact(c);
        };
        choose->initialize(8, cityNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setCity(nullptr);
}

void eCityButton::setCity(const stdsptr<eWorldCity>& c) {
    const auto lcity = eLanguage::text("none");
    const auto ccname = c ? c->name() : lcity;
    setText(ccname);
    fitContent();
    mCity = c;
}
