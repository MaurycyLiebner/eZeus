#ifndef EBUTTONBASE_H
#define EBUTTONBASE_H

#include "elabel.h"

class eButtonBase : public eLabel {
public:
    using eLabel::eLabel;

    void setPressAction(const eAction& a);
    void setMouseEnterAction(const eAction& a);
    void setMouseLeaveAction(const eAction& a);

    void setEnabled(const bool b);
    bool enabled() const;

    bool pressed() const;
    bool hovered() const;
protected:
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);
private:
    eAction mPressAction;
    eAction mEnterAction;
    eAction mLeaveAction;

    bool mEnabled = true;
    bool mPressed = false;
    bool mHover = false;
};

#endif // EBUTTONBASE_H
