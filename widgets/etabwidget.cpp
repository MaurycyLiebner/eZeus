#include "etabwidget.h"

eTabWidget::eTabWidget(eMainWindow* const window) :
    eWidget(window), mTabWidget(new eWidget(window)) {
    mTabWidget->setHeight(75);
    addWidget(mTabWidget);
}

void eTabWidget::initialize() {
    mTabWidget->setWidth(width());
}

void eTabWidget::addTab(const std::string& text,
                        eWidget* const w) {
    const auto button = new eCheckableButton(window());
    button->setText(text);
    button->fitContent();
    w->setY(mTabWidget->height());
    if(mButtons.empty()) {
        button->setChecked(true);
        addWidget(w);
        fitContent();
    }
    mTabWidget->addWidget(button);
    mTabWidget->layoutHorizontally();
    mButtons.push_back(button);
    mWidgets.push_back(w);
    const int id = mButtons.size() - 1;
    button->setCheckAction([this, id, w](const bool c) {
        if(!c) return;
        const int iMax = mButtons.size();
        for(int i = 0; i < iMax; i++) {
            if(i != id) mButtons[i]->setChecked(false);
            removeWidget(mWidgets[i]);
        }
        addWidget(w);
        fitContent();
    });
}
