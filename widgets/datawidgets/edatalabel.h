#ifndef EDATALABEL_H
#define EDATALABEL_H

#include "../elabel.h"

class eDataLabel : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& text);

    eLabel* label() { return mLabel; }
private:
    eLabel* mLabel = nullptr;
};

#endif // EDATALABEL_H
