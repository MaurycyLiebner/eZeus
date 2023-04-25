#include "emultipleselectionwidget.h"

#include "echoosebutton.h"

#include "emainwindow.h"

#include "ebuttonslistwidget.h"

void eMultipleSelectionWidget::initialize(
        const eLabels& labels,
        const eSetAction& setAct,
        const std::vector<int>& ini) {
    setType(eFrameType::message);

    mBLW = new eButtonsListWidget(window());
    const int p = padding();
    mBLW->resize(width() - 4*p, height() - 4*p);
    mBLW->initialize();
    mBLW->move(2*p, 2*p);
    addWidget(mBLW);

    mBLW->setButtonPressEvent([this, labels, setAct](const int id) {
        const auto choose = new eChooseButton(window());
        const auto act = [this, setAct, labels, id](const int val) {
            mBLW->setText(id, labels[val]);
            mValues[id] = val;
            setAct(mValues);
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });

    mBLW->setButtonCreateEvent([this, labels, setAct]() {
        const auto choose = new eChooseButton(window());
        const auto act = [this, setAct, labels](const int val) {
            mBLW->addButton(labels[val]);
            mValues.push_back(val);
            setAct(mValues);
        };
        choose->initialize(8, labels, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });

    mBLW->setButtonRemoveEvent([this, setAct](const int id) {
        mValues.erase(mValues.begin() + id);
        setAct(mValues);
    });

    mValues = ini;
    for(const int i : ini) {
        mBLW->addButton(labels[i]);
    }
}
