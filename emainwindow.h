#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"
#include "widgets/eresolution.h"
#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"

using eSlot = std::function<void()>;

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const eRes& res);
public:

    void setWidget(eWidget* const w);

    int exec();

    void addSlot(const eSlot& slot);

    int width() const { return eResolution::width(mResolution); }
    int height() const { return eResolution::height(mResolution); }
    eRes resolution() const { return mResolution; }
    SDL_Renderer* renderer() const { return mSdlRenderer; }
private:
    void setResolution(const eRes res);
    void setFullscreen(const bool f);

    void showMainMenu();
    void showSettingsMenu();
    void showGame();

    bool mFullscreen = false;
    eRes mResolution;

    bool mQuit = false;

    std::vector<eSlot> mSlots;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer = nullptr;
};

#endif // EMAINWINDOW_H
