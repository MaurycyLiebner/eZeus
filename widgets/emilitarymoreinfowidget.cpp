#include "emilitarymoreinfowidget.h"

#include "engine/egameboard.h"
#include "characters/esoldierbanner.h"
#include "elabel.h"
#include "emicrobutton.h"
#include "elanguage.h"

eMilitaryMoreInfoWidget::eMilitaryMoreInfoWidget(
        eMainWindow* const window) :
    eInfoWidget(window, false, false) {}

void sArmySectionButtonUpdate(const stdsptr<eSoldierBanner>& b,
                              eMicroButton* const mb) {
    if(b->isAbroad()) { // abroad
        mb->setText(eLanguage::zeusText(51, 24));
        mb->setTooltip(eLanguage::zeusText(51, 31));
    } else if(b->fighting()) { // fighting
        mb->setText(eLanguage::zeusText(51, 23));
        mb->setTooltip(eLanguage::zeusText(51, 27));
        mb->setPressAction([b, mb]() {
            b->goHome();
            sArmySectionButtonUpdate(b, mb);
        });
    } else if(b->isGoingHome()) { // going home
        mb->setText(eLanguage::zeusText(51, 21));
        mb->setTooltip(eLanguage::zeusText(51, 28));
        mb->setPressAction([b, mb]() {
            b->backFromHome();
            sArmySectionButtonUpdate(b, mb);
        });
    } else if(b->isHome()) { // at home
        mb->setText(eLanguage::zeusText(51, 18));
        mb->setTooltip(eLanguage::zeusText(51, 25));
        mb->setPressAction([b, mb]() {
            b->backFromHome();
            sArmySectionButtonUpdate(b, mb);
        });
    } else if(b->stationary()) { // still
        mb->setText(eLanguage::zeusText(51, 19));
        mb->setTooltip(eLanguage::zeusText(51, 26));
        mb->setPressAction([b, mb]() {
            b->goHome();
            sArmySectionButtonUpdate(b, mb);
        });
    } else { // marching
        mb->setText(eLanguage::zeusText(51, 20));
        mb->setTooltip(eLanguage::zeusText(51, 27));
        mb->setPressAction([b, mb]() {
            b->goHome();
            sArmySectionButtonUpdate(b, mb);
        });
    }
}

class eArmySection : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eBanners = std::vector<stdsptr<eSoldierBanner>>;
    void initialize(const std::string& name,
                    const eBanners& banners,
                    const bool atlantean) {
        setType(eFrameType::inner);

        const auto res = resolution();
        const auto uiScale = res.uiScale();
        const auto& intrfc = eGameTextures::interface();
        const auto& coll = intrfc[static_cast<int>(uiScale)];
        const int p = padding();

        const auto iw = new eWidget(window());
        iw->setNoPadding();
        iw->setWidth(width() - 2*p);

        if(!name.empty()) {
            const auto rowW = new eWidget(window());
            rowW->setNoPadding();
            rowW->setWidth(iw->width() - 2*p);

            const auto nameL = new eLabel(window());
            nameL->setNoPadding();
            nameL->setTinyFontSize();
            nameL->setText(name);
            nameL->fitContent();
            rowW->addWidget(nameL);

            const auto troopsL = new eLabel(window());
            troopsL->setNoPadding();
            troopsL->setTinyFontSize();
            troopsL->setText(eLanguage::zeusText(51, 17));
            troopsL->fitContent();
            rowW->addWidget(troopsL);
            troopsL->align(eAlignment::right);

            rowW->fitHeight();
            addWidget(rowW);
            rowW->setX(p);
        }

        if(banners.empty()) {
            const auto noneL = new eLabel(window());
            noneL->setNoPadding();
            noneL->setTinyFontSize();
            noneL->setText(eLanguage::zeusText(283, 12));
            noneL->fitContent();
            iw->addWidget(noneL);
        }

        for(const auto& b : banners) {
            const auto w = new eWidget(window());
            w->setNoPadding();
            w->setWidth(iw->width());

            const int id = b->id();
            const auto type = b->type();
            if(type == eBannerType::rockThrower ||
               type == eBannerType::hoplite ||
               type == eBannerType::horseman) {
                const auto& bnrs = coll.fInterfaceBanners;
                const auto& bnr = bnrs.getTexture(id % bnrs.size());
                const auto bnrl = new eLabel(window());
                bnrl->setTexture(bnr);
                bnrl->setNoPadding();
                bnrl->fitContent();
                w->addWidget(bnrl);
            }

            {
                stdsptr<eTexture> tex;
                bool valid = false;
                if(atlantean && type != eBannerType::amazon &&
                   type != eBannerType::aresWarrior) {
                    const auto& tops = coll.fPoseidonInterfaceBannerTops;
                    int topId = 0;
                    switch(type) {
                    case eBannerType::horseman:
                        topId = 0;
                        valid = true;
                        break;
                    case eBannerType::hoplite:
                        topId = 2;
                        valid = true;
                        break;
                    case eBannerType::rockThrower:
                        topId = 1;
                        valid = true;
                        break;
                    default:
                        topId = 0;
                        valid = false;
                        break;
                    }

                    tex = tops.getTexture(topId);
                } else {
                    const auto& tops = coll.fInterfaceBannerTops;
                    int topId = 0;
                    switch(type) {
                    case eBannerType::horseman:
                        topId = 0;
                        valid = true;
                        break;
                    case eBannerType::hoplite:
                        topId = 1;
                        valid = true;
                        break;
                    case eBannerType::rockThrower:
                        topId = 2;
                        valid = true;
                        break;
                    case eBannerType::amazon:
                        topId = 4;
                        valid = true;
                        break;
                    case eBannerType::aresWarrior:
                        topId = 5;
                        valid = true;
                        break;
                    default:
                        topId = 0;
                        valid = false;
                        break;
                    }

                    tex = tops.getTexture(topId);
                }
                const auto bnrl = new eLabel(window());
                bnrl->setTexture(tex);
                bnrl->setNoPadding();
                bnrl->fitContent();
                w->addWidget(bnrl);
                bnrl->setVisible(valid);
            }

            {
                const auto titlel = new eLabel(window());
                titlel->setTinyFontSize();
                titlel->setNoPadding();
                titlel->setText(b->name());
                titlel->fitContent();
                w->addWidget(titlel);
            }
            w->stackHorizontally();

            const auto ww = new eWidget(window());
            ww->setNoPadding();

            const auto cLabel = new eLabel(window());
            cLabel->setNoPadding();
            cLabel->setTinyFontSize();
            cLabel->setText(std::to_string(b->count()));
            cLabel->fitContent();
            ww->addWidget(cLabel);

            const double mult = res.multiplier();

            const int microW = std::round(70*mult);

            const auto mb = new eMicroButton(window());
            mb->setNoPadding();
            mb->setTinyFontSize();
            sArmySectionButtonUpdate(b, mb);
            mb->setWidth(microW);
            mb->fitHeight();
            ww->addWidget(mb);

            ww->stackHorizontally(p);
            ww->fitContent();
            w->addWidget(ww);
            ww->align(eAlignment::right);

            w->fitHeight();
            iw->addWidget(w);
        }

        iw->stackVertically();
        iw->fitHeight();
        setHeight(iw->height() + 2*p);
        iw->move(p, p);
        addWidget(iw);
        stackVertically();
    }
};

void eMilitaryMoreInfoWidget::initialize(eGameBoard& board) {
    eInfoWidget::initialize("");

    mBoard = &board;

    const bool atlantean = board.poseidonMode();

    const auto res = resolution();
    const int p = res.largePadding();
    const auto cw = addCentralWidget();

    const int ww = (cw->width() - p)/2;

    const auto leftW = new eWidget(window());
    leftW->setNoPadding();
    leftW->setWidth(ww);

    const auto citizenArmy = new eLabel(window());
    citizenArmy->setNoPadding();
    citizenArmy->setSmallFontSize();
    citizenArmy->setText(eLanguage::zeusText(51, 13));
    citizenArmy->fitContent();
    leftW->addWidget(citizenArmy);
    citizenArmy->align(eAlignment::hcenter);

    const auto& banners = board.banners();
//    std::vector<stdsptr<eSoldierBanner>> banners;
//    for(int i = 0; i < 3; i++) {
//        banners.push_back(e::make_shared<eSoldierBanner>(
//                              eBannerType::horseman, board));
//    }
//    for(int i = 0; i < 4; i++) {
//        banners.push_back(e::make_shared<eSoldierBanner>(
//                              eBannerType::hoplite, board));
//    }
//    for(int i = 0; i < 13; i++) {
//        banners.push_back(e::make_shared<eSoldierBanner>(
//                              eBannerType::rockThrower, board));
//    }
//    for(int i = 0; i < 2; i++) {
//        banners.push_back(e::make_shared<eSoldierBanner>(
//                              eBannerType::amazon, board));
//    }

    std::vector<stdsptr<eSoldierBanner>> horsemenBanners;
    for(const auto& b : banners) {
        const auto type = b->type();
        if(type != eBannerType::horseman) continue;
        horsemenBanners.push_back(b);
    }

    std::vector<stdsptr<eSoldierBanner>> hopliteBanners;
    for(const auto& b : banners) {
        const auto type = b->type();
        if(type != eBannerType::hoplite) continue;
        hopliteBanners.push_back(b);
    }

    std::vector<stdsptr<eSoldierBanner>> rabbleBanners;
    for(const auto& b : banners) {
        const auto type = b->type();
        if(type != eBannerType::rockThrower) continue;
        rabbleBanners.push_back(b);
    }

    std::vector<stdsptr<eSoldierBanner>> mythicalBanners;
    for(const auto& b : banners) {
        const auto type = b->type();
        if(type != eBannerType::amazon &&
           type != eBannerType::aresWarrior) continue;
        mythicalBanners.push_back(b);
    }

    if(!horsemenBanners.empty()) {
        const auto horsemen = new eArmySection(window());
        horsemen->setWidth(ww);
        const auto title = atlantean ? eLanguage::zeusText(51, 86) :
                                       eLanguage::zeusText(51, 14);
        horsemen->initialize(title, horsemenBanners, atlantean);
        leftW->addWidget(horsemen);
    }

    if(!hopliteBanners.empty()) {
        const auto hoplites = new eArmySection(window());
        hoplites->setWidth(ww);
        const auto title = atlantean ? eLanguage::zeusText(51, 87) :
                                       eLanguage::zeusText(51, 15);
        hoplites->initialize(title, hopliteBanners, atlantean);
        leftW->addWidget(hoplites);
    }

    if(!rabbleBanners.empty()) {
        const auto rabble = new eArmySection(window());
        rabble->setWidth(ww);
        const auto title = atlantean ? eLanguage::zeusText(51, 88) :
                                       eLanguage::zeusText(51, 16);
        rabble->initialize(title, rabbleBanners, atlantean);
        leftW->addWidget(rabble);
    }

    leftW->stackVertically(p);
    leftW->fitHeight();
    cw->addWidget(leftW);

    const auto rightW = new eWidget(window());
    rightW->setNoPadding();
    rightW->setWidth(ww);

    const auto navyL = new eLabel(window());
    navyL->setNoPadding();
    navyL->setSmallFontSize();
    navyL->setText(eLanguage::zeusText(51, 32));
    navyL->fitContent();
    rightW->addWidget(navyL);
    navyL->align(eAlignment::hcenter);

    const auto navy = new eArmySection(window());
    navy->setWidth(ww);
    navy->initialize("", {}, atlantean);
    rightW->addWidget(navy);

    const auto otherForesL = new eLabel(window());
    otherForesL->setNoPadding();
    otherForesL->setSmallFontSize();
    otherForesL->setText(eLanguage::zeusText(51, 54));
    otherForesL->fitContent();
    rightW->addWidget(otherForesL);
    otherForesL->align(eAlignment::hcenter);

    const auto mercenaries = new eArmySection(window());
    mercenaries->setWidth(ww);
    mercenaries->initialize(eLanguage::zeusText(51, 67),
                            {}, atlantean);
    rightW->addWidget(mercenaries);

    const auto mythical = new eArmySection(window());
    mythical->setWidth(ww);
    mythical->initialize(eLanguage::zeusText(51, 68),
                         mythicalBanners, atlantean);
    rightW->addWidget(mythical);

    rightW->stackVertically(p);
    rightW->fitHeight();
    cw->addWidget(rightW);
    rightW->align(eAlignment::right);

    setCloseAction([this]() {
        deleteLater();
    });
}
