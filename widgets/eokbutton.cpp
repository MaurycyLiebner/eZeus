#include "eokbutton.h"

#include "textures/egametextures.h"

eOkButton::eOkButton(eMainWindow* const window) :
    eBasicButton(&eInterfaceTextures::fOkButton, window) {}
