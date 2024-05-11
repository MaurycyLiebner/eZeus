#ifndef EKILLCHARACTERFINISHFAIL_H
#define EKILLCHARACTERFINISHFAIL_H

#include "echaracteractionfunction.h"

#include "characters/echaracter.h"

class eKillCharacterFinishFail : public eCharActFunc {
public:
    eKillCharacterFinishFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::killCharacterFinishFail) {}
    eKillCharacterFinishFail(eGameBoard& board, eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::killCharacterFinishFail),
        mCptr(c) {}

    void call();

    void read(eReadStream& src) {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = static_cast<eCharacter*>(c);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacter(mCptr);
    }
private:
    stdptr<eCharacter> mCptr;
};

#endif // EKILLCHARACTERFINISHFAIL_H
