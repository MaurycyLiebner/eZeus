#ifndef EGAMEMENUBASE_H
#define EGAMEMENUBASE_H

#include "elabel.h"

#include "echeckablebutton.h"
#include "etexturecollection.h"

class eDataWidget;

struct eWid {
    eWid(eWidget* const w) :
        fW(w) {}
    eWid(eWidget* const w, eDataWidget* const dw) :
        fW(w), fDW(dw) {}

    eWidget* fW;
    eDataWidget* fDW = nullptr;
};

class eGameMenuBase : public eLabel {
public:
    using eLabel::eLabel;

    void initialize();
    eCheckableButton* addButton(const eTextureCollection& coll,
                                const eWid& w);
    void connectAndLayoutButtons();
private:
    eWidget* mButtonsWidget = nullptr;
    std::vector<eCheckableButton*> mButtons;
    std::vector<eWid> mWidgets;
};

#endif // EGAMEMENUBASE_H
