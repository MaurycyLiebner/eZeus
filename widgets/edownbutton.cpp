#include "edownbutton.h"

#include "textures/egametextures.h"

eDownButton::eDownButton(eMainWindow* const window) :
    eBasicButton(&eInterfaceTextures::fDownButton, window) {}
