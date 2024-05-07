#ifndef EGAMEMENU_H
#define EGAMEMENU_H

#include "egamemenubase.h"
#include "ebuildingmode.h"

class eCheckableButton;
class eTextureCollection;
class eInterfaceTextures;
class eButton;
class eGameBoard;
class ePopulationDataWidget;
class eEmploymentDataWidget;
class eAdminDataWidget;
class eStorageDataWidget;
class eAppealDataWidget;
class eHygieneSafetyDataWidget;
class eHusbandryDataWidget;
class eMythologyDataWidget;
class eCultureDataWidget;
class eMilitaryDataWidget;
class eOverviewDataWidget;
class eMiniMap;
class eGameWidget;
class eEventWidget;
class eBuildButton;
class eBuildWidget;
class eFramedLabel;
enum class eEvent;

struct eSubButtonData;

class eSubButton;

class eContextMenu;

struct eSPR {
    eBuildingMode fMode;
    std::string fName;
    int fMarbleCost = 0;
    int fCity = -1;
};

class eGameMenu : public eGameMenuBase {
public:
    using eGameMenuBase::eGameMenuBase;
    ~eGameMenu();
    void initialize(eGameBoard* const b);

    int cityId() const { return mCityId; }
    eBuildingMode mode() const { return mMode; }
    void clearMode() { mMode = eBuildingMode::none; }

    void setGameWidget(eGameWidget* const gw);

    eMiniMap* miniMap() const;

    void pushEvent(const eEvent e, eTile* const tile);

    using eViewTileHandler = std::function<void(eTile*)>;
    void setViewTileHandler(const eViewTileHandler& h);

    void closeBuildWidget();
    void setBuildWidget(eBuildWidget* const bw);

    void updateButtonsVisibility();
    void openBuildWidget(const int cmx, const int cmy,
                         const std::vector<eSPR>& cs);

    void setModeChangedAction(const eAction& func);

    void updateGodQuestButtons();
protected:
    bool mousePressEvent(const eMouseEvent& e);
private:
    void setMode(const eBuildingMode mode);
    using eButtonsDataVec = std::vector<eSubButtonData>;
    eWidget* createSubButtons(const int resoltuionMult,
                              const eButtonsDataVec& buttons);
    void addAction(const eSPR& c, const int mult,
                   const eInterfaceTextures& coll,
                   eContextMenu* const cm);
    eBuildButton* createBuildButton(const eSPR& c);

    void displayPrice(const int price, const int loc);
    eWidget* createPriceWidget(const eInterfaceTextures& coll);

    eGameBoard* mBoard{nullptr};

    eBuildWidget* mBuildWidget = nullptr;

    eFramedLabel* mNameLabel = nullptr;

    eWidget* mStadiumButton = nullptr;
    eWidget* mPalaceButton = nullptr;

    ePopulationDataWidget* mPopDataW = nullptr;
    eEmploymentDataWidget* mEmplDataW = nullptr;
    eHusbandryDataWidget* mHusbDataW = nullptr;
    eStorageDataWidget* mStrgDataW = nullptr;
    eAppealDataWidget* mApplDataW = nullptr;
    eHygieneSafetyDataWidget* mHySaDataW = nullptr;
    eAdminDataWidget* mAdminDataW = nullptr;
    eCultureDataWidget* mCultureDataW = nullptr;
    eMythologyDataWidget* mMythDataW = nullptr;
    eMilitaryDataWidget* mMiltDataW = nullptr;
    eOverviewDataWidget* mOverDataW = nullptr;

    eButton* mWorldButton = nullptr;

    eMiniMap* mMiniMap = nullptr;

    int mCityId = -1;
    eBuildingMode mMode{eBuildingMode::none};

    std::vector<eWidget*> mWidgets;

    eEventWidget* mEventW = nullptr;

    std::vector<eWidget*> mPriceWidgets;
    std::vector<eLabel*> mPriceLabels;

    std::vector<eSubButton*> mSubButtons;

    eAction mModeChangeAct;
};

#endif // EGAMEMENU_H
