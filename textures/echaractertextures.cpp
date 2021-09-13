#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"
#include "offsets/PoseidonImps.h"

#include "etextureloader.h"

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

    fEmptyCart(renderer),

    fOrangeTender(renderer) {

}

void loadBasicTexture(eBasicCharacterTextures& tex,
                      SDL_Renderer* const renderer,
                      const int start,
                      eTextureClass& texClass) {
    for(int j = 0; j < 8; j++) {
        tex.fWalk.emplace_back(renderer);
    }
    for(int i = start; i < start + 96;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, tex.fWalk[j]);
        }
    }
    for(int i = start + 96; i < start + 104; i++) {
        texClass.load(i, tex.fDie);
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

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();
    eTextureClass texClass(pathBase, texLoader, &eSprMainOffset);

    for(int j = 0; j < 8; j++) {
        fActor.fWalk.emplace_back(fRenderer);
    }
    for(int i = 105; i < 201;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fActor.fWalk[j]);
        }
    }
    for(int i = 201; i < 209; i++) {
        texClass.load(i, fActor.fDie);
    }

    for(int j = 0; j < 8; j++) {
        fSettlers1.fWalk.emplace_back(fRenderer);
    }
    for(int i = 505; i < 601;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fSettlers1.fWalk[j]);
        }
    }
    for(int i = 601; i < 609; i++) {
        texClass.load(i, fSettlers1.fDie);
    }


    for(int j = 0; j < 8; j++) {
        fSettlers2.fWalk.emplace_back(fRenderer);
    }
    for(int i = 1793; i < 1889;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fSettlers2.fWalk[j]);
        }
    }
    for(int i = 1889; i < 1897; i++) {
        texClass.load(i, fSettlers2.fDie);
    }



    for(int j = 0; j < 8; j++) {
        fFireFighter.fWalk.emplace_back(fRenderer);
        fFireFighter.fCarry.emplace_back(fRenderer);
        fFireFighter.fPutOut.emplace_back(fRenderer);
    }
    for(int i = 609; i < 705;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFireFighter.fWalk[j]);
        }
    }
    for(int i = 705; i < 801;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFireFighter.fCarry[j]);
        }
    }
    for(int i = 801; i < 809; i++) {
        texClass.load(i, fFireFighter.fDie);
    }
    for(int i = 809; i < 1129;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFireFighter.fPutOut[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fWatchman.fWalk.emplace_back(fRenderer);
        fWatchman.fFight.emplace_back(fRenderer);
    }
    for(int i = 2209; i < 2305;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWatchman.fWalk[j]);
        }
    }
    for(int i = 2305; i < 2313; i++) {
        texClass.load(i, fWatchman.fDie);
    }
    for(int i = 2312; i < 2377;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWatchman.fFight[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fGoatherd.fWalk.emplace_back(fRenderer);
        fGoatherd.fCollect.emplace_back(fRenderer);
        fGoatherd.fCarry.emplace_back(fRenderer);
    }
    for(int i = 2377; i < 2473;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGoatherd.fWalk[j]);
        }
    }
    for(int i = 2473; i < 2481; i++) {
        texClass.load(i, fGoatherd.fDie);
    }
    for(int i = 2489; i < 2585;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGoatherd.fCarry[j]);
        }
    }
    for(int i = 2481; i < 2489; i++) {
        for(int j = 0; j < 8; j++) {
            texClass.load(i, fGoatherd.fCollect[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fBronzeMiner.fWalk.emplace_back(fRenderer);
        fBronzeMiner.fCollect.emplace_back(fRenderer);
        fBronzeMiner.fCarry.emplace_back(fRenderer);
    }
    for(int i = 2595; i < 2691;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBronzeMiner.fWalk[j]);
        }
    }
    for(int i = 2691; i < 2699; i++) {
        texClass.load(i, fBronzeMiner.fDie);
    }
    for(int i = 2711; i < 2807;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBronzeMiner.fCarry[j]);
        }
    }
    for(int i = 2807; i < 2887;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBronzeMiner.fCollect[j]);
        }
    }


    loadBasicTexture(fFoodVendor, fRenderer, 2887, texClass);
    loadBasicTexture(fFleeceVendor, fRenderer, 1897, texClass);
    loadBasicTexture(fOilVendor, fRenderer, 5297, texClass);
    loadBasicTexture(fWineVendor, fRenderer, 5401, texClass);
    loadBasicTexture(fArmsVendor, fRenderer, 2105, texClass);
    loadBasicTexture(fHorseVendor, fRenderer, 1129, texClass);

    for(int j = 0; j < 8; j++) {
        fFleecedSheep.fWalk.emplace_back(fRenderer);
        fFleecedSheep.fFight.emplace_back(fRenderer);
        fFleecedSheep.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 3183; i < 3279;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFleecedSheep.fWalk[j]);
        }
    }
    for(int i = 3279; i < 3287; i++) {
        texClass.load(i, fFleecedSheep.fDie);
    }
    for(int i = 3287; i < 3351;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFleecedSheep.fFight[j]);
        }
    }
    for(int i = 3351; i < 3415;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFleecedSheep.fLayDown[j]);
        }
    }



    for(int j = 0; j < 8; j++) {
        fShepherd.fWalk.emplace_back(fRenderer);
        fShepherd.fCollect.emplace_back(fRenderer);
        fShepherd.fCarry.emplace_back(fRenderer);
    }
    for(int i = 3415; i < 3511;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fShepherd.fWalk[j]);
        }
    }
    for(int i = 3511; i < 3519; i++) {
        texClass.load(i, fShepherd.fDie);
    }
    for(int i = 3531; i < 3627;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fShepherd.fCarry[j]);
        }
    }
    for(int i = 3519; i < 3531; i++) {
        for(int j = 0; j < 8; j++) {
            texClass.load(i, fShepherd.fCollect[j]);
        }
    }



    for(int j = 0; j < 8; j++) {
        fSilverMiner.fWalk.emplace_back(fRenderer);
        fSilverMiner.fCollect.emplace_back(fRenderer);
        fSilverMiner.fCarry.emplace_back(fRenderer);
    }
    for(int i = 3741; i < 3837;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fSilverMiner.fWalk[j]);
        }
    }
    for(int i = 3837; i < 3845; i++) {
        texClass.load(i, fSilverMiner.fDie);
    }
    for(int i = 3857; i < 3953;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fSilverMiner.fCarry[j]);
        }
    }
    for(int i = 3953; i < 4033;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fSilverMiner.fCollect[j]);
        }
    }



    for(int j = 0; j < 8; j++) {
        fLumberjack.fWalk.emplace_back(fRenderer);
        fLumberjack.fCollect.emplace_back(fRenderer);
        fLumberjack.fCarry.emplace_back(fRenderer);
    }
    for(int i = 4329; i < 4425;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fLumberjack.fWalk[j]);
        }
    }
    for(int i = 4425; i < 4433; i++) {
        texClass.load(i, fLumberjack.fDie);
    }
    for(int i = 4433; i < 4529;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fLumberjack.fCollect[j]);
        }
    }
    for(int i = 4529; i < 4625;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fLumberjack.fCarry[j]);
        }
    }


    loadBasicTexture(fTaxCollector, fRenderer, 4625, texClass);
    loadBasicTexture(fTransporter, fRenderer, 4729, texClass);



    for(int j = 0; j < 8; j++) {
        fGrower.fWalk.emplace_back(fRenderer);
        fGrower.fWorkOnGrapes.emplace_back(fRenderer);
        fGrower.fWorkOnOlives.emplace_back(fRenderer);
        fGrower.fCollectGrapes.emplace_back(fRenderer);
        fGrower.fCollectOlives.emplace_back(fRenderer);
    }
    for(int i = 5505; i < 5601;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrower.fWalk[j]);
        }
    }
    for(int i = 5601; i < 5609; i++) {
        texClass.load(i, fGrower.fDie);
    }
    for(int i = 5609; i < 5689;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrower.fWorkOnGrapes[j]);
        }
    }
    for(int i = 5689; i < 5769;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrower.fWorkOnOlives[j]);
        }
    }
    for(int i = 5769; i < 5849;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrower.fCollectGrapes[j]);
        }
    }
    for(int i = 5849; i < 5929;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrower.fCollectOlives[j]);
        }
    }


    loadBasicTexture(fWaterDistributor, fRenderer, 6737, texClass);


    for(int j = 0; j < 8; j++) {
        fHealer.fWalk.emplace_back(fRenderer);
    }
    for(int i = 7473; i < 7569;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fHealer.fWalk[j]);
        }
    }
    for(int i = 7569; i < 7577; i++) {
        texClass.load(i, fHealer.fDie);
    }



    for(int j = 0; j < 8; j++) {
        fNudeSheep.fWalk.emplace_back(fRenderer);
        fNudeSheep.fFight.emplace_back(fRenderer);
        fNudeSheep.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 7873; i < 7969;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fNudeSheep.fWalk[j]);
        }
    }
    for(int i = 7969; i < 7977; i++) {
        texClass.load(i, fNudeSheep.fDie);
    }
    for(int i = 7977; i < 8041;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fNudeSheep.fFight[j]);
        }
    }
    for(int i = 8041; i < 8105;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fNudeSheep.fLayDown[j]);
        }
    }


    for(int i = 8428; i < 8436; i++) {
        texClass.load(i, fEmptyCart);
    }

    for(int j = 0; j < 8; j++) {
        fUrchinCart.emplace_back(fRenderer);
    }
    for(int i = 8436; i < 8460;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fUrchinCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFishCart.emplace_back(fRenderer);
    }
    for(int i = 8460; i < 8484;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFishCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fMeatCart.emplace_back(fRenderer);
    }
    for(int i = 8484; i < 8508;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fMeatCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fCheeseCart.emplace_back(fRenderer);
    }
    for(int i = 8508; i < 8532;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fCheeseCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fCarrotsCart.emplace_back(fRenderer);
    }
    for(int i = 8532; i < 8556;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fCarrotsCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOnionsCart.emplace_back(fRenderer);
    }
    for(int i = 8556; i < 8580;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fOnionsCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fWheatCart.emplace_back(fRenderer);
    }
    for(int i = 8580; i < 8604;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWheatCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fBronzeCart.emplace_back(fRenderer);
    }
    for(int i = 8604; i < 8620;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBronzeCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fGrapesCart.emplace_back(fRenderer);
    }
    for(int i = 8620; i < 8644;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGrapesCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOlivesCart.emplace_back(fRenderer);
    }
    for(int i = 8644; i < 8668;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fOlivesCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFleeceCart.emplace_back(fRenderer);
    }
    for(int i = 8668; i < 8684;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFleeceCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fArmorCart.emplace_back(fRenderer);
    }
    for(int i = 8684; i < 8700;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fArmorCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOliveOilCart.emplace_back(fRenderer);
    }
    for(int i = 8700; i < 8716;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fOliveOilCart[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fWineCart.emplace_back(fRenderer);
    }
    for(int i = 8716; i < 8732;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWineCart[j]);
        }
    }



    for(int j = 0; j < 8; j++) {
        fBoar.fWalk.emplace_back(fRenderer);
        fBoar.fFight.emplace_back(fRenderer);
        fBoar.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 10124; i < 10220;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBoar.fWalk[j]);
        }
    }
    for(int i = 10220; i < 10228; i++) {
        texClass.load(i, fBoar.fDie);
    }
    for(int i = 10228; i < 10356;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBoar.fFight[j]);
        }
    }
    for(int i = 10356; i < 10420;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBoar.fLayDown[j]);
        }
    }

    loadBasicTexture(fGymnast, fRenderer, 10588, texClass);


    for(int j = 0; j < 8; j++) {
        fGoat.fWalk.emplace_back(fRenderer);
        fGoat.fFight.emplace_back(fRenderer);
        fGoat.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 11228; i < 11324;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGoat.fWalk[j]);
        }
    }
    for(int i = 11324; i < 11332; i++) {
        texClass.load(i, fGoat.fDie);
    }
    for(int i = 11332; i < 11460;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGoat.fFight[j]);
        }
    }
    for(int i = 11460; i < 11524;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fGoat.fLayDown[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fWolf.fWalk.emplace_back(fRenderer);
        fWolf.fFight.emplace_back(fRenderer);
        fWolf.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 11524; i < 11620;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWolf.fWalk[j]);
        }
    }
    for(int i = 11620; i < 11628; i++) {
        texClass.load(i, fWolf.fDie);
    }
    for(int i = 11628; i < 11756;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWolf.fFight[j]);
        }
    }
    for(int i = 11756; i < 11820;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWolf.fLayDown[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fHunter.fWalk.emplace_back(fRenderer);
        fHunter.fCollect.emplace_back(fRenderer);
        fHunter.fCarry.emplace_back(fRenderer);
    }
    for(int i = 11820; i < 11916;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fHunter.fWalk[j]);
        }
    }
    for(int i = 11916; i < 11924; i++) {
        texClass.load(i, fHunter.fDie);
    }
    for(int i = 11924; i < 12019;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fHunter.fCollect[j]);
        }
    }
    for(int i = 12032; i < 12128;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fHunter.fCarry[j]);
        }
    }

    loadBasicTexture(fPhilosopher, fRenderer, 12128, texClass);


    const std::string ppathBase{dir + "PoseidonImps/PoseidonImps_"};

    eTextureClass ptexClass(ppathBase, texLoader, &ePoseidonImpsOffset);

    for(int j = 0; j < 8; j++) {
        fDeerHunter.fWalk.emplace_back(fRenderer);
        fDeerHunter.fCollect.emplace_back(fRenderer);
        fDeerHunter.fCarry.emplace_back(fRenderer);
    }
    for(int i = 183; i < 279;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeerHunter.fWalk[j]);
        }
    }
    for(int i = 279; i < 287; i++) {
        ptexClass.load(i, fDeerHunter.fDie);
    }
    for(int i = 287; i < 407;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeerHunter.fCollect[j]);
        }
    }
    for(int i = 435; i < 531;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeerHunter.fCarry[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fDeer.fWalk.emplace_back(fRenderer);
        fDeer.fFight.emplace_back(fRenderer);
        fDeer.fLayDown.emplace_back(fRenderer);
    }
    for(int i = 531; i < 627;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeer.fWalk[j]);
        }
    }
    for(int i = 627; i < 635; i++) {
        ptexClass.load(i, fDeer.fDie);
    }
    for(int i = 635; i < 859;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeer.fFight[j]);
        }
    }
    for(int i = 859; i < 955;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fDeer.fLayDown[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fOrangesCart.emplace_back(fRenderer);
    }
    for(int i = 1091; i < 1115;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fOrangesCart[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fOrangeTender.fWalk.emplace_back(fRenderer);
        fOrangeTender.fWorkOnTree.emplace_back(fRenderer);
        fOrangeTender.fCollect.emplace_back(fRenderer);
    }
    for(int i = 1211; i < 1307;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fOrangeTender.fWalk[j]);
        }
    }
    for(int i = 1307; i < 1315; i++) {
        ptexClass.load(i, fOrangeTender.fDie);
    }
    for(int i = 1315; i < 1411;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fOrangeTender.fWorkOnTree[j]);
        }
    }
    for(int i = 1411; i < 1507;) {
        for(int j = 0; j < 8; j++, i++) {
            ptexClass.load(i, fOrangeTender.fCollect[j]);
        }
    }

    texLoader.waitUntilFinished();

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
}
