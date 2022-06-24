#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"
#include "offsets/PoseidonImps.h"
#include "offsets/Zeus_Greek.h"
#include "offsets/SprAmbient.h"

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

    fTradeBoat(renderer) {

}

void loadBasicTexture(eBasicCharacterTextures& tex,
                      const int start,
                      eTextureClass& texClass) {
    texClass.loadSkipFlipped(tex.fWalk, start, start + 96);

    for(int i = start + 96; i < start + 104; i++) {
        texClass.load(i, tex.fDie);
    }
}

void eCharacterTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    const std::string dir{"../ZeusTextures/" + std::to_string(fTileH) + "/"};

    const std::string pathBase{dir + "SprMain/SprMain_"};

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();
    eTextureClass texClass(pathBase, texLoader, &eSprMainOffset);

    texClass.loadSkipFlipped(fPeddler.fWalk, 1, 97);

    for(int i = 97; i < 105; i++) {
        texClass.load(i, fPeddler.fDie);
    }

    texClass.loadSkipFlipped(fActor.fWalk, 105, 201);

    for(int i = 201; i < 209; i++) {
        texClass.load(i, fActor.fDie);
    }

    texClass.loadSkipFlipped(fOx.fWalk, 209, 305);

    for(auto& coll : fOx.fWalk) {
        const int iMax = coll.size();
        for(int i = 0; i < iMax; i++) {
            auto& tex = coll.getTexture(i);
            tex->setOffset(tex->offsetX(),
                           tex->offsetY() + 4);
        }
    }

    for(int i = 497; i < 505; i++) {
        texClass.load(i, fOx.fDie);
    }

    texClass.loadSkipFlipped(fPorter.fWalk, 1233, 1329);

    for(int i = 1329; i < 1337; i++) {
        texClass.load(i, fPorter.fDie);
    }

    texClass.loadSkipFlipped(fOxHandler.fWalk, 1337, 1433);

    for(int i = 1433; i < 1441; i++) {
        texClass.load(i, fOxHandler.fDie);
    }

    const auto loadTrailer =
            [&](const int i,
            eTextureCollection& coll,
            const int dy) {
        const auto tex = texClass.load(i, coll);

        tex->setOffset(tex->offsetX(), tex->offsetY() + dy);
    };

    for(int i = 2991; i < 2999; i++) {
        loadTrailer(i, fEmptyTrailer, -7);
    }
    for(int i = 2999; i < 3007; i++) {
        loadTrailer(i, fWoodTrailer1, -7);
    }
    for(int i = 3007; i < 3015; i++) {
        loadTrailer(i, fWoodTrailer2, -7);
    }
    for(int i = 3015; i < 3023; i++) {
        loadTrailer(i, fMarbleTrailer1, -7);
    }
    for(int i = 3023; i < 3031; i++) {
        loadTrailer(i, fMarbleTrailer2, -7);
    }
    for(int i = 3031; i < 3039; i++) {
        loadTrailer(i, fSculptureTrailer, -7);
    }

    for(int i = 3039; i < 3047; i++) {
        loadTrailer(i, fEmptyBigTrailer, -4);
    }
    for(int i = 3047; i < 3055; i++) {
        loadTrailer(i, fMarbleBigTrailer, -4);
    }

    texClass.loadSkipFlipped(fSettlers1.fWalk, 505, 601);

    for(int i = 601; i < 609; i++) {
        texClass.load(i, fSettlers1.fDie);
    }


    texClass.loadSkipFlipped(fSettlers2.fWalk, 1793, 1889);

    for(int i = 1889; i < 1897; i++) {
        texClass.load(i, fSettlers2.fDie);
    }


    texClass.loadSkipFlipped(fFireFighter.fWalk, 609, 705);
    texClass.loadSkipFlipped(fFireFighter.fCarry, 705, 801);
    texClass.loadSkipFlipped(fFireFighter.fPutOut, 809, 1129);

    for(int i = 801; i < 809; i++) {
        texClass.load(i, fFireFighter.fDie);
    }

    texClass.loadSkipFlipped(fWatchman.fWalk, 2209, 2305);
    texClass.loadSkipFlipped(fWatchman.fFight, 2313, 2377);

    for(int i = 2305; i < 2313; i++) {
        texClass.load(i, fWatchman.fDie);
    }


    texClass.loadSkipFlipped(fGoatherd.fWalk, 2377, 2473);
    texClass.loadSkipFlipped(fGoatherd.fCollect, 2481, 2489);
    texClass.loadSkipFlipped(fGoatherd.fCarry, 2489, 2585);

    for(int i = 2473; i < 2481; i++) {
        texClass.load(i, fGoatherd.fDie);
    }

    for(int i = 2585; i < 2595; i++) {
        texClass.load(i, fGoatherd.fFight);
    }

    texClass.loadSkipFlipped(fBronzeMiner.fWalk, 2595, 2691);
    texClass.loadSkipFlipped(fBronzeMiner.fCarry, 2711, 2807);
    texClass.loadSkipFlipped(fBronzeMiner.fCollect, 2807, 2887);

    for(int i = 2691; i < 2699; i++) {
        texClass.load(i, fBronzeMiner.fDie);
    }

    texClass.loadSkipFlipped(fArtisan.fWalk, 1545, 1641);
    for(int i = 1641; i < 1649; i++) {
        texClass.load(i, fArtisan.fDie);
    }
    texClass.loadSkipFlipped(fArtisan.fBuild, 1649, 1721);
    texClass.loadSkipFlipped(fArtisan.fBuildStanding, 1721, 1793);

    loadBasicTexture(fFoodVendor, 2887, texClass);
    loadBasicTexture(fFleeceVendor, 1897, texClass);
    loadBasicTexture(fOilVendor, 5297, texClass);
    loadBasicTexture(fWineVendor, 5401, texClass);
    loadBasicTexture(fArmsVendor, 2105, texClass);
    loadBasicTexture(fHorseVendor, 1129, texClass);


    texClass.loadSkipFlipped(fFleecedSheep.fWalk, 3183, 3279);
    texClass.loadSkipFlipped(fFleecedSheep.fFight, 3287, 3351);
    texClass.loadSkipFlipped(fFleecedSheep.fLayDown, 3351, 3415);

    for(int i = 3279; i < 3287; i++) {
        texClass.load(i, fFleecedSheep.fDie);
    }

    texClass.loadSkipFlipped(fShepherd.fWalk, 3415, 3511);
    for(int j = 0; j < 8; j++) {
        fShepherd.fCollect.emplace_back(fRenderer);
    }
    for(int i = 3519; i < 3531; i++) {
        for(int j = 0; j < 8; j++) {
            texClass.load(i, fShepherd.fCollect[j]);
        }
    }
    texClass.loadSkipFlipped(fShepherd.fCarry, 3531, 3627);

    for(int i = 3511; i < 3519; i++) {
        texClass.load(i, fShepherd.fDie);
    }

    for(int i = 3627; i < 3637; i++) {
        texClass.load(i, fShepherd.fFight);
    }

    texClass.loadSkipFlipped(fMarbleMiner.fWalk, 11044, 11140);
    texClass.loadSkipFlipped(fMarbleMiner.fCollect, 11148, 11228);

    for(int i = 11140; i < 11148; i++) {
        texClass.load(i, fMarbleMiner.fDie);
    }

    texClass.loadSkipFlipped(fSilverMiner.fWalk, 3741, 3837);
    texClass.loadSkipFlipped(fSilverMiner.fCarry, 3857, 3953);
    texClass.loadSkipFlipped(fSilverMiner.fCollect, 3953, 4033);

    for(int i = 3837; i < 3845; i++) {
        texClass.load(i, fSilverMiner.fDie);
    }

    texClass.loadSkipFlipped(fArcher.fWalk, 4033, 4129);
    for(int i = 4129; i < 4137; i++) {
        texClass.load(i, fArcher.fDie);
    }
    texClass.loadSkipFlipped(fArcher.fFight, 4137, 4233);
    texClass.loadSkipFlipped(fArcher.fPatrol, 4233, 4329);

    texClass.loadSkipFlipped(fLumberjack.fWalk, 4329, 4425);
    texClass.loadSkipFlipped(fLumberjack.fCollect, 4433, 4529);
    texClass.loadSkipFlipped(fLumberjack.fCarry, 4529, 4625);

    for(int i = 4425; i < 4433; i++) {
        texClass.load(i, fLumberjack.fDie);
    }


    loadBasicTexture(fTaxCollector, 4625, texClass);
    loadBasicTexture(fTransporter, 4729, texClass);



    texClass.loadSkipFlipped(fGrower.fWalk, 5505, 5601);
    texClass.loadSkipFlipped(fGrower.fWorkOnGrapes, 5609, 5689);
    texClass.loadSkipFlipped(fGrower.fWorkOnOlives, 5689, 5769);
    texClass.loadSkipFlipped(fGrower.fCollectGrapes, 5769, 5849);
    texClass.loadSkipFlipped(fGrower.fCollectOlives, 5849, 5929);

    for(int i = 5601; i < 5609; i++) {
        texClass.load(i, fGrower.fDie);
    }

    texClass.loadSkipFlipped(fTrader.fWalk, 5929, 6025);
    for(int i = 6025; i < 6033; i++) {
        texClass.load(i, fTrader.fDie);
    }


    loadBasicTexture(fWaterDistributor, 6737, texClass);


    texClass.loadSkipFlipped(fRockThrower.fWalk, 6841, 6937);
    for(int i = 6937; i < 6945; i++) {
        texClass.load(i, fRockThrower.fDie);
    }
    texClass.loadSkipFlipped(fRockThrower.fFight2, 6945, 7041);
    texClass.loadSkipFlipped(fRockThrower.fFight, 7041, 7105);


    texClass.loadSkipFlipped(fHoplite.fWalk, 7105, 7201);
    for(int i = 7201; i < 7209; i++) {
        texClass.load(i, fHoplite.fDie);
    }
    texClass.loadSkipFlipped(fHoplite.fFight, 7209, 7273);


    texClass.loadSkipFlipped(fHorseman.fWalk, 7273, 7369);
    for(int i = 7369; i < 7377; i++) {
        texClass.load(i, fHorseman.fDie);
    }
    texClass.loadSkipFlipped(fHorseman.fFight, 7377, 7473);


    texClass.loadSkipFlipped(fHealer.fWalk, 7473, 7569);
    for(int i = 7569; i < 7577; i++) {
        texClass.load(i, fHealer.fDie);
    }

    texClass.loadSkipFlipped(fNudeSheep.fWalk, 7873, 7969);
    texClass.loadSkipFlipped(fNudeSheep.fFight, 7977, 8041);
    texClass.loadSkipFlipped(fNudeSheep.fLayDown, 8041, 8105);

    for(int i = 7969; i < 7977; i++) {
        texClass.load(i, fNudeSheep.fDie);
    }


    for(int i = 8428; i < 8436; i++) {
        texClass.load(i, fEmptyCart);
    }

    texClass.loadSkipFlipped(fUrchinCart, 8436, 8460);
    texClass.loadSkipFlipped(fFishCart, 8460, 8484);
    texClass.loadSkipFlipped(fMeatCart, 8484, 8508);
    texClass.loadSkipFlipped(fCheeseCart, 8508, 8532);
    texClass.loadSkipFlipped(fCarrotsCart, 8532, 8556);
    texClass.loadSkipFlipped(fOnionsCart, 8556, 8580);
    texClass.loadSkipFlipped(fWheatCart, 8580, 8604);

    texClass.loadSkipFlipped(fBronzeCart, 8604, 8620);
    texClass.loadSkipFlipped(fGrapesCart, 8620, 8644);
    texClass.loadSkipFlipped(fOlivesCart, 8644, 8668);
    texClass.loadSkipFlipped(fFleeceCart, 8668, 8684);
    texClass.loadSkipFlipped(fArmorCart, 8684, 8700);
    texClass.loadSkipFlipped(fOliveOilCart, 8700, 8716);
    texClass.loadSkipFlipped(fWineCart, 8716, 8732);


    texClass.loadSkipFlipped(fBoar.fWalk, 10124, 10220);
    texClass.loadSkipFlipped(fBoar.fFight, 10228, 10356);
    texClass.loadSkipFlipped(fBoar.fLayDown, 10356, 10420);

    loadBasicTexture(fGymnast, 10588, texClass);

    texClass.loadSkipFlipped(fGoat.fWalk, 11228, 11324);
    texClass.loadSkipFlipped(fGoat.fFight, 11332, 11460);
    texClass.loadSkipFlipped(fGoat.fLayDown, 11460, 11524);

    for(int i = 11324; i < 11332; i++) {
        texClass.load(i, fGoat.fDie);
    }

    texClass.loadSkipFlipped(fWolf.fWalk, 11524, 11620);
    texClass.loadSkipFlipped(fWolf.fFight, 11628, 11756);
    texClass.loadSkipFlipped(fWolf.fLayDown, 11756, 11820);

    for(int i = 11620; i < 11628; i++) {
        texClass.load(i, fWolf.fDie);
    }

    texClass.loadSkipFlipped(fHunter.fWalk, 11820, 11916);
    texClass.loadSkipFlipped(fHunter.fCollect, 11924, 12019);
    texClass.loadSkipFlipped(fHunter.fCarry, 12032, 12128);

    for(int i = 11916; i < 11924; i++) {
        texClass.load(i, fHunter.fDie);
    }

    loadBasicTexture(fPhilosopher, 12128, texClass);

    for(int j = 0; j < 8; j++) {
        fFishingBoat.fSwim.emplace_back(fRenderer);
    }

    for(int i = 10797; i < 10860;) {
        for(int j = 0; j < 8; j++, i += 2) {
            texClass.load(i, fFishingBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fFishingBoat.fCollect.emplace_back(fRenderer);
        fFishingBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 10860; i < 10940;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFishingBoat.fCollect[j]);
        }
    }

    for(int i = 10940; i < 10948; i++) {
        texClass.load(i, fFishingBoat.fStand);
    }

    for(int i = 10948; i < 11036;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFishingBoat.fDie[j]);
        }
    }


    for(int j = 0; j < 8; j++) {
        fTradeBoat.fSwim.emplace_back(fRenderer);
    }

    for(int i = 10420; i < 10484;) {
        for(int j = 0; j < 8; j++, i += 2) {
            texClass.load(i, fTradeBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fTradeBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 10484; i < 10564;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fTradeBoat.fDie[j]);
        }
    }

    for(int i = 10580; i < 10588; i++) {
        texClass.load(i, fTradeBoat.fStand);
    }

    {
        const std::string pathBase{dir + "PoseidonImps/PoseidonImps_"};

        eTextureClass texClass(pathBase, texLoader, &ePoseidonImpsOffset);


        texClass.loadSkipFlipped(fDeerHunter.fWalk, 183, 279);
        texClass.loadSkipFlipped(fDeerHunter.fCollect, 287, 407);
        texClass.loadSkipFlipped(fDeerHunter.fCarry, 435, 531);

        for(int i = 279; i < 287; i++) {
            texClass.load(i, fDeerHunter.fDie);
        }

        texClass.loadSkipFlipped(fDeer.fWalk, 531, 627);
        texClass.loadSkipFlipped(fDeer.fFight, 635, 859);
        texClass.loadSkipFlipped(fDeer.fLayDown, 859, 955);

        for(int i = 627; i < 635; i++) {
            texClass.load(i, fDeer.fDie);
        }

        texClass.loadSkipFlipped(fOrangesCart, 1091, 1115);

        texClass.loadSkipFlipped(fOrangeTender.fWalk, 1211, 1307);
        texClass.loadSkipFlipped(fOrangeTender.fWorkOnTree, 1315, 1411);
        texClass.loadSkipFlipped(fOrangeTender.fCollect, 1411, 1507);

        for(int i = 1307; i < 1315; i++) {
            texClass.load(i, fOrangeTender.fDie);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Greek/Zeus_Greek_"};

        eTextureClass texClass(pathBase, texLoader, &eZeus_GreekOffset);


        texClass.loadSkipFlipped(fGreekHoplite.fWalk, 1, 97);
        for(int i = 97; i < 105; i++) {
            texClass.load(i, fGreekHoplite.fDie);
        }
        texClass.loadSkipFlipped(fGreekHoplite.fFight, 105, 169);


        texClass.loadSkipFlipped(fGreekHorseman.fWalk, 169, 265);
        for(int i = 265; i < 273; i++) {
            texClass.load(i, fGreekHorseman.fDie);
        }
        texClass.loadSkipFlipped(fGreekHorseman.fFight, 273, 369);


        texClass.loadSkipFlipped(fGreekRockThrower.fWalk, 369, 465);
        for(int i = 465; i < 473; i++) {
            texClass.load(i, fGreekRockThrower.fDie);
        }
        texClass.loadSkipFlipped(fGreekRockThrower.fFight2, 473, 569);
        texClass.loadSkipFlipped(fGreekRockThrower.fFight, 569, 633);
    }

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

        fSelected = std::make_shared<eTexture>();
        fSelected->load(fRenderer, pathBase + "08436.png");
    }

    {
        const std::string pathBase{dir + "SprAmbient/SprAmbient_"};

        eTextureClass texClass(pathBase, texLoader, &eSprAmbientOffset);

        texClass.loadSkipFlipped(fDonkey.fWalk, 529, 625);
        for(int i = 625; i < 633; i++) {
            texClass.load(i, fDonkey.fDie);
        }
    }

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

    texLoader.waitUntilFinished();
}
