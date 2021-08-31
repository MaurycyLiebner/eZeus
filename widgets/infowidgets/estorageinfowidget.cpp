#include "estorageinfowidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

class eResourceStorageStack : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::vector<eResourceType>& types,
                    const eResourceType get,
                    const eResourceType empty,
                    const eResourceType accept,
                    std::map<eResourceType, eSwitchButton*>& buttons) {
        const auto iconsW = new eWidget(window());
        const auto namesW = new eWidget(window());
        const auto buttonsW = new eWidget(window());

        const auto& intrfc = eGameTextures::interface();
        int icoll;
        int mult;
        switch(resolution()) {
        case eRes::p480:
            mult = 1;
            icoll = 0;
            break;
        case eRes::p720:
        case eRes::p1080:
            mult = 2;
            icoll = 1;
            break;
        default:
            mult = 4;
            icoll = 2;
        }
        const auto& coll = intrfc[icoll];

        const int rowHeight = mult*20;
        const int iconsWidth = mult*20;
        const int namesWidth = mult*45;
        const int buttonsWidth = mult*65;

        iconsW->setWidth(iconsWidth);
        namesW->setWidth(namesWidth);
        buttonsW->setWidth(buttonsWidth);

        namesW->setX(iconsW->x() + iconsW->width());
        buttonsW->setX(namesW->x() + namesW->width());

        for(const auto type : types) {
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

            iconsW->addWidget(icon);
            namesW->addWidget(n);
            buttonsW->addWidget(b);

            icon->align(eAlignment::hcenter);
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

        iconsW->stackVertically();
        namesW->stackVertically();
        buttonsW->stackVertically();

        iconsW->fitContent();
        namesW->fitContent();
        buttonsW->fitContent();

        addWidget(iconsW);
        addWidget(namesW);
        addWidget(buttonsW);

        layoutHorizontally();
    }
};

void eStorageInfoWidget::initialize(const eResourceType all,
                                    const eResourceType get,
                                    const eResourceType empty,
                                    const eResourceType accept) {
    eInfoWidget::initialize();

    const auto rect = centralWidgetRect();

    const auto stWid = new eWidget(window());

    const auto types = eResourceTypeHelpers::extractResourceTypes(all);

    stWid->move(rect.x, rect.y);
    stWid->resize(rect.w, rect.h);

    if(types.size() < 7) {
        const auto r = new eResourceStorageStack(window());
        r->setWidth(rect.w);
        r->setHeight(rect.h);
        r->initialize(types, get, empty, accept, mButtons);
        stWid->addWidget(r);
    } else {
        {
            const auto r = new eResourceStorageStack(window());
            r->setWidth(rect.w/2);
            r->setHeight(rect.h);
            const std::vector<eResourceType> types1(
                        types.begin(), types.begin() + 6);
            r->initialize(types1, get, empty, accept, mButtons);
            stWid->addWidget(r);
        }
        {
            const auto r = new eResourceStorageStack(window());
            r->setWidth(rect.w/2);
            r->setHeight(rect.h);
            const std::vector<eResourceType> types1(
                        types.begin() + 6, types.end());
            r->initialize(types1, get, empty, accept, mButtons);
            stWid->addWidget(r);
        }
    }

    stWid->layoutHorizontally();

    addWidget(stWid);
}

void eStorageInfoWidget::get(eResourceType& get,
                             eResourceType& empty,
                             eResourceType& accept,
                             eResourceType& dontaccept) const {
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
}
