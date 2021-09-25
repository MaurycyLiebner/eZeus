#ifndef EINTERFACETEXTURES_H
#define EINTERFACETEXTURES_H

#include "etexturecollection.h"

class eInterfaceTextures {
public:
    eInterfaceTextures(const int tileW, const int tileH,
                       SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    std::shared_ptr<eTexture> fGameMenuBackground;

    // normal, hover, selected, disabled
    eTextureCollection fShowInfo;
    eTextureCollection fShowMap;

    // normal, hover, selected, disabled
    eTextureCollection fPopulation;
    eTextureCollection fHusbandry;
    eTextureCollection fIndustry;
    eTextureCollection fDistribution;
    eTextureCollection fHygieneSafety;
    eTextureCollection fAdministration;
    eTextureCollection fCulture;
    eTextureCollection fMythology;
    eTextureCollection fMilitary;
    eTextureCollection fAesthetics;
    eTextureCollection fOverview;

    std::shared_ptr<eTexture> fMapEditMenuBackground;

    eTextureCollection fBrushSize;
    eTextureCollection fEmptyLand;
    eTextureCollection fForest;
    eTextureCollection fWaterMarshBeach;
    eTextureCollection fMeadow;
    eTextureCollection fFishAndUrchin;
    eTextureCollection fRocks;
    eTextureCollection fScrub;
    eTextureCollection fElevation;
    eTextureCollection fDisasters;
    eTextureCollection fWaterPoints;
    eTextureCollection fLandInvasionPoints;
    eTextureCollection fExitEndEntryPoints;
    eTextureCollection fAnimalPoints;

    // normal, hover, pressed
    eTextureCollection fCommonHousing;
    eTextureCollection fEliteHousing;

    eTextureCollection fFoodFarming;
    eTextureCollection fOtherFarming; // e.g. wine
    eTextureCollection fAnimalFarming;
    eTextureCollection fAnimalHunting;

    eTextureCollection fResources; // e.g. wood, marble
    eTextureCollection fProcessing; // e.g. olives
    eTextureCollection fBuildersGuild;

    eTextureCollection fGranary;
    eTextureCollection fWarehouse;
    eTextureCollection fAgoras;
    eTextureCollection fTrade;

    eTextureCollection fFireFighter;
    eTextureCollection fFountain;
    eTextureCollection fPolice;
    eTextureCollection fHospital;

    eTextureCollection fPalace;
    eTextureCollection fTaxCollector;
    eTextureCollection fBridge;

    eTextureCollection fPhilosophy;
    eTextureCollection fGymnasium;
    eTextureCollection fDrama;
    eTextureCollection fStadium;

    eTextureCollection fTemples;
    eTextureCollection fHeroShrines;

    eTextureCollection fFortifications;
    eTextureCollection fMilitaryProduction;

    eTextureCollection fBeautification;
    eTextureCollection fRecreation;
    eTextureCollection fMonuments;

    // normal, hover, pressed, disabled
    eTextureCollection fBuildRoad;
    eTextureCollection fRoadBlock;
    eTextureCollection fClear;
    eTextureCollection fUndo;

    eTextureCollection fMessages;

    eTextureCollection fGoals;
    eTextureCollection fRotation;
    eTextureCollection fWorld;

    // normal, hoer, pressed
    eTextureCollection fFireAlert;
    eTextureCollection fGroundFissureAlert;
    eTextureCollection fFloodAlert;
    eTextureCollection fAvalancheAltert;
    eTextureCollection fLavaAltert;
    eTextureCollection fCollapseAltert;
    eTextureCollection fRoadBlockAltert;
    eTextureCollection fVirusAlert;
    eTextureCollection fIllnessAlert;
    eTextureCollection fInvasionAlert;
    eTextureCollection fMonsterAltert;
    eTextureCollection fGodAttackAlert;
    eTextureCollection fGodVisitAlert;
    eTextureCollection fHeroArrivalAlert;
    eTextureCollection fArmyComebackAlert;

    // topLeft, top, topRight, left, center, right, bottomLeft, bottom, bottomRight,
    std::vector<eTextureCollection> fComboBox;
    std::vector<eTextureCollection> fMessageBox;
    std::vector<eTextureCollection> fInnerBox;

    std::shared_ptr<eTexture> fLoadImage;
    std::shared_ptr<eTexture> fMainMenuImage;

    eTextureCollection fCheckBox;
    eTextureCollection fLargeCheckBox;

    std::shared_ptr<eTexture> fSpawner;

    //

    std::shared_ptr<eTexture> fDrachmasTopMenu;
    std::shared_ptr<eTexture> fPopulationTopMenu;
    std::shared_ptr<eTexture> fDrachmasUnit;

    std::shared_ptr<eTexture> fUrchinUnit;
    std::shared_ptr<eTexture> fFishUnit;
    std::shared_ptr<eTexture> fMeatUnit;
    std::shared_ptr<eTexture> fCheeseUnit;
    std::shared_ptr<eTexture> fCarrotsUnit;
    std::shared_ptr<eTexture> fOnionsUnit;
    std::shared_ptr<eTexture> fWheatUnit;
    std::shared_ptr<eTexture> fOrangesUnit;

    std::shared_ptr<eTexture> fWoodUnit;
    std::shared_ptr<eTexture> fBronzeUnit;
    std::shared_ptr<eTexture> fMarbleUnit;
    std::shared_ptr<eTexture> fGrapesUnit;
    std::shared_ptr<eTexture> fOlivesUnit;
    std::shared_ptr<eTexture> fFleeceUnit;
    std::shared_ptr<eTexture> fHorseUnit;
    std::shared_ptr<eTexture> fArmsUnit;
    std::shared_ptr<eTexture> fSculptureUnit;
    std::shared_ptr<eTexture> fOliveOilUnit;
    std::shared_ptr<eTexture> fWineUnit;
    std::shared_ptr<eTexture> fFoodUnit;

    std::shared_ptr<eTexture> fSuppliesBg;
    std::shared_ptr<eTexture> fEliteSuppliesBg;

    std::shared_ptr<eTexture> fHasFood;
    std::shared_ptr<eTexture> fHasFleece;
    std::shared_ptr<eTexture> fHasOil;
    std::shared_ptr<eTexture> fHasWine;
    std::shared_ptr<eTexture> fHasArms;
    std::shared_ptr<eTexture> fHasHorses;

    std::shared_ptr<eTexture> fNHasFood;
    std::shared_ptr<eTexture> fNHasFleece;
    std::shared_ptr<eTexture> fNHasOil;
    std::shared_ptr<eTexture> fNHasWine;
    std::shared_ptr<eTexture> fNHasArms;
    std::shared_ptr<eTexture> fNHasHorses;

    // normal, hover, pressed, disabled
    eTextureCollection fUpButton;
    eTextureCollection fDownButton;

    eTextureCollection fColumn1;
    eTextureCollection fColumn2;
    eTextureCollection fColumn3;
    eTextureCollection fColumn4;
    eTextureCollection fColumn5;

    eTextureCollection fDiamond;
};

#endif // EINTERFACETEXTURES_H
