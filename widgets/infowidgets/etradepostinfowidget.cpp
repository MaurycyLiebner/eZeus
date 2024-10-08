#include "etradepostinfowidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"
#include "engine/egameboard.h"
#include "elanguage.h"

class eResourceStorageStack : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eStorageBuilding* const stor,
                    const std::vector<eResourceTrade>& importTypes,
                    const eResourceType imports,
                    std::map<eResourceType, eSwitchButton*>& buttons,
                    std::map<eResourceType, eSpinBox*>& spinBoxes,
                    const std::map<eResourceType, int>& maxCount,
                    const std::string& notBuyingTxt,
                    const std::string& buyingTxt,
                    const eAction& changed) {
        const auto countW = new eWidget(window());
        const auto iconsW = new eWidget(window());
        const auto namesW = new eWidget(window());
        const auto priceW = new eWidget(window());
        const auto buttonsW = new eWidget(window());
        const auto spinsW = new eWidget(window());
        const auto tradedW = new eWidget(window());

        const auto res = resolution();
        const double mult = res.multiplier();
        const int rowHeight = mult*23;
        const int countWidth = mult*25;
        const int iconsWidth = mult*40;
        const int namesWidth = mult*120;
        const int priceWidth = mult*60;
        const int buttonsWidth = mult*160;
        const int spinsWidth = mult*90;
        const int tradedWidth = mult*80;

        priceW->setWidth(priceWidth);
        buttonsW->setWidth(buttonsWidth);

        for(const auto& trade : importTypes) {
            const auto type = trade.fType;

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

            const auto nameStr = eResourceTypeHelpers::typeName(type);
            const auto n = new eLabel(window());
//            const auto n = new eButton(window());
//            n->setPressAction([stor, type, count]() {
//                stor->add(type, 1);
//                const int c = stor->count(type);
//                count->setText(std::to_string(c));
//            });
            n->setSmallFontSize();
            n->setText(nameStr);
            n->fitContent();
            n->setHeight(rowHeight);


            const auto pi = new eLabel(window());
            const auto& intrfs = eGameTextures::interface();
            int icoll;
            switch(res.uiScale()) {
            case eUIScale::tiny:
            case eUIScale::small:
                icoll = 1;
                break;
            default:
                icoll = 2;
            }
            pi->setTexture(intrfs[icoll].fDrachmasUnit);
            pi->setNoPadding();
            pi->fitContent();

            const auto p = new eLabel(window());
            auto& board = stor->getBoard();
            p->setText(std::to_string(board.price(trade.fType)));
            p->setSmallFontSize();
            p->setNoPadding();
            p->fitContent();

            const auto pw = new eWidget(window());
            pw->setNoPadding();
            pw->addWidget(pi);
            pw->addWidget(p);
            pw->stackHorizontally();
            pw->fitContent();
            pw->setHeight(rowHeight);

            pi->align(eAlignment::vcenter);
            p->align(eAlignment::vcenter);

            const auto b = new eSwitchButton(window());
            b->setUnderline(false);
            b->setSwitchAction([b, changed](const int i) {
                if(i == 0) {
                    b->setDarkFontColor();
                } else {
                    b->setLightFontColor();
                }
                changed();
            });

            b->setSmallFontSize();
            b->addValue(notBuyingTxt);
            b->addValue(buyingTxt);
            b->fitContent();
            b->setHeight(rowHeight);

            buttons[type] = b;

            const auto s = new eSpinBox(window());
            s->setHeight(rowHeight);
            s->setWidth(spinsWidth);
            s->initialize(changed);
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

            const auto t = new eLabel(window());
            t->setSmallFontSize();
            const int cc = trade.fUsed;
            const int ccc = trade.fMax;
            t->setText(std::to_string(cc) + " " + eLanguage::zeusText(44, 148) + " " + std::to_string(ccc));
            t->fitContent();
            t->setHeight(rowHeight);

            countW->addWidget(count);
            iconsW->addWidget(icon);
            namesW->addWidget(n);
            priceW->addWidget(pw);
            pw->align(eAlignment::hcenter);
            buttonsW->addWidget(b);
            spinsW->addWidget(s);
            tradedW->addWidget(t);

            icon->align(eAlignment::left);
            n->align(eAlignment::left);
            b->align(eAlignment::hcenter);

            if(static_cast<bool>(imports & type)) {
                b->setValue(1);
            } else {
                b->setValue(0);
                b->setDarkFontColor();
            }
        }

        countW->stackVertically();
        iconsW->stackVertically();
        namesW->stackVertically();
        priceW->stackVertically();
        buttonsW->stackVertically();
        spinsW->stackVertically();
        tradedW->stackVertically();

        countW->fitContent();
        iconsW->fitContent();
        namesW->fitContent();
        priceW->fitContent();
        buttonsW->fitContent();
        spinsW->fitContent();
        tradedW->fitContent();

        countW->setWidth(countWidth);
        iconsW->setWidth(iconsWidth);
        namesW->setWidth(namesWidth);
        priceW->setWidth(priceWidth);
        buttonsW->setWidth(buttonsWidth);
        spinsW->setWidth(spinsWidth);
        tradedW->setWidth(tradedWidth);

        addWidget(countW);
        addWidget(iconsW);
        addWidget(namesW);
        addWidget(priceW);
        addWidget(buttonsW);
        addWidget(spinsW);
        addWidget(tradedW);

        stackHorizontally();
        setNoPadding();
        fitContent();
    }
};

eTradePostInfoWidget::eTradePostInfoWidget(eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, false, false) {}

void eTradePostInfoWidget::initialize(eTradePost* const stor) {
    const auto& city = stor->city();
    const auto title = eLanguage::zeusText(28, 62) + ": " + city.name();

    eEmployingBuildingInfoWidget::initialize(title, stor);

    eResourceType imports;
    eResourceType exports;
    stor->getOrders(imports, exports);
    const auto& maxCount = stor->maxCount();

    const auto stWid = centralWidget();

    const auto changed = [this, stor]() {
        std::map<eResourceType, int> maxCount;
        eResourceType imports;
        eResourceType exports;
        this->get(imports, exports, maxCount);
        stor->setOrders(imports, exports);
        stor->setMaxCount(maxCount);
    };

    {
        const auto wrapper = new eWidget(window());
        const auto importsLabel = new eLabel(eLanguage::zeusText(130, 17), window());
        importsLabel->fitContent();

        const auto r = new eResourceStorageStack(window());

        const auto& csells = city.sells();

        r->initialize(stor, csells, imports,
                      mImportButtons, mSpinBoxes, maxCount,
                      eLanguage::zeusText(130, 20),
                      eLanguage::zeusText(130, 12),
                      changed);

        wrapper->addWidget(importsLabel);
        wrapper->addWidget(r);
        wrapper->stackVertically();
        wrapper->setNoPadding();
        wrapper->fitContent();

        stWid->addWidget(wrapper);
        wrapper->align(eAlignment::hcenter);
    }
    {
        const auto wrapper = new eWidget(window());
        const auto exportsLabel = new eLabel(eLanguage::zeusText(130, 18), window());
        exportsLabel->fitContent();

        const auto r = new eResourceStorageStack(window());

        const auto& cbuys = city.buys();

        r->initialize(stor, cbuys, exports,
                      mExportButtons, mSpinBoxes, maxCount,
                      eLanguage::zeusText(130, 21),
                      eLanguage::zeusText(130, 13),
                      changed);

        wrapper->addWidget(exportsLabel);
        wrapper->addWidget(r);
        wrapper->stackVertically();
        wrapper->setNoPadding();
        wrapper->fitContent();

        stWid->addWidget(wrapper);
        wrapper->align(eAlignment::hcenter);
    }

    stWid->layoutVertically();
}

void eTradePostInfoWidget::get(eResourceType& imports,
                               eResourceType& exports,
                               std::map<eResourceType, int>& count) const {
    imports = eResourceType::none;
    exports = eResourceType::none;
    for(const auto b : mImportButtons) {
        const auto type = b.first;
        const int val = b.second->currentValue();
        if(val == 1) {
            imports = imports | type;
        }
    }
    for(const auto b : mExportButtons) {
        const auto type = b.first;
        const int val = b.second->currentValue();
        if(val == 1) {
            exports = exports | type;
        }
    }
    for(const auto s : mSpinBoxes) {
        const auto type = s.first;
        const int val = s.second->value();
        count[type] = val;
    }
}
