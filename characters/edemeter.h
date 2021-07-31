#ifndef EDEMETER_H
#define EDEMETER_H

#include "textures/edemetertextures.h"
#include "echaracter.h"

enum class eDemeterAction {
    walk
};

class eDemeter : public eCharacter {
public:
    eDemeter(std::vector<eDemeterTextures>& texs);

    eDemeterAction action() const { return mAction; }

    eTexture getTexture(const eTileSize size) const;
private:
    eDemeterAction mAction{eDemeterAction::walk};

    std::vector<eDemeterTextures>& mTextures;
};

#endif // EDEMETER_H
