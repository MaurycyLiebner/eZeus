﻿#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include <deque>

#include "ewidget.h"
#include "eframedlabel.h"

#include "engine/etile.h"

#include "textures/eterraintextures.h"
#include "textures/ebuildingtextures.h"

#include "buildings/epatrolbuilding.h"

#include "widgets/egamemenu.h"
#include "widgets/earmymenu.h"
#include "egamemainmenu.h"
#include "etopbarwidget.h"

#include "eviewmode.h"
#include "emessage.h"
#include "echeckbox.h"

#include "engine/eeventdata.h"

class eTerrainEditMenu;
class eDomesticatedAnimal;
struct eSanctBlueprint;
class eWorldWidget;
struct eGodMessages;
struct eHeroMessages;
class eMessageBox;
class eGameBoard;
class eAgoraBase;
class eInfoWidget;
enum class eAgoraOrientation;
enum class eGodType;
enum class eHeroType;
enum class eGodQuestId;
enum class eWorldDirection;

using eBuildingCreator = std::function<stdsptr<eBuilding>()>;

struct eSavedMessage {
    eEventData fEd;
    eMessage fMsg;
};

struct eGameWidgetSettings {
    bool fPaused = false;
    int fSpeedId = 1;
    int fSpeed = 10;
    int fDX = 0;
    int fDY = 0;
    eTileSize fTileSize = eTileSize::s30;
    eWorldDirection fDir = eWorldDirection::N;

    void read(eReadStream& src) {
        src >> fPaused;
        src >> fSpeedId;
        src >> fSpeed;
        src >> fDX;
        src >> fDY;
        src >> fTileSize;
        src >> fDir;
    }

    void write(eWriteStream& dst) const {
        dst << fPaused;
        dst << fSpeedId;
        dst << fSpeed;
        dst << fDX;
        dst << fDY;
        dst << fTileSize;
        dst << fDir;
    }
};

class eGameWidget : public eWidget {
public:
    eGameWidget(eMainWindow* const window);
    ~eGameWidget();

    void initialize();

    void pixToId(const int pixX, const int pixY,
                 int& idX, int& idY) const;

    void setViewMode(const eViewMode m);
    eViewMode viewMode() const { return mViewMode; }

    void viewFraction(const double fx, const double fy);
    void viewTile(eTile* const tile);
    eTile* viewedTile() const;
    bool tileVisible(eTile* const tile) const;

    void setBoard(eGameBoard* const board);

    eGameWidgetSettings settings() const;
    void setSettings(const eGameWidgetSettings& s);

    void updateRequestButtons();
    void showTip(const std::string& tip);
    void showQuestion(const std::string& title,
                      const std::string& q,
                      const eAction& action);

    void updateViewBoxSize();
    void updateTopBottomAltitude();
    void updateMinMaxAltitude();
    void updateMaps();

    void setWorldDirection(const eWorldDirection dir);

    void openDialog(eWidget* const d);
protected:
    void paintEvent(ePainter& p) override;

    bool keyPressEvent(const eKeyPressEvent& e) override;
    bool mousePressEvent(const eMouseEvent& e) override;
    bool mouseMoveEvent(const eMouseEvent& e) override;
    bool mouseReleaseEvent(const eMouseEvent& e) override;
    bool mouseWheelEvent(const eMouseWheelEvent& e) override;
private:
    void renderTargetsReset() override;
    void initializeNumbers();

    void drawXY(int tx, int ty,
                double& rx, double& ry,
                const int wSpan, const int hSpan,
                const int a);

    void showGoals();

    void setDX(const int dx);
    void setDY(const int dy);
    void clampViewBox();

    using eApply = std::function<void(eTile* const)>;
    eApply editFunc();
    bool buildMouseRelease();

    using eTileAction = std::function<void(eTile* const)>;
    void iterateOverVisibleTiles(const eTileAction& a);

    void setTileSize(const eTileSize size);

    void actionOnSelectedTiles(const eTileAction& apply);

    using eSpecialRequirement = std::function<bool(eTile*)>;
    bool canBuildBase(const int minX, const int maxX,
                      const int minY, const int maxY,
                      const bool fertile = false,
                      const bool flat = false) const;
    bool canBuild(const int tx, const int ty,
                  const int sw, const int sh,
                  const bool fertile = false,
                  const bool flat = false) const;
    bool canBuildVendor(const int tx, const int ty,
                        const eResourceType resType) const;
    bool canBuildFishery(const int tx, const int ty,
                         eOrientation& o) const;
    bool canBuildPier(const int tx, const int ty,
                      eOrientation& o) const;

    bool build(const int tx, const int ty,
               const int sw, const int sh,
               const eBuildingCreator& bc,
               const bool fertile = false,
               const bool flat = false);
    using eDA = eCharacter;
    using eAnimalCreator = std::function<stdsptr<eDA>(eGameBoard&)>;
    void buildAnimal(eTile* const tile,
                     const eBuildingType type,
                     const eAnimalCreator& creator);

    std::vector<eTile*> agoraBuildPlaceBR(eTile* const tile) const;
    std::vector<eTile*> agoraBuildPlaceTL(eTile* const tile) const;
    std::vector<eTile*> agoraBuildPlaceBL(eTile* const tile) const;
    std::vector<eTile*> agoraBuildPlaceTR(eTile* const tile) const;
    std::vector<eTile*> agoraBuildPlaceIter(
            eTile* const tile, const bool grand,
            eAgoraOrientation& bt) const;

    std::vector<ePatrolGuide>::iterator
        findGuide(const int tx, const int ty);

    void handleEvent(const eEvent e, eEventData& ed);
    void handleGodQuestEvent(eEventData& ed,
                             const bool fulfilled);
    void handleGodVisitEvent(eEventData& ed);
    void handleGodInvasionEvent(eEventData& ed);
    void handleGodHelpEvent(eEventData& ed);
    void handleSanctuaryComplete(const eGodType god);
    void handleMonsterUnleashEvent(eEventData& ed);
    void handleMonsterInvasion36Event(eEventData& ed);
    void handleMonsterInvasion24Event(eEventData& ed);
    void handleMonsterInvasion12Event(eEventData& ed);
    void handleMonsterInvasion6Event(eEventData& ed);
    void handleMonsterInvasion1Event(eEventData& ed);
    void handleMonsterInvasionEvent(eEventData& ed);
    void handleMonsterSlainEvent(eEventData& ed);
    void handleHeroArrivalEvent(eEventData& ed);

    void mapDimensions(int& mdx, int& mdy) const;
    void viewBoxSize(double& fx, double& fy) const;
    void viewedFraction(double& fx, double& fy) const;
    void tileViewFraction(eTile* const tile,
                          double& xf, double& yf) const;

    void updateMinimap();

    int waterParkId() const;

    void showMessage(eEventData& ed, const eMessage& msg,
                     const bool prepend = false);
    void showMessage(eEventData& ed, const eMessageType& msg,
                     const bool prepend = false);

    void updateTipPositions();

    bool roadPath(std::vector<eOrientation>& path);
    bool columnPath(std::vector<eOrientation>& path);
    bool bridgeTiles(eTile* const t, const eTerrain terr,
                     std::vector<eTile*>& tiles,
                     bool& rotated);
    bool canBuildAvenue(eTile* const t) const;

    bool inErase(const int tx, const int ty);
    bool inErase(const SDL_Rect& rect);
    bool inErase(eAgoraBase* const a);
    bool inErase(eBuilding* const b);

    bool inPatrolBuildingHover(eBuilding* const b);

    void setArmyMenuVisible(const bool v);

    void updateTerrainTextures(eTile* const tile,
                               const eTerrainTextures& trrTexs,
                               const eBuildingTextures& builTexs);
    void updateTerrainTextures();

    void updatePatrolPath();
    void setPatrolBuilding(ePatrolBuildingBase* const pb);

    eInfoWidget* openInfoWidget(eBuilding* const b);

    void switchPause();

    stdsptr<eTexture> getBasementTexture(
            const int tx, const int ty, eBuilding* const d,
            const eTerrainTextures& trrTexs, const eWorldDirection dir,
            const int boardw, const int boardh);

    std::vector<eTile*> selectedTiles() const;

    eMouseButton mPressedButtons = eMouseButton::none;

    bool mEditorMode = false;

    bool mRotate = false;
    int mRotateId = 0;

    const int sSpeeds[5] = {2, 10, 25, 50, 100};

    bool mPaused = false;
    bool mLocked = false;
    int mFrame{0};
    int mTime{0};
    int mSpeedId = 1;
    int mSpeed = sSpeeds[mSpeedId];

    int mWheel = 0;

    int mMinAltitude = 0;
    int mMaxAltitude = 0;

    int mTopMinAltitude = 0;
    int mBottomMaxAltitude = 0;

    int mDX = 0;
    int mDY = 0;

    bool mLeftPressed = false;
    bool mMovedSincePress = false;

    int mHoverX = -1;
    int mHoverY = -1;
    int mHoverTX = -1;
    int mHoverTY = -1;
    int mPressedX = -1;
    int mPressedY = -1;
    int mPressedTX = -1;
    int mPressedTY = -1;
    int mLastX = -1;
    int mLastY = -1;

    eViewMode mViewMode = eViewMode::defaultView;

    eTileSize mTileSize = eTileSize::s30;
    int mTileW = 60;
    int mTileH = 30;

    int mUpdateRect = 0;
    std::vector<SDL_Rect> mUpdateRects;
    stdptr<eGameBoard> mBoard;

    bool mDrawElevation = true;
    stdptr<ePatrolBuildingBase> mPatrolBuilding;
    std::vector<eTile*> mPatrolPath;
    std::vector<eTile*> mExcessPatrolPath;
    std::vector<eTile*> mPatrolPath1;
    std::vector<eTile*> mExcessPatrolPath1;
    eWidget* mPatrolPathWid = nullptr;
    std::vector<ePatrolGuide> mSavedGuides;

    eFramedLabel* mPausedLabel = nullptr;

    eTopBarWidget* mTopBar = nullptr;
    eInfoWidget* mInfoWidget = nullptr;
    eMessageBox* mMsgBox = nullptr;
    std::deque<eSavedMessage> mSavedMsgs;
    eTerrainEditMenu* mTem = nullptr;
    eGameMenu* mGm = nullptr;
    eArmyMenu* mAm = nullptr;

    eWorldWidget* mWW = nullptr;

    struct eTip {
        std::string fText;
        eWidget* fWid = nullptr;
        int fLastFrame = 0;
    };

    std::deque<eTip> mTips;

    std::map<eTileSize, std::vector<stdsptr<eTexture>>> mNumbers;
    std::vector<eTile*> mInflTiles;
    std::vector<eTile*> mHoverTiles;
};

#endif // EGAMEWIDGET_H
