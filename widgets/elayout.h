#ifndef ELAYOUT_H
#define ELAYOUT_H

#include "ewidget.h"

class eLayout {
public:
    eLayout();
    virtual ~eLayout();

    using eWidgets = std::vector<eWidget*>;
    virtual void layoutWidgets(const SDL_Rect& rect,
                               const eWidgets& ws) const = 0;
};

#endif // ELAYOUT_H
