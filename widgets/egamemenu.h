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
class eCultureDataWidget;
class eMiniMap;
class eGameWidget;
class eEventWidget;
enum class eEvent;

struct eSubButtonData;

class eContextMenu;

class eGameMenu : public eGameMenuBase {
public:
    using eGameMenuBase::eGameMenuBase;
    void initialize();

    eBuildingMode mode() const { return mMode; }
    void clearMode() { mMode = eBuildingMode::none; }

    void setGameWidget(eGameWidget* const gw);
    void setBoard(eGameBoard* const b);

    eMiniMap* miniMap() const;

    void pushEvent(const eEvent e, eTile* const tile);

    using eViewTileHandler = std::function<void(eTile*)>;
    void setViewTileHandler(const eViewTileHandler& h);
private:
    void setMode(const eBuildingMode mode);
    using eButtonsDataVec = std::vector<eSubButtonData>;
    eWidget* createSubButtons(const int resoltuionMult,
                              const eButtonsDataVec& buttons);
    using eSPR = std::pair<eBuildingMode, std::string>;
    void addAction(const eSPR& c, const int mult,
                   const eInterfaceTextures& coll,
                   eContextMenu* const cm);

    eGameBoard* mBoard{nullptr};

    ePopulationDataWidget* mPopDataW = nullptr;
    eEmploymentDataWidget* mEmplDataW = nullptr;
    eStorageDataWidget* mStrgDataW = nullptr;
    eAppealDataWidget* mApplDataW = nullptr;
    eHygieneSafetyDataWidget* mHySaDataW = nullptr;
    eAdminDataWidget* mAdminDataW = nullptr;
    eCultureDataWidget* mCultureDataW = nullptr;

    eButton* mWorldButton = nullptr;

    eMiniMap* mMiniMap = nullptr;

    eBuildingMode mMode{eBuildingMode::none};

    std::vector<eWidget*> mWidgets;

    eEventWidget* mEventW = nullptr;
};

#endif // EGAMEMENU_H
