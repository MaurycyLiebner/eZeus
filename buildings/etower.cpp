#include "etower.h"

#include "textures/egametextures.h"

#include "characters/actions/earcheraction.h"
#include "vec2.h"
#include "missiles/earrowmissile.h"
#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"
#include "audio/esounds.h"

eTower::eTower(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::tower, 2, 2, 15) {
    eGameTextures::loadGatehouseAndTower();
    setHP(5000);
}

eTower::~eTower() {
    if(mArcher) mArcher->kill();
}

std::shared_ptr<eTexture>
eTower::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].fTower;
}

std::vector<eOverlay>
eTower::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::characters()[sizeId];
    const eArcherTextures* aTexs;
    auto& board = getBoard();
    if(board.poseidonMode()) {
        eGameTextures::loadPoseidonTowerArcher();
        aTexs = &texs.fPoseidonTowerArcher;
    } else {
        eGameTextures::loadArcher();
        aTexs = &texs.fArcher;
    }
    if(mAttack) {
        const int oid = static_cast<int>(mAttackOrientation);
        const auto& coll = &aTexs->fFight[oid];
        const int t = time()/20;
        const int texId = t % coll->size();
        eOverlay o;
        o.fTex = coll->getTexture(texId);
        o.fX = -3.5;
        o.fY = -5.5;
        return {o};
    } else {
        const auto& colls = aTexs->fPatrol;
        const int tt = textureTime();
        const int idid = tt/50 % 8;
        const int ids[8] = {5, 0, 3, 7, 4, 2, 6, 1};
        const int id = ids[idid];
        const auto& coll = colls[id];
        eOverlay o;
        o.fTex = coll.getTexture(tt % coll.size());
        o.fX = -3.5;
        o.fY = -5.5;
        return {o};
    }
}

void eTower::timeChanged(const int by) {
    const int waitTime = 5000;
    if(enabled()) {
        if(!mArcher) {
            mSpawnTime += by;
            if(mSpawnTime > waitTime) {
                spawn();
                mSpawnTime = 0;
            }
        }

        const int rangeAttackCheck = 500;
        const int missileCheck = 200;
        const int range = 8;
        const double attack = 0.5;

        const auto ct = centerTile();
        const int tx = ct->x();
        const int ty = ct->y();
        const vec2d cpos{1.*tx, 1.*ty};
        const int pid = playerId();
        auto& brd = getBoard();

        if(mAttack) {
            if(range > 0 && mAttackTarget) {
                mMissile += by;
                if(mMissile > missileCheck) {
                    mMissile = mMissile - missileCheck;
                    const auto tt = mAttackTarget->tile();
                    const int ttx = tt->x();
                    const int tty = tt->y();
                    eMissile::sCreate<eArrowMissile>(brd, tx, ty, 3.5,
                                                     ttx, tty, 0.5, 2);
                    auto& board = getBoard();
                    board.ifVisible(centerTile(), [&]() {
                        eSounds::playAttackSound(eCharacterType::archer);
                    });
                }
            }
            mAttackTime += by;
            bool finishAttack = !mAttackTarget ||
                                mAttackTarget->dead() ||
                                mAttackTime > 1000;
            if(mAttackTarget && !mAttackTarget->dead()) {
                const double att = by*attack;
                const bool d = mAttackTarget->defend(att);
                if(d) finishAttack = true;
            }
            if(finishAttack) {
                mAttack = false;
                mAttackTarget = nullptr;
                mAttackTime = 0;
                mRangeAttack = rangeAttackCheck;
            } else {
                return;
            }
        }

        mRangeAttack += by;
        if(mRangeAttack > rangeAttackCheck) {
            mRangeAttack = mRangeAttack - rangeAttackCheck;
            for(int i = -range; i <= range; i++) {
                for(int j = -range; j <= range; j++) {
                    const auto t = brd.tile(tx + i, ty + j);
                    if(!t) continue;
                    const auto& chars = t->characters();
                    for(const auto& cc : chars) {
                        if(!cc->isSoldier()) continue;
                        if(cc->playerId() == pid) continue;
                        if(cc->dead()) continue;
                        const vec2d ccpos{cc->absX(), cc->absY()};
                        const vec2d posdif = ccpos - cpos;
                        mAttackTarget = cc;
                        mAttack = true;
                        mAttackTime = 0;
                        const double angle = posdif.angle();
                        const auto o = sAngleOrientation(angle);
                        mAttackOrientation = o;

                        const auto tt = cc->tile();
                        const int ttx = tt->x();
                        const int tty = tt->y();
                        for(int ii = -2; ii <= 2; ii++) {
                            for(int jj = -2; jj <= 2; jj++) {
                                const auto tt = brd.tile(ttx + ii, tty + jj);
                                if(!tt) continue;
                                const auto& ccchars = tt->characters();
                                for(const auto& ccc : ccchars) {
                                    if(!ccc->isSoldier()) continue;
                                    if(ccc->playerId() == pid) continue;
                                    if(ccc->dead()) continue;

                                    const auto sss = static_cast<eSoldier*>(ccc.get());
                                    const auto aaa = sss->soldierAction();
                                    if(aaa) aaa->beingAttacked(tx, ty);
                                }
                            }
                        }

                        return;
                    }
                }
            }
        }
    }
    eEmployingBuilding::timeChanged(by);
}

void eTower::read(eReadStream& src) {
    eEmployingBuilding::read(src);
    src >> mMissile;
    src >> mRangeAttack;
    src >> mAttackTime;
    src >> mAttack;
    src >> mAttackOrientation;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mAttackTarget = c;
    });
    src >> mSpawnTime;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mArcher = static_cast<eArcher*>(c);
    });
}

void eTower::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);
    dst << mMissile;
    dst << mRangeAttack;
    dst << mAttackTime;
    dst << mAttack;
    dst << mAttackOrientation;
    dst.writeCharacter(mAttackTarget);
    dst << mSpawnTime;
    dst.writeCharacter(mArcher);
}

bool eTower::spawn() {
    const auto archer = e::make_shared<eArcher>(getBoard());
    archer->changeTile(centerTile());
    const auto a = e::make_shared<eArcherAction>(archer.get());
    archer->setAction(a);
    mArcher = archer;
    return true;
}

