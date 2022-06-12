#ifndef EBUILDBUTTON_H
#define EBUILDBUTTON_H

#include "ebuttonbase.h"

class eBuildButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void initialize(const std::string& name,
                    const int marbleCost,
                    const int cost);
protected:
    void paintEvent(ePainter& p);
};

#endif // EBUILDBUTTON_H
