#ifndef EBASICBUTTON_H
#define EBASICBUTTON_H

#include "ebutton.h"

#include "textures/egametextures.h"

class eBasicButton : public eButton {
public:
    using eTex = eTextureCollection eInterfaceTextures::*;
    eBasicButton(const eTex tex,
                 eMainWindow* const window);
};

#endif // EBASICBUTTON_H
