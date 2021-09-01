#include "estorageinfowidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

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

        const auto& intrfc = eGameTextures::interface();
        int icoll;
        const auto res = resolution();
        const double mult = eResolution::multiplier(res);
        switch(res) {
        case eRes::p480:
//            icoll = 0;
//            break;
        case eRes::p720:
        case eRes::p1080:
            icoll = 1;
            break;
        default:
            icoll = 2;
        }
        const auto& coll = intrfc[icoll];

        const int rowHeight = mult*40;
        const int countWidth = mult*25;
        const int iconsWidth = mult*40;
        const int namesWidth = mult*80;
        const int buttonsWidth = mult*120;
        const int spinsWidth = mult*90;

        for(const auto type : types) {
            const auto count = new eLabel(window());
            count->setSmallFontSize();
            const int c = stor->count(type);
            count->setText(std::to_string(c));
            count->fitContent();
            count->setHeight(rowHeight);

            const auto icon = new eLabel(window());
            std::shared_ptr<eTexture> tex;
            switch(type) {
            case eResourceType::urchin:
                tex = coll.fUrchinUnit;
                break;
            case eResourceType::fish:
                tex = coll.fFishUnit;
                break;
            case eResourceType::meat:
                tex = coll.fMeatUnit;
                break;
            case eResourceType::cheese:
                tex = coll.fCheeseUnit;
                break;
            case eResourceType::carrots:
                tex = coll.fCarrotsUnit;
                break;
            case eResourceType::onions:
                tex = coll.fOnionsUnit;
                break;
            case eResourceType::wheat:
                tex = coll.fWheatUnit;
                break;
            case eResourceType::wood:
                tex = coll.fWoodUnit;
                break;
            case eResourceType::bronze:
                tex = coll.fBronzeUnit;
                break;
            case eResourceType::marble:
                tex = coll.fMarbleUnit;
                break;
            case eResourceType::grapes:
                tex = coll.fGrapesUnit;
                break;
            case eResourceType::olives:
                tex = coll.fOlivesUnit;
                break;
            case eResourceType::fleece:
                tex = coll.fFleeceUnit;
                break;
            case eResourceType::horse:
                tex = coll.fHorseUnit;
                break;
            case eResourceType::armor:
                tex = coll.fArmsUnit;
                break;
            case eResourceType::sculpture:
                tex = coll.fSculptureUnit;
                break;
            case eResourceType::oliveOil:
                tex = coll.fOliveOilUnit;
                break;
            case eResourceType::wine:
                tex = coll.fWineUnit;
                break;
            case eResourceType::food:
                tex = coll.fFoodUnit;
                break;
            }
            icon->setTexture(tex);
            icon->fitContent();
            icon->setHeight(rowHeight);

            const auto nameStr = eResourceTypeHelpers::typeName(type);
            const auto n = new eLabel(window());
            n->setSmallFontSize();
            n->setText(nameStr);
            n->fitContent();
            n->setHeight(rowHeight);

            const auto b = new eSwitchButton(window());

            b->setSwitchAction([b](const int i) {
                if(i == 0 || i == 3) {
                    b->setFontColor({180, 180, 200, 255});
                } else {
                    b->setFontColor({255, 255, 255, 255});
                }
            });

            b->setSmallFontSize();
            b->addValue("Don't Accept");
            b->addValue("Accept");
            b->addValue("Get");
            b->addValue("Empty");
            b->fitContent();
            b->setHeight(rowHeight);

            buttons[type] = b;

            const auto s = new eSpinBox(window());
            s->setHeight(rowHeight);
            s->setWidth(spinsWidth);
            s->initialize();
            s->label()->setSmallFontSize();
            if(type == eResourceType::sculpture) {
                s->setRange(0, 8);
            } else {
                s->setRange(0, 32);
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
            b->align(eAlignment::left);

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

        countW->fitContent();
        iconsW->fitContent();
        namesW->fitContent();
        buttonsW->fitContent();
        spinsW->fitContent();

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
    }
};

void eStorageInfoWidget::initialize(eStorageBuilding* const stor) {
    eInfoWidget::initialize();

    eResourceType get;
    eResourceType empty;
    eResourceType accept;
    stor->getOrders(get, empty, accept);
    const auto all = stor->canAccept();
    const auto& maxCount = stor->maxCount();

    const auto rect = centralWidgetRect();

    const auto stWid = new eWidget(window());

    const auto types = eResourceTypeHelpers::extractResourceTypes(all);

    stWid->move(rect.x, rect.y);
    stWid->resize(rect.w, rect.h);

    if(types.size() < 7) {
        const auto r = new eResourceStorageStack(window());
        r->setWidth(rect.w);
        r->setHeight(rect.h);
        r->initialize(stor, types, get, empty, accept,
                      mButtons, mSpinBoxes, maxCount);
        stWid->addWidget(r);
    } else {
        {
            const auto r = new eResourceStorageStack(window());
            r->setWidth(rect.w/2);
            r->setHeight(rect.h);
            const std::vector<eResourceType> types1(
                        types.begin(), types.begin() + 6);
            r->initialize(stor, types1, get, empty, accept,
                          mButtons, mSpinBoxes, maxCount);
            stWid->addWidget(r);
        }
        {
            const auto r = new eResourceStorageStack(window());
            r->setWidth(rect.w/2);
            r->setHeight(rect.h);
            const std::vector<eResourceType> types1(
                        types.begin() + 6, types.end());
            r->initialize(stor, types1, get, empty, accept,
                          mButtons, mSpinBoxes, maxCount);
            stWid->addWidget(r);
        }
    }

    stWid->layoutHorizontally();

    addWidget(stWid);
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
