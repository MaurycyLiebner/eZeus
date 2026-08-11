#include "ehippodrome.h"

#include "characters/eracinghorse.h"

eHippodrome::eHippodrome(const eCityId cid, eGameBoard& board) :
    mCid(cid), mBoard(board) {}

void eHippodrome::nextMonth() {
    const int d = drachmasPerMonth();
    if(d <= 0) return;
    const auto pid = mBoard.cityIdToPlayerId(mCid);
    mBoard.incDrachmas(pid, d, eFinanceTarget::hippodrome);
    purgeHorses();
    const bool r = racing();
    if(!r) spawnHorses();
}

void eHippodrome::addPieces(eHippodromePiece * const start) {
    mPieces.clear();
    mFinish = -1;
    auto current = addPiece(eN{start, eDiagonalOrientation::topRight});
    eHippodromePiece* prev = nullptr;
    while(current) {
        if(mFinish == -1 && current->fPtr->id() == 5) {
            mFinish = mPieces.size() - 1;
        }
        const auto ns = current->fPtr->neighbours();
        if(ns.empty()) break;
        if(prev && ns.size() == 1) break;
        for(const auto& n : ns) {
            if(n.fPtr == prev) continue;
            current->fO = n.fO;
            if(n.fPtr == start) {
                current = nullptr;
                break;
            }
            prev = current->fPtr;
            current = addPiece(n);
            break;
        }
    }
    updatePaths();
}

bool eHippodrome::closed() const {
    if(mPieces.size() < 4) return false;
    const auto first = mPieces.front().fPtr;
    const auto last = mPieces.back().fPtr;
    const auto ns = last->neighbours();
    for(const auto& n : ns) {
        if(n.fPtr == first) return true;
    }
    return false;
}

void eHippodrome::clear() {
    for(const auto p : mPieces) {
        p.fPtr->setHippodrome(nullptr);
    }
    mPieces.clear();
    for(const auto& h : mHorses) {
        if(!h) continue;
        h->destroy();
    }
    mHorses.clear();
}

void eHippodrome::spawnHorses() {
    for(int i = 0; i < mNHorses;) {
        for(int j = 0; j < 2 && i < mNHorses; j++, i++) {
            const auto h = e::make_shared<eRacingHorse>(
                mBoard, i, j == 0 ? mPath1 : mPath2);
            h->incTime((i/2)*50);
            h->setSpeed(0.5 + i*0.05);
            mHorses.push_back(h.get());
        }
    }
}

void eHippodrome::addHorses(const int h) {
    mNHorses += h;
}

int eHippodrome::neededHorses() const {
    const bool c = closed();
    if(!c) return 0;
    const int l = length();
    if(l < 23) return 4;
    else if(l < 59) return 8;
    else if(l < 199) return 12;
    else return 24;
}

int eHippodrome::drachmasPerMonth() const {
    const bool w = working();
    if(!w) return 0;
    const int l = length();
    if(l < 11) return 10;
    else if(l < 23) return 20;
    else if(l < 35) return 40;
    else if(l < 59) return 60;
    else if(l < 99) return 100;
    else if(l < 199) return 200;
    else return 500;
}

bool eHippodrome::working() const {
    const bool c = closed();
    if(!c) return false;
    const int needed = neededHorses();
    return mNHorses >= needed;
}

bool eHippodrome::racing() const {
    for(const auto& h : mHorses) {
        if(h) return true;
    }
    return false;
}

int eHippodrome::length() const {
    return mPieces.size();
}

void eHippodrome::setCart(eCartTransporter* const c) {
    mCart = c;
}

void eHippodrome::nextCleaningPartId() {
    const int l = length();
    if(l == 0) return;
    mCleaningPartId = (mCleaningPartId + 1) % l;
}

void eHippodrome::write(eWriteStream& dst) const {
    dst << mFinish;
    dst << mNHorses;
    dst.writeCharacter(mCart);
    dst << mPieces.size();
    for(const auto& p : mPieces) {
        dst << p.fO;
        dst.writeBuilding(p.fPtr);
    }
}

void eHippodrome::read(eReadStream& src) {
    src >> mFinish;
    src >> mNHorses;
    src.readCharacter(&mBoard, [this](eCharacter* const c) {
        mCart = static_cast<eCartTransporter*>(c);
    });
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        auto& p = mPieces.emplace_back();
        src >> p.fO;
        src.readBuilding(&mBoard, [this, i](eBuilding* const b) {
            const auto hp = static_cast<eHippodromePiece*>(b);
            mPieces[i].fPtr = hp;
            hp->setHippodrome(this);
            hp->setPartId(i);
        });
    }
    src.addPostFunc([this]() {
        updatePaths();
    });
}

eHippodrome::eN* eHippodrome::addPiece(const eN& n) {
    const auto current = &mPieces.emplace_back(n);
    const auto ptr = current->fPtr;
    ptr->setHippodrome(this);
    ptr->setPartId(mPieces.size() - 1);
    return current;
}

void eHippodrome::purgeHorses() {
    for(int i = 0; i < (int)mHorses.size(); i++) {
        const auto h = mHorses[i];
        if(h) continue;
        mHorses.erase(mHorses.begin() + i);
        i--;
    }
}

void eHippodrome::updatePaths() {
    mPath1.clear();
    mPath2.clear();
    const bool c = closed();
    if(!c) return;
    int i = mFinish;
    const eN* start = &mPieces[i];
    const eN* current = start;
    const auto next = [&]() {
        i++;
        if(i >= (int)mPieces.size()) {
            i = 0;
        }
        current = &mPieces[i];
    };

    const auto& r = current->fPtr->tileRect();
    mPath1.push_back(ePathPoint{r.x + 1., (double)r.y, 0.});
    mPath2.push_back(ePathPoint{r.x + 2., (double)r.y, 0.});
    while(current) {
        const auto ptr = current->fPtr;
        ptr->progressPath(mPath1);
        ptr->progressPath(mPath2);
        next();
        if(current == start) break;
    }
}
