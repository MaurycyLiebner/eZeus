#include "emultipleselectionwidget.h"

#include "echoosebutton.h"

#include "emainwindow.h"

#include "ebuttonslistwidget.h"

void eMultipleSelectionWidget::initialize(
        const eLabels& labels,
        const eSetAction& setAct,
        const std::vector<int>& ini) {
    setType(eFrameType::message);

    const auto blw = new eButtonsListWidget(window());
    const int p = padding();
    blw->resize(width() - 4*p, height() - 4*p);
    blw->initialize(true);
    blw->move(2*p, 2*p);
    addWidget(blw);

    blw->setButtonPressEvent([this, blw, labels, setAct](const int id) {
        const auto choose = new eChooseButton(window());
        const auto act = [this, blw, labels, setAct, id](const int val) {
            blw->setText(id, labels[val]);
            mValues[id] = val;
            setAct(mValues);
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });

    blw->setButtonCreateEvent([this, blw, labels, setAct]() {
        const auto choose = new eChooseButton(window());
        const auto act = [this, blw, labels, setAct](const int val) {
            blw->addButton(labels[val]);
            mValues.push_back(val);
            setAct(mValues);
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });

    blw->setButtonRemoveEvent([this, setAct](const int id) {
        mValues.erase(mValues.begin() + id);
        setAct(mValues);
    });

    mValues = ini;
    for(const int i : ini) {
        blw->addButton(labels[i]);
    }
}
