#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/SprMain.h"
#include "offsets/Zeus_Greek.h"
#include "offsets/SprAmbient.h"

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

#include "spriteData/competitor15.h"
#include "spriteData/competitor30.h"
#include "spriteData/competitor45.h"
#include "spriteData/competitor60.h"

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

#include "spriteData/urchinGatherer15.h"
#include "spriteData/urchinGatherer30.h"
#include "spriteData/urchinGatherer45.h"
#include "spriteData/urchinGatherer60.h"

#include "spriteData/tradeBoat15.h"
#include "spriteData/tradeBoat30.h"
#include "spriteData/tradeBoat45.h"
#include "spriteData/tradeBoat60.h"

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

#include "spriteData/banners15.h"
#include "spriteData/banners30.h"
#include "spriteData/banners45.h"
#include "spriteData/banners60.h"

#include "spriteData/poseidonBannerTops15.h"
#include "spriteData/poseidonBannerTops30.h"
#include "spriteData/poseidonBannerTops45.h"
#include "spriteData/poseidonBannerTops60.h"

#include "espriteloader.h"

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
    fCompetitor(renderer),
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

    fCattle1(renderer),
    fCattle2(renderer),
    fCattle3(renderer),
    fBull(renderer),
    fButcher(renderer),

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
    fPoseidonTowerArcher(renderer),

    fRockThrower(renderer),
    fHoplite(renderer),
    fHorseman(renderer),

    fHoplitePoseidon(renderer),
    fArcherPoseidon(renderer),

    fGreekRockThrower(renderer),
    fGreekHoplite(renderer),
    fGreekHorseman(renderer),

    fAmazonSpear(renderer),
    fAmazonArcher(renderer),

    fTrojanHoplite(renderer),
    fTrojanSpearthrower(renderer),
    fTrojanHorseman(renderer),

    fCentaurHorseman(renderer),
    fCentaurArcher(renderer),

    fEgyptianHoplite(renderer),
    fEgyptianArcher(renderer),

    fMayanHoplite(renderer),
    fMayanArcher(renderer),

    fPhoenicianHorseman(renderer),
    fPhoenicianArcher(renderer),

    fOceanidHoplite(renderer),
    fOceanidSpearthrower(renderer),

    fPersianHoplite(renderer),
    fPersianHorseman(renderer),
    fPersianArcher(renderer),

    fAtlanteanHoplite(renderer),
    fAtlanteanArcher(renderer),

    fBannerRod(renderer),
    fBannerTops(renderer),
    fPoseidonBannerTops(renderer),

    fTrader(renderer),
    fDonkey(renderer),

    fPorter(renderer),

    fFishingBoat(renderer),
    fUrchinGatherer(renderer),

    fTradeBoat(renderer),
    fTrireme(renderer),
    fEnemyBoat(renderer),

    fDisgruntled(renderer),
    fSick(renderer),
    fHomeless(renderer),

    fKraken(renderer),
    fScylla(renderer),

    fScholar(renderer),
    fAstronomer(renderer),
    fInventor(renderer),
    fCurator(renderer),

    fChariotVendor(renderer),

    fElephant(renderer),

    fEliteCitizen(renderer) {

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
    for(int i = 2481; i < 2489; i++) {
        loader.load(2377, i, fGoatherd.fCollect);
    }
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
    for(int i = 3519; i < 3531; i++) {
        loader.load(3415, i, fShepherd.fCollect);
    }
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
    loadOrangeTender();
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
    loadOrangesCart();
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

void eCharacterTextures::loadCompetitor() {
    if(fCompetitorLoaded) return;
    fCompetitorLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eCompetitorSpriteData15,
                                 eCompetitorSpriteData30,
                                 eCompetitorSpriteData45,
                                 eCompetitorSpriteData60);
    eSpriteLoader loader(fTileH, "competitor", sds,
                         &eSprMainOffset, fRenderer);
    loadBasicTexture(fCompetitor, 10692, loader);
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
    loadDeerHunter();
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

void eCharacterTextures::loadUrchinGatherer() {
    if(fUrchinGathererLoaded) return;
    fUrchinGathererLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eUrchinGathererSpriteData15,
                                 eUrchinGathererSpriteData30,
                                 eUrchinGathererSpriteData45,
                                 eUrchinGathererSpriteData60);
    eSpriteLoader loader(fTileH, "urchinGatherer", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(9508, 9508, 9604, fUrchinGatherer.fSwim);
    loader.loadSkipFlipped(9508, 9604, 9924, fUrchinGatherer.fCollect);
    loader.loadSkipFlipped(9508, 9924, 10020, fUrchinGatherer.fCarry);
    loader.loadSkipFlipped(9508, 10020, 10116, fUrchinGatherer.fDeposit);
    for(int i = 10116; i < 10124; i++) {
        loader.load(9508, i, fUrchinGatherer.fDie);
    }
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
            loader.load(10420, i, fTradeBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fTradeBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 10484; i < 10580;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(10420, i, fTradeBoat.fDie[j]);
        }
    }

    for(int i = 10580; i < 10588; i++) {
        loader.load(10420, i, fTradeBoat.fStand);
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

void eCharacterTextures::loadBanners() {
    if(fBannersLoaded) return;
    fBannersLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eBannersSpriteData15,
                                     eBannersSpriteData30,
                                     eBannersSpriteData45,
                                     eBannersSpriteData60);
        eSpriteLoader loader(fTileH, "banners", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 22; i++) {
            loader.load(1, i, fBannerRod);
        }

        int ban = 0;
        for(int i = 43; i < 204;) {
            fBanners.emplace_back(fRenderer);
            auto& bani = fBanners[ban++];
            for(int j = 0; j < 7; j++, i++) {
                loader.load(1, i, bani);
            }
        }

        for(int i = 204; i < 207; i++) {
            loader.load(1, i, fBannerTops);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonBannerTopsSpriteData15,
                                     ePoseidonBannerTopsSpriteData30,
                                     ePoseidonBannerTopsSpriteData45,
                                     ePoseidonBannerTopsSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonBannerTops", sds,
                             nullptr, fRenderer);

        for(int i = 44; i < 47; i++) {
            loader.load(44, i, fPoseidonBannerTops);
        }
    }
}
