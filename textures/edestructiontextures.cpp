#include "edestructiontextures.h"

#include "etextureloadinghelpers.h"
#include "etextureloader.h"
#include "offsets/SprAmbient.h"
#include "offsets/destruction.h"

eDestructionTextures::eDestructionTextures(const int tileW, const int tileH,
                                           SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fBlessed(renderer),
    fCursed(renderer),

    fRock(renderer),
    fArrow(renderer),

    fBless(renderer),
    fCurse(renderer) {

}

void eDestructionTextures::load() {
    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();

    std::string basedir{"../ZeusTextures/"};
    basedir += std::to_string(fTileH) + "/";
    {
        std::string dir = basedir + "destruction/";
        const std::string pathBase{dir + "destruction_"};
        eTextureClass texClass(pathBase, texLoader, &eDestructionOffset);

        for(int i = 0; i < 3; i++) {
            fFire.emplace_back(fRenderer);
        }

        for(int i = 37; i < 63; i++) {
            texClass.load(i, fFire[0], false);
        }
        for(int i = 63; i < 89; i++) {
            texClass.load(i, fFire[1], false);
        }
    //    for(int i = 89; i < 115; i++) {
    //        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[2]);
    //    }
        for(int i = 115; i < 133; i++) {
            texClass.load(i, fFire[2], false);
        }
    //    for(int i = 133; i < 157; i++) {
    //        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[4]);
    //    }
    //    for(int i = 1007; i < 1033; i++) {
    //        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[4]);
    //    }

    //    for(int i = 0; i < 2; i++) {
    //        fBigFire.emplace_back(fRenderer);
    //    }

    //    for(int i = 1033; i < 1059; i++) {
    //        eTextureLoadingHelpers::loadTex(pathBase, i, fBigFire[0]);
    //    }
    //    for(int i = 1059; i < 1085; i++) {
    //        eTextureLoadingHelpers::loadTex(pathBase, i, fBigFire[1]);
    //    }

        for(int i = 692; i < 716; i++) {
            texClass.load(i, fCursed);
        }

        for(int i = 716; i < 740; i++) {
            texClass.load(i, fBlessed);
        }

        for(int i = 492; i < 692; i++) {
            texClass.load(i, fBless);
        }

        for(int i = 807; i < 1007; i++) {
            texClass.load(i, fCurse);
        }
    }

    {
        const auto dir = basedir + "SprAmbient/";
        const std::string pathBase{dir + "SprAmbient_"};
        eTextureClass texClass(pathBase, texLoader, &eSprAmbientOffset);

        for(int i = 1490; i < 1492; i++) {
            texClass.load(i, fRock);
        }

        for(int i = 2607; i < 2639; i++) {
            texClass.load(i, fArrow);
        }
    }

    texLoader.waitUntilFinished();
}
