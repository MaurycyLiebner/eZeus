#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"

eCharacterTextures::eCharacterTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fFoodDistributor(renderer),
    fActor(renderer),
    fTaxCollector(renderer),
    fWaterDistributor(renderer),
    fWatchman(renderer),
    fHealer(renderer),
    fGymnast(renderer),
    fPhilosopher(renderer),

    fSilverMiner(renderer),
    fBronzeMiner(renderer),
    fLumberjack(renderer),

    fHunter(renderer) {

}

void eCharacterTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "SprMain/";

    const std::string pathBase{dir + "SprMain_"};

    for(int j = 0; j < 8; j++) {
        fFoodDistributor.fWalk.emplace_back(fRenderer);
    }
    for(int i = 1; i < 97;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fFoodDistributor.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 97; i < 105; i++) {
        auto& die = fFoodDistributor.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }


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
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }


    for(int j = 0; j < 8; j++) {
        fWatchman.fWalk.emplace_back(fRenderer);
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
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }
    for(int j = 0; j < 8; j++) {
        fWatchman.fFight.emplace_back(fRenderer);
    }
    for(int i = 2312; i < 2377;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& fight = fWatchman.fFight;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fight[j], eSprMainOffset);
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



    for(int j = 0; j < 8; j++) {
        fTaxCollector.fWalk.emplace_back(fRenderer);
    }
    for(int i = 4625; i < 4721;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fTaxCollector.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 4721; i < 4729; i++) {
        auto& die = fTaxCollector.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }



    for(int j = 0; j < 8; j++) {
        fWaterDistributor.fWalk.emplace_back(fRenderer);
    }
    for(int i = 6737; i < 6833;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fWaterDistributor.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 6833; i < 6841; i++) {
        auto& die = fWaterDistributor.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }


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
        fGymnast.fWalk.emplace_back(fRenderer);
    }
    for(int i = 10588; i < 10684;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fGymnast.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 10684; i < 10692; i++) {
        auto& die = fGymnast.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
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



    for(int j = 0; j < 8; j++) {
        fPhilosopher.fWalk.emplace_back(fRenderer);
    }
    for(int i = 12128; i < 12224;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fPhilosopher.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 12224; i < 12232; i++) {
        auto& die = fPhilosopher.fDie;
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, die, eSprMainOffset);
    }
}
