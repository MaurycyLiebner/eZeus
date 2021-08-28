#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"
#include "offsets/PoseidonImps.h"

eCharacterTextures::eCharacterTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
//    fFoodDistributor(renderer),
    fActor(renderer),
    fTaxCollector(renderer),
    fWaterDistributor(renderer),
    fWatchman(renderer),
    fFireFighter(renderer),
    fHealer(renderer),
    fGymnast(renderer),
    fPhilosopher(renderer),

    fSilverMiner(renderer),
    fBronzeMiner(renderer),
    fLumberjack(renderer),

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

    fSettlers1(renderer),
    fSettlers2(renderer),

    fTransporter(renderer),

    fEmptyCart(renderer) {

}

void loadBasicTexture(eBasicCharacterTextures& tex,
                      SDL_Renderer* const renderer,
                      const std::string& pathBase,
                      const int start) {
    for(int j = 0; j < 8; j++) {
        tex.fWalk.emplace_back(renderer);
    }
    for(int i = start; i < start + 96;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = tex.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = start + 96; i < start + 104; i++) {
        auto& die = tex.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
}

void eCharacterTextures::load() {
    const std::string dir{"../ZeusTextures/" + std::to_string(fTileH) + "/"};

    const std::string pathBase{dir + "SprMain/SprMain_"};

//    for(int j = 0; j < 8; j++) {
//        fFoodDistributor.fWalk.emplace_back(fRenderer);
//    }
//    for(int i = 1; i < 97;) {
//        for(int j = 0; j < 8; j++, i++) {
//            auto& walk = fFoodDistributor.fWalk;
//            eTextureLoadingHelpers::loadTexWithOffset(
//                        pathBase, i, walk[j], eSprMainOffset);
//        }
//    }
//    for(int i = 97; i < 105; i++) {
//        auto& die = fFoodDistributor.fDie;
//        eTextureLoadingHelpers::loadTexWithOffset(
//                    pathBase, i, die, eSprMainOffset);
//    }


    for(int j = 0; j < 8; j++) {
        fActor.fWalk.emplace_back(fRenderer);
    }
    for(int i = 105; i < 201;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fActor.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 201; i < 209; i++) {
        auto& die = fActor.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }

    for(int j = 0; j < 8; j++) {
        fSettlers1.fWalk.emplace_back(fRenderer);
    }
    for(int i = 505; i < 601;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fSettlers1.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 601; i < 609; i++) {
        auto& die = fSettlers1.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }


    for(int j = 0; j < 8; j++) {
        fSettlers2.fWalk.emplace_back(fRenderer);
    }
    for(int i = 1793; i < 1889;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fSettlers2.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 1889; i < 1897; i++) {
        auto& die = fSettlers2.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }



    for(int j = 0; j < 8; j++) {
        fFireFighter.fWalk.emplace_back(fRenderer);
        fFireFighter.fCarry.emplace_back(fRenderer);
        fFireFighter.fPutOut.emplace_back(fRenderer);
    }
    for(int i = 609; i < 705;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fFireFighter.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 705; i < 801;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fFireFighter.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 801; i < 809; i++) {
        auto& die = fFireFighter.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 809; i < 1129;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fFireFighter.fPutOut;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fWatchman.fWalk.emplace_back(fRenderer);
        fWatchman.fFight.emplace_back(fRenderer);
    }
    for(int i = 2209; i < 2305;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fWatchman.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 2305; i < 2313; i++) {
        auto& die = fWatchman.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 2312; i < 2377;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fWatchman.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fGoatherd.fWalk.emplace_back(fRenderer);
        fGoatherd.fCollect.emplace_back(fRenderer);
        fGoatherd.fCarry.emplace_back(fRenderer);
    }
    for(int i = 2377; i < 2473;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fGoatherd.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 2473; i < 2481; i++) {
        auto& die = fGoatherd.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 2489; i < 2585;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fGoatherd.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }
    for(int i = 2481; i < 2489; i++) {
        for(int j = 0; j < 8; j++) {
            auto& collect = fGoatherd.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fBronzeMiner.fWalk.emplace_back(fRenderer);
        fBronzeMiner.fCollect.emplace_back(fRenderer);
        fBronzeMiner.fCarry.emplace_back(fRenderer);
    }
    for(int i = 2595; i < 2691;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fBronzeMiner.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 2691; i < 2699; i++) {
        auto& die = fBronzeMiner.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 2711; i < 2807;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fBronzeMiner.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }
    for(int i = 2807; i < 2887;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fBronzeMiner.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }


    loadBasicTexture(fFoodVendor, fRenderer, pathBase, 2887);
    loadBasicTexture(fFleeceVendor, fRenderer, pathBase, 1897);
    loadBasicTexture(fOilVendor, fRenderer, pathBase, 5297);
    loadBasicTexture(fWineVendor, fRenderer, pathBase, 5401);
    loadBasicTexture(fArmsVendor, fRenderer, pathBase, 2105);
    loadBasicTexture(fHorseVendor, fRenderer, pathBase, 1129);

    for(int j = 0; j < 8; j++) {
        fFleecedSheep.fWalk.emplace_back(fRenderer);
        fFleecedSheep.fFight.emplace_back(fRenderer);
        fFleecedSheep.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 3183; i < 3279;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fFleecedSheep.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 3279; i < 3287; i++) {
        auto& die = fFleecedSheep.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 3287; i < 3351;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fFleecedSheep.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }
    for(int i = 3351; i < 3415;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fFleecedSheep.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, lay[j], eSprMainOffset);
        }
    }



    for(int j = 0; j < 8; j++) {
        fShepherd.fWalk.emplace_back(fRenderer);
        fShepherd.fCollect.emplace_back(fRenderer);
        fShepherd.fCarry.emplace_back(fRenderer);
    }
    for(int i = 3415; i < 3511;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fShepherd.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 3511; i < 3519; i++) {
        auto& die = fShepherd.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 3531; i < 3627;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fShepherd.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }
    for(int i = 3519; i < 3531;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fShepherd.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }



    for(int j = 0; j < 8; j++) {
        fSilverMiner.fWalk.emplace_back(fRenderer);
        fSilverMiner.fCollect.emplace_back(fRenderer);
        fSilverMiner.fCarry.emplace_back(fRenderer);
    }
    for(int i = 3741; i < 3837;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fSilverMiner.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 3837; i < 3845; i++) {
        auto& die = fSilverMiner.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 3857; i < 3953;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fSilverMiner.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }
    for(int i = 3953; i < 4033;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fSilverMiner.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }



    for(int j = 0; j < 8; j++) {
        fLumberjack.fWalk.emplace_back(fRenderer);
        fLumberjack.fCollect.emplace_back(fRenderer);
        fLumberjack.fCarry.emplace_back(fRenderer);
    }
    for(int i = 4329; i < 4425;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fLumberjack.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 4425; i < 4433; i++) {
        auto& die = fLumberjack.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 4433; i < 4529;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fLumberjack.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }
    for(int i = 4529; i < 4625;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fLumberjack.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }


    loadBasicTexture(fTaxCollector, fRenderer, pathBase, 4625);
    loadBasicTexture(fTransporter, fRenderer, pathBase, 4729);



    for(int j = 0; j < 8; j++) {
        fGrower.fWalk.emplace_back(fRenderer);
        fGrower.fWorkOnGrapes.emplace_back(fRenderer);
        fGrower.fWorkOnOlives.emplace_back(fRenderer);
        fGrower.fCollectGrapes.emplace_back(fRenderer);
        fGrower.fCollectOlives.emplace_back(fRenderer);
    }
    for(int i = 5505; i < 5601;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fGrower.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 5601; i < 5609; i++) {
        auto& die = fGrower.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 5609; i < 5689;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fGrower.fWorkOnGrapes;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }
    for(int i = 5689; i < 5769;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fGrower.fWorkOnOlives;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }
    for(int i = 5769; i < 5849;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fGrower.fCollectGrapes;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }
    for(int i = 5849; i < 5929;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fGrower.fCollectOlives;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }


    loadBasicTexture(fWaterDistributor, fRenderer, pathBase, 6737);


    for(int j = 0; j < 8; j++) {
        fHealer.fWalk.emplace_back(fRenderer);
    }
    for(int i = 7473; i < 7569;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fHealer.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 7569; i < 7577; i++) {
        auto& die = fHealer.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }



    for(int j = 0; j < 8; j++) {
        fNudeSheep.fWalk.emplace_back(fRenderer);
        fNudeSheep.fFight.emplace_back(fRenderer);
        fNudeSheep.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 7873; i < 7969;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fNudeSheep.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 7969; i < 7977; i++) {
        auto& die = fNudeSheep.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 7977; i < 8041;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fNudeSheep.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }
    for(int i = 8041; i < 8105;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fNudeSheep.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, lay[j], eSprMainOffset);
        }
    }


    for(int i = 8428; i < 8436; i++) {
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, fEmptyCart, eSprMainOffset);
    }

    for(int j = 0; j < 8; j++) {
        fUrchinCart.emplace_back(fRenderer);
    }
    for(int i = 8436; i < 8460;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fUrchinCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFishCart.emplace_back(fRenderer);
    }
    for(int i = 8460; i < 8484;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fFishCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fMeatCart.emplace_back(fRenderer);
    }
    for(int i = 8484; i < 8508;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fMeatCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fCheeseCart.emplace_back(fRenderer);
    }
    for(int i = 8508; i < 8532;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fCheeseCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fCarrotsCart.emplace_back(fRenderer);
    }
    for(int i = 8532; i < 8556;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fCarrotsCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOnionsCart.emplace_back(fRenderer);
    }
    for(int i = 8556; i < 8580;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fOnionsCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fWheatCart.emplace_back(fRenderer);
    }
    for(int i = 8580; i < 8604;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWheatCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fBronzeCart.emplace_back(fRenderer);
    }
    for(int i = 8604; i < 8620;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fBronzeCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fGrapesCart.emplace_back(fRenderer);
    }
    for(int i = 8620; i < 8644;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fGrapesCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOlivesCart.emplace_back(fRenderer);
    }
    for(int i = 8644; i < 8668;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fOlivesCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFleeceCart.emplace_back(fRenderer);
    }
    for(int i = 8668; i < 8684;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fFleeceCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fArmorCart.emplace_back(fRenderer);
    }
    for(int i = 8684; i < 8700;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fArmorCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOliveOilCart.emplace_back(fRenderer);
    }
    for(int i = 8700; i < 8716;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fOliveOilCart[j], eSprMainOffset);
        }
    }

    for(int j = 0; j < 8; j++) {
        fWineCart.emplace_back(fRenderer);
    }
    for(int i = 8716; i < 8732;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWineCart[j], eSprMainOffset);
        }
    }



    for(int j = 0; j < 8; j++) {
        fBoar.fWalk.emplace_back(fRenderer);
        fBoar.fFight.emplace_back(fRenderer);
        fBoar.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 10124; i < 10220;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fBoar.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 10220; i < 10228; i++) {
        auto& die = fBoar.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 10228; i < 10356;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fBoar.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }
    for(int i = 10356; i < 10420;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fBoar.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, lay[j], eSprMainOffset);
        }
    }

    loadBasicTexture(fGymnast, fRenderer, pathBase, 10588);


    for(int j = 0; j < 8; j++) {
        fGoat.fWalk.emplace_back(fRenderer);
        fGoat.fFight.emplace_back(fRenderer);
        fGoat.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 11228; i < 11324;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fGoat.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 11324; i < 11332; i++) {
        auto& die = fGoat.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 11332; i < 11460;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fGoat.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }
    for(int i = 11460; i < 11524;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fGoat.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, lay[j], eSprMainOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fWolf.fWalk.emplace_back(fRenderer);
        fWolf.fFight.emplace_back(fRenderer);
        fWolf.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 11524; i < 11620;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fWolf.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 11620; i < 11628; i++) {
        auto& die = fWolf.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 11628; i < 11756;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fWolf.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
        }
    }
    for(int i = 11756; i < 11820;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fWolf.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, lay[j], eSprMainOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fHunter.fWalk.emplace_back(fRenderer);
        fHunter.fCollect.emplace_back(fRenderer);
        fHunter.fCarry.emplace_back(fRenderer);
    }
    for(int i = 11820; i < 11916;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fHunter.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 11916; i < 11924; i++) {
        auto& die = fHunter.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
    for(int i = 11924; i < 12019;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fHunter.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, collect[j], eSprMainOffset);
        }
    }
    for(int i = 12032; i < 12128;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fHunter.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, carry[j], eSprMainOffset);
        }
    }


    loadBasicTexture(fPhilosopher, fRenderer, pathBase, 12128);


    const std::string ppathBase{dir + "PoseidonImps/PoseidonImps_"};

    for(int j = 0; j < 8; j++) {
        fDeerHunter.fWalk.emplace_back(fRenderer);
        fDeerHunter.fCollect.emplace_back(fRenderer);
        fDeerHunter.fCarry.emplace_back(fRenderer);
    }
    for(int i = 183; i < 279;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fDeerHunter.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, walk[j], ePoseidonImpsOffset);
        }
    }
    for(int i = 279; i < 287; i++) {
        auto& die = fDeerHunter.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    ppathBase, i, die, ePoseidonImpsOffset);
    }
    for(int i = 287; i < 407;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& collect = fDeerHunter.fCollect;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, collect[j], ePoseidonImpsOffset);
        }
    }
    for(int i = 435; i < 531;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& carry = fDeerHunter.fCarry;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, carry[j], ePoseidonImpsOffset);
        }
    }


    for(int j = 0; j < 8; j++) {
        fDeer.fWalk.emplace_back(fRenderer);
        fDeer.fFight.emplace_back(fRenderer);
        fDeer.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 531; i < 627;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fDeer.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, walk[j], ePoseidonImpsOffset);
        }
    }
    for(int i = 627; i < 635; i++) {
        auto& die = fDeer.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    ppathBase, i, die, ePoseidonImpsOffset);
    }
    for(int i = 635; i < 859;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fDeer.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, fight[j], ePoseidonImpsOffset);
        }
    }
    for(int i = 859; i < 955;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& lay = fDeer.fLayDown;
            eTextureLoadingHelpers::loadTexWithOffset(
                        ppathBase, i, lay[j], ePoseidonImpsOffset);
        }
    }
}
