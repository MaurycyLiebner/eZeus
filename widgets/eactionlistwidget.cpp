#include "eactionlistwidget.h"

#include "eflatbutton.h"

class eStateCheckingFlatButton : public eFlatButton {
public:
    using eFlatButton::eFlatButton;

    using eStateChecker = std::function<bool()>;
    void initialize(const std::string& text,
                    const eAction& a,
                    const eStateChecker& stateChecker) {
        int iRes;
        int mult;
        iResAndMult(iRes, mult);

        const int width = 64*mult;

        setWidth(width);
        setHeight(10*mult);

        setNoPadding();
        setTinyFontSize();
        setText(text);
        setPressAction(a);

        mStateChecker = stateChecker;
    }
protected:
    void paintEvent(ePainter& p) {
        eFlatButton::paintEvent(p);
        mUpdateCounter++;
        if(mUpdateCounter >= 10) {
            mUpdateCounter = 0;
            if(mStateChecker) {
                const bool r = mStateChecker();
                if(r) {
                    setLightFontColor();
                } else {
                    setYellowFontColor();
                }
            }
        }
    }
private:
    int mUpdateCounter = 0;
    eStateChecker mStateChecker = nullptr;
};

void eActionListWidget::addAction(const std::string& text,
                                  const eAction& a,
                                  const eStateChecker& stateChecker) {
    const auto b = new eStateCheckingFlatButton(window());
    b->initialize(text, a, stateChecker);
    addWidget(b);
}
