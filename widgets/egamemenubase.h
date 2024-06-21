#ifndef EGAMEMENUBASE_H
#define EGAMEMENUBASE_H

#include "elabel.h"

#include "echeckablebutton.h"
#include "etexturecollection.h"

class eGameMenuBase : public eLabel {
public:
    using eLabel::eLabel;

    void initialize();
    eCheckableButton* addButton(
            const eTextureCollection& coll,
            eWidget* const w);
    void connectAndLayoutButtons();
private:
    eWidget* mButtonsWidget = nullptr;
    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
};

#endif // EGAMEMENUBASE_H
