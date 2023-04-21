#include "echoosebutton.h"

#include "eframedbutton.h"

void eChooseButton::initialize(
        const int nRows,
        const eLabels& labels,
        const eButtonAction& act) {
    setType(eFrameType::message);

    std::vector<eFramedButton*> buttons;

    int i = 0;
    for(const auto& l : labels) {
        const auto b = new eFramedButton(window());
        b->setUnderline(false);
        b->setText(l);
        b->fitContent();
        b->setPressAction([this, act, i]() {
            act(i);
            deleteLater();
        });
        addWidget(b);
        buttons.push_back(b);
        i++;
    }

    int colWidth = 0;
    for(const auto b : buttons) {
        const int w = b->width();
        if(w > colWidth) colWidth = w;
    }

    const int p = padding();

    int r = 0;
    int x = 2*p;
    int y = 2*p;

    for(const auto b : buttons) {
        b->setWidth(colWidth);
        b->move(x, y);
        y += b->height() + p;
        r++;
        if(r > nRows) {
            r = 0;
            x += colWidth + p;
            y = 2*p;
        }
    }

    fitContent();
}
