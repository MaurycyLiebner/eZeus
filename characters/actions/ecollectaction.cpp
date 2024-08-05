#include "ecollectaction.h"

#include "engine/egameboard.h"
#include "audio/esounds.h"

#include "textures/emarbletile.h"

#include "engine/eregrowforestaction.h"
#include "enumbers.h"

eCollectAction::eCollectAction(eCharacter* const c,
                               const eTranformFunc tf) :
    eCharacterAction(c, eCharActionType::collectAction),
    mTile(c->tile()), mTransFunc(tf) {}

eCollectAction::eCollectAction(eCharacter* const c) :
    eCollectAction(c, eTranformFunc::none) {}

void transformMarble(eTile* const t, eGameBoard& board) {
    if(t->resource() > 0) return;
    const int l = t->marbleLevel();
    t->setMarbleLevel(l + 1);
    board.restockMarbleTiles();
}

void transformForest(eTile* const t, eGameBoard& brd) {
    t->setTerrain(eTerrain::choppedForest);
    const auto a = new eRegrowForestAction(t);
    brd.planAction(a);
}

void eCollectAction::increment(const int by) {
    mTime += by;
    mSoundTime += sqrt(by);
    const auto c = character();
    const auto cType = c->type();
    if(mSoundTime > 100) {
        mSoundTime = 0;
        auto& board = c->getBoard();
        board.ifVisible(c->tile(), [cType]() {
            if(cType == eCharacterType::marbleMiner) {
                eSounds::playStoneCutterSound();
            } else if(cType == eCharacterType::bronzeMiner) {
                eSounds::playCopperMinerSound();
            } else if(cType == eCharacterType::silverMiner) {
                eSounds::playSilverMinerSound();
            } else if(cType == eCharacterType::lumberjack) {
                eSounds::playTreeCutterSound();
            }
        });
    }
    int period = 10000;
    if(cType == eCharacterType::marbleMiner) {
        period = eNumbers::sMarbleCollectTime;
    } else if(cType == eCharacterType::bronzeMiner) {
        period = eNumbers::sBronzeCollectTime;
    } else if(cType == eCharacterType::silverMiner) {
        period = eNumbers::sSilverCollectTime;
    } else if(cType == eCharacterType::lumberjack) {
        period = eNumbers::sWoodCollectTime;
    } else if(cType == eCharacterType::fishingBoat) {
        period = eNumbers::sFishCollectTime;
    } else if(cType == eCharacterType::urchinGatherer) {
        period = eNumbers::sUrchinCollectTime;
    }
    if(mTime > period) {
        mTile->decResource(1);
        const auto c = character();
        const auto cc = static_cast<eResourceCollectorBase*>(c);
        cc->incCollected(1);
        const bool noResLeft = mTile->resource() <= 0;
        auto& brd = cc->getBoard();
        if(noResLeft) {
            switch(mTransFunc) {
            case eTranformFunc::tree:
                transformForest(mTile, brd);
                break;
            case eTranformFunc::marble:
                transformMarble(mTile, brd);
                break;
            default:
                break;
            }
        }
        mTime = 0;
        setState(eCharacterActionState::finished);
    }
}

void eCollectAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    src >> mSoundTime;
    src >> mTime;
    mTile = src.readTile(board());
    src >> mTransFunc;
}

void eCollectAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst << mSoundTime;
    dst << mTime;
    dst.writeTile(mTile);
    dst << mTransFunc;
}
