#ifndef EMAINMENUBASE_H
#define EMAINMENUBASE_H

#include "elabel.h"

class eMainMenuBase : public eLabel {
public:
    using eLabel::eLabel;

    void initialize();
};

#endif // EMAINMENUBASE_H
