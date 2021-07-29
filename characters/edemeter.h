#ifndef EDEMETER_H
#define EDEMETER_H

#include "textures/edemetertextures.h"
#include "engine/eorientation.h"
#include "engine/etile.h"
#include "characters/echaracteraction.h"

enum class eDemeterAction {
    walk
};

class eDemeter {
public:
    eDemeter(std::vector<eDemeterTextures>& texs);

    double x() const { return mX; }
    double y() const { return mY; }
    eTile* tile() const { return mTile; }
    int time() const { return mTime; }
    eDemeterAction action() const { return mAction; }
    eOrientation orientation() const { return mOrientation; }

    eTexture getTexture(const eTileSize size) const;

    void setTile(eTile* const t);
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void incTime();
    void setOrientation(const eOrientation o);
    void setCharAction(eCharacterAction* const a);
private:
    eTile* mTile = nullptr;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0;
    double mY = 0;

    int mTime = 0;

    eCharacterAction* mCharAction = nullptr;
    eDemeterAction mAction{eDemeterAction::walk};

    std::vector<eDemeterTextures>& mTextures;
};

#endif // EDEMETER_H
