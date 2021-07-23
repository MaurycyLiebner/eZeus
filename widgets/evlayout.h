#ifndef EVLAYOUT_H
#define EVLAYOUT_H

#include "elayout.h"

class eVLayout : public eLayout {
public:
    eVLayout();

    void layoutWidgets(const SDL_Rect& rect,
                       const eWidgets& ws) const;
};

#endif // EVLAYOUT_H
