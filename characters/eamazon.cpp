#include "eamazon.h"

#include "textures/egametextures.h"

eAmazon::eAmazon(eGameBoard& board) :
    eSoldier(board, nullptr, eCharacterType::amazon) {
    setIsArcher(false);
}

void eAmazon::setIsArcher(const bool a) {
    mIsArcher = a;
    if(a) {
        eGameTextures::loadAmazonArcher();
        setCharTexs(&eCharacterTextures::fAmazonArcher);
    } else {
        eGameTextures::loadAmazonSpear();
        setCharTexs(&eCharacterTextures::fAmazonSpear);
    }
}

void eAmazon::read(eReadStream& src) {
    eSoldier::read(src);
    bool archer;
    src >> archer;
    setIsArcher(archer);
}

void eAmazon::write(eWriteStream& dst) const {
    eSoldier::write(dst);
    dst << mIsArcher;
}

