#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/zeus_hydra.h"
#include "offsets/zeus_kraken.h"
#include "offsets/zeus_maenads.h"
#include "offsets/zeus_medusa.h"
#include "offsets/zeus_minotaur.h"
#include "offsets/zeus_scylla.h"
#include "offsets/Poseidon_Sphinx.h"
#include "offsets/zeus_talos.h"

#include "spriteData/hydra15.h"
#include "spriteData/hydra30.h"
#include "spriteData/hydra45.h"
#include "spriteData/hydra60.h"

#include "spriteData/kraken15.h"
#include "spriteData/kraken30.h"
#include "spriteData/kraken45.h"
#include "spriteData/kraken60.h"

#include "spriteData/maenads15.h"
#include "spriteData/maenads30.h"
#include "spriteData/maenads45.h"
#include "spriteData/maenads60.h"

#include "spriteData/medusa15.h"
#include "spriteData/medusa30.h"
#include "spriteData/medusa45.h"
#include "spriteData/medusa60.h"

#include "spriteData/minotaur15.h"
#include "spriteData/minotaur30.h"
#include "spriteData/minotaur45.h"
#include "spriteData/minotaur60.h"

#include "spriteData/scylla15.h"
#include "spriteData/scylla30.h"
#include "spriteData/scylla45.h"
#include "spriteData/scylla60.h"

#include "spriteData/sphinx15.h"
#include "spriteData/sphinx30.h"
#include "spriteData/sphinx45.h"
#include "spriteData/sphinx60.h"

#include "spriteData/talos15.h"
#include "spriteData/talos30.h"
#include "spriteData/talos45.h"
#include "spriteData/talos60.h"

void eCharacterTextures::loadHydra() {
    if(fHydraLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHydraSpriteData15,
                                 eHydraSpriteData30,
                                 eHydraSpriteData45,
                                 eHydraSpriteData60);
    fHydraLoaded = true;
    eSpriteLoader loader(fTileH, "hydra", sds,
                         &eZeus_hydraOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fHydra.fWalk);
    loader.loadSkipFlipped(1, 121, 289, fHydra.fDie);
    loader.loadSkipFlipped(1, 289, 473, fHydra.fFight);
    loader.loadSkipFlipped(1, 473, 609, fHydra.fFight2);
}

void eCharacterTextures::loadKraken() {
    if(fKrakenLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eKrakenSpriteData15,
                                 eKrakenSpriteData30,
                                 eKrakenSpriteData45,
                                 eKrakenSpriteData60);
    fKrakenLoaded = true;
    eSpriteLoader loader(fTileH, "kraken", sds,
                         &eZeus_krakenOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 169, fKraken.fWalk);
    for(int i = 169; i < 200; i++) {
        loader.load(1, i, fKraken.fDie);
    }
    loader.loadSkipFlipped(1, 200, 488, fKraken.fFight);
    loader.loadSkipFlipped(1, 488, 728, fKraken.fFight2);
}

void eCharacterTextures::loadMaenads() {
    if(fMaenadsLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eMaenadsSpriteData15,
                                 eMaenadsSpriteData30,
                                 eMaenadsSpriteData45,
                                 eMaenadsSpriteData60);
    fMaenadsLoaded = true;
    eSpriteLoader loader(fTileH, "maenads", sds,
                         &eZeus_maenadsOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fMaenads.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fMaenads.fDie);
    loader.loadSkipFlipped(1, 289, 457, fMaenads.fFight);
    loader.loadSkipFlipped(1, 457, 561, fMaenads.fFight2);
}

void eCharacterTextures::loadMedusa() {
    if(fMedusaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eMedusaSpriteData15,
                                 eMedusaSpriteData30,
                                 eMedusaSpriteData45,
                                 eMedusaSpriteData60);
    fMedusaLoaded = true;
    eSpriteLoader loader(fTileH, "medusa", sds,
                         &eZeus_medusaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fMedusa.fWalk);
    loader.loadSkipFlipped(1, 129, 273, fMedusa.fDie);
    loader.loadSkipFlipped(1, 273, 409, fMedusa.fFight);
    loader.loadSkipFlipped(1, 409, 545, fMedusa.fFight2);
}

void eCharacterTextures::loadMinotaur() {
    if(fMinotaurLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eMinotaurSpriteData15,
                                 eMinotaurSpriteData30,
                                 eMinotaurSpriteData45,
                                 eMinotaurSpriteData60);
    fMinotaurLoaded = true;
    eSpriteLoader loader(fTileH, "minotaur", sds,
                         &eZeus_minotaurOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 161, fMinotaur.fWalk);
    loader.loadSkipFlipped(1, 161, 321, fMinotaur.fDie);
    loader.loadSkipFlipped(1, 321, 481, fMinotaur.fFight);
    loader.loadSkipFlipped(1, 481, 641, fMinotaur.fFight2);
}

void eCharacterTextures::loadScylla() {
    if(fScyllaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eScyllaSpriteData15,
                                 eScyllaSpriteData30,
                                 eScyllaSpriteData45,
                                 eScyllaSpriteData60);
    fScyllaLoaded = true;
    eSpriteLoader loader(fTileH, "scylla", sds,
                         &eZeus_scyllaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 161, fScylla.fWalk);
    for(int i = 161; i < 192; i++) {
        loader.load(1, i, fScylla.fDie);
    }
    loader.loadSkipFlipped(1, 192, 432, fScylla.fFight);
    loader.loadSkipFlipped(1, 432, 680, fScylla.fFight2);
}

void eCharacterTextures::loadSphinx() {
    if(fSphinxLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eSphinxSpriteData15,
                                 eSphinxSpriteData30,
                                 eSphinxSpriteData45,
                                 eSphinxSpriteData60);
    fSphinxLoaded = true;
    eSpriteLoader loader(fTileH, "sphinx", sds,
                         &ePoseidon_SphinxOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 137, fSphinx.fWalk);
    loader.loadSkipFlipped(1, 137, 321, fSphinx.fDie);
    loader.loadSkipFlipped(1, 321, 529, fSphinx.fFight);
    loader.loadSkipFlipped(1, 529, 793, fSphinx.fFight2);
}

void eCharacterTextures::loadTalos() {
    if(fTalosLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eTalosSpriteData15,
                                 eTalosSpriteData30,
                                 eTalosSpriteData45,
                                 eTalosSpriteData60);
    fTalosLoaded = true;
    eSpriteLoader loader(fTileH, "talos", sds,
                         &eZeus_talosOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 153, fTalos.fWalk);
    loader.loadSkipFlipped(1, 153, 273, fTalos.fDie);
    loader.loadSkipFlipped(1, 273, 393, fTalos.fFight);
    loader.loadSkipFlipped(1, 393, 545, fTalos.fFight2);
}
