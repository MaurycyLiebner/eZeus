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

    const eRes mRes;
};

#endif // EGAMEMENU_H
