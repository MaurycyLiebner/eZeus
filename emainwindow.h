#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"

using eSlot = std::function<void()>;

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const int width, const int height);

    void setWidget(eWidget* const w);

    int exec();

    static void addSlot(const eSlot& slot);
    static eMainWindow* instance();
private:
    void addSlotImpl(const eSlot& slot);

    int mWidth = 0;
    int mHeight = 0;

    static eMainWindow* sInstance;

    std::vector<eSlot> mSlots;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer;
};

#endif // EMAINWINDOW_H
