#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"
#include "widgets/eresolution.h"

using eSlot = std::function<void()>;

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const eResolution& res);
public:

    void setWidget(eWidget* const w);

    int exec();

    static void addSlot(const eSlot& slot);
    static eMainWindow* instance();

    int width() const { return mResolution.width(); }
    int height() const { return mResolution.height(); }
private:
    void addSlotImpl(const eSlot& slot);

    void showMainMenu();
    void showSettingsMenu();

    eResolution mResolution;

    static eMainWindow* sInstance;

    bool mQuit = false;

    std::vector<eSlot> mSlots;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer;
};

#endif // EMAINWINDOW_H
