#include "egodselectionwidget.h"

void eGodSelectionWidget::initialize(const eGodSetAction& godSetAct,
                                     const std::vector<eGodType>& ini) {
    std::vector<eGodType> gods;
    const int iMin = static_cast<int>(eGodType::aphrodite);
    const int iMax = static_cast<int>(eGodType::zeus);
    for(int i = iMin; i <= iMax; i++) {
        const auto mi = static_cast<eGodType>(i);
        gods.push_back(mi);
    }

    std::vector<std::string> godNames;
    for(const auto g : gods) {
        godNames.push_back(eGod::sGodName(g));
    }

    const auto act = [godSetAct, gods](const std::vector<int>& ns) {
        std::vector<eGodType> godNs;
        for(const int n : ns) {
            godNs.push_back(gods[n]);
        }
        godSetAct(godNs);
    };

    std::vector<int> iini;
    for(const auto g : ini) {
        const int i = static_cast<int>(g);
        iini.push_back(i);
    }
    eMultipleSelectionWidget::initialize(godNames, act, iini);
}
