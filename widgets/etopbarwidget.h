#ifndef ETOPBARWIDGET_H
#define ETOPBARWIDGET_H

#include "eframedwidget.h"
#include "elabel.h"

class eGameBoard;
class eButton;

class eTopWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::shared_ptr<eTexture>& icon,
                    const std::string& text) {
        setPadding(0);
        mIcon = new eLabel(window());
        mIcon->setPadding(0);
        mIcon->setTexture(icon);
        mIcon->fitContent();
        mText = new eLabel(window());
        mText->setX(1.5*mIcon->width());
        mText->setPadding(0);
        mText->setSmallFontSize();

        addWidget(mIcon);
        addWidget(mText);

        setText(text);

        mIcon->align(eAlignment::vcenter);
        mText->align(eAlignment::vcenter);
    }

    void setText(const std::string& text) {
        mText->setText(text);
        mText->fitContent();
        fitContent();
    }
private:
    eLabel* mIcon = nullptr;
    eLabel* mText = nullptr;
};

class eTopBarWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();
    void setBoard(eGameBoard* const board);

    void paintEvent(ePainter& p);
private:
    eGameBoard* mBoard = nullptr;
    eTopWidget* mDrachmasWidget = nullptr;
    eTopWidget* mPopulationWidget = nullptr;
    eButton* mDateLabel = nullptr;
    int mTime = 0;
};

#endif // ETOPBARWIDGET_H
