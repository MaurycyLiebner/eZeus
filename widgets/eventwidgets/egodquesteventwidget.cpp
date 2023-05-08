#include "egodquesteventwidget.h"

#include "widgets/eswitchbutton.h"

#include "widgets/elabeledwidget.h"
#include "widgets/egodbutton.h"
#include "widgets/eherobutton.h"
#include "elanguage.h"

#include "emainwindow.h"

void eGodQuestEventWidget::initialize(
        eGodQuestEvent* const e) {
    const auto godButtonL = new eLabeledWidget(window());
    const auto act = [e](const eGodType type) {
        e->setGod(type);
    };
    const auto godButton = new eGodButton(window());
    godButton->initialize(act);
    const auto iniT = e->god();
    godButton->setType(iniT);
    godButtonL->setup(eLanguage::text("god:"), godButton);
    addWidget(godButtonL);

    const auto idButtonL = new eLabeledWidget(window());
    const auto switchAct = [e](const int id) {
        e->setId(id == 0 ? eGodQuestId::godQuest1 : eGodQuestId::godQuest2);
    };
    const auto idButton = new eSwitchButton(window());
    idButton->addValue("1");
    idButton->addValue("2");
    idButton->fitValialbeContent();
    const auto iniId = e->id();
    idButton->setValue(iniId == eGodQuestId::godQuest1 ? 0 : 1);
    idButton->setSwitchAction(switchAct);
    idButtonL->setup(eLanguage::text("id:"), idButton);
    addWidget(idButtonL);

    const auto heroButtonL = new eLabeledWidget(window());
    const auto hact = [e](const eHeroType type) {
        e->setHero(type);
    };
    const auto heroButton = new eHeroButton(window());
    heroButton->initialize(hact);
    const auto iniH = e->hero();
    heroButton->setType(iniH);
    heroButtonL->setup(eLanguage::text("hero:"), heroButton);
    addWidget(heroButtonL);

    const int p = padding();
    stackVertically(p);
    setNoPadding();
    fitContent();
}
