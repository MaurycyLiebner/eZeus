#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"
#include "widgets/eresolution.h"

using eSlot = std::function<void()>;

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const eRes& res);
public:

    void setWidget(eWidget* const w);

    int exec();

    static void addSlot(const eSlot& slot);
    static eMainWindow* instance();

    int width() const { return eResolution::width(mResolution); }
    int height() const { return eResolution::height(mResolution); }
    eRes resolution() const { return mResolution; }
    SDL_Renderer* renderer() const { return mSdlRenderer; }
private:
    void addSlotImpl(const eSlot& slot);

    void setResolution(const eRes res);
    void setFullscreen(const bool f);

    void showMainMenu();
    void showSettingsMenu();

    bool mFullscreen = false;
    eRes mResolution;

    static eMainWindow* sInstance;

    bool mQuit = false;

    std::vector<eSlot> mSlots;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer;
};

#endif // EMAINWINDOW_H
