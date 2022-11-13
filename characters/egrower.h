#ifndef EGROWER_H
#define EGROWER_H

#include "echaracter.h"

enum class eGrowerType {
    grapesAndOlives,
    oranges
};

class eCharacterTextures;

class eGrower : public eCharacter {
public:
    eGrower(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setGrowerType(const eGrowerType t) { mType = t; }

    int olives() const { return mOlives; }
    int grapes() const { return mGrapes; }
    int oranges() const { return mOranges; }

    void incGrapes(const int i = 1);
    void incOlives(const int i = 1);
    void incOranges(const int i = 1);
private:
    std::shared_ptr<eTexture> getGrapesAndOlivesTex(
            const eCharacterTextures& texs) const;
    std::shared_ptr<eTexture> getOrangesTex(
            const eCharacterTextures& texs) const;

    eGrowerType mType = eGrowerType::grapesAndOlives;
    int mOlives = 0;
    int mGrapes = 0;
    int mOranges = 0;
};

#endif // EGROWER_H
