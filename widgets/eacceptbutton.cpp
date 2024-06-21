#include "eacceptbutton.h"

#include "textures/egametextures.h"

eAcceptButton::eAcceptButton(eMainWindow* const window) :
    eBasicButton(&eInterfaceTextures::fAcceptButton, window) {}
