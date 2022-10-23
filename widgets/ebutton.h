#ifndef EBUTTON_H
#define EBUTTON_H

#include "ebuttonbase.h"

#include "efonts.h"
#include "etexturecollection.h"

class eButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void setHoverTexture(const std::shared_ptr<eTexture>& tex);
    void setPressedTexture(const std::shared_ptr<eTexture>& tex);
    void setDisabledTexture(const std::shared_ptr<eTexture>& tex);

    static eButton* sCreate(const eTextureCollection& texs,
                            eMainWindow* const window,
                            eWidget* const buttons = nullptr);

    void setUnderline(const bool u) { mUnderline = u; }
protected:
    void sizeHint(int& w, int& h);
    void paintEvent(ePainter& p);

    template <class T>
    static T* sCreateButtonBase(
            const eTextureCollection& texs,
            eMainWindow* const window,
            eWidget* const buttons);
private:
    std::shared_ptr<eTexture> mHoverTexture;
    std::shared_ptr<eTexture> mPressedTexture;
    std::shared_ptr<eTexture> mDisabledTexture;

    bool mUnderline = true;
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
