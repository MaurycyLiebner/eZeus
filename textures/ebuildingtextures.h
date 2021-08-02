#ifndef EBUILDINGTEXTURES_H
#define EBUILDINGTEXTURES_H

#include "etexturecollection.h"

class eBuildingTextures {
public:
    eBuildingTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eTexture fHouseSpace;
    std::vector<eTextureCollection> fCommonHouse;


    eTexture fGymnasium;
    eTextureCollection fGymnasiumOverlay;

    eTexture fCollege;
    eTextureCollection fCollegeOverlay;

    eTexture fDramaSchool;
    eTextureCollection fDramaSchoolOverlay;

    eTexture fPodium;
    eTextureCollection fPodiumOverlay;

    eTexture fTheater;

    eTexture fStadium1H;
    eTexture fStadium2H;

    eTexture fStadium1W;
    eTexture fStadium2W;


    eTexture fFountain;
    eTextureCollection fFountainOverlay;

    eTexture fHospital;
    eTextureCollection fHospitalOverlay;


    eTextureCollection fOliveTree;
    eTextureCollection fVine;

    eTexture fPlantation;
    eTextureCollection fWheat;
    eTextureCollection fCarrots;
    eTextureCollection fOnions;

    eTexture fHuntingLodge;
    eTextureCollection fHuntingLodgeOverlay;

    eTextureCollection fFishery;
    eTextureCollection fUrchinQuay;

    eTexture fCardingShed;
    eTextureCollection fCardingShedOverlay;

    eTexture fDairy;
    eTextureCollection fDairyOverlay;

    eTexture fGrowersLodge;
    eTextureCollection fGrowersLodgeOverlay;

    eTexture fTimberMill;
    eTextureCollection fTimberMillOverlay;

    eTexture fMasonryShop;
    eTextureCollection fMasonryShopStones;

    eTexture fMint;
    eTextureCollection fMintOverlay;

    eTexture fFoundry;
    eTextureCollection fFoundryOverlay;

    eTexture fArtisansGuild;
    eTextureCollection fArtisansGuildOverlay;

    eTexture fOlivePress;
    eTextureCollection fOlivePressOverlay;

    eTexture fWinery;
    eTextureCollection fWineryOverlay;

    eTexture fSculptureStudio;
    eTextureCollection fSculptureStudioOverlay;


    eTextureCollection fTriremeWharf;

    eTexture fHorseRanch;
    eTextureCollection fHorseRanchOverlay;
    eTexture fHorseRanchEnclosure;

    eTexture fArmory;
    eTextureCollection fArmoryOverlay;

    eTexture fMaintenanceOffice;
    eTextureCollection fMaintenanceOfficeOverlay;

    eTexture fTaxOffice;
    eTextureCollection fTaxOfficeOverlay;

    eTexture fWatchPost;
    eTextureCollection fWatchPostOverlay;

    eTextureCollection fBeachRoad;
    eTextureCollection fRoad;
};

#endif // EBUILDINGTEXTURES_H
