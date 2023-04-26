#include "egodattackeventwidget.h"

#include "widgets/eswitchbutton.h"
#include "elanguage.h"

#include "widgets/egodselectionwidget.h"

#include "emainwindow.h"

void eGodAttackEventWidget::initialize(eWidget* const parent,
                                       eGodAttackEvent* const e) {
    const auto randomButton = new eSwitchButton(window());
    randomButton->addValue(eLanguage::text("iterative"));
    randomButton->addValue(eLanguage::text("random"));
    randomButton->setSwitchAction([e](const int v) {
        e->setRandom(v);
    });
    randomButton->fitValialbeContent();
    randomButton->setUnderline(false);
    randomButton->setValue(e->random() ? 1 : 0);
    addWidget(randomButton);

    const auto godsStr = eLanguage::text("gods");
    const auto godsButton = new eFramedButton(godsStr, window());
    godsButton->fitContent();
    godsButton->setUnderline(false);
    godsButton->setPressAction([this, parent, e]() {
        const auto choose = new eGodSelectionWidget(window());
        const auto act = [e](const std::vector<eGodType>& godNs) {
            e->setTypes(godNs);
        };

        choose->resize(parent->width(), parent->height());
        choose->initialize(act, e->types());

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    addWidget(godsButton);

    const int p = padding();
    stackVertically(p);
    setNoPadding();
    fitContent();
}
