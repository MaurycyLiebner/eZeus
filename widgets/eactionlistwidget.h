#ifndef EACTIONLISTWIDGET_H
#define EACTIONLISTWIDGET_H

#include "eframedwidget.h"

class eActionListWidget;

class eActionInstance {
public:
    eActionInstance(eActionListWidget* const parent,
                    const eAction& a);

    int width() const;
    int height() const;

    void addText(const int margin, const std::string& text);
    void addTexture(const int margin, const eTexture& tex);

    const eAction& action() const;

    void draw(ePainter& p, const SDL_Rect& rect) const;
private:
    eActionListWidget* const mParent;
    const eAction mAction;
    std::vector<eTexture> mTextures;
    std::vector<int> mMargins;
};

class eActionListWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    eTexture textToTexture(const std::string& text);
    eActionInstance& addAction(const std::string& text, const eAction& a);
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

    std::vector<eActionInstance> mActions;
};

#endif // EACTIONLISTWIDGET_H
