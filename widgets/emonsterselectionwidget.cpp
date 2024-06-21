#include "emonsterselectionwidget.h"

void eMonsterSelectionWidget::initialize(const eMonsterSetAction& monsterSetAct,
                                         const std::vector<eMonsterType>& ini) {
    std::vector<eMonsterType> monsters;
    std::vector<std::string> monsterNames;
    eMonster::sMonsterStrings(monsters, monsterNames);

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
