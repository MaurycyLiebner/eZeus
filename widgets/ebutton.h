#ifndef EBUTTON_H
#define EBUTTON_H

#include "elabel.h"
#include "efonts.h"
#include "etexturecollection.h"

class eButton : public eLabel {
public:
    eButton(eMainWindow* const window);

    void setPressAction(const eAction& a);

    void setHoverTexture(const std::shared_ptr<eTexture>& tex);
    void setPressedTexture(const std::shared_ptr<eTexture>& tex);
    void setDisabledTexture(const std::shared_ptr<eTexture>& tex);

    int lineWidth() const;

    void setEnabled(const bool b);
    bool enabled() const;

    static eButton* sCreate(const eTextureCollection& texs,
                            eMainWindow* const window,
                            eWidget* const buttons = nullptr);
protected:
    void sizeHint(int& w, int& h);
    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseEnterEvent(const eMouseEvent& e);
    bool mouseLeaveEvent(const eMouseEvent& e);

    template <class T>
    static T* sCreateButtonBase(
            const eTextureCollection& texs,
            eMainWindow* const window,
            eWidget* const buttons);
private:
    std::shared_ptr<eTexture> mTexture;
    std::shared_ptr<eTexture> mHoverTexture;
    std::shared_ptr<eTexture> mPressedTexture;
    std::shared_ptr<eTexture> mDisabledTexture;

    eAction mPressAction;

    bool mEnabled = true;
    bool mPressed = false;
    bool mHover = false;
};

template <class T>
T* eButton::sCreateButtonBase(const eTextureCollection& texs,
                              eMainWindow* const window,
                              eWidget* const buttons) {
    const auto b = new T(window);
    b->setTexture(texs.getTexture(0));
    b->setPadding(0);
    b->setHoverTexture(texs.getTexture(1));
    if(texs.size() > 3){
        b->setDisabledTexture(texs.getTexture(3));
    }
    b->fitContent();
    if(buttons) buttons->addWidget(b);
    return b;
}

#endif // EBUTTON_H
