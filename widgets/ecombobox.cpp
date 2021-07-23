#include "ecombobox.h"

#include "econtextmenu.h"

eComboBox::eComboBox(SDL_Renderer* const renderer) :
    eButton(renderer) {
    setPressAction([this, renderer]() {
        const auto cm = new eContextMenu(renderer);
        const int as = mActions.size();
        for(int i = 0; i < as; i++) {
            const auto& a = mActions[i];
            cm->addAction(a, [this, i]() {
                setCurrentIndex(i);
            });
        }
        addWidget(cm);
        cm->setWidth(width());
        cm->setY(height());
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
    const auto& txt = mActions[id];
    setText(txt);
    if(mCurrentAction) mCurrentAction(txt);
    return true;
}

void eComboBox::addAction(const std::string& a) {
    if(mActions.empty()) setText(a);
    mActions.push_back(a);
}
