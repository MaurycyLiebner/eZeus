#include "eterraineditmenu.h"

eTerrainEditMenu::eTerrainEditMenu(eMainWindow* const window) :
    eWidget(window) {

    resize(500, 150);

    {
        mBasicWidget = new eWidget(window);
        mBasicWidget->resize(500, 75);

        {
            const auto b = new eButton(window);
            b->setText("scrub");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::scrub;
            });
            mBasicWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("forest");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::forest;
            });
            mBasicWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("dry");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::dry;
            });
            mBasicWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("beach");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::beach;
            });
            mBasicWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("water");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::water;
            });
            mBasicWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("fertile");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::fertile;
            });
            mBasicWidget->addWidget(b);
        }


        mBasicWidget->layoutHorizontally();
        addWidget(mBasicWidget);
        mBasicWidget->align(eAlignment::hcenter | eAlignment::bottom);
    }

    {
        mStonesWidget = new eWidget(window);
        mStonesWidget->resize(500, 75);

        {
            const auto b = new eButton(window);
            b->setText("flat stones");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::flatStones;
            });
            mStonesWidget->addWidget(b);
        }
        {
            const auto b = new eButton(window);
            b->setText("bronze");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::bronze;
            });
            mStonesWidget->addWidget(b);
        }
        {
            const auto b = new eButton(window);
            b->setText("silver");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::silver;
            });
            mStonesWidget->addWidget(b);
        }
        {
            const auto b = new eButton(window);
            b->setText("tall stones");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::tallStones;
            });
            mStonesWidget->addWidget(b);
        }
        {
            const auto b = new eButton(window);
            b->setText("tiny stones");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::tinyStones;
            });
            mStonesWidget->addWidget(b);
        }

        mStonesWidget->layoutHorizontally();
        addWidget(mStonesWidget);
        mStonesWidget->align(eAlignment::hcenter | eAlignment::bottom);
        mStonesWidget->hide();
    }

    {
        const auto menuW = new eWidget(window);
        menuW->resize(500, 75);

        {
            const auto b = new eCheckableButton(window);
            mBasicButton = b;
            b->setText("basic");
            b->setChecked(true);
            b->fitContent();
            b->setCheckAction([this](const bool c) {
                if(!c) return;
                mBasicWidget->setVisible(true);
                mStonesWidget->setVisible(false);
                mStonesButton->setChecked(false);
            });
            menuW->addWidget(b);
        }

        {
            const auto b = new eCheckableButton(window);
            mStonesButton = b;
            b->setText("stones");
            b->fitContent();
            b->setCheckAction([this](const bool c) {
                if(!c) return;
                mBasicWidget->setVisible(false);
                mStonesWidget->setVisible(true);
                mBasicButton->setChecked(false);
            });
            menuW->addWidget(b);
        }

        menuW->layoutHorizontally();
        addWidget(menuW);
        menuW->align(eAlignment::hcenter | eAlignment::top);
    }
}
