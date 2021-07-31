#ifndef EGYMNAST_H
#define EGYMNAST_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

enum class eGymnastAction {
    walk, die
};

class eGymnast : public eCharacter {
public:
    eGymnast(std::vector<eCharacterTextures>& tex);

    eGymnastAction action() const { return mAction; }
    void setAction(const eGymnastAction a);

    eTexture getTexture(const eTileSize size) const;
private:
    int mActionStartTime = 0;
    eGymnastAction mAction{eGymnastAction::walk};

    std::vector<eCharacterTextures>& mTextures;
};

#endif // EGYMNAST_H