#include "ecombobox.h"

#include "econtextmenu.h"

eComboBox::eComboBox(eMainWindow* const window) :
    eButton(window) {
    setPressAction([this, window]() {
        const auto cm = new eContextMenu(window);
        const int as = mActions.size();
        for(int i = 0; i < as; i++) {
            const auto& a = mActions[i];
            cm->addAction(a, [this, i]() {
                setCurrentIndex(i);
            });
        }
        int gx = 0;
        int gy = height();
        mapToGlobal(gx, gy);
        lastAncestor()->addWidget(cm);
        cm->setWidth(width());
        cm->move(gx, gy);
        cm->exec();
    });
}

void eComboBox::setCurrentChangedAction(const eCurrentAction& a) {
    mCurrentAction = a;
}

bool eComboBox::setCurrentIndex(const int id) {
    if(id < 0) return false;
    const int as = mActions.size();
    if(id >= as) return false;
    if(mIndex == id) return false;
    mIndex = id;
    const auto& txt = mActions[id];
    setText(txt);
    if(mCurrentAction) mCurrentAction(id);
    return true;
}

void eComboBox::addAction(const std::string& a) {
    if(mActions.empty()) setText(a);
    mActions.push_back(a);
}

int eComboBox::currentIndex() const {
    return mIndex;
}

std::string eComboBox::currentText() const {
    if(mActions.empty()) return "";
    return mActions[mIndex];
}
