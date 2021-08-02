#ifndef EGAMEMENU_H
#define EGAMEMENU_H

#include "elabel.h"

class eCheckableButton;
class eTextureCollection;
class eInterfaceTextures;
class eButton;

class eGameMenu : public eLabel {
public:
    eGameMenu(eMainWindow* const window);
private:
    eCheckableButton* createButton(const eTextureCollection& texs,
                                   eWidget* const buttons);
    eButton* createSubButton(const eTextureCollection& texs,
                             eWidget* const buttons);
    using eTexCollVec = std::vector<const eTextureCollection*>;
    eWidget* createSubButtons(const int resoltuionMult,
                              const eTexCollVec& colls);

    const eRes mRes;

    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENU_H
