#ifndef ECHECKBOX_H
#define ECHECKBOX_H

#include "ewidget.h"

class eCheckBox : public eWidget {
public:
    eCheckBox(eMainWindow* const window);

    void setChecked(const bool c);

    using eCheckAction = std::function<void(bool)>;
    void setCheckAction(const eCheckAction& a);
protected:
    void sizeHint(int& w, int& h);

    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
private:
    bool mChecked = false;
    eCheckAction mAction;
};

#endif // ECHECKBOX_H
