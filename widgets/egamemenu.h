#ifndef EGAMEMENU_H
#define EGAMEMENU_H

#include "elabel.h"

class eCheckableButton;
class eTextureCollection;
class eInterfaceTextures;

class eGameMenu : public eLabel {
public:
    eGameMenu(eMainWindow* const window);
private:
    eCheckableButton* createButton(const eTextureCollection& texs,
                                   eWidget* const buttons);
    eWidget* createButtons(const std::vector<const eTextureCollection*>& colls);

    const eRes mRes;

    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENU_H
