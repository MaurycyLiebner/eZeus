#include "eterraineditmenu.h"

#include "ebutton.h"

eTerrainEditMenu::eTerrainEditMenu(eMainWindow* const window) :
    eWidget(window) {

    resize(500, 100);

    {
        const auto b = new eButton(window);
        b->setText("scrub");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::scrub;
        });
        addWidget(b);
    }

    {
        const auto b = new eButton(window);
        b->setText("forest");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::forest;
        });
        addWidget(b);
    }

    {
        const auto b = new eButton(window);
        b->setText("dry");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::dry;
        });
        addWidget(b);
    }

    {
        const auto b = new eButton(window);
        b->setText("beach");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::beach;
        });
        addWidget(b);
    }

    {
        const auto b = new eButton(window);
        b->setText("river");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::river;
        });
        addWidget(b);
    }

    {
        const auto b = new eButton(window);
        b->setText("fertile");
        b->fitContent();
        b->setPressAction([this]() {
            mMode = eTerrainEditMode::fertile;
        });
        addWidget(b);
    }


    layoutHorizontally();
}
