#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include "widgets/ewidget.h"
#include "widgets/eresolution.h"
#include "textures/eterraintextures.h"
#include "textures/egodtextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"
#include "widgets/esettingsmenu.h"

using eSlot = std::function<void()>;

class eGameBoard;
class eGameWidget;
class eWorldWidget;
class eCampaign;

struct eGameWidgetSettings;

class eMainWindow {
public:
    eMainWindow();
    ~eMainWindow();

    bool initialize(const eSettings& settings);
public:

    void setWidget(eWidget* const w);
    eWidget* takeWidget();

    int exec();

    void addSlot(const eSlot& slot);

    int width() const { return resolution().width(); }
    int height() const { return resolution().height(); }
    const eResolution& resolution() const { return mSettings.fRes; }
    SDL_Renderer* renderer() const { return mSdlRenderer; }

    void setResolution(const eResolution& res);
    void setFullscreen(const bool f);

    void startGameAction(eGameBoard* const board,
                         const eGameWidgetSettings& settings);
    void startGameAction(const stdsptr<eCampaign>& c,
                         const eGameWidgetSettings& settings);
    void startGameAction(const eAction& a);
    void episodeFinished();
    void adventureComplete();
    void episodeLost();

    bool saveGame(const std::string& path);
    bool loadGame(const std::string& path);
    void closeGame();

    void showRosterOfLeaders();
    void showMenuLoading();
    void showMainMenu();
    void showSettingsMenu();
    void showChooseGameMenu();
    void showChooseGameEditMenu();
    void showGame(const stdsptr<eCampaign>& c,
                  const eGameWidgetSettings& settings);
    void showGame(eGameBoard* b,
                  const eGameWidgetSettings& settings);
    void showWorld();

    eWidget* currentWidget() const { return mWidget; }
    eWorldWidget* worldWidget() const { return mWW; }

    const eSettings& settings() const { return mSettings; }

    void execDialog(eWidget* const d,
                    const bool closable = true,
                    const eAction& closeFunc = nullptr,
                    eWidget* const parent = nullptr);

    void showEpisodeIntroduction(const stdsptr<eCampaign>& c = nullptr);
    const stdsptr<eCampaign>& campaign() const { return mCampaign; }

    const std::string& leader() const { return mLeader; }
    void setLeader(const std::string& leader) { mLeader = leader; }
    std::string leaderSaveDir() const;
private:
    void clearWidgets();

    eSettings mSettings;

    std::string mLeader;

    bool mQuit = false;

    std::vector<eSlot> mSlots;

    int mShiftPressed = 0;

    stdsptr<eCampaign> mCampaign;
    eGameBoard* mBoard = nullptr;
    eGameWidget* mGW = nullptr;
    eWorldWidget* mWW = nullptr;

    eWidget* mWidget = nullptr;
    SDL_Window* mSdlWindow = nullptr;
    SDL_Renderer* mSdlRenderer = nullptr;
};

#endif // EMAINWINDOW_H
