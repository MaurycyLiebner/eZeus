#include "eappealdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"
#include "widgets/emultilinelabel.h"
#include "engine/egameboard.h"
#include "evectorhelpers.h"
#include "buildings/eaestheticsbuilding.h"

#include "elanguage.h"
#include "estringhelpers.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eViewModeButton(
                     eLanguage::zeusText(14, 17), // see appeal
                     eViewMode::appeal,
                     window());
    addViewButton(mSeeAppeal);

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int iw = inner->width();

    const auto title = new eLabel(window());
    title->setNoPadding();
    title->setVerySmallFontSize();
    title->setWrapWidth(iw);
    title->setWrapAlignment(eAlignment::hcenter);
    title->setText(eLanguage::zeusText(133, 1)); // commemorative monuments
    title->fitContent();
    inner->addWidget(title);

    mMonumentsWidget = new eWidget(window());
    mMonumentsWidget->setNoPadding();
    const int innerW = inner->width();
    mMonumentsWidget->setWidth(innerW);
    inner->addWidget(mMonumentsWidget);

    inner->stackVertically();
    title->align(eAlignment::hcenter);

    mNoMonumentsWidget = new eLabel(window());
    mNoMonumentsWidget->setWrapWidth(iw);
    mNoMonumentsWidget->setWrapAlignment(eAlignment::hcenter);
    mNoMonumentsWidget->setYellowFontColor();
    mNoMonumentsWidget->setNoPadding();
    mNoMonumentsWidget->setTinyFontSize();
    const auto text = eLanguage::zeusText(133, 2); // no commemorative monuments
    mNoMonumentsWidget->setText(text);
    mNoMonumentsWidget->fitContent();
    inner->addWidget(mNoMonumentsWidget);
    mNoMonumentsWidget->setY(mMonumentsWidget->y());
    mNoMonumentsWidget->align(eAlignment::hcenter);
}

class eMonumentButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void initialize(const std::string& txt,
                    const std::vector<eTile*>& tiles,
                    eGameWidget* const gw) {
        mTiles = tiles;

        setYellowFontColor();
        setNoPadding();
        setTinyFontSize();
        setText(txt);
        fitContent();

        setMouseEnterAction([this]() {
            setLightFontColor();
        });
        setMouseLeaveAction([this]() {
            setYellowFontColor();
        });
        setPressAction([this, gw]() {
            const int ts = mTiles.size();
            if(mId >= ts) mId = 0;
            const auto tile = mTiles[mId];
            gw->viewTile(tile);
            mId++;
        });
    }
private:
    int mId = 0;
    std::vector<eTile*> mTiles;
};

void eAppealDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        const auto& bs = mBoard.commemorativeBuildings();
        const bool changed = !eVectorHelpers::same(bs, mBuildings);
        if(changed) {
            mNoMonumentsWidget->setVisible(bs.empty());
            mBuildings = bs;
            mMonumentsWidget->removeAllWidgets();
            const auto gw = gameWidget();

            const auto templ1 = eLanguage::zeusText(133, 3); // [commemorative_monument]
            const auto templ2 = eLanguage::zeusText(133, 4); // [commemorative_monument] ([amount])

            const auto commParser = [&](const int id, const int string) {
                std::vector<eTile*> tiles;
                for(const auto b : mBuildings) {
                    const auto bt = b->type();
                    if(bt != eBuildingType::commemorative) continue;
                    const auto c = static_cast<eCommemorative*>(b);
                    const int cid = c->id();
                    if(cid == id) {
                        const auto tile = b->centerTile();
                        tiles.push_back(tile);
                    }
                }
                if(tiles.empty()) return;

                std::string title;
                const auto count = tiles.size();
                if(count > 1) {
                    title = templ2;
                    const auto countStr = std::to_string(count);
                    eStringHelpers::replace(title, "[amount]", countStr);
                } else {
                    title = templ1;
                }
                const auto monStr = eLanguage::zeusText(133, string);
                eStringHelpers::replace(title, "[commemorative_monument]", monStr);

                const auto w = new eMonumentButton(window());
                w->initialize(title, tiles, gw);
                mMonumentsWidget->addWidget(w);
                w->align(eAlignment::hcenter);
            };

            commParser(0, 5); // population
            commParser(1, 7); // victory
            commParser(2, 10); // colony
            commParser(3, 13); // athelete
            commParser(4, 8); // conquest
            commParser(5, 11); // happiness
            commParser(6, 6); // heroic
            commParser(7, 9); // diplomacy
            commParser(8, 12); // scholar

            std::map<eGodType, std::vector<eTile*>> gods;
            for(const auto b : mBuildings) {
                const auto bt = b->type();
                if(bt != eBuildingType::godMonument) continue;
                const auto c = static_cast<eGodMonument*>(b);
                const auto tile = c->centerTile();
                const auto god = c->god();
                gods[god].push_back(tile);
            }
            for(const auto& gg : gods) {
                const auto g = gg.first;
                const auto& tiles = gg.second;
                const auto count = tiles.size();
                std::string title;
                if(count > 1) {
                    title = templ2;
                    const auto countStr = std::to_string(count);
                    eStringHelpers::replace(title, "[amount]", countStr);
                } else {
                    title = templ1;
                }
                const auto name = eGod::sGodName(g);
                eStringHelpers::replace(title, "[commemorative_monument]", name);

                const auto w = new eMonumentButton(window());
                w->initialize(title, tiles, gw);
                mMonumentsWidget->addWidget(w);
                w->align(eAlignment::hcenter);
            }

            mMonumentsWidget->stackVertically();
            mMonumentsWidget->fitHeight();
        }
    }
    eWidget::paintEvent(p);
}
