#include "ekillcharacterfinishfail.h"

void eKillCharacterFinishFail::call() {
    if(!mCptr) return;
    mCptr->kill();
}
