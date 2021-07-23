#include "esettingsmenu.h"

#include "ecombobox.h"

eSettingsMenu::eSettingsMenu(SDL_Renderer* const renderer) :
    eWidget(renderer) {

}

void eSettingsMenu::initialize(const eAction& backA) {
    const auto buttons = new eWidget(renderer());
    addWidget(buttons);
    buttons->resize(500, 500);
    buttons->align(eAlignment::center);

    {
        const auto cw = new eWidget(renderer());

        const auto l = new eLabel("Resolution: ", renderer());
        l->fitSizeToText(10);
        cw->addWidget(l);

        const auto b = new eComboBox(renderer());
        b->addAction("1920x1080");
        b->addAction("1280x720");
        cw->addWidget(b);
        b->resize(200, 50);
        b->align(eAlignment::hcenter);

        cw->resize(l->width() + b->width() + 50, 50);
        cw->layoutHorizontally();
        buttons->addWidget(cw);
    }

    buttons->layoutVertically();

    {
        const auto b = new eButton(renderer());
        b->setPressAction(backA);
        buttons->addWidget(b);
        b->setText("Back");
        b->resize(200, 50);
        b->align(eAlignment::left | eAlignment::bottom);
    }

    {
        const auto b = new eButton(renderer());
        b->setPressAction(backA);
        buttons->addWidget(b);
        b->setText("Apply");
        b->resize(200, 50);
        b->align(eAlignment::right | eAlignment::bottom);
    }
}
