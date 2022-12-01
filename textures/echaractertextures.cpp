#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"
#include "offsets/PoseidonImps.h"
#include "offsets/Zeus_Greek.h"
#include "offsets/SprAmbient.h"

#include "offsets/zeus_calydonianboar.h"
#include "offsets/zeus_cerberus.h"
#include "offsets/Poseidon_Chimera.h"
#include "offsets/zeus_cyclops.h"
#include "offsets/zeus_dragon.h"
#include "offsets/Poseidon_Echidna.h"
#include "offsets/Poseidon_Harpie.h"
#include "offsets/zeus_hector.h"
#include "offsets/zeus_hydra.h"
#include "offsets/zeus_kraken.h"
#include "offsets/zeus_maenads.h"
#include "offsets/zeus_medusa.h"
#include "offsets/zeus_minotaur.h"
#include "offsets/zeus_scylla.h"
#include "offsets/Poseidon_Sphinx.h"
#include "offsets/zeus_talos.h"

#include "offsets/zeus_achilles.h"
#include "offsets/Poseidon_Atalanta.h"
#include "offsets/Poseidon_Bellerophon.h"
#include "offsets/zeus_heracles.h"
#include "offsets/zeus_jason.h"
#include "offsets/zeus_odysseus.h"
#include "offsets/zeus_perseus.h"
#include "offsets/zeus_theseus.h"

#include "spriteData/peddler15.h"
#include "spriteData/peddler30.h"
#include "spriteData/peddler45.h"
#include "spriteData/peddler60.h"

#include "spriteData/actor15.h"
#include "spriteData/actor30.h"
#include "spriteData/actor45.h"
#include "spriteData/actor60.h"

#include "spriteData/ox15.h"
#include "spriteData/ox30.h"
#include "spriteData/ox45.h"
#include "spriteData/ox60.h"

#include "spriteData/porter15.h"
#include "spriteData/porter30.h"
#include "spriteData/porter45.h"
#include "spriteData/porter60.h"

#include "spriteData/oxHandler15.h"
#include "spriteData/oxHandler30.h"
#include "spriteData/oxHandler45.h"
#include "spriteData/oxHandler60.h"

#include "spriteData/trailer15.h"
#include "spriteData/trailer30.h"
#include "spriteData/trailer45.h"
#include "spriteData/trailer60.h"

#include "spriteData/settlers115.h"
#include "spriteData/settlers130.h"
#include "spriteData/settlers145.h"
#include "spriteData/settlers160.h"

#include "spriteData/settlers215.h"
#include "spriteData/settlers230.h"
#include "spriteData/settlers245.h"
#include "spriteData/settlers260.h"

#include "spriteData/fireFighter15.h"
#include "spriteData/fireFighter30.h"
#include "spriteData/fireFighter45.h"
#include "spriteData/fireFighter60.h"

#include "spriteData/watchman15.h"
#include "spriteData/watchman30.h"
#include "spriteData/watchman45.h"
#include "spriteData/watchman60.h"

#include "spriteData/goatherd15.h"
#include "spriteData/goatherd30.h"
#include "spriteData/goatherd45.h"
#include "spriteData/goatherd60.h"

#include "spriteData/bronzeMiner15.h"
#include "spriteData/bronzeMiner30.h"
#include "spriteData/bronzeMiner45.h"
#include "spriteData/bronzeMiner60.h"

#include "spriteData/artisan15.h"
#include "spriteData/artisan30.h"
#include "spriteData/artisan45.h"
#include "spriteData/artisan60.h"

#include "spriteData/foodVendor15.h"
#include "spriteData/foodVendor30.h"
#include "spriteData/foodVendor45.h"
#include "spriteData/foodVendor60.h"

#include "spriteData/fleeceVendor15.h"
#include "spriteData/fleeceVendor30.h"
#include "spriteData/fleeceVendor45.h"
#include "spriteData/fleeceVendor60.h"

#include "spriteData/oilVendor15.h"
#include "spriteData/oilVendor30.h"
#include "spriteData/oilVendor45.h"
#include "spriteData/oilVendor60.h"

#include "spriteData/wineVendor15.h"
#include "spriteData/wineVendor30.h"
#include "spriteData/wineVendor45.h"
#include "spriteData/wineVendor60.h"

#include "spriteData/armsVendor15.h"
#include "spriteData/armsVendor30.h"
#include "spriteData/armsVendor45.h"
#include "spriteData/armsVendor60.h"

#include "spriteData/horseVendor15.h"
#include "spriteData/horseVendor30.h"
#include "spriteData/horseVendor45.h"
#include "spriteData/horseVendor60.h"

#include "spriteData/fleecedSheep15.h"
#include "spriteData/fleecedSheep30.h"
#include "spriteData/fleecedSheep45.h"
#include "spriteData/fleecedSheep60.h"

#include "spriteData/horse15.h"
#include "spriteData/horse30.h"
#include "spriteData/horse45.h"
#include "spriteData/horse60.h"

#include "spriteData/shepherd15.h"
#include "spriteData/shepherd30.h"
#include "spriteData/shepherd45.h"
#include "spriteData/shepherd60.h"

#include "spriteData/marbleMiner15.h"
#include "spriteData/marbleMiner30.h"
#include "spriteData/marbleMiner45.h"
#include "spriteData/marbleMiner60.h"

#include "spriteData/silverMiner15.h"
#include "spriteData/silverMiner30.h"
#include "spriteData/silverMiner45.h"
#include "spriteData/silverMiner60.h"

#include "spriteData/archer15.h"
#include "spriteData/archer30.h"
#include "spriteData/archer45.h"
#include "spriteData/archer60.h"

#include "spriteData/lumberjack15.h"
#include "spriteData/lumberjack30.h"
#include "spriteData/lumberjack45.h"
#include "spriteData/lumberjack60.h"

#include "spriteData/taxCollector15.h"
#include "spriteData/taxCollector30.h"
#include "spriteData/taxCollector45.h"
#include "spriteData/taxCollector60.h"

#include "spriteData/transporter15.h"
#include "spriteData/transporter30.h"
#include "spriteData/transporter45.h"
#include "spriteData/transporter60.h"

#include "spriteData/grower15.h"
#include "spriteData/grower30.h"
#include "spriteData/grower45.h"
#include "spriteData/grower60.h"

#include "spriteData/trader15.h"
#include "spriteData/trader30.h"
#include "spriteData/trader45.h"
#include "spriteData/trader60.h"

#include "spriteData/waterDistributor15.h"
#include "spriteData/waterDistributor30.h"
#include "spriteData/waterDistributor45.h"
#include "spriteData/waterDistributor60.h"

#include "spriteData/rockThrower15.h"
#include "spriteData/rockThrower30.h"
#include "spriteData/rockThrower45.h"
#include "spriteData/rockThrower60.h"

#include "spriteData/hoplite15.h"
#include "spriteData/hoplite30.h"
#include "spriteData/hoplite45.h"
#include "spriteData/hoplite60.h"

#include "spriteData/horseman15.h"
#include "spriteData/horseman30.h"
#include "spriteData/horseman45.h"
#include "spriteData/horseman60.h"

#include "spriteData/healer15.h"
#include "spriteData/healer30.h"
#include "spriteData/healer45.h"
#include "spriteData/healer60.h"

#include "spriteData/nudeSheep15.h"
#include "spriteData/nudeSheep30.h"
#include "spriteData/nudeSheep45.h"
#include "spriteData/nudeSheep60.h"

#include "spriteData/cart15.h"
#include "spriteData/cart30.h"
#include "spriteData/cart45.h"
#include "spriteData/cart60.h"

#include "spriteData/boar15.h"
#include "spriteData/boar30.h"
#include "spriteData/boar45.h"
#include "spriteData/boar60.h"

#include "spriteData/gymnast15.h"
#include "spriteData/gymnast30.h"
#include "spriteData/gymnast45.h"
#include "spriteData/gymnast60.h"

#include "spriteData/goat15.h"
#include "spriteData/goat30.h"
#include "spriteData/goat45.h"
#include "spriteData/goat60.h"

#include "spriteData/wolf15.h"
#include "spriteData/wolf30.h"
#include "spriteData/wolf45.h"
#include "spriteData/wolf60.h"

#include "spriteData/hunter15.h"
#include "spriteData/hunter30.h"
#include "spriteData/hunter45.h"
#include "spriteData/hunter60.h"

#include "spriteData/philosopher15.h"
#include "spriteData/philosopher30.h"
#include "spriteData/philosopher45.h"
#include "spriteData/philosopher60.h"

#include "spriteData/fishingBoat15.h"
#include "spriteData/fishingBoat30.h"
#include "spriteData/fishingBoat45.h"
#include "spriteData/fishingBoat60.h"

#include "spriteData/tradeBoat15.h"
#include "spriteData/tradeBoat30.h"
#include "spriteData/tradeBoat45.h"
#include "spriteData/tradeBoat60.h"

#include "spriteData/deerHunter15.h"
#include "spriteData/deerHunter30.h"
#include "spriteData/deerHunter45.h"
#include "spriteData/deerHunter60.h"

#include "spriteData/deer15.h"
#include "spriteData/deer30.h"
#include "spriteData/deer45.h"
#include "spriteData/deer60.h"

#include "spriteData/orangesCart15.h"
#include "spriteData/orangesCart30.h"
#include "spriteData/orangesCart45.h"
#include "spriteData/orangesCart60.h"

#include "spriteData/orangeTender15.h"
#include "spriteData/orangeTender30.h"
#include "spriteData/orangeTender45.h"
#include "spriteData/orangeTender60.h"

#include "spriteData/greekHoplite15.h"
#include "spriteData/greekHoplite30.h"
#include "spriteData/greekHoplite45.h"
#include "spriteData/greekHoplite60.h"

#include "spriteData/greekHorseman15.h"
#include "spriteData/greekHorseman30.h"
#include "spriteData/greekHorseman45.h"
#include "spriteData/greekHorseman60.h"

#include "spriteData/greekRockThrower15.h"
#include "spriteData/greekRockThrower30.h"
#include "spriteData/greekRockThrower45.h"
#include "spriteData/greekRockThrower60.h"

#include "spriteData/foodCart15.h"
#include "spriteData/foodCart30.h"
#include "spriteData/foodCart45.h"
#include "spriteData/foodCart60.h"

#include "spriteData/donkey15.h"
#include "spriteData/donkey30.h"
#include "spriteData/donkey45.h"
#include "spriteData/donkey60.h"

#include "spriteData/calydonianBoar15.h"
#include "spriteData/calydonianBoar30.h"
#include "spriteData/calydonianBoar45.h"
#include "spriteData/calydonianBoar60.h"

#include "spriteData/cerberus15.h"
#include "spriteData/cerberus30.h"
#include "spriteData/cerberus45.h"
#include "spriteData/cerberus60.h"

#include "spriteData/chimera15.h"
#include "spriteData/chimera30.h"
#include "spriteData/chimera45.h"
#include "spriteData/chimera60.h"

#include "spriteData/cyclops15.h"
#include "spriteData/cyclops30.h"
#include "spriteData/cyclops45.h"
#include "spriteData/cyclops60.h"

#include "spriteData/dragon15.h"
#include "spriteData/dragon30.h"
#include "spriteData/dragon45.h"
#include "spriteData/dragon60.h"

#include "spriteData/echidna15.h"
#include "spriteData/echidna30.h"
#include "spriteData/echidna45.h"
#include "spriteData/echidna60.h"

#include "spriteData/harpie15.h"
#include "spriteData/harpie30.h"
#include "spriteData/harpie45.h"
#include "spriteData/harpie60.h"

#include "spriteData/hector15.h"
#include "spriteData/hector30.h"
#include "spriteData/hector45.h"
#include "spriteData/hector60.h"

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

#include "spriteData/achilles15.h"
#include "spriteData/achilles30.h"
#include "spriteData/achilles45.h"
#include "spriteData/achilles60.h"

#include "spriteData/atalanta15.h"
#include "spriteData/atalanta30.h"
#include "spriteData/atalanta45.h"
#include "spriteData/atalanta60.h"

#include "spriteData/bellerophon15.h"
#include "spriteData/bellerophon30.h"
#include "spriteData/bellerophon45.h"
#include "spriteData/bellerophon60.h"

#include "spriteData/heracles15.h"
#include "spriteData/heracles30.h"
#include "spriteData/heracles45.h"
#include "spriteData/heracles60.h"

#include "spriteData/jason15.h"
#include "spriteData/jason30.h"
#include "spriteData/jason45.h"
#include "spriteData/jason60.h"

#include "spriteData/odysseus15.h"
#include "spriteData/odysseus30.h"
#include "spriteData/odysseus45.h"
#include "spriteData/odysseus60.h"

#include "spriteData/perseus15.h"
#include "spriteData/perseus30.h"
#include "spriteData/perseus45.h"
#include "spriteData/perseus60.h"

#include "spriteData/theseus15.h"
#include "spriteData/theseus30.h"
#include "spriteData/theseus45.h"
#include "spriteData/theseus60.h"

#include "espriteloader.h"

#include "etextureloader.h"

eCharacterTextures::eCharacterTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fPeddler(renderer),
    fActor(renderer),
    fTaxCollector(renderer),
    fWaterDistributor(renderer),
    fWatchman(renderer),
    fFireFighter(renderer),
    fHealer(renderer),
    fGymnast(renderer),
    fPhilosopher(renderer),

    fOx(renderer),
    fOxHandler(renderer),

    fEmptyTrailer(renderer),
    fWoodTrailer1(renderer),
    fWoodTrailer2(renderer),
    fMarbleTrailer1(renderer),
    fMarbleTrailer2(renderer),
    fSculptureTrailer(renderer),
    fEmptyBigTrailer(renderer),
    fMarbleBigTrailer(renderer),

    fMarbleMiner(renderer),
    fSilverMiner(renderer),
    fBronzeMiner(renderer),
    fLumberjack(renderer),

    fArtisan(renderer),

    fHunter(renderer),
    fDeerHunter(renderer),

    fShepherd(renderer),
    fGoatherd(renderer),

    fFoodVendor(renderer),
    fFleeceVendor(renderer),
    fOilVendor(renderer),
    fWineVendor(renderer),
    fArmsVendor(renderer),
    fHorseVendor(renderer),

    fGrower(renderer),

    fBoar(renderer),
    fDeer(renderer),
    fWolf(renderer),

    fGoat(renderer),
    fNudeSheep(renderer),
    fFleecedSheep(renderer),
    fHorse(renderer),

    fSettlers1(renderer),
    fSettlers2(renderer),

    fTransporter(renderer),

    fEmptyCart(renderer),

    fOrangeTender(renderer),

    fArcher(renderer),

    fRockThrower(renderer),
    fHoplite(renderer),
    fHorseman(renderer),

    fGreekRockThrower(renderer),
    fGreekHoplite(renderer),
    fGreekHorseman(renderer),

    fBannerRod(renderer),
    fBannerTops(renderer),

    fTrader(renderer),
    fDonkey(renderer),

    fPorter(renderer),

    fFishingBoat(renderer),

    fTradeBoat(renderer),

    fKraken(renderer),
    fScylla(renderer) {

}

void loadBasicTexture(eBasicCharacterTextures& tex,
                      const int start,
                      eSpriteLoader& loader) {
    loader.loadSkipFlipped(start, start, start + 96, tex.fWalk);

    for(int i = start + 96; i < start + 104; i++) {
        loader.load(start, i, tex.fDie);
    }
}

void eCharacterTextures::loadPeddler() {
    if(fPeddlerLoaded) return;
    fPeddlerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePeddlerSpriteData15,
                                 ePeddlerSpriteData30,
                                 ePeddlerSpriteData45,
                                 ePeddlerSpriteData60);
    eSpriteLoader loader(fTileH, "peddler", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fPeddler, 1, loader);
}

void eCharacterTextures::loadActor() {
    if(fActorLoaded) return;
    fActorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eActorSpriteData15,
                                 eActorSpriteData30,
                                 eActorSpriteData45,
                                 eActorSpriteData60);
    eSpriteLoader loader(fTileH, "actor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fActor, 105, loader);
}

void eCharacterTextures::loadOx() {
    if(fOxLoaded) return;
    fOxLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOxSpriteData15,
                                 eOxSpriteData30,
                                 eOxSpriteData45,
                                 eOxSpriteData60);
    eSpriteLoader loader(fTileH, "ox", sds,
                         &eSprMainOffset, fRenderer);
    loader.loadSkipFlipped(209, 209, 305, fOx.fWalk);

    for(auto& coll : fOx.fWalk) {
        const int iMax = coll.size();
        for(int i = 0; i < iMax; i++) {
            auto& tex = coll.getTexture(i);
            tex->setOffset(tex->offsetX(),
                           tex->offsetY() + 4);
        }
    }

    for(int i = 497; i < 505; i++) {
        loader.load(209, i, fOx.fDie);
    }
}

void eCharacterTextures::loadPorter() {
    if(fPorterLoaded) return;
    fPorterLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePorterSpriteData15,
                                 ePorterSpriteData30,
                                 ePorterSpriteData45,
                                 ePorterSpriteData60);
    eSpriteLoader loader(fTileH, "porter", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fPorter, 1233, loader);
}

void eCharacterTextures::loadOxHandler() {
    if(fOxHandlerLoaded) return;
    fOxHandlerLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOxHandlerSpriteData15,
                                 eOxHandlerSpriteData30,
                                 eOxHandlerSpriteData45,
                                 eOxHandlerSpriteData60);
    eSpriteLoader loader(fTileH, "oxHandler", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fOxHandler, 1337, loader);
}

void eCharacterTextures::loadTrailer() {
    if(fTrailerLoaded) return;
    fTrailerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTrailerSpriteData15,
                                 eTrailerSpriteData30,
                                 eTrailerSpriteData45,
                                 eTrailerSpriteData60);
    eSpriteLoader loader(fTileH, "trailer", sds,
                         &eSprMainOffset, fRenderer);

    const auto loadTrailer =
            [&](const int min, const int max,
                eTextureCollection& coll,
                const int dy) {
        for(int i = min; i < max; i++) {
            const auto& tex = loader.load(2991, i, coll);
            tex->setOffset(tex->offsetX(), tex->offsetY() + dy);
        }
    };

    loadTrailer(2991, 2999, fEmptyTrailer, -7);
    loadTrailer(2999, 3007, fWoodTrailer1, -7);
    loadTrailer(3007, 3015, fWoodTrailer2, -7);
    loadTrailer(3015, 3023, fMarbleTrailer1, -7);
    loadTrailer(3023, 3031, fMarbleTrailer2, -7);
    loadTrailer(3031, 3039, fSculptureTrailer, -7);
    loadTrailer(3039, 3047, fEmptyBigTrailer, -4);
    loadTrailer(3047, 3055, fMarbleBigTrailer, -4);
}

void eCharacterTextures::loadSettlers() {
    if(fSettlersLoaded) return;
    fSettlersLoaded = true;
    {
        const auto& sds = spriteData(fTileH,
                                     eSettlers1SpriteData15,
                                     eSettlers1SpriteData30,
                                     eSettlers1SpriteData45,
                                     eSettlers1SpriteData60);
        eSpriteLoader loader(fTileH, "settlers1", sds,
                             &eSprMainOffset, fRenderer);
        loadBasicTexture(fSettlers1, 505, loader);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eSettlers2SpriteData15,
                                     eSettlers2SpriteData30,
                                     eSettlers2SpriteData45,
                                     eSettlers2SpriteData60);
        eSpriteLoader loader(fTileH, "settlers2", sds,
                             &eSprMainOffset, fRenderer);
        loadBasicTexture(fSettlers2, 1793, loader);
    }
}

void eCharacterTextures::loadFireFighter() {
    if(fFireFighterLoaded) return;
    fFireFighterLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eFireFighterSpriteData15,
                                 eFireFighterSpriteData30,
                                 eFireFighterSpriteData45,
                                 eFireFighterSpriteData60);
    eSpriteLoader loader(fTileH, "fireFighter", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(609, 609, 705,
                           fFireFighter.fWalk);
    loader.loadSkipFlipped(609, 705, 801,
                           fFireFighter.fCarry);
    loader.loadSkipFlipped(609, 809, 1129,
                           fFireFighter.fPutOut);

    for(int i = 801; i < 809; i++) {
        loader.load(609, i, fFireFighter.fDie);
    }
}

void eCharacterTextures::loadWatchman() {
    if(fWatchmanLoaded) return;
    fWatchmanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eWatchmanSpriteData15,
                                 eWatchmanSpriteData30,
                                 eWatchmanSpriteData45,
                                 eWatchmanSpriteData60);
    eSpriteLoader loader(fTileH, "watchman", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(2209, 2209, 2305, fWatchman.fWalk);
    loader.loadSkipFlipped(2209, 2313, 2377, fWatchman.fFight);

    for(int i = 2305; i < 2313; i++) {
        loader.load(2209, i, fWatchman.fDie);
    }
}

void eCharacterTextures::loadGoatherd() {
    if(fGoatherdLoaded) return;
    fGoatherdLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eGoatherdSpriteData15,
                                 eGoatherdSpriteData30,
                                 eGoatherdSpriteData45,
                                 eGoatherdSpriteData60);
    eSpriteLoader loader(fTileH, "goatherd", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(2377, 2377, 2473, fGoatherd.fWalk);
    loader.loadSkipFlipped(2377, 2481, 2489, fGoatherd.fCollect);
    loader.loadSkipFlipped(2377, 2489, 2585, fGoatherd.fCarry);

    for(int i = 2473; i < 2481; i++) {
        loader.load(2377, i, fGoatherd.fDie);
    }
    for(int i = 2585; i < 2595; i++) {
        loader.load(2377, i, fGoatherd.fFight);
    }
}

void eCharacterTextures::loadBronzeMiner() {
    if(fBronzeMinerLoaded) return;
    fBronzeMinerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eBronzeMinerSpriteData15,
                                 eBronzeMinerSpriteData30,
                                 eBronzeMinerSpriteData45,
                                 eBronzeMinerSpriteData60);
    eSpriteLoader loader(fTileH, "bronzeMiner", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(2595, 2595, 2691, fBronzeMiner.fWalk);
    loader.loadSkipFlipped(2595, 2711, 2807, fBronzeMiner.fCarry);
    loader.loadSkipFlipped(2595, 2807, 2887, fBronzeMiner.fCollect);

    for(int i = 2691; i < 2699; i++) {
        loader.load(2595, i, fBronzeMiner.fDie);
    }
}

void eCharacterTextures::loadArtisan() {
    if(fArtisanLoaded) return;
    fArtisanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eArtisanSpriteData15,
                                 eArtisanSpriteData30,
                                 eArtisanSpriteData45,
                                 eArtisanSpriteData60);
    eSpriteLoader loader(fTileH, "artisan", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(1545, 1545, 1641, fArtisan.fWalk);
    loader.loadSkipFlipped(1545, 1649, 1721, fArtisan.fBuild);
    loader.loadSkipFlipped(1545, 1721, 1793, fArtisan.fBuildStanding);

    for(int i = 1641; i < 1649; i++) {
        loader.load(1545, i, fArtisan.fDie);
    }
}

void eCharacterTextures::loadFoodVendor() {
    if(fFoodVendorLoaded) return;
    fFoodVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eFoodVendorSpriteData15,
                                 eFoodVendorSpriteData30,
                                 eFoodVendorSpriteData45,
                                 eFoodVendorSpriteData60);
    eSpriteLoader loader(fTileH, "foodVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fFoodVendor, 2887, loader);
}

void eCharacterTextures::loadFleeceVendor() {
    if(fFleeceVendorLoaded) return;
    fFleeceVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eFleeceVendorSpriteData15,
                                 eFleeceVendorSpriteData30,
                                 eFleeceVendorSpriteData45,
                                 eFleeceVendorSpriteData60);
    eSpriteLoader loader(fTileH, "fleeceVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fFleeceVendor, 1897, loader);
}

void eCharacterTextures::loadOilVendor() {
    if(fOilVendorLoaded) return;
    fOilVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eOilVendorSpriteData15,
                                 eOilVendorSpriteData30,
                                 eOilVendorSpriteData45,
                                 eOilVendorSpriteData60);
    eSpriteLoader loader(fTileH, "oilVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fOilVendor, 5297, loader);
}

void eCharacterTextures::loadWineVendor() {
    if(fWineVendorLoaded) return;
    fWineVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eWineVendorSpriteData15,
                                 eWineVendorSpriteData30,
                                 eWineVendorSpriteData45,
                                 eWineVendorSpriteData60);
    eSpriteLoader loader(fTileH, "wineVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fWineVendor, 5401, loader);
}

void eCharacterTextures::loadArmsVendor() {
    if(fArmsVendorLoaded) return;
    fArmsVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eArmsVendorSpriteData15,
                                 eArmsVendorSpriteData30,
                                 eArmsVendorSpriteData45,
                                 eArmsVendorSpriteData60);
    eSpriteLoader loader(fTileH, "armsVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fArmsVendor, 2105, loader);
}

void eCharacterTextures::loadHorseVendor() {
    if(fHorseVendorLoaded) return;
    fHorseVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eHorseVendorSpriteData15,
                                 eHorseVendorSpriteData30,
                                 eHorseVendorSpriteData45,
                                 eHorseVendorSpriteData60);
    eSpriteLoader loader(fTileH, "horseVendor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fHorseVendor, 1129, loader);
}

void eCharacterTextures::loadSheep() {
    if(fSheepLoaded) return;
    fSheepLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eFleecedSheepSpriteData15,
                                     eFleecedSheepSpriteData30,
                                     eFleecedSheepSpriteData45,
                                     eFleecedSheepSpriteData60);
        eSpriteLoader loader(fTileH, "fleecedSheep", sds,
                             &eSprMainOffset, fRenderer);
        loader.loadSkipFlipped(3183, 3183, 3279, fFleecedSheep.fWalk);
        loader.loadSkipFlipped(3183, 3287, 3351, fFleecedSheep.fFight);
        loader.loadSkipFlipped(3183, 3351, 3415, fFleecedSheep.fLayDown);

        for(int i = 3279; i < 3287; i++) {
            loader.load(3183, i, fFleecedSheep.fDie);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eNudeSheepSpriteData15,
                                     eNudeSheepSpriteData30,
                                     eNudeSheepSpriteData45,
                                     eNudeSheepSpriteData60);
        eSpriteLoader loader(fTileH, "nudeSheep", sds,
                             &eSprMainOffset, fRenderer);
        loader.loadSkipFlipped(7873, 7873, 7969, fNudeSheep.fWalk);
        loader.loadSkipFlipped(7873, 7977, 8041, fNudeSheep.fFight);
        loader.loadSkipFlipped(7873, 8041, 8105, fNudeSheep.fLayDown);

        for(int i = 7969; i < 7977; i++) {
            loader.load(7873, i, fNudeSheep.fDie);
        }
    }
}

void eCharacterTextures::loadHorse() {
    if(fHorseLoaded) return;
    fHorseLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eHorseSpriteData15,
                                 eHorseSpriteData30,
                                 eHorseSpriteData45,
                                 eHorseSpriteData60);
    eSpriteLoader loader(fTileH, "horse", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(5001, 5001, 5097, fHorse.fWalk);
    loader.loadSkipFlipped(5001, 5105, 5297, fHorse.fStand);

    for(int i = 5097; i < 5105; i++) {
        loader.load(5001, i, fHorse.fDie);
    }
}

void eCharacterTextures::loadShepherd() {
    if(fShepherdLoaded) return;
    fShepherdLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eShepherdSpriteData15,
                                 eShepherdSpriteData30,
                                 eShepherdSpriteData45,
                                 eShepherdSpriteData60);
    eSpriteLoader loader(fTileH, "shepherd", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(3415, 3415, 3511, fShepherd.fWalk);
    loader.loadSkipFlipped(3415, 3519, 3531, fShepherd.fCollect);
    loader.loadSkipFlipped(3415, 3531, 3627, fShepherd.fCarry);

    for(int i = 3627; i < 3637; i++) {
        loader.load(3415, i, fShepherd.fFight);
    }
    for(int i = 3511; i < 3519; i++) {
        loader.load(3415, i, fShepherd.fDie);
    }
}

void eCharacterTextures::loadMarbleMiner() {
    if(fMarbleMinerLoaded) return;
    fMarbleMinerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eMarbleMinerSpriteData15,
                                 eMarbleMinerSpriteData30,
                                 eMarbleMinerSpriteData45,
                                 eMarbleMinerSpriteData60);
    eSpriteLoader loader(fTileH, "marbleMiner", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(11044, 11044, 11140, fMarbleMiner.fWalk);
    loader.loadSkipFlipped(11044, 11148, 11228, fMarbleMiner.fCollect);

    for(int i = 11140; i < 11148; i++) {
        loader.load(11044, i, fMarbleMiner.fDie);
    }
}

void eCharacterTextures::loadSilverMiner() {
    if(fSilverMinerLoaded) return;
    fSilverMinerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eSilverMinerSpriteData15,
                                 eSilverMinerSpriteData30,
                                 eSilverMinerSpriteData45,
                                 eSilverMinerSpriteData60);
    eSpriteLoader loader(fTileH, "silverMiner", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(3741, 3741, 3837, fSilverMiner.fWalk);
    loader.loadSkipFlipped(3741, 3857, 3953, fSilverMiner.fCarry);
    loader.loadSkipFlipped(3741, 3953, 4033, fSilverMiner.fCollect);

    for(int i = 3837; i < 3845; i++) {
        loader.load(3741, i, fSilverMiner.fDie);
    }
}

void eCharacterTextures::loadArcher() {
    if(fArcherLoaded) return;
    fArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eArcherSpriteData15,
                                 eArcherSpriteData30,
                                 eArcherSpriteData45,
                                 eArcherSpriteData60);
    eSpriteLoader loader(fTileH, "archer", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(4033, 4033, 4129, fArcher.fWalk);
    loader.loadSkipFlipped(4033, 4137, 4233, fArcher.fFight);
    loader.loadSkipFlipped(4033, 4233, 4329, fArcher.fPatrol);

    for(int i = 4129; i < 4137; i++) {
        loader.load(4033, i, fArcher.fDie);
    }
}

void eCharacterTextures::loadLumberjack() {
    if(fLumberjackLoaded) return;
    fLumberjackLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eLumberjackSpriteData15,
                                 eLumberjackSpriteData30,
                                 eLumberjackSpriteData45,
                                 eLumberjackSpriteData60);
    eSpriteLoader loader(fTileH, "lumberjack", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(4329, 4329, 4425, fLumberjack.fWalk);
    loader.loadSkipFlipped(4329, 4433, 4529, fLumberjack.fCollect);
    loader.loadSkipFlipped(4329, 4529, 4625, fLumberjack.fCarry);

    for(int i = 4425; i < 4433; i++) {
        loader.load(4329, i, fLumberjack.fDie);
    }
}

void eCharacterTextures::loadTaxCollector() {
    if(fTaxCollectorLoaded) return;
    fTaxCollectorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTaxCollectorSpriteData15,
                                 eTaxCollectorSpriteData30,
                                 eTaxCollectorSpriteData45,
                                 eTaxCollectorSpriteData60);
    eSpriteLoader loader(fTileH, "taxCollector", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fTaxCollector, 4625, loader);
}

void eCharacterTextures::loadTransporter() {
    if(fTransporterLoaded) return;
    fTransporterLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTransporterSpriteData15,
                                 eTransporterSpriteData30,
                                 eTransporterSpriteData45,
                                 eTransporterSpriteData60);
    eSpriteLoader loader(fTileH, "transporter", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fTransporter, 4729, loader);
}

void eCharacterTextures::loadGrower() {
    if(fGrowerLoaded) return;
    fGrowerLoaded = true;
    {
        const auto& sds = spriteData(fTileH,
                                     eGrowerSpriteData15,
                                     eGrowerSpriteData30,
                                     eGrowerSpriteData45,
                                     eGrowerSpriteData60);
        eSpriteLoader loader(fTileH, "grower", sds,
                             &eSprMainOffset, fRenderer);

        loader.loadSkipFlipped(5505, 5505, 5601, fGrower.fWalk);
        loader.loadSkipFlipped(5505, 5609, 5689, fGrower.fWorkOnGrapes);
        loader.loadSkipFlipped(5505, 5689, 5769, fGrower.fWorkOnOlives);
        loader.loadSkipFlipped(5505, 5769, 5849, fGrower.fCollectGrapes);
        loader.loadSkipFlipped(5505, 5849, 5929, fGrower.fCollectOlives);

        for(int i = 5601; i < 5609; i++) {
            loader.load(5505, i, fGrower.fDie);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eOrangeTenderSpriteData15,
                                     eOrangeTenderSpriteData30,
                                     eOrangeTenderSpriteData45,
                                     eOrangeTenderSpriteData60);
        eSpriteLoader loader(fTileH, "orangeTender", sds,
                             &ePoseidonImpsOffset, fRenderer);

        loader.loadSkipFlipped(1211, 1211, 1307, fOrangeTender.fWalk);
        loader.loadSkipFlipped(1211, 1315, 1411, fOrangeTender.fWorkOnTree);
        loader.loadSkipFlipped(1211, 1411, 1507, fOrangeTender.fCollect);

        for(int i = 1307; i < 1315; i++) {
            loader.load(1211, i, fOrangeTender.fDie);
        }
    }
}

void eCharacterTextures::loadTrader() {
    if(fTraderLoaded) return;
    fTraderLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTraderSpriteData15,
                                 eTraderSpriteData30,
                                 eTraderSpriteData45,
                                 eTraderSpriteData60);
    eSpriteLoader loader(fTileH, "trader", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fTrader, 5929, loader);
}

void eCharacterTextures::loadWaterDistributor() {
    if(fWaterDistributorLoaded) return;
    fWaterDistributorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eWaterDistributorSpriteData15,
                                 eWaterDistributorSpriteData30,
                                 eWaterDistributorSpriteData45,
                                 eWaterDistributorSpriteData60);
    eSpriteLoader loader(fTileH, "waterDistributor", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fWaterDistributor, 6737, loader);
}

void eCharacterTextures::loadRockThrower() {
    if(fRockThrowerLoaded) return;
    fRockThrowerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eRockThrowerSpriteData15,
                                 eRockThrowerSpriteData30,
                                 eRockThrowerSpriteData45,
                                 eRockThrowerSpriteData60);
    eSpriteLoader loader(fTileH, "rockThrower", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(6841, 6841, 6937, fRockThrower.fWalk);
    loader.loadSkipFlipped(6841, 6945, 7041, fRockThrower.fFight2);
    loader.loadSkipFlipped(6841, 7041, 7105, fRockThrower.fFight);

    for(int i = 6937; i < 6945; i++) {
        loader.load(6841, i, fRockThrower.fDie);
    }
}

void eCharacterTextures::loadHoplite() {
    if(fHopliteLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHopliteSpriteData15,
                                 eHopliteSpriteData30,
                                 eHopliteSpriteData45,
                                 eHopliteSpriteData60);
    fHopliteLoaded = true;
    eSpriteLoader loader(fTileH, "hoplite", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(7105, 7105, 7201, fHoplite.fWalk);
    loader.loadSkipFlipped(7105, 7209, 7273, fHoplite.fFight);

    for(int i = 7201; i < 7209; i++) {
        loader.load(7105, i, fHoplite.fDie);
    }
}

void eCharacterTextures::loadHorseman() {
    if(fHorsemanLoaded) return;
    fHorsemanLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHorsemanSpriteData15,
                                 eHorsemanSpriteData30,
                                 eHorsemanSpriteData45,
                                 eHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "horseman", sds,
                         &eSprMainOffset, fRenderer);
    loader.loadSkipFlipped(7273, 7273, 7369, fHorseman.fWalk);
    loader.loadSkipFlipped(7273, 7377, 7473, fHorseman.fFight);

    for(int i = 7369; i < 7377; i++) {
        loader.load(7273, i, fHorseman.fDie);
    }
}

void eCharacterTextures::loadHealer() {
    if(fHealerLoaded) return;
    fHealerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eHealerSpriteData15,
                                 eHealerSpriteData30,
                                 eHealerSpriteData45,
                                 eHealerSpriteData60);
    eSpriteLoader loader(fTileH, "healer", sds,
                         &eSprMainOffset, fRenderer);

    loadBasicTexture(fHealer, 7473, loader);
}

void eCharacterTextures::loadCart() {
    if(fCartLoaded) return;
    fCartLoaded = true;
    {
        const auto& sds = spriteData(fTileH,
                                     eCartSpriteData15,
                                     eCartSpriteData30,
                                     eCartSpriteData45,
                                     eCartSpriteData60);
        eSpriteLoader loader(fTileH, "cart", sds,
                             &eSprMainOffset, fRenderer);

        for(int i = 8428; i < 8436; i++) {
            loader.load(8428, i, fEmptyCart);
        }
        loader.loadSkipFlipped(8428, 8436, 8460, fUrchinCart);
        loader.loadSkipFlipped(8428, 8460, 8484, fFishCart);
        loader.loadSkipFlipped(8428, 8484, 8508, fMeatCart);
        loader.loadSkipFlipped(8428, 8508, 8532, fCheeseCart);
        loader.loadSkipFlipped(8428, 8532, 8556, fCarrotsCart);
        loader.loadSkipFlipped(8428, 8556, 8580, fOnionsCart);
        loader.loadSkipFlipped(8428, 8580, 8604, fWheatCart);
        loader.loadSkipFlipped(8428, 8604, 8620, fBronzeCart);
        loader.loadSkipFlipped(8428, 8620, 8644, fGrapesCart);
        loader.loadSkipFlipped(8428, 8644, 8668, fOlivesCart);
        loader.loadSkipFlipped(8428, 8668, 8684, fFleeceCart);
        loader.loadSkipFlipped(8428, 8684, 8700, fArmorCart);
        loader.loadSkipFlipped(8428, 8700, 8716, fOliveOilCart);
        loader.loadSkipFlipped(8428, 8716, 8732, fWineCart);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eOrangesCartSpriteData15,
                                     eOrangesCartSpriteData30,
                                     eOrangesCartSpriteData45,
                                     eOrangesCartSpriteData60);
        eSpriteLoader loader(fTileH, "orangesCart", sds,
                             &ePoseidonImpsOffset, fRenderer);

        loader.loadSkipFlipped(1091, 1091, 1115, fWineCart);
    }
}

void eCharacterTextures::loadBoar() {
    if(fBoarLoaded) return;
    fBoarLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eBoarSpriteData15,
                                 eBoarSpriteData30,
                                 eBoarSpriteData45,
                                 eBoarSpriteData60);
    eSpriteLoader loader(fTileH, "boar", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(10124, 10124, 10220, fBoar.fWalk);
    loader.loadSkipFlipped(10124, 10228, 10356, fBoar.fFight);
    loader.loadSkipFlipped(10124, 10356, 10420, fBoar.fLayDown);

    for(int i = 10220; i < 10228; i++) {
        loader.load(10124, i, fBoar.fDie);
    }
}

void eCharacterTextures::loadGymnast() {
    if(fGymnastLoaded) return;
    fGymnastLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGymnastSpriteData15,
                                 eGymnastSpriteData30,
                                 eGymnastSpriteData45,
                                 eGymnastSpriteData60);
    eSpriteLoader loader(fTileH, "gymnast", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fGymnast, 10588, loader);
}

void eCharacterTextures::loadGoat() {
    if(fGoatLoaded) return;
    fGoatLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGoatSpriteData15,
                                 eGoatSpriteData30,
                                 eGoatSpriteData45,
                                 eGoatSpriteData60);
    eSpriteLoader loader(fTileH, "goat", sds,
                         &eSprMainOffset, fRenderer);
    loader.loadSkipFlipped(11228, 11228, 11324, fGoat.fWalk);
    loader.loadSkipFlipped(11228, 11332, 11460, fGoat.fFight);
    loader.loadSkipFlipped(11228, 11460, 11524, fGoat.fLayDown);

    for(int i = 11324; i < 11332; i++) {
        loader.load(11228, i, fGoat.fDie);
    }
}

void eCharacterTextures::loadWolf() {
    if(fWolfLoaded) return;
    fWolfLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eWolfSpriteData15,
                                 eWolfSpriteData30,
                                 eWolfSpriteData45,
                                 eWolfSpriteData60);
    eSpriteLoader loader(fTileH, "wolf", sds,
                         &eSprMainOffset, fRenderer);
    loader.loadSkipFlipped(11524, 11524, 11620, fWolf.fWalk);
    loader.loadSkipFlipped(11524, 11628, 11756, fWolf.fFight);
    loader.loadSkipFlipped(11524, 11756, 11820, fWolf.fLayDown);

    for(int i = 11620; i < 11628; i++) {
        loader.load(11524, i, fWolf.fDie);
    }
}

void eCharacterTextures::loadHunter() {
    if(fHunterLoaded) return;
    fHunterLoaded = true;
    {

        const auto& sds = spriteData(fTileH,
                                     eHunterSpriteData15,
                                     eHunterSpriteData30,
                                     eHunterSpriteData45,
                                     eHunterSpriteData60);
        eSpriteLoader loader(fTileH, "hunter", sds,
                             &eSprMainOffset, fRenderer);
        loader.loadSkipFlipped(11820, 11820, 11916, fHunter.fWalk);
        loader.loadSkipFlipped(11820, 11924, 12019, fHunter.fCollect);
        loader.loadSkipFlipped(11820, 12032, 12128, fHunter.fCarry);

        for(int i = 11916; i < 11924; i++) {
            loader.load(11820, i, fHunter.fDie);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eDeerHunterSpriteData15,
                                     eDeerHunterSpriteData30,
                                     eDeerHunterSpriteData45,
                                     eDeerHunterSpriteData60);

        eSpriteLoader loader(fTileH, "deerHunter", sds,
                             &ePoseidonImpsOffset, fRenderer);
        loader.loadSkipFlipped(183, 183, 279, fDeerHunter.fWalk);
        loader.loadSkipFlipped(183, 287, 407, fDeerHunter.fCollect);
        loader.loadSkipFlipped(183, 435, 531, fDeerHunter.fCarry);

        for(int i = 279; i < 287; i++) {
            loader.load(183, i, fDeerHunter.fDie);
        }
    }
}

void eCharacterTextures::loadPhilosopher() {
    if(fPhilosopherLoaded) return;
    fPhilosopherLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePhilosopherSpriteData15,
                                 ePhilosopherSpriteData30,
                                 ePhilosopherSpriteData45,
                                 ePhilosopherSpriteData60);
    eSpriteLoader loader(fTileH, "philosopher", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fPhilosopher, 12128, loader);
}

void eCharacterTextures::loadFishingBoat() {
    if(fFishingBoatLoaded) return;
    fFishingBoatLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eFishingBoatSpriteData15,
                                 eFishingBoatSpriteData30,
                                 eFishingBoatSpriteData45,
                                 eFishingBoatSpriteData60);
    eSpriteLoader loader(fTileH, "fishingBoat", sds,
                         &eSprMainOffset, fRenderer);

    for(int j = 0; j < 8; j++) {
        fFishingBoat.fSwim.emplace_back(fRenderer);
    }

    for(int i = 10797; i < 10860;) {
        for(int j = 0; j < 8; j++, i += 2) {
            loader.load(10797, i, fFishingBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFishingBoat.fCollect.emplace_back(fRenderer);
        fFishingBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 10860; i < 10940;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(10797, i, fFishingBoat.fCollect[j]);
        }
    }

    for(int i = 10940; i < 10948; i++) {
        loader.load(10797, i, fFishingBoat.fStand);
    }

    for(int i = 10948; i < 11036;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(10797, i, fFishingBoat.fDie[j]);
        }
    }
}

void eCharacterTextures::loadTradeBoat() {
    if(fTradeBoatLoaded) return;
    fTradeBoatLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTradeBoatSpriteData15,
                                 eTradeBoatSpriteData30,
                                 eTradeBoatSpriteData45,
                                 eTradeBoatSpriteData60);
    eSpriteLoader loader(fTileH, "tradeBoat", sds,
                         &eSprMainOffset, fRenderer);

    for(int j = 0; j < 8; j++) {
        fTradeBoat.fSwim.emplace_back(fRenderer);
    }

    for(int i = 10421; i < 10484;) {
        for(int j = 0; j < 8; j++, i += 2) {
            loader.load(10421, i, fTradeBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fTradeBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 10484; i < 10564;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(10421, i, fTradeBoat.fDie[j]);
        }
    }

    for(int i = 10580; i < 10588; i++) {
        loader.load(10421, i, fTradeBoat.fStand);
    }
}

void eCharacterTextures::loadDeer() {
    if(fDeerLoaded) return;
    fDeerLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDeerSpriteData15,
                                 eDeerSpriteData30,
                                 eDeerSpriteData45,
                                 eDeerSpriteData60);
    eSpriteLoader loader(fTileH, "deer", sds,
                         &ePoseidonImpsOffset, fRenderer);
    loader.loadSkipFlipped(531, 531, 627, fDeer.fWalk);
    loader.loadSkipFlipped(531, 635, 859, fDeer.fFight);
    loader.loadSkipFlipped(531, 859, 955, fDeer.fLayDown);

    for(int i = 627; i < 635; i++) {
        loader.load(531, i, fDeer.fDie);
    }
}


void eCharacterTextures::loadGreekRockThrower() {
    if(fGreekRockThrowerLoaded) return;
    fGreekRockThrowerLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGreekRockThrowerSpriteData15,
                                 eGreekRockThrowerSpriteData30,
                                 eGreekRockThrowerSpriteData45,
                                 eGreekRockThrowerSpriteData60);
    eSpriteLoader loader(fTileH, "greekRockThrower", sds,
                         &eZeus_GreekOffset, fRenderer);
    loader.loadSkipFlipped(369, 369, 465, fGreekRockThrower.fWalk);
    loader.loadSkipFlipped(369, 473, 569, fGreekRockThrower.fFight2);
    loader.loadSkipFlipped(369, 569, 633, fGreekRockThrower.fFight);

    for(int i = 465; i < 473; i++) {
        loader.load(369, i, fGreekRockThrower.fDie);
    }
}

void eCharacterTextures::loadGreekHoplite() {
    if(fGreekHopliteLoaded) return;
    fGreekHopliteLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGreekHopliteSpriteData15,
                                 eGreekHopliteSpriteData30,
                                 eGreekHopliteSpriteData45,
                                 eGreekHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "greekHoplite", sds,
                         &eZeus_GreekOffset, fRenderer);
    loader.loadSkipFlipped(1, 1, 97, fGreekHoplite.fWalk);
    loader.loadSkipFlipped(1, 105, 169, fGreekHoplite.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fGreekHoplite.fDie);
    }
}

void eCharacterTextures::loadGreekHorseman() {
    if(fGreekHorsemanLoaded) return;
    fGreekHorsemanLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGreekHorsemanSpriteData15,
                                 eGreekHorsemanSpriteData30,
                                 eGreekHorsemanSpriteData45,
                                 eGreekHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "greekHorseman", sds,
                         &eZeus_GreekOffset, fRenderer);
    loader.loadSkipFlipped(169, 169, 265, fGreekHorseman.fWalk);
    loader.loadSkipFlipped(169, 273, 369, fGreekHorseman.fFight);

    for(int i = 265; i < 273; i++) {
        loader.load(169, i, fGreekHorseman.fDie);
    }
}

void eCharacterTextures::loadDonkey() {
    if(fDonkeyLoaded) return;
    fDonkeyLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDonkeySpriteData15,
                                 eDonkeySpriteData30,
                                 eDonkeySpriteData45,
                                 eDonkeySpriteData60);
    eSpriteLoader loader(fTileH, "donkey", sds,
                         &eSprAmbientOffset, fRenderer);
    loadBasicTexture(fDonkey, 529, loader);
}

void loadBasicTexture(eBasicCharacterTextures& tex,
                      const int start,
                      eTextureClass& texClass) {
    texClass.loadSkipFlipped(tex.fWalk, start, start + 96);

    for(int i = start + 96; i < start + 104; i++) {
        texClass.load(i, tex.fDie);
    }
}

void eCharacterTextures::loadCalydonianBoar() {
    if(fCalydonianBoarLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCalydonianBoarSpriteData15,
                                 eCalydonianBoarSpriteData30,
                                 eCalydonianBoarSpriteData45,
                                 eCalydonianBoarSpriteData60);
    fCalydonianBoarLoaded = true;
    eSpriteLoader loader(fTileH, "calydonianBoar", sds,
                         &eZeus_calydonianboarOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fCalydonianBoar.fWalk);
    loader.loadSkipFlipped(1, 97, 201, fCalydonianBoar.fDie);
    loader.loadSkipFlipped(1, 201, 361, fCalydonianBoar.fFight);
    loader.loadSkipFlipped(1, 361, 457, fCalydonianBoar.fFight2);
}

void eCharacterTextures::loadCerberus() {
    if(fCerberusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCerberusSpriteData15,
                                 eCerberusSpriteData30,
                                 eCerberusSpriteData45,
                                 eCerberusSpriteData60);
    fCerberusLoaded = true;
    eSpriteLoader loader(fTileH, "cerberus", sds,
                         &eZeus_cerberusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fCerberus.fWalk);
    loader.loadSkipFlipped(1, 185, 361, fCerberus.fDie);
    loader.loadSkipFlipped(1, 361, 465, fCerberus.fFight);
    loader.loadSkipFlipped(1, 465, 633, fCerberus.fFight2);
}

void eCharacterTextures::loadChimera() {
    if(fChimeraLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eChimeraSpriteData15,
                                 eChimeraSpriteData30,
                                 eChimeraSpriteData45,
                                 eChimeraSpriteData60);
    fChimeraLoaded = true;
    eSpriteLoader loader(fTileH, "chimera", sds,
                         &ePoseidon_ChimeraOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fChimera.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fChimera.fDie);
    loader.loadSkipFlipped(1, 289, 489, fChimera.fFight);
    loader.loadSkipFlipped(1, 489, 641, fChimera.fFight2);
}

void eCharacterTextures::loadCyclops() {
    if(fCyclopsLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCyclopsSpriteData15,
                                 eCyclopsSpriteData30,
                                 eCyclopsSpriteData45,
                                 eCyclopsSpriteData60);
    fCyclopsLoaded = true;
    eSpriteLoader loader(fTileH, "cyclops", sds,
                         &eZeus_cyclopsOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fCyclops.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fCyclops.fDie);
    loader.loadSkipFlipped(1, 289, 425, fCyclops.fFight);
    loader.loadSkipFlipped(1, 425, 553, fCyclops.fFight2);
}

void eCharacterTextures::loadDragon() {
    if(fDragonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eDragonSpriteData15,
                                 eDragonSpriteData30,
                                 eDragonSpriteData45,
                                 eDragonSpriteData60);
    fDragonLoaded = true;
    eSpriteLoader loader(fTileH, "dragon", sds,
                         &eZeus_dragonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 161, fDragon.fWalk);
    loader.loadSkipFlipped(1, 161,409, fDragon.fDie);
    loader.loadSkipFlipped(1, 409, 553, fDragon.fFight);
    loader.loadSkipFlipped(1, 553, 697, fDragon.fFight2);
}

void eCharacterTextures::loadEchidna() {
    if(fEchidnaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eEchidnaSpriteData15,
                                 eEchidnaSpriteData30,
                                 eEchidnaSpriteData45,
                                 eEchidnaSpriteData60);
    fEchidnaLoaded = true;
    eSpriteLoader loader(fTileH, "echidna", sds,
                         &ePoseidon_EchidnaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 153, fEchidna.fWalk);
    loader.loadSkipFlipped(1, 153, 345, fEchidna.fDie);
    loader.loadSkipFlipped(1, 345, 513, fEchidna.fFight);
    loader.loadSkipFlipped(1, 513, 649, fEchidna.fFight2);
}

void eCharacterTextures::loadHarpie() {
    if(fHarpieLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHarpieSpriteData15,
                                 eHarpieSpriteData30,
                                 eHarpieSpriteData45,
                                 eHarpieSpriteData60);
    fHarpieLoaded = true;
    eSpriteLoader loader(fTileH, "harpie", sds,
                         &ePoseidon_HarpieOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 337, fHarpies.fWalk);
    loader.loadSkipFlipped(1, 337, 617, fHarpies.fDie);
    loader.loadSkipFlipped(1, 617, 769, fHarpies.fFight);
    loader.loadSkipFlipped(1, 769, 929, fHarpies.fFight2);
}

void eCharacterTextures::loadHector() {
    if(fHectorLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHectorSpriteData15,
                                 eHectorSpriteData30,
                                 eHectorSpriteData45,
                                 eHectorSpriteData60);
    fHectorLoaded = true;
    eSpriteLoader loader(fTileH, "hector", sds,
                         &eZeus_hectorOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fHector.fWalk);
    loader.loadSkipFlipped(1, 121, 201, fHector.fDie);
    loader.loadSkipFlipped(1, 201, 329, fHector.fFight);
    loader.loadSkipFlipped(1, 329, 465, fHector.fFight2);
}

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

void eCharacterTextures::loadAchilles() {
    if(fAchillesLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAchillesSpriteData15,
                                 eAchillesSpriteData30,
                                 eAchillesSpriteData45,
                                 eAchillesSpriteData60);
    fAchillesLoaded = true;
    eSpriteLoader loader(fTileH, "achilles", sds,
                         &eZeus_achillesOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 257, fAchilles.fWalk);
    loader.loadSkipFlipped(1, 257, 457, fAchilles.fDie);
    loader.loadSkipFlipped(1, 457, 577, fAchilles.fFight);
}

void eCharacterTextures::loadAtalanta() {
    if(fAtalantaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAtalantaSpriteData15,
                                 eAtalantaSpriteData30,
                                 eAtalantaSpriteData45,
                                 eAtalantaSpriteData60);
    fAtalantaLoaded = true;
    eSpriteLoader loader(fTileH, "atalanta", sds,
                         &ePoseidon_AtalantaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 257, fAtalanta.fWalk);
    loader.loadSkipFlipped(1, 257, 457, fAtalanta.fDie);
    loader.loadSkipFlipped(1, 457, 577, fAtalanta.fFight);
}

void eCharacterTextures::loadBellerophon() {
    if(fBellerophonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eBellerophonSpriteData15,
                                 eBellerophonSpriteData30,
                                 eBellerophonSpriteData45,
                                 eBellerophonSpriteData60);
    fBellerophonLoaded = true;
    eSpriteLoader loader(fTileH, "bellerophon", sds,
                         &ePoseidon_BellerophonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fBellerophon.fWalk);
    loader.loadSkipFlipped(1, 121, 289, fBellerophon.fDie);
    loader.loadSkipFlipped(1, 289, 529, fBellerophon.fFight);
}

void eCharacterTextures::loadHeracles() {
    if(fHeraclesLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHeraclesSpriteData15,
                                 eHeraclesSpriteData30,
                                 eHeraclesSpriteData45,
                                 eHeraclesSpriteData60);
    fHeraclesLoaded = true;
    eSpriteLoader loader(fTileH, "heracles", sds,
                         &eZeus_heraclesOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fHercules.fWalk);
    loader.loadSkipFlipped(1, 185, 345, fHercules.fDie);
    loader.loadSkipFlipped(1, 345, 481, fHercules.fFight);
}

void eCharacterTextures::loadJason() {
    if(fJasonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eJasonSpriteData15,
                                 eJasonSpriteData30,
                                 eJasonSpriteData45,
                                 eJasonSpriteData60);
    fJasonLoaded = true;
    eSpriteLoader loader(fTileH, "jason", sds,
                         &eZeus_jasonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 249, fJason.fWalk);
    loader.loadSkipFlipped(1, 249, 409, fJason.fDie);
    loader.loadSkipFlipped(1, 409, 657, fJason.fFight);
}

void eCharacterTextures::loadOdysseus() {
    if(fOdysseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eOdysseusSpriteData15,
                                 eOdysseusSpriteData30,
                                 eOdysseusSpriteData45,
                                 eOdysseusSpriteData60);
    fOdysseusLoaded = true;
    eSpriteLoader loader(fTileH, "odysseus", sds,
                         &eZeus_odysseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 241, fOdysseus.fWalk);
    loader.loadSkipFlipped(1, 241, 489, fOdysseus.fDie);
    loader.loadSkipFlipped(1, 489, 769, fOdysseus.fFight);
}

void eCharacterTextures::loadPerseus() {
    if(fPerseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 ePerseusSpriteData15,
                                 ePerseusSpriteData30,
                                 ePerseusSpriteData45,
                                 ePerseusSpriteData60);
    fPerseusLoaded = true;
    eSpriteLoader loader(fTileH, "perseus", sds,
                         &eZeus_perseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fPerseus.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fPerseus.fDie);
    loader.loadSkipFlipped(1, 289, 417, fPerseus.fFight);
}

void eCharacterTextures::loadTheseus() {
    if(fTheseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eTheseusSpriteData15,
                                 eTheseusSpriteData30,
                                 eTheseusSpriteData45,
                                 eTheseusSpriteData60);
    fTheseusLoaded = true;
    eSpriteLoader loader(fTileH, "theseus", sds,
                         &eZeus_theseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fTheseus.fWalk);
    loader.loadSkipFlipped(1, 185, 409, fTheseus.fDie);
    loader.loadSkipFlipped(1, 409, 585, fTheseus.fFight);
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

void eCharacterTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    const std::string dir{"../ZeusTextures/" + std::to_string(fTileH) + "/"};

    const std::string pathBase{dir + "SprMain/SprMain_"};

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize("../textures/" + std::to_string(fTileH) + "/characters.ei");
    eTextureClass texClass(pathBase, texLoader, &eSprMainOffset);

//    texClass.loadSkipFlipped(fPeddler.fWalk, 1, 97);

//    for(int i = 97; i < 105; i++) {
//        texClass.load(i, fPeddler.fDie);
//    }

//    texClass.loadSkipFlipped(fActor.fWalk, 105, 201);

//    for(int i = 201; i < 209; i++) {
//        texClass.load(i, fActor.fDie);
//    }

//    texClass.loadSkipFlipped(fOx.fWalk, 209, 305);

//    for(auto& coll : fOx.fWalk) {
//        const int iMax = coll.size();
//        for(int i = 0; i < iMax; i++) {
//            auto& tex = coll.getTexture(i);
//            tex->setOffset(tex->offsetX(),
//                           tex->offsetY() + 4);
//        }
//    }

//    for(int i = 497; i < 505; i++) {
//        texClass.load(i, fOx.fDie);
//    }

//    texClass.loadSkipFlipped(fPorter.fWalk, 1233, 1329);

//    for(int i = 1329; i < 1337; i++) {
//        texClass.load(i, fPorter.fDie);
//    }

//    texClass.loadSkipFlipped(fOxHandler.fWalk, 1337, 1433);

//    for(int i = 1433; i < 1441; i++) {
//        texClass.load(i, fOxHandler.fDie);
//    }

//    const auto loadTrailer =
//            [&](const int i,
//            eTextureCollection& coll,
//            const int dy) {
//        const auto tex = texClass.load(i, coll);

//        tex->setOffset(tex->offsetX(), tex->offsetY() + dy);
//    };

//    for(int i = 2991; i < 2999; i++) {
//        loadTrailer(i, fEmptyTrailer, -7);
//    }
//    for(int i = 2999; i < 3007; i++) {
//        loadTrailer(i, fWoodTrailer1, -7);
//    }
//    for(int i = 3007; i < 3015; i++) {
//        loadTrailer(i, fWoodTrailer2, -7);
//    }
//    for(int i = 3015; i < 3023; i++) {
//        loadTrailer(i, fMarbleTrailer1, -7);
//    }
//    for(int i = 3023; i < 3031; i++) {
//        loadTrailer(i, fMarbleTrailer2, -7);
//    }
//    for(int i = 3031; i < 3039; i++) {
//        loadTrailer(i, fSculptureTrailer, -7);
//    }

//    for(int i = 3039; i < 3047; i++) {
//        loadTrailer(i, fEmptyBigTrailer, -4);
//    }
//    for(int i = 3047; i < 3055; i++) {
//        loadTrailer(i, fMarbleBigTrailer, -4);
//    }

//    texClass.loadSkipFlipped(fSettlers1.fWalk, 505, 601);

//    for(int i = 601; i < 609; i++) {
//        texClass.load(i, fSettlers1.fDie);
//    }


//    texClass.loadSkipFlipped(fSettlers2.fWalk, 1793, 1889);

//    for(int i = 1889; i < 1897; i++) {
//        texClass.load(i, fSettlers2.fDie);
//    }


//    texClass.loadSkipFlipped(fFireFighter.fWalk, 609, 705);
//    texClass.loadSkipFlipped(fFireFighter.fCarry, 705, 801);
//    texClass.loadSkipFlipped(fFireFighter.fPutOut, 809, 1129);

//    for(int i = 801; i < 809; i++) {
//        texClass.load(i, fFireFighter.fDie);
//    }

//    texClass.loadSkipFlipped(fWatchman.fWalk, 2209, 2305);
//    texClass.loadSkipFlipped(fWatchman.fFight, 2313, 2377);

//    for(int i = 2305; i < 2313; i++) {
//        texClass.load(i, fWatchman.fDie);
//    }


//    texClass.loadSkipFlipped(fGoatherd.fWalk, 2377, 2473);
//    texClass.loadSkipFlipped(fGoatherd.fCollect, 2481, 2489);
//    texClass.loadSkipFlipped(fGoatherd.fCarry, 2489, 2585);

//    for(int i = 2473; i < 2481; i++) {
//        texClass.load(i, fGoatherd.fDie);
//    }

//    for(int i = 2585; i < 2595; i++) {
//        texClass.load(i, fGoatherd.fFight);
//    }

//    texClass.loadSkipFlipped(fBronzeMiner.fWalk, 2595, 2691);
//    texClass.loadSkipFlipped(fBronzeMiner.fCarry, 2711, 2807);
//    texClass.loadSkipFlipped(fBronzeMiner.fCollect, 2807, 2887);

//    for(int i = 2691; i < 2699; i++) {
//        texClass.load(i, fBronzeMiner.fDie);
//    }

//    texClass.loadSkipFlipped(fArtisan.fWalk, 1545, 1641);
//    for(int i = 1641; i < 1649; i++) {
//        texClass.load(i, fArtisan.fDie);
//    }
//    texClass.loadSkipFlipped(fArtisan.fBuild, 1649, 1721);
//    texClass.loadSkipFlipped(fArtisan.fBuildStanding, 1721, 1793);

//    loadBasicTexture(fFoodVendor, 2887, texClass);
//    loadBasicTexture(fFleeceVendor, 1897, texClass);
//    loadBasicTexture(fOilVendor, 5297, texClass);
//    loadBasicTexture(fWineVendor, 5401, texClass);
//    loadBasicTexture(fArmsVendor, 2105, texClass);
//    loadBasicTexture(fHorseVendor, 1129, texClass);


//    texClass.loadSkipFlipped(fFleecedSheep.fWalk, 3183, 3279);
//    texClass.loadSkipFlipped(fFleecedSheep.fFight, 3287, 3351);
//    texClass.loadSkipFlipped(fFleecedSheep.fLayDown, 3351, 3415);

//    for(int i = 3279; i < 3287; i++) {
//        texClass.load(i, fFleecedSheep.fDie);
//    }

//    texClass.loadSkipFlipped(fHorse.fWalk, 5001, 5097);

//    for(int i = 5097; i < 5105; i++) {
//        texClass.load(i, fHorse.fDie);
//    }

//    texClass.loadSkipFlipped(fHorse.fStand, 5105, 5297);

//    texClass.loadSkipFlipped(fShepherd.fWalk, 3415, 3511);
//    for(int j = 0; j < 8; j++) {
//        fShepherd.fCollect.emplace_back(fRenderer);
//    }
//    for(int i = 3519; i < 3531; i++) {
//        for(int j = 0; j < 8; j++) {
//            texClass.load(i, fShepherd.fCollect[j]);
//        }
//    }
//    texClass.loadSkipFlipped(fShepherd.fCarry, 3531, 3627);

//    for(int i = 3511; i < 3519; i++) {
//        texClass.load(i, fShepherd.fDie);
//    }

//    for(int i = 3627; i < 3637; i++) {
//        texClass.load(i, fShepherd.fFight);
//    }

//    texClass.loadSkipFlipped(fMarbleMiner.fWalk, 11044, 11140);
//    texClass.loadSkipFlipped(fMarbleMiner.fCollect, 11148, 11228);

//    for(int i = 11140; i < 11148; i++) {
//        texClass.load(i, fMarbleMiner.fDie);
//    }

//    texClass.loadSkipFlipped(fSilverMiner.fWalk, 3741, 3837);
//    texClass.loadSkipFlipped(fSilverMiner.fCarry, 3857, 3953);
//    texClass.loadSkipFlipped(fSilverMiner.fCollect, 3953, 4033);

//    for(int i = 3837; i < 3845; i++) {
//        texClass.load(i, fSilverMiner.fDie);
//    }

//    texClass.loadSkipFlipped(fArcher.fWalk, 4033, 4129);
//    for(int i = 4129; i < 4137; i++) {
//        texClass.load(i, fArcher.fDie);
//    }
//    texClass.loadSkipFlipped(fArcher.fFight, 4137, 4233);
//    texClass.loadSkipFlipped(fArcher.fPatrol, 4233, 4329);

//    texClass.loadSkipFlipped(fLumberjack.fWalk, 4329, 4425);
//    texClass.loadSkipFlipped(fLumberjack.fCollect, 4433, 4529);
//    texClass.loadSkipFlipped(fLumberjack.fCarry, 4529, 4625);

//    for(int i = 4425; i < 4433; i++) {
//        texClass.load(i, fLumberjack.fDie);
//    }


//    loadBasicTexture(fTaxCollector, 4625, texClass);
//    loadBasicTexture(fTransporter, 4729, texClass);



//    texClass.loadSkipFlipped(fGrower.fWalk, 5505, 5601);
//    texClass.loadSkipFlipped(fGrower.fWorkOnGrapes, 5609, 5689);
//    texClass.loadSkipFlipped(fGrower.fWorkOnOlives, 5689, 5769);
//    texClass.loadSkipFlipped(fGrower.fCollectGrapes, 5769, 5849);
//    texClass.loadSkipFlipped(fGrower.fCollectOlives, 5849, 5929);

//    for(int i = 5601; i < 5609; i++) {
//        texClass.load(i, fGrower.fDie);
//    }

//    texClass.loadSkipFlipped(fTrader.fWalk, 5929, 6025);
//    for(int i = 6025; i < 6033; i++) {
//        texClass.load(i, fTrader.fDie);
//    }


//    loadBasicTexture(fWaterDistributor, 6737, texClass);


//    texClass.loadSkipFlipped(fRockThrower.fWalk, 6841, 6937);
//    for(int i = 6937; i < 6945; i++) {
//        texClass.load(i, fRockThrower.fDie);
//    }
//    texClass.loadSkipFlipped(fRockThrower.fFight2, 6945, 7041);
//    texClass.loadSkipFlipped(fRockThrower.fFight, 7041, 7105);


//    texClass.loadSkipFlipped(fHoplite.fWalk, 7105, 7201);
//    for(int i = 7201; i < 7209; i++) {
//        texClass.load(i, fHoplite.fDie);
//    }
//    texClass.loadSkipFlipped(fHoplite.fFight, 7209, 7273);


//    texClass.loadSkipFlipped(fHorseman.fWalk, 7273, 7369);
//    for(int i = 7369; i < 7377; i++) {
//        texClass.load(i, fHorseman.fDie);
//    }
//    texClass.loadSkipFlipped(fHorseman.fFight, 7377, 7473);


//    texClass.loadSkipFlipped(fHealer.fWalk, 7473, 7569);
//    for(int i = 7569; i < 7577; i++) {
//        texClass.load(i, fHealer.fDie);
//    }

//    texClass.loadSkipFlipped(fNudeSheep.fWalk, 7873, 7969);
//    texClass.loadSkipFlipped(fNudeSheep.fFight, 7977, 8041);
//    texClass.loadSkipFlipped(fNudeSheep.fLayDown, 8041, 8105);

//    for(int i = 7969; i < 7977; i++) {
//        texClass.load(i, fNudeSheep.fDie);
//    }


//    for(int i = 8428; i < 8436; i++) {
//        texClass.load(i, fEmptyCart);
//    }

//    texClass.loadSkipFlipped(fUrchinCart, 8436, 8460);
//    texClass.loadSkipFlipped(fFishCart, 8460, 8484);
//    texClass.loadSkipFlipped(fMeatCart, 8484, 8508);
//    texClass.loadSkipFlipped(fCheeseCart, 8508, 8532);
//    texClass.loadSkipFlipped(fCarrotsCart, 8532, 8556);
//    texClass.loadSkipFlipped(fOnionsCart, 8556, 8580);
//    texClass.loadSkipFlipped(fWheatCart, 8580, 8604);

//    texClass.loadSkipFlipped(fBronzeCart, 8604, 8620);
//    texClass.loadSkipFlipped(fGrapesCart, 8620, 8644);
//    texClass.loadSkipFlipped(fOlivesCart, 8644, 8668);
//    texClass.loadSkipFlipped(fFleeceCart, 8668, 8684);
//    texClass.loadSkipFlipped(fArmorCart, 8684, 8700);
//    texClass.loadSkipFlipped(fOliveOilCart, 8700, 8716);
//    texClass.loadSkipFlipped(fWineCart, 8716, 8732);


//    texClass.loadSkipFlipped(fBoar.fWalk, 10124, 10220);
//    texClass.loadSkipFlipped(fBoar.fFight, 10228, 10356);
//    texClass.loadSkipFlipped(fBoar.fLayDown, 10356, 10420);
//    for(int i = 10220; i < 10228; i++) {
//        texClass.load(i, fBoar.fDie);
//    }

//    loadBasicTexture(fGymnast, 10588, texClass);

//    texClass.loadSkipFlipped(fGoat.fWalk, 11228, 11324);
//    texClass.loadSkipFlipped(fGoat.fFight, 11332, 11460);
//    texClass.loadSkipFlipped(fGoat.fLayDown, 11460, 11524);

//    for(int i = 11324; i < 11332; i++) {
//        texClass.load(i, fGoat.fDie);
//    }

//    texClass.loadSkipFlipped(fWolf.fWalk, 11524, 11620);
//    texClass.loadSkipFlipped(fWolf.fFight, 11628, 11756);
//    texClass.loadSkipFlipped(fWolf.fLayDown, 11756, 11820);

//    for(int i = 11620; i < 11628; i++) {
//        texClass.load(i, fWolf.fDie);
//    }

//    texClass.loadSkipFlipped(fHunter.fWalk, 11820, 11916);
//    texClass.loadSkipFlipped(fHunter.fCollect, 11924, 12019);
//    texClass.loadSkipFlipped(fHunter.fCarry, 12032, 12128);

//    for(int i = 11916; i < 11924; i++) {
//        texClass.load(i, fHunter.fDie);
//    }

//    loadBasicTexture(fPhilosopher, 12128, texClass);

//    for(int j = 0; j < 8; j++) {
//        fFishingBoat.fSwim.emplace_back(fRenderer);
//    }

//    for(int i = 10797; i < 10860;) {
//        for(int j = 0; j < 8; j++, i += 2) {
//            texClass.load(i, fFishingBoat.fSwim[j]);
//        }
//    }

//    for(int j = 0; j < 8; j++) {
//        fFishingBoat.fCollect.emplace_back(fRenderer);
//        fFishingBoat.fDie.emplace_back(fRenderer);
//    }

//    for(int i = 10860; i < 10940;) {
//        for(int j = 0; j < 8; j++, i++) {
//            texClass.load(i, fFishingBoat.fCollect[j]);
//        }
//    }

//    for(int i = 10940; i < 10948; i++) {
//        texClass.load(i, fFishingBoat.fStand);
//    }

//    for(int i = 10948; i < 11036;) {
//        for(int j = 0; j < 8; j++, i++) {
//            texClass.load(i, fFishingBoat.fDie[j]);
//        }
//    }


//    for(int j = 0; j < 8; j++) {
//        fTradeBoat.fSwim.emplace_back(fRenderer);
//    }

//    for(int i = 10421; i < 10484;) {
//        for(int j = 0; j < 8; j++, i += 2) {
//            texClass.load(i, fTradeBoat.fSwim[j]);
//        }
//    }

//    for(int j = 0; j < 8; j++) {
//        fTradeBoat.fDie.emplace_back(fRenderer);
//    }

//    for(int i = 10484; i < 10564;) {
//        for(int j = 0; j < 8; j++, i++) {
//            texClass.load(i, fTradeBoat.fDie[j]);
//        }
//    }

//    for(int i = 10580; i < 10588; i++) {
//        texClass.load(i, fTradeBoat.fStand);
//    }

//    {
//        const std::string pathBase{dir + "PoseidonImps/PoseidonImps_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidonImpsOffset);


//        texClass.loadSkipFlipped(fDeerHunter.fWalk, 183, 279);
//        texClass.loadSkipFlipped(fDeerHunter.fCollect, 287, 407);
//        texClass.loadSkipFlipped(fDeerHunter.fCarry, 435, 531);

//        for(int i = 279; i < 287; i++) {
//            texClass.load(i, fDeerHunter.fDie);
//        }

//        texClass.loadSkipFlipped(fDeer.fWalk, 531, 627);
//        texClass.loadSkipFlipped(fDeer.fFight, 635, 859);
//        texClass.loadSkipFlipped(fDeer.fLayDown, 859, 955);

//        for(int i = 627; i < 635; i++) {
//            texClass.load(i, fDeer.fDie);
//        }

//        texClass.loadSkipFlipped(fOrangesCart, 1091, 1115);

//        texClass.loadSkipFlipped(fOrangeTender.fWalk, 1211, 1307);
//        texClass.loadSkipFlipped(fOrangeTender.fWorkOnTree, 1315, 1411);
//        texClass.loadSkipFlipped(fOrangeTender.fCollect, 1411, 1507);

//        for(int i = 1307; i < 1315; i++) {
//            texClass.load(i, fOrangeTender.fDie);
//        }
//    }

//    {
//        const std::string pathBase{dir + "Zeus_Greek/Zeus_Greek_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_GreekOffset);


//        texClass.loadSkipFlipped(fGreekHoplite.fWalk, 1, 97);
//        for(int i = 97; i < 105; i++) {
//            texClass.load(i, fGreekHoplite.fDie);
//        }
//        texClass.loadSkipFlipped(fGreekHoplite.fFight, 105, 169);


//        texClass.loadSkipFlipped(fGreekHorseman.fWalk, 169, 265);
//        for(int i = 265; i < 273; i++) {
//            texClass.load(i, fGreekHorseman.fDie);
//        }
//        texClass.loadSkipFlipped(fGreekHorseman.fFight, 273, 369);


//        texClass.loadSkipFlipped(fGreekRockThrower.fWalk, 369, 465);
//        for(int i = 465; i < 473; i++) {
//            texClass.load(i, fGreekRockThrower.fDie);
//        }
//        texClass.loadSkipFlipped(fGreekRockThrower.fFight2, 473, 569);
//        texClass.loadSkipFlipped(fGreekRockThrower.fFight, 569, 633);
//    }

    {
        const std::string pathBase{dir + "Zeus_Added/SprMain_"};
        for(int j = 0; j < 8; j++) {
            fFoodCart.emplace_back(fRenderer);
        }
        for(int i = 8428; i < 8436;) {
            for(int j = 0; j < 8; j++, i++) {
                const auto r = eTextureLoadingHelpers::loadTexWithOffset(
                            pathBase, i, fFoodCart[j], eSprMainOffset);
                r->setOffset(r->offsetX(), r->offsetY() + 10);
            }
        }
    }

//    {
//        const std::string pathBase{dir + "SprAmbient/SprAmbient_"};

//        eTextureClass texClass(pathBase, texLoader, &eSprAmbientOffset);

//        texClass.loadSkipFlipped(fDonkey.fWalk, 529, 625);
//        for(int i = 625; i < 633; i++) {
//            texClass.load(i, fDonkey.fDie);
//        }
//    }

    {
        const std::string pathBase{dir + "Zeus_General/Zeus_Banners_"};

        for(int i = 1; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBannerRod);
        }

        int ban = 0;
        for(int i = 43; i < 204;) {
            fBanners.emplace_back(fRenderer);
            auto& bani = fBanners[ban++];
            for(int j = 0; j < 7; j++, i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, bani);
            }
        }

        for(int i = 204; i < 207; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBannerTops);
        }
    }

//    {
//        const std::string pathBase{dir + "zeus_calydonianboar/zeus_calydonianboar_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_calydonianboarOffset);

//        texClass.loadSkipFlipped(fCalydonianBoar.fWalk, 1, 97);
//        texClass.loadSkipFlipped(fCalydonianBoar.fDie, 97, 201);
//        texClass.loadSkipFlipped(fCalydonianBoar.fFight, 201, 361);
//        texClass.loadSkipFlipped(fCalydonianBoar.fFight2, 361, 457);
//    }

//    {
//        const std::string pathBase{dir + "zeus_cerberus/zeus_cerberus_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_cerberusOffset);

//        texClass.loadSkipFlipped(fCerberus.fWalk, 1, 185);
//        texClass.loadSkipFlipped(fCerberus.fDie, 185, 361);
//        texClass.loadSkipFlipped(fCerberus.fFight, 361, 465);
//        texClass.loadSkipFlipped(fCerberus.fFight2, 465, 633);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Chimera/Poseidon_Chimera_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_ChimeraOffset);

//        texClass.loadSkipFlipped(fChimera.fWalk, 1, 129);
//        texClass.loadSkipFlipped(fChimera.fDie, 129, 289);
//        texClass.loadSkipFlipped(fChimera.fFight, 289, 489);
//        texClass.loadSkipFlipped(fChimera.fFight2, 489, 641);
//    }

//    {
//        const std::string pathBase{dir + "zeus_cyclops/zeus_cyclops_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_cyclopsOffset);

//        texClass.loadSkipFlipped(fCyclops.fWalk, 1, 129);
//        texClass.loadSkipFlipped(fCyclops.fDie, 129, 289);
//        texClass.loadSkipFlipped(fCyclops.fFight, 289, 425);
//        texClass.loadSkipFlipped(fCyclops.fFight2, 425, 553);
//    }

//    {
//        const std::string pathBase{dir + "zeus_dragon/zeus_dragon_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_dragonOffset);

//        texClass.loadSkipFlipped(fDragon.fWalk, 1, 161);
//        texClass.loadSkipFlipped(fDragon.fDie, 161, 409);
//        texClass.loadSkipFlipped(fDragon.fFight, 409, 553);
//        texClass.loadSkipFlipped(fDragon.fFight2, 553, 697);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Echidna/Poseidon_Echidna_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_EchidnaOffset);

//        texClass.loadSkipFlipped(fEchidna.fWalk, 1, 153);
//        texClass.loadSkipFlipped(fEchidna.fDie, 153, 345);
//        texClass.loadSkipFlipped(fEchidna.fFight, 345, 513);
//        texClass.loadSkipFlipped(fEchidna.fFight2, 513, 649);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Harpie/Poseidon_Harpie_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_HarpieOffset);

//        texClass.loadSkipFlipped(fHarpies.fWalk, 1, 337);
//        texClass.loadSkipFlipped(fHarpies.fDie, 337, 617);
//        texClass.loadSkipFlipped(fHarpies.fFight, 617, 769);
//        texClass.loadSkipFlipped(fHarpies.fFight2, 769, 929);
//    }

//    {
//        const std::string pathBase{dir + "zeus_hector/zeus_hector_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_hectorOffset);

//        texClass.loadSkipFlipped(fHector.fWalk, 1, 121);
//        texClass.loadSkipFlipped(fHector.fDie, 121, 201);
//        texClass.loadSkipFlipped(fHector.fFight, 201, 329);
//        texClass.loadSkipFlipped(fHector.fFight2, 329, 465);
//    }

//    {
//        const std::string pathBase{dir + "zeus_hydra/zeus_hydra_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_hydraOffset);

//        texClass.loadSkipFlipped(fHydra.fWalk, 1, 121);
//        texClass.loadSkipFlipped(fHydra.fDie, 121, 289);
//        texClass.loadSkipFlipped(fHydra.fFight, 289, 473);
//        texClass.loadSkipFlipped(fHydra.fFight2, 473, 609);
//    }

//    {
//        const std::string pathBase{dir + "zeus_kraken/zeus_kraken_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_krakenOffset);

//        texClass.loadSkipFlipped(fKraken.fWalk, 1, 169);
//        for(int i = 169; i < 200; i++) {
//            texClass.load(i, fKraken.fDie);
//        }
//        texClass.loadSkipFlipped(fKraken.fFight, 200, 488);
//        texClass.loadSkipFlipped(fKraken.fFight2, 488, 728);
//    }

//    {
//        const std::string pathBase{dir + "zeus_maenads/zeus_maenads_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_maenadsOffset);

//        texClass.loadSkipFlipped(fMaenads.fWalk, 1, 129);
//        texClass.loadSkipFlipped(fMaenads.fDie, 129, 289);
//        texClass.loadSkipFlipped(fMaenads.fFight, 289, 457);
//        texClass.loadSkipFlipped(fMaenads.fFight2, 457, 561);
//    }

//    {
//        const std::string pathBase{dir + "zeus_medusa/zeus_medusa_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_medusaOffset);

//        texClass.loadSkipFlipped(fMedusa.fWalk, 1, 129);
//        texClass.loadSkipFlipped(fMedusa.fDie, 129, 273);
//        texClass.loadSkipFlipped(fMedusa.fFight, 273, 409);
//        texClass.loadSkipFlipped(fMedusa.fFight2, 409, 545);
//    }

//    {
//        const std::string pathBase{dir + "zeus_minotaur/zeus_minotaur_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_minotaurOffset);

//        texClass.loadSkipFlipped(fMinotaur.fWalk, 1, 161);
//        texClass.loadSkipFlipped(fMinotaur.fDie, 161, 321);
//        texClass.loadSkipFlipped(fMinotaur.fFight, 321, 481);
//        texClass.loadSkipFlipped(fMinotaur.fFight2, 481, 641);
//    }

//    {
//        const std::string pathBase{dir + "zeus_scylla/zeus_scylla_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_scyllaOffset);

//        texClass.loadSkipFlipped(fScylla.fWalk, 1, 161);
//        for(int i = 161; i < 192; i++) {
//            texClass.load(i, fScylla.fDie);
//        }
//        texClass.loadSkipFlipped(fScylla.fFight, 192, 432);
//        texClass.loadSkipFlipped(fScylla.fFight2, 432, 680);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Sphinx/Poseidon_Sphinx_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_SphinxOffset);

//        texClass.loadSkipFlipped(fSphinx.fWalk, 1, 137);
//        texClass.loadSkipFlipped(fSphinx.fDie, 137, 321);
//        texClass.loadSkipFlipped(fSphinx.fFight, 321, 529);
//        texClass.loadSkipFlipped(fSphinx.fFight2, 529, 793);
//    }

//    {
//        const std::string pathBase{dir + "zeus_talos/zeus_talos_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_talosOffset);

//        texClass.loadSkipFlipped(fTalos.fWalk, 1, 153);
//        texClass.loadSkipFlipped(fTalos.fDie, 153, 273);
//        texClass.loadSkipFlipped(fTalos.fFight, 273, 393);
//        texClass.loadSkipFlipped(fTalos.fFight2, 393, 545);
//    }

//    {
//        const std::string pathBase{dir + "zeus_achilles/zeus_achilles_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_achillesOffset);

//        texClass.loadSkipFlipped(fAchilles.fWalk, 1, 257);
//        texClass.loadSkipFlipped(fAchilles.fDie, 257, 457);
//        texClass.loadSkipFlipped(fAchilles.fFight, 457, 577);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Atalanta/Poseidon_Atalanta_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_AtalantaOffset);

//        texClass.loadSkipFlipped(fAtalanta.fWalk, 1, 161);
//        texClass.loadSkipFlipped(fAtalanta.fDie, 161, 329);
//        texClass.loadSkipFlipped(fAtalanta.fFight, 329, 473);
//    }

//    {
//        const std::string pathBase{dir + "Poseidon_Bellerophon/Poseidon_Bellerophon_"};

//        eTextureClass texClass(pathBase, texLoader, &ePoseidon_BellerophonOffset);

//        texClass.loadSkipFlipped(fBellerophon.fWalk, 1, 121);
//        texClass.loadSkipFlipped(fBellerophon.fDie, 121, 289);
//        texClass.loadSkipFlipped(fBellerophon.fFight, 289, 529);
//    }

//    {
//        const std::string pathBase{dir + "zeus_heracles/zeus_heracles_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_heraclesOffset);

//        texClass.loadSkipFlipped(fHercules.fWalk, 1, 185);
//        texClass.loadSkipFlipped(fHercules.fDie, 185, 345);
//        texClass.loadSkipFlipped(fHercules.fFight, 345, 481);
//    }

//    {
//        const std::string pathBase{dir + "zeus_jason/zeus_jason_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_jasonOffset);

//        texClass.loadSkipFlipped(fJason.fWalk, 1, 249);
//        texClass.loadSkipFlipped(fJason.fDie, 249, 409);
//        texClass.loadSkipFlipped(fJason.fFight, 409, 657);
//    }

//    {
//        const std::string pathBase{dir + "zeus_odysseus/zeus_odysseus_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_odysseusOffset);

//        texClass.loadSkipFlipped(fOdysseus.fWalk, 1, 241);
//        texClass.loadSkipFlipped(fOdysseus.fDie, 241, 489);
//        texClass.loadSkipFlipped(fOdysseus.fFight, 489, 769);
//    }

//    {
//        const std::string pathBase{dir + "zeus_perseus/zeus_perseus_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_perseusOffset);

//        texClass.loadSkipFlipped(fPerseus.fWalk, 1, 129);
//        texClass.loadSkipFlipped(fPerseus.fDie, 129, 289);
//        texClass.loadSkipFlipped(fPerseus.fFight, 289, 417);
//    }

//    {
//        const std::string pathBase{dir + "zeus_theseus/zeus_theseus_"};

//        eTextureClass texClass(pathBase, texLoader, &eZeus_theseusOffset);

//        texClass.loadSkipFlipped(fTheseus.fWalk, 1, 185);
//        texClass.loadSkipFlipped(fTheseus.fDie, 185, 409);
//        texClass.loadSkipFlipped(fTheseus.fFight, 409, 585);
//    }


    texLoader.waitUntilFinished();
}
