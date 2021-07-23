#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const int width, const int height);

    void setWidget(eWidget* const w);

    int exec();
private:
    int mWidth = 0;
    int mHeight = 0;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer;
};

#endif // EMAINWINDOW_H
