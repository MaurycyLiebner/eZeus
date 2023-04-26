#include "emonsterselectionwidget.h"

#include "elanguage.h"

void eMonsterSelectionWidget::initialize(const eMonsterSetAction& monsterSetAct,
                                         const std::vector<eMonsterType>& ini) {

    std::vector<eMonsterType> monsters;
    const int iMin = static_cast<int>(eMonsterType::calydonianBoar);
    const int iMax = static_cast<int>(eMonsterType::talos);
    for(int i = iMin; i <= iMax; i++) {
        const auto mi = static_cast<eMonsterType>(i);
        monsters.push_back(mi);
    }

    const std::vector<std::string> monsterGods {
        eLanguage::text("artemis"),
        eLanguage::text("hades"),
        eLanguage::text("atlas"),
        eLanguage::text("zeus"),
        eLanguage::text("ares"),
        "-",
        "-",
        eLanguage::text("aphrodite"),
        eLanguage::text("athena"),
        eLanguage::text("poseidon"),
        eLanguage::text("dionysus"),
        eLanguage::text("demeter"),
        eLanguage::text("hermes"),
        eLanguage::text("apollo"),
        eLanguage::text("hera"),
        eLanguage::text("hephaestus")
    };
    const std::vector<std::string> monsterHeroes {
        eLanguage::text("theseus"),
        eLanguage::text("hercules"),
        eLanguage::text("bellerophon"),
        eLanguage::text("odysseus"),
        eLanguage::text("jason"),
        eLanguage::text("bellerophon"),
        eLanguage::text("atalanta"),
        eLanguage::text("achilles"),
        eLanguage::text("hercules"),
        eLanguage::text("perseus"),
        eLanguage::text("achilles"),
        eLanguage::text("perseus"),
        eLanguage::text("theseus"),
        eLanguage::text("odysseus"),
        eLanguage::text("atalanta"),
        eLanguage::text("jason")
    };

    std::vector<std::string> monsterNames;
    const int iMax2 = monsters.size();
    for(int i = 0; i < iMax2; i++) {
        const auto& m = monsters[i];
        const auto& g = monsterGods[i];
        const auto& h = monsterHeroes[i];
        monsterNames.push_back(eMonster::sMonsterName(m) + " (" +
                               g + ", " + h + ")");
    }

    const auto act = [monsterSetAct, monsters](const std::vector<int>& ns) {
        std::vector<eMonsterType> monsterNs;
        for(const int n : ns) {
            monsterNs.push_back(monsters[n]);
        }
        monsterSetAct(monsterNs);
    };

    std::vector<int> iini;
    for(const auto m : ini) {
        const int i = static_cast<int>(m);
        iini.push_back(i);
    }
    eMultipleSelectionWidget::initialize(monsterNames, act, iini);
}
