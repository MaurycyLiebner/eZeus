#ifndef EGAMEMENU_H
#define EGAMEMENU_H

#include "elabel.h"

class eCheckableButton;
class eTextureCollection;
class eInterfaceTextures;
class eButton;

struct eSubButtonData;

enum class eBuildingMode {
    road,

    commonHousing,
    eliteHousing,

    wheatFarm,
    carrotFarm,
    onionFarm,

    vine,
    oliveTree,
    growersLodge,

    dairy,
    goat,
    cardingShed,
    sheep,

    fishery,
    urchinQuay,
    huntingLodge,

    mint,
    foundry,
    timberMill,
    masonryShop,

    winery,
    olivePress,
    sculptureStudio,
    artisansGuild,

    podium,
    college,

    theater,
    dramaSchool,

    gymnasium,
    stadium,

    granary,
    warehouse,

    maintenanceOffice,
    fountain,
    hospital,
    watchpost,

    taxOffice
};

class eGameMenu : public eLabel {
public:
    eGameMenu(eMainWindow* const window);

    eBuildingMode mode() const { return mMode; }
private:
    void setMode(const eBuildingMode mode);

    eCheckableButton* createButton(const eTextureCollection& texs,
                                   eWidget* const buttons);
    eButton* createSubButton(const eTextureCollection& texs,
                             eWidget* const buttons);
    using eButtonsDataVec = std::vector<eSubButtonData>;
    eWidget* createSubButtons(const int resoltuionMult,
                              const eButtonsDataVec& buttons);

    const eRes mRes;

    eBuildingMode mMode{eBuildingMode::road};

    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENU_H
