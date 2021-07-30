#include "eterraineditmenu.h"

#include "etabwidget.h"

eTerrainEditMenu::eTerrainEditMenu(eMainWindow* const window) :
    eTabWidget(window) {

    resize(500, 150);
    initialize();

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
    }

    {
        mBuildingsWidget = new eWidget(window);
        mBuildingsWidget->resize(500, 75);

        {
            const auto b = new eButton(window);
            b->setText("small house");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::smallHouse;
            });
            mBuildingsWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("gymnasium");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::gymnasium;
            });
            mBuildingsWidget->addWidget(b);
        }

        {
            const auto b = new eButton(window);
            b->setText("road");
            b->fitContent();
            b->setPressAction([this]() {
                mMode = eTerrainEditMode::road;
            });
            mBuildingsWidget->addWidget(b);
        }

        mBuildingsWidget->layoutHorizontally();
    }

    {
        addTab("basic", mBasicWidget);
        addTab("stones", mStonesWidget);
        addTab("buildings", mBuildingsWidget);
    }
}
