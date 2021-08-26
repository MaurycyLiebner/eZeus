#ifndef EACTIONLISTWIDGET_H
#define EACTIONLISTWIDGET_H

#include "eframedwidget.h"

class eActionListWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void addAction(const std::string& text, const eAction& a);
    void setSmallFontSize();
protected:
    void sizeHint2(int& w, int& h);
    void paintEvent(ePainter& p);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
private:
    int yToActionId(const int y) const;
    eAction yToAction(const int y) const;

    int mFontSize = eResolution::largeFontSize(resolution());

    int mHoverId = -1;

    std::vector<eTexture> mTextures;
    std::vector<eAction> mActions;
};

#endif // EACTIONLISTWIDGET_H
