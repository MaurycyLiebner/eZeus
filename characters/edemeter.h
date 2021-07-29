#ifndef EDEMETER_H
#define EDEMETER_H

#include "textures/edemetertextures.h"

#include "engine/etile.h"

enum class eDemeterAction {
    walk
};

class eDemeter {
public:
    eDemeter(std::vector<eDemeterTextures>& texs);

    int x() const { return mX; }
    int y() const { return mY; }
    int time() const { return mTime; }
    eDemeterAction action() const { return mAction; }
    eTexture getTexture(const eTileSize size) const;

    void setTile(eTile* const t) { mTile = t; }
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void incTime() { mTime++; }
private:
    eTile* mTile = nullptr;

    double mX = 0;
    double mY = 0;

    int mTime = 0;

    eDemeterAction mAction{eDemeterAction::walk};
    std::vector<eDemeterTextures>& mTextures;
};

#endif // EDEMETER_H
