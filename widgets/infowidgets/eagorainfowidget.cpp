#include "eagorainfowidget.h"

#include "widgets/eframedbutton.h"

#include "buildings/ecommonagora.h"
#include "buildings/egrandagora.h"
#include "buildings/evendor.h"

#include "elanguage.h"

class eAgoraButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    void initialize(eAgoraBase* const a,
                    const eResourceType res);

    void updateStateLabel(eAgoraBase* const a,
                          const eResourceType res) {
        const int c = a->agoraCount(res);
        std::string text;
        bool dark = true;
        if(const auto v = a->vendor(res)) {
            if(!v->vendorEnabled()) {
                text = "not_buying";
            } else if(c == 0) {
                text = "no_goods";
            } else {
                text = "distributing";
                dark = false;
            }
        } else {
            text = "no_vendor";
        }
        if(dark) mStateLabel->setDarkFontColor();
        else mStateLabel->setLightFontColor();
        mStateLabel->setText(eLanguage::text(text));
        mStateLabel->fitContent();
    }
private:
    eLabel* mStateLabel = nullptr;
};

void eAgoraButton::initialize(eAgoraBase* const a,
                              const eResourceType res) {
    const int c = a->agoraCount(res);
    const auto reso = resolution();
    const auto uiScale = reso.uiScale();
    const int m = reso.multiplier();
    const auto icon = eResourceTypeHelpers::icon(uiScale, res);
    const auto name = eResourceTypeHelpers::typeName(res);

    const auto cw = new eWidget(window());
    cw->resize(123*m, 80*m);
    cw->setNoPadding();

    const auto nameLabel = new eLabel(window());
    nameLabel->setSmallFontSize();
    nameLabel->setTinyPadding();
    nameLabel->setText(name);
    nameLabel->fitContent();
    cw->addWidget(nameLabel);

    const auto iw = new eWidget(window());
    iw->setNoPadding();

    const auto iconLabel = new eLabel(window());
    iconLabel->setTinyPadding();
    iconLabel->setTexture(icon);
    iconLabel->fitContent();
    iw->addWidget(iconLabel);

    const auto countLabel = new eLabel(window());
    countLabel->setTinyPadding();
    countLabel->setSmallFontSize();
    countLabel->setText(std::to_string(c));
    countLabel->fitContent();
    iw->addWidget(countLabel);
    countLabel->setX(iconLabel->width());

    iw->fitContent();
    cw->addWidget(iw);
    iw->setY(nameLabel->height());

    const auto stateLabel = new eLabel(window());
    stateLabel->setTinyPadding();
    stateLabel->setSmallFontSize();
    mStateLabel = stateLabel;
    updateStateLabel(a, res);
    stateLabel->fitContent();
    cw->addWidget(stateLabel);
    stateLabel->setY(iw->y() + iw->height());

    addWidget(cw);
    cw->move(5*m, 5*m);
    resize(cw->width() + 10*m, cw->height() + 10*m);
}

eAgoraInfoWidget::eAgoraInfoWidget(eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, true) {}

void eAgoraInfoWidget::initialize(eAgoraBase* const a) {
    std::string title;
    if(dynamic_cast<eCommonAgora*>(a)) {
        title = eLanguage::text("common_agora");
    } else if(dynamic_cast<eGrandAgora*>(a)) {
        title = eLanguage::text("grand_agora");
    } else {
        return;
    }
    eEmployingBuildingInfoWidget::initialize(title, a);

    const auto cw = centralWidget();

    const int p = padding();
    const int d = 2*p;

    int x = 0;
    int y = 0;

    const auto food = new eAgoraButton(window());
    food->initialize(a, eResourceType::food);
    cw->addWidget(food);
    food->move(x, y);
    food->setPressAction([a, food]() {
        const auto v = a->vendor(eResourceType::food);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        food->updateStateLabel(a, eResourceType::food);
    });

    x += food->width() + d;

    const auto fleece = new eAgoraButton(window());
    fleece->initialize(a, eResourceType::fleece);
    cw->addWidget(fleece);
    fleece->move(x, y);
    fleece->setPressAction([a, fleece]() {
        const auto v = a->vendor(eResourceType::fleece);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        fleece->updateStateLabel(a, eResourceType::fleece);
    });

    x += food->width() + d;

    const auto oil = new eAgoraButton(window());
    oil->initialize(a, eResourceType::oliveOil);
    cw->addWidget(oil);
    oil->move(x, y);
    oil->setPressAction([a, oil]() {
        const auto v = a->vendor(eResourceType::oliveOil);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        oil->updateStateLabel(a, eResourceType::oliveOil);
    });

    x = 0;
    y += food->height() + d;

    const auto wine = new eAgoraButton(window());
    wine->initialize(a, eResourceType::wine);
    cw->addWidget(wine);
    wine->move(x, y);
    wine->setPressAction([a, wine]() {
        const auto v = a->vendor(eResourceType::wine);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        wine->updateStateLabel(a, eResourceType::wine);
    });

    x += food->width() + d;

    const auto arms = new eAgoraButton(window());
    arms->initialize(a, eResourceType::armor);
    cw->addWidget(arms);
    arms->move(x, y);
    arms->setPressAction([a, arms]() {
        const auto v = a->vendor(eResourceType::armor);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        arms->updateStateLabel(a, eResourceType::armor);
    });

    x += food->width() + d;

    const auto horse = new eAgoraButton(window());
    horse->initialize(a, eResourceType::horse);
    cw->addWidget(horse);
    horse->move(x, y);
    horse->setPressAction([a, horse]() {
        const auto v = a->vendor(eResourceType::horse);
        if(!v) return;
        const bool ve = v->vendorEnabled();
        v->setVendorEnabled(!ve);
        horse->updateStateLabel(a, eResourceType::horse);
    });
}
