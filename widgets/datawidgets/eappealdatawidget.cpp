#include "eappealdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"
#include "widgets/emultilinelabel.h"
#include "engine/egameboard.h"
#include "evectorhelpers.h"
#include "buildings/eaestheticsbuilding.h"

#include "elanguage.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eViewModeButton(
                     eLanguage::text("see_appeal"),
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

            const auto commParser = [&](const int id, const std::string& name) {
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

                auto title = eLanguage::text(name + "_monument_data_widget");
                const auto count = tiles.size();
                if(count > 1) {
                    title = title + " (" + std::to_string(count) + ")";
                }

                const auto w = new eMonumentButton(window());
                w->initialize(title, tiles, gw);
                mMonumentsWidget->addWidget(w);
                w->align(eAlignment::hcenter);
            };

            commParser(0, "population");
            commParser(1, "victory");
            commParser(2, "colony");
            commParser(3, "athlete");
            commParser(4, "conquest");
            commParser(5, "happiness");
            commParser(6, "commemorative7");
            commParser(7, "commemorative8");
            commParser(8, "scholar");

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
                const auto name = eGod::sGodName(g);
                auto title = name;
                if(count > 1) {
                    title = title + " (" + std::to_string(count) + ")";
                }

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
