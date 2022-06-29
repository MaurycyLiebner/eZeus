#include "ecancelbutton.h"

#include "textures/egametextures.h"

eCancelButton::eCancelButton(eMainWindow* const window) :
    eBasicButton(&eInterfaceTextures::fCancelButton, window) {}
