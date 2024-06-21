#include "egodbutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"

void eGodButton::initialize(const eGodAction& gact) {
    setUnderline(false);
    setPressAction([this, gact]() {
        const auto choose = new eChooseButton(window());
        std::vector<eGodType> gods;
        std::vector<std::string> godNames;
        eGod::sGodStrings(gods, godNames);
        const auto act = [this, gods, gact](const int val) {
            const auto t = gods[val];
            setType(t);
            if(gact) gact(t);
        };
        choose->initialize(8, godNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setType(eGodType::hephaestus);
    fitContent();
}

void eGodButton::setType(const eGodType type) {
    setText(eGod::sGodName(type));
    mType = type;
}
