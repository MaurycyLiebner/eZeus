#ifndef EGAMEMENU_H
#define EGAMEMENU_H

#include "elabel.h"

class eCheckableButton;
class eTextureCollection;
class eInterfaceTextures;
class eButton;

struct eSubButtonData;

class eGameMenu : public eLabel {
public:
    eGameMenu(eMainWindow* const window);
private:
    eCheckableButton* createButton(const eTextureCollection& texs,
                                   eWidget* const buttons);
    eButton* createSubButton(const eTextureCollection& texs,
                             eWidget* const buttons);
    using eButtonsDataVec = std::vector<eSubButtonData>;
    eWidget* createSubButtons(const int resoltuionMult,
                              const eButtonsDataVec& buttons);

    const eRes mRes;

    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENU_H
