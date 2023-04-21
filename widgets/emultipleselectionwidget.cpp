#include "emultipleselectionwidget.h"

#include "eselectionbutton.h"
#include "elanguage.h"
#include "eframedbutton.h"
#include "evectorhelpers.h"

#include "ecancelbutton.h"
#include "echoosebutton.h"

#include "emainwindow.h".h"

void eMultipleSelectionWidget::initialize(
        eWidget* const parent,
        const eLabels& labels,
        const eSetAction& setAct,
        const std::vector<int>& ini) {
    const auto setActAct = [this, setAct]() {
        std::vector<int> values;
        for(const auto w : mButtons) {
            values.push_back(w->value());
        }
        setAct(values);
    };
    setType(eFrameType::message);
    const auto addStr = eLanguage::text("add");
    mNewButton = new eFramedButton(addStr, window());
    mNewButton->fitContent();
    mNewButton->setUnderline(false);
    mNewButton->setPressAction([this, parent, setActAct, labels]() {
        const auto choose = new eChooseButton(window());
        const auto act = [this, parent, setActAct, labels](const int n) {
            addButton(parent, setActAct, labels, n);
            setActAct();
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    for(const int i : ini) {
        addButton(parent, setActAct, labels, i);
    }
    updateButtons();
}

void eMultipleSelectionWidget::addButton(eWidget* const parent,
        const eAction& setActAct,
        const eLabels& labels, const int i) {
    const auto b = new eSelectionButton(window());
    b->initialize(i, mButtons.size());
    const auto bb = new eFramedButton(labels[i], window());
    bb->setUnderline(false);
    bb->fitContent();
    b->addWidget(bb);
    bb->setPressAction([this, parent, b, bb, setActAct, labels]() {
        const auto choose = new eChooseButton(window());
        const auto act = [b, bb, setActAct, labels](const int n) {
            b->setValue(n);
            bb->setText(labels[n]);
            setActAct();
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    const auto c = new eCancelButton(window());
    c->setPressAction([this, setActAct, b]() {
        eVectorHelpers::remove(mButtons, b);
        updateButtons();
        setActAct();
        b->deleteLater();
    });
    b->addWidget(c);
    b->stackHorizontally();
    b->fitContent();
    c->align(eAlignment::vcenter);
    mButtons.push_back(b);
    updateButtons();
}

void eMultipleSelectionWidget::updateButtons() {
    removeAllWidgets();
    const int p = padding();
    int y = 2*p;
    int i = 0;
    for(const auto b : mButtons) {
        addWidget(b);
        b->setX(2*p);
        b->setY(y);
        b->setId(i++);
        y += b->height() + p;
    }
    addWidget(mNewButton);
    mNewButton->setX(2*p);
    mNewButton->setY(y);
}
