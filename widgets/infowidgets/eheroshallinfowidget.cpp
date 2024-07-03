#include "eheroshallinfowidget.h"

#include "buildings/eheroshall.h"
#include "widgets/elabel.h"
#include "widgets/eframedbutton.h"
#include "textures/egametextures.h"
#include "elanguage.h"

void eHerosHallInfoWidget::initialize(eHerosHall* const b) {
    const auto ht = b->heroType();
    const auto title = eBuilding::sNameForBuilding(b);
    eInfoWidget::initialize(title);

    const int p = padding();

    int met = 0;
    const auto& reqs = b->requirements();
    int y = 0;
    std::vector<eWidget*> wids;
    for(const auto& r : reqs) {
        const auto w = new eWidget(window());
        wids.push_back(w);
        w->setNoPadding();
        w->setWidth(widgetWidth() - 2*p);

        const bool finished = r.met();
        if(finished) met++;

        int x = 0;

        {
            const auto checkBox = new eLabel(window());
            checkBox->setNoPadding();

            const auto res = resolution();
            const auto uiScale = res.uiScale();
            const int iRes = static_cast<int>(uiScale);
            const auto& intrfc = eGameTextures::interface();
            const auto& texs = intrfc[iRes].fCheckBox;

            if(finished) {
                checkBox->setTexture(texs.getTexture(0));
            } else {
                checkBox->setTexture(texs.getTexture(1));
            }
            checkBox->fitContent();
            x += checkBox->width() + p;

            w->addWidget(checkBox);
        }

        {
            const auto reqStr = eHerosHall::sHeroRequirementText(r);
            const auto reqLabel = new eLabel(window());
            reqLabel->setNoPadding();
            reqLabel->setSmallFontSize();
            if(!finished) reqLabel->setYellowFontColor();
            reqLabel->setText(reqStr);
            reqLabel->fitContent();

            w->addWidget(reqLabel);
            reqLabel->setX(x);
        }

        {
            const auto statusStr = eHerosHall::sHeroRequirementStatusText(r);
            const auto sttsLabel = new eLabel(window());
            sttsLabel->setNoPadding();
            sttsLabel->setSmallFontSize();
            if(!finished) sttsLabel->setYellowFontColor();
            sttsLabel->setText(statusStr);
            sttsLabel->fitContent();

            w->addWidget(sttsLabel);
            sttsLabel->align(eAlignment::right);
        }

        w->setY(y);
        w->fitContent();
        y += w->height() + p;
    }

    const auto wid = addFramedWidget(y + p);
    for(const auto w : wids) {
        wid->addWidget(w);
    }

    const int reqC = reqs.size();
    const auto stage = b->stage();
    if(met >= reqC && stage == eHeroSummoningStage::none) {
        const auto summonButton = new eFramedButton(window());
        const auto txt = eLanguage::zeusText(185, 62) + " " + eHero::sHeroName(ht);
        summonButton->setText(txt);
        summonButton->setSmallFontSize();
        summonButton->fitContent();
        summonButton->setUnderline(false);
        const stdptr<eHerosHall> bptr(b);
        summonButton->setPressAction([bptr, summonButton]() {
            if(!bptr) return;
            bptr->summon();
            summonButton->deleteLater();
        });
        const auto wid = addRegularWidget(summonButton->height());
        wid->addWidget(summonButton);
        summonButton->align(eAlignment::center);
    }
}
