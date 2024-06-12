#include "eepisodeswidget.h"

#include "evectorhelpers.h"

#include "elabel.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "echoosebutton.h"
#include "emainwindow.h"
#include "eeditorsettingsmenu.h"

#include "engine/ecampaign.h"

void eEpisodesWidget::intialize(const std::shared_ptr<eCampaign>& c,
                                const eSetTextAction& sta) {
    mC = c;
    mSta = sta;

    const int colW = columnWidth();

    const auto labelsW = new eWidget(window());
    labelsW->setNoPadding();

    const auto idC = new eLabel(window());
    idC->setTinyFontSize();
    idC->setTinyPadding();
    idC->setText(eLanguage::zeusText(195, 9));
    idC->fitContent();
    idC->setWidth(colW);
    labelsW->addWidget(idC);

    const auto nextEpisodeC = new eLabel(window());
    nextEpisodeC->setTinyFontSize();
    nextEpisodeC->setTinyPadding();
    nextEpisodeC->setText(eLanguage::zeusText(195, 2));
    nextEpisodeC->fitContent();
    nextEpisodeC->setWidth(colW);
    labelsW->addWidget(nextEpisodeC);

    const auto episodeSettingsC = new eLabel(window());
    episodeSettingsC->setTinyFontSize();
    episodeSettingsC->setTinyPadding();
    episodeSettingsC->setText(eLanguage::zeusText(195, 10));
    episodeSettingsC->fitContent();
    episodeSettingsC->setWidth(colW);
    labelsW->addWidget(episodeSettingsC);

    const auto episodeTextC = new eLabel(window());
    episodeTextC->setTinyFontSize();
    episodeTextC->setTinyPadding();
    episodeTextC->setText(eLanguage::zeusText(195, 21));
    episodeTextC->fitContent();
    episodeTextC->setWidth(colW);
    labelsW->addWidget(episodeTextC);

    labelsW->stackHorizontally();
    addWidget(labelsW);
    labelsW->fitContent();

    mEpisodesW = new eWidget(window());
    mEpisodesW->setNoPadding();
    mEpisodesW->setWidth(width());
    addWidget(mEpisodesW);

    stackVertically();

    update();
}

void eEpisodesWidget::update() {
    mWs.clear();
    mEpisodesW->removeChildren();
    auto& es = mC->parentCityEpisodes();
    const int iMax = es.size();
    for(int i = 0; i < iMax; i++) {
        const auto& e = es[i];
        add(mC.get(), e, i == iMax - 1);
    }
}

class eEpisodeWidget : public eWidget {
public:
    using eWidget::eWidget;

    using ePCE = std::shared_ptr<eParentCityEpisode>;
    void initialize(const int id, const int colW,
                    eCampaign* const c,
                    const ePCE& e, const bool last,
                    const eAction& newE,
                    const eAction& insertE,
                    const eAction& deleteE,
                    const eAction& victoryE,
                    const eAction& selectTextE) {
        setNoPadding();

        const auto idL = new eLabel(window());
        idL->setTinyFontSize();
        idL->setNoPadding();
        idL->setWidth(colW);
        const auto idStr = std::to_string(id + 1) + ".";
        idL->setText(idStr);
        idL->fitHeight();
        addWidget(idL);

        const auto nextEpisodeW = new eWidget(window());
        nextEpisodeW->setNoPadding();
        nextEpisodeW->setWidth(colW);
        const auto nextEpisodeB = new eFramedButton(window());
        nextEpisodeB->setUnderline(false);
        nextEpisodeB->setTinyFontSize();
        nextEpisodeB->setTinyPadding();
        if(last) {
            nextEpisodeB->setText(eLanguage::zeusText(195, 50));
            nextEpisodeB->setTooltip(eLanguage::zeusText(278, 13));
            nextEpisodeB->setPressAction(newE);
        } else {
            const auto ne = e->fNextEpisode;
            nextEpisodeB->setText(ne == eEpisodeType::parentCity ?
                                      eLanguage::zeusText(195, 14) :
                                      eLanguage::zeusText(195, 15));
            nextEpisodeB->setTooltip(ne == eEpisodeType::parentCity ?
                                      eLanguage::zeusText(278, 12) :
                                      eLanguage::zeusText(278, 11));
            nextEpisodeB->setPressAction([e, nextEpisodeB]() {
                auto& ne = e->fNextEpisode;
                if(ne == eEpisodeType::parentCity) {
                    ne = eEpisodeType::colony;
                } else {
                    ne = eEpisodeType::parentCity;
                }
                nextEpisodeB->setText(ne == eEpisodeType::parentCity ?
                                          eLanguage::zeusText(195, 14) :
                                          eLanguage::zeusText(195, 15));
                nextEpisodeB->setTooltip(ne == eEpisodeType::parentCity ?
                                          eLanguage::zeusText(278, 12) :
                                          eLanguage::zeusText(278, 11));
            });
        }
        nextEpisodeB->fitContent();
        nextEpisodeW->addWidget(nextEpisodeB);
        nextEpisodeW->fitHeight();
        nextEpisodeB->align(eAlignment::hcenter);
        addWidget(nextEpisodeW);
        nextEpisodeB->setRightPressAction([this, insertE, deleteE, victoryE]() {
            const std::vector<std::string> anames{
                eLanguage::zeusText(195, 50), // victory
                eLanguage::zeusText(195, 17), // insert
                eLanguage::zeusText(195, 18) // delete
            };
            const auto choose = new eChooseButton(window());
            const auto act = [insertE, deleteE, victoryE](const int val) {
                if(val == 0) { // victory
                    victoryE();
                } else if(val == 1) { // insert
                    insertE();
                } else if(val == 2) { // delete
                    deleteE();
                }
            };
            choose->initialize(8, anames, act);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        });

        const auto settingsW = new eWidget(window());
        settingsW->setNoPadding();
        settingsW->setWidth(colW);
        const auto settingsB = new eFramedButton(window());
        settingsB->setUnderline(false);
        settingsB->setTinyFontSize();
        settingsB->setTinyPadding();
        settingsB->setText(eLanguage::zeusText(195, 13));
        settingsB->setTooltip(eLanguage::zeusText(278, 15));
        settingsB->fitContent();
        settingsW->addWidget(settingsB);
        settingsW->fitHeight();
        settingsB->align(eAlignment::hcenter);
        addWidget(settingsW);
        settingsB->setPressAction([this, c, e]() {
            const auto w = window();
            const auto m = new eEditorSettingsMenu(w);
            m->resize(w->width()/2, 2*w->height()/3);
            m->initialize(e.get(), &c->worldBoard());

            window()->execDialog(m);
            m->align(eAlignment::center);
        });
        settingsB->setRightPressAction([this, c, e]() {
            const auto& es = c->parentCityEpisodes();
            std::vector<stdsptr<eParentCityEpisode>> res;
            std::vector<std::string> anames;
            const int iMax = es.size();
            for(int i = 0; i < iMax; i++) {
                const auto& ee = es[i];
                if(ee == e) continue;
                anames.push_back(eLanguage::zeusText(195, 34 + i));
                res.push_back(ee);
            }
            anames.push_back(eLanguage::zeusText(195, 44)); // clear
            const auto choose = new eChooseButton(window());
            const auto act = [c, res, e](const int val) {
                const int rs = res.size();
                if(val < rs) {
                    const auto& ee = res[val];
                    c->copyParentCityEpisodeSettings(ee.get(), e.get());
                } else {
                    e->clear();
                }
            };
            choose->initialize(8, anames, act);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        });

        const auto textW = new eWidget(window());
        textW->setNoPadding();
        textW->setWidth(colW);
        mTextB = new eFramedButton(window());
        mTextB->setUnderline(false);
        mTextB->setTinyFontSize();
        mTextB->setTinyPadding();
        mTextB->setText("x");
        mTextB->setTooltip(eLanguage::zeusText(278, 16));
        mTextB->fitContent();
        textW->addWidget(mTextB);
        textW->fitHeight();
        mTextB->align(eAlignment::hcenter);
        addWidget(textW);
        mTextB->setPressAction([this, selectTextE]() {
            mTextB->setText("x");
            selectTextE();
        });
        mTextB->setText("");

        stackHorizontally();
        fitContent();

        idL->align(eAlignment::vcenter);
    }

    void deselectTextB() {
        mTextB->setText("");
    }
private:
    eFramedButton* mTextB = nullptr;
};

void eEpisodesWidget::deselectText(const int skipId) {
    const int iMax = mWs.size();
    for(int i = 0; i < iMax; i++) {
        if(i == skipId) continue;
        mWs[i]->deselectTextB();
    }
}

void eEpisodesWidget::add(eCampaign* const c,
                          const std::shared_ptr<eParentCityEpisode>& e,
                          const bool last) {
    const int colW = columnWidth();

    const auto w = new eEpisodeWidget(window());
    const int id = mEpisodesW->children().size();
    const auto newE = [this]() {
        mC->addParentCityEpisode();
        update();
    };
    const auto insertE = [this, id]() {
        mC->insertParentCityEpisode(id);
        update();
    };
    const auto deleteE = [this, id]() {
        mC->deleteParentCityEpisode(id);
        update();
    };
    const auto victoryE = [this, id]() {
        mC->setVictoryParentCityEpisode(id);
        update();
    };
    const auto setTextE = [this, id]() {
        deselectText(id);
        mSta(id);
    };
    w->initialize(id, colW, c, e, last,
                  newE, insertE, deleteE, victoryE, setTextE);
    mWs.push_back(w);

    mEpisodesW->addWidget(w);
    const auto res = resolution();
    const int p = res.tinyPadding();
    mEpisodesW->stackVertically(p);
    mEpisodesW->fitHeight();
}
