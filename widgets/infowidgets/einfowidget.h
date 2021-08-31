#ifndef EINFOWIDGET_H
#define EINFOWIDGET_H

#include "../eframedwidget.h"

class eButton;

class eInfoWidget : public eFramedWidget {
public:
    eInfoWidget(eMainWindow* const window);

    void initialize();

    void setCloseAction(const eAction& closeAction);
protected:
    SDL_Rect centralWidgetRect() const;
private:
    eButton* mOk = nullptr;
};

#endif // EINFOWIDGET_H
