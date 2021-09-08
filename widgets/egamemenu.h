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
class eAppealDataWidget;
class eMiniMap;
class eGameWidget;

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
private:
    void setMode(const eBuildingMode mode);
    eButton* createSubButton(const eTextureCollection& texs,
                             eWidget* const buttons);
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
    eAppealDataWidget* mApplDataW = nullptr;

    eMiniMap* mMiniMap = nullptr;

    eBuildingMode mMode{eBuildingMode::road};

    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENU_H
