#include "eherobutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"

void eHeroButton::initialize(const eHeroAction& gact) {
    setUnderline(false);
    setPressAction([this, gact]() {
        const auto choose = new eChooseButton(window());
        std::vector<eHeroType> heros;
        std::vector<std::string> heroNames;
        eHero::sHeroStrings(heros, heroNames);
        const auto act = [this, heros, gact](const int val) {
            const auto t = heros[val];
            setType(t);
            if(gact) gact(t);
        };
        choose->initialize(8, heroNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setType(eHeroType::bellerophon);
    fitContent();
}

void eHeroButton::setType(const eHeroType type) {
    setText(eHero::sHeroName(type));
    mType = type;
}
