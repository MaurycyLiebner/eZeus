#include "estorageinfowidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "elanguage.h"

class eResourceStorageStack : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eStorageBuilding* const stor,
                    const std::vector<eResourceType>& types,
                    const eResourceType get,
                    const eResourceType empty,
                    const eResourceType accept,
                    std::map<eResourceType, eSwitchButton*>& buttons,
                    std::map<eResourceType, eSpinBox*>& spinBoxes,
                    const std::map<eResourceType, int>& maxCount) {
        const auto countW = new eWidget(window());
        const auto iconsW = new eWidget(window());
        const auto namesW = new eWidget(window());
        const auto buttonsW = new eWidget(window());
        const auto spinsW = new eWidget(window());

        const auto res = resolution();
        const double mult = res.multiplier();
        const int rowHeight = mult*23;
        const int countWidth = mult*25;
        const int iconsWidth = mult*40;
        const int namesWidth = mult*120;
        const int buttonsWidth = mult*160;
        const int spinsWidth = mult*90;

        buttonsW->setWidth(namesWidth);

        for(const auto type : types) {
            const auto count = new eLabel(window());
            count->setSmallFontSize();
            const int c = stor->count(type);
            count->setText(std::to_string(c));
            count->fitContent();
            count->setHeight(rowHeight);

            const auto icon = new eLabel(window());
            const auto tex = eResourceTypeHelpers::icon(
                                 res.uiScale(), type);
            icon->setTexture(tex);
            icon->fitContent();
            icon->setHeight(rowHeight);
            icon->setVisible(c > 0);

            const auto nameStr = eResourceTypeHelpers::typeName(type);
//            const auto n = new eLabel(window());
            const auto n = new eButton(window());
            n->setPressAction([stor, type, count, icon]() {
                stor->add(type, 1);
                const int c = stor->count(type);
                count->setText(std::to_string(c));
                icon->setVisible(c > 0);
            });
            n->setSmallFontSize();
            n->setText(nameStr);
            n->fitContent();
            n->setHeight(rowHeight);

            const auto b = new eSwitchButton(window());

            b->setSwitchAction([b](const int i) {
                if(i == 0 || i == 3) {
                    b->setDarkFontColor();
                } else {
                    b->setLightFontColor();
                }
            });

            b->setSmallFontSize();
            b->addValue(eLanguage::text("dont_accept"));
            b->addValue(eLanguage::text("accept"));
            b->addValue(eLanguage::text("get"));
            b->addValue(eLanguage::text("empty"));
            b->fitContent();
            b->setHeight(rowHeight);

            buttons[type] = b;

            const auto s = new eSpinBox(window());
            s->setHeight(rowHeight);
            s->setWidth(spinsWidth);
            s->initialize();
            s->label()->setSmallFontSize();
            const int space = stor->spaceCount();
            if(type == eResourceType::sculpture) {
                s->setRange(0, space);
            } else {
                s->setRange(0, 4*space);
                s->setIncrement(4);
            }
            s->setValue(maxCount.at(type));

            spinBoxes[type] = s;

            countW->addWidget(count);
            iconsW->addWidget(icon);
            namesW->addWidget(n);
            buttonsW->addWidget(b);
            spinsW->addWidget(s);

            icon->align(eAlignment::left);
            n->align(eAlignment::left);
            b->align(eAlignment::hcenter);

            if(static_cast<bool>(get & type)) {
                b->setValue(2);
            } else if(static_cast<bool>(empty & type)) {
                b->setValue(3);
            } else if(static_cast<bool>(accept & type)) {
                b->setValue(1);
            } else {
                b->setValue(0);
            }
        }

        countW->stackVertically();
        iconsW->stackVertically();
        namesW->stackVertically();
        buttonsW->stackVertically();
        spinsW->stackVertically();

        const int h = types.size()*rowHeight;
        countW->setHeight(h);
        iconsW->setHeight(h);
        namesW->setHeight(h);
        buttonsW->setHeight(h);
        spinsW->setHeight(h);

        countW->setWidth(countWidth);
        iconsW->setWidth(iconsWidth);
        namesW->setWidth(namesWidth);
        buttonsW->setWidth(buttonsWidth);
        spinsW->setWidth(spinsWidth);

        addWidget(countW);
        addWidget(iconsW);
        addWidget(namesW);
        addWidget(buttonsW);
        addWidget(spinsW);

        stackHorizontally();
        setNoPadding();
        fitContent();
    }
};

eStorageInfoWidget::eStorageInfoWidget(eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, false) {}

void eStorageInfoWidget::initialize(eStorageBuilding* const stor) {
    const auto st = stor->type();
    std::string title;
    if(st == eBuildingType::warehouse) {
        title = eLanguage::text("storehouse");
    } else if(st == eBuildingType::granary) {
        title = eLanguage::text("granary");
    }
    eEmployingBuildingInfoWidget::initialize(title, stor);

    eResourceType get;
    eResourceType empty;
    eResourceType accept;
    stor->getOrders(get, empty, accept);
    const auto all = stor->canAccept();
    const auto& maxCount = stor->maxCount();

    const auto stWid = centralWidget();

    const auto types = eResourceTypeHelpers::extractResourceTypes(all);

    const auto r = new eResourceStorageStack(window());
    r->initialize(stor, types, get, empty, accept,
                  mButtons, mSpinBoxes, maxCount);
    stWid->addWidget(r);
    r->align(eAlignment::center);
}

void eStorageInfoWidget::get(eResourceType& get,
                             eResourceType& empty,
                             eResourceType& accept,
                             eResourceType& dontaccept,
                             std::map<eResourceType, int>& count) const {
    get = eResourceType::none;
    empty = eResourceType::none;
    accept = eResourceType::none;
    dontaccept = eResourceType::none;
    for(const auto b : mButtons) {
        const auto type = b.first;
        const int val = b.second->currentValue();
        if(val == 0) {
            dontaccept = dontaccept | type;
        } else if(val == 1) {
            accept = accept | type;
        } else if(val == 2) {
            get = get | type;
        } else if(val == 3) {
            empty = empty | type;
        }
    }
    for(const auto s : mSpinBoxes) {
        const auto type = s.first;
        const int val = s.second->value();
        count[type] = val;
    }
}
