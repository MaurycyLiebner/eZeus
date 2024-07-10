#include "ebuildingtextures.h"

#include "offsets/SprAmbient.h"

#include "spriteData/palaceTiles15.h"
#include "spriteData/palaceTiles30.h"
#include "spriteData/palaceTiles45.h"
#include "spriteData/palaceTiles60.h"

#include "spriteData/commonHouse15.h"
#include "spriteData/commonHouse30.h"
#include "spriteData/commonHouse45.h"
#include "spriteData/commonHouse60.h"

#include "spriteData/eliteHouse15.h"
#include "spriteData/eliteHouse30.h"
#include "spriteData/eliteHouse45.h"
#include "spriteData/eliteHouse60.h"

#include "spriteData/college15.h"
#include "spriteData/college30.h"
#include "spriteData/college45.h"
#include "spriteData/college60.h"

#include "spriteData/gymnasium15.h"
#include "spriteData/gymnasium30.h"
#include "spriteData/gymnasium45.h"
#include "spriteData/gymnasium60.h"

#include "spriteData/dramaSchool15.h"
#include "spriteData/dramaSchool30.h"
#include "spriteData/dramaSchool45.h"
#include "spriteData/dramaSchool60.h"

#include "spriteData/podium15.h"
#include "spriteData/podium30.h"
#include "spriteData/podium45.h"
#include "spriteData/podium60.h"

#include "spriteData/theater15.h"
#include "spriteData/theater30.h"
#include "spriteData/theater45.h"
#include "spriteData/theater60.h"

#include "spriteData/stadium15.h"
#include "spriteData/stadium30.h"
#include "spriteData/stadium45.h"
#include "spriteData/stadium60.h"

#include "spriteData/fountain15.h"
#include "spriteData/fountain30.h"
#include "spriteData/fountain45.h"
#include "spriteData/fountain60.h"

#include "spriteData/hospital15.h"
#include "spriteData/hospital30.h"
#include "spriteData/hospital45.h"
#include "spriteData/hospital60.h"

#include "spriteData/oliveTree15.h"
#include "spriteData/oliveTree30.h"
#include "spriteData/oliveTree45.h"
#include "spriteData/oliveTree60.h"

#include "spriteData/vine15.h"
#include "spriteData/vine30.h"
#include "spriteData/vine45.h"
#include "spriteData/vine60.h"

#include "spriteData/plantation15.h"
#include "spriteData/plantation30.h"
#include "spriteData/plantation45.h"
#include "spriteData/plantation60.h"

#include "spriteData/huntingLodge15.h"
#include "spriteData/huntingLodge30.h"
#include "spriteData/huntingLodge45.h"
#include "spriteData/huntingLodge60.h"

#include "spriteData/fishery15.h"
#include "spriteData/fishery30.h"
#include "spriteData/fishery45.h"
#include "spriteData/fishery60.h"

#include "spriteData/urchinQuay15.h"
#include "spriteData/urchinQuay30.h"
#include "spriteData/urchinQuay45.h"
#include "spriteData/urchinQuay60.h"

#include "spriteData/cardingShed15.h"
#include "spriteData/cardingShed30.h"
#include "spriteData/cardingShed45.h"
#include "spriteData/cardingShed60.h"

#include "spriteData/dairy15.h"
#include "spriteData/dairy30.h"
#include "spriteData/dairy45.h"
#include "spriteData/dairy60.h"

#include "spriteData/growersLodge15.h"
#include "spriteData/growersLodge30.h"
#include "spriteData/growersLodge45.h"
#include "spriteData/growersLodge60.h"

#include "spriteData/timberMill15.h"
#include "spriteData/timberMill30.h"
#include "spriteData/timberMill45.h"
#include "spriteData/timberMill60.h"

#include "spriteData/masonryShop15.h"
#include "spriteData/masonryShop30.h"
#include "spriteData/masonryShop45.h"
#include "spriteData/masonryShop60.h"

#include "spriteData/mint15.h"
#include "spriteData/mint30.h"
#include "spriteData/mint45.h"
#include "spriteData/mint60.h"

#include "spriteData/foundry15.h"
#include "spriteData/foundry30.h"
#include "spriteData/foundry45.h"
#include "spriteData/foundry60.h"

#include "spriteData/artisansGuild15.h"
#include "spriteData/artisansGuild30.h"
#include "spriteData/artisansGuild45.h"
#include "spriteData/artisansGuild60.h"

#include "spriteData/olivePress15.h"
#include "spriteData/olivePress30.h"
#include "spriteData/olivePress45.h"
#include "spriteData/olivePress60.h"

#include "spriteData/winery15.h"
#include "spriteData/winery30.h"
#include "spriteData/winery45.h"
#include "spriteData/winery60.h"

#include "spriteData/sculptureStudio15.h"
#include "spriteData/sculptureStudio30.h"
#include "spriteData/sculptureStudio45.h"
#include "spriteData/sculptureStudio60.h"

#include "spriteData/triremeWharf15.h"
#include "spriteData/triremeWharf30.h"
#include "spriteData/triremeWharf45.h"
#include "spriteData/triremeWharf60.h"

#include "spriteData/horseRanch15.h"
#include "spriteData/horseRanch30.h"
#include "spriteData/horseRanch45.h"
#include "spriteData/horseRanch60.h"

#include "spriteData/horseRanchEnclosure15.h"
#include "spriteData/horseRanchEnclosure30.h"
#include "spriteData/horseRanchEnclosure45.h"
#include "spriteData/horseRanchEnclosure60.h"

#include "spriteData/armory15.h"
#include "spriteData/armory30.h"
#include "spriteData/armory45.h"
#include "spriteData/armory60.h"

#include "spriteData/gatehouseAndTower15.h"
#include "spriteData/gatehouseAndTower30.h"
#include "spriteData/gatehouseAndTower45.h"
#include "spriteData/gatehouseAndTower60.h"

#include "spriteData/wall15.h"
#include "spriteData/wall30.h"
#include "spriteData/wall45.h"
#include "spriteData/wall60.h"

#include "spriteData/maintenanceOffice15.h"
#include "spriteData/maintenanceOffice30.h"
#include "spriteData/maintenanceOffice45.h"
#include "spriteData/maintenanceOffice60.h"

#include "spriteData/taxOffice15.h"
#include "spriteData/taxOffice30.h"
#include "spriteData/taxOffice45.h"
#include "spriteData/taxOffice60.h"

#include "spriteData/watchpost15.h"
#include "spriteData/watchpost30.h"
#include "spriteData/watchpost45.h"
#include "spriteData/watchpost60.h"

#include "spriteData/roadblock15.h"
#include "spriteData/roadblock30.h"
#include "spriteData/roadblock45.h"
#include "spriteData/roadblock60.h"

#include "spriteData/bridge15.h"
#include "spriteData/bridge30.h"
#include "spriteData/bridge45.h"
#include "spriteData/bridge60.h"

#include "spriteData/mun_Palace15.h"
#include "spriteData/mun_Palace30.h"
#include "spriteData/mun_Palace45.h"
#include "spriteData/mun_Palace60.h"

#include "spriteData/zeusSanctuaryElements15.h"
#include "spriteData/zeusSanctuaryElements30.h"
#include "spriteData/zeusSanctuaryElements45.h"
#include "spriteData/zeusSanctuaryElements60.h"

#include "spriteData/zeusHerosHall15.h"
#include "spriteData/zeusHerosHall30.h"
#include "spriteData/zeusHerosHall45.h"
#include "spriteData/zeusHerosHall60.h"

#include "spriteData/poseidonHerosHall15.h"
#include "spriteData/poseidonHerosHall30.h"
#include "spriteData/poseidonHerosHall45.h"
#include "spriteData/poseidonHerosHall60.h"

#include "spriteData/poseidonStatues115.h"
#include "spriteData/poseidonStatues130.h"
#include "spriteData/poseidonStatues145.h"
#include "spriteData/poseidonStatues160.h"

#include "spriteData/poseidonStatues215.h"
#include "spriteData/poseidonStatues230.h"
#include "spriteData/poseidonStatues245.h"
#include "spriteData/poseidonStatues260.h"

#include "spriteData/stor_bays15.h"
#include "spriteData/stor_bays30.h"
#include "spriteData/stor_bays45.h"
#include "spriteData/stor_bays60.h"

#include "spriteData/tallObelisk15.h"
#include "spriteData/tallObelisk30.h"
#include "spriteData/tallObelisk45.h"
#include "spriteData/tallObelisk60.h"

#include "spriteData/avenue15.h"
#include "spriteData/avenue30.h"
#include "spriteData/avenue45.h"
#include "spriteData/avenue60.h"

#include "spriteData/columns15.h"
#include "spriteData/columns30.h"
#include "spriteData/columns45.h"
#include "spriteData/columns60.h"

#include "spriteData/commemorative15.h"
#include "spriteData/commemorative30.h"
#include "spriteData/commemorative45.h"
#include "spriteData/commemorative60.h"

#include "spriteData/fishPond15.h"
#include "spriteData/fishPond30.h"
#include "spriteData/fishPond45.h"
#include "spriteData/fishPond60.h"

#include "spriteData/hedgeMaze15.h"
#include "spriteData/hedgeMaze30.h"
#include "spriteData/hedgeMaze45.h"
#include "spriteData/hedgeMaze60.h"

#include "spriteData/gazebo15.h"
#include "spriteData/gazebo30.h"
#include "spriteData/gazebo45.h"
#include "spriteData/gazebo60.h"

#include "spriteData/flowerGarden15.h"
#include "spriteData/flowerGarden30.h"
#include "spriteData/flowerGarden45.h"
#include "spriteData/flowerGarden60.h"

#include "spriteData/bench15.h"
#include "spriteData/bench30.h"
#include "spriteData/bench45.h"
#include "spriteData/bench60.h"

#include "spriteData/park15.h"
#include "spriteData/park30.h"
#include "spriteData/park45.h"
#include "spriteData/park60.h"

#include "spriteData/sundial15.h"
#include "spriteData/sundial30.h"
#include "spriteData/sundial45.h"
#include "spriteData/sundial60.h"

#include "spriteData/topiary15.h"
#include "spriteData/topiary30.h"
#include "spriteData/topiary45.h"
#include "spriteData/topiary60.h"

#include "spriteData/spring15.h"
#include "spriteData/spring30.h"
#include "spriteData/spring45.h"
#include "spriteData/spring60.h"

#include "spriteData/stoneCircle15.h"
#include "spriteData/stoneCircle30.h"
#include "spriteData/stoneCircle45.h"
#include "spriteData/stoneCircle60.h"

#include "spriteData/dolphinSculpture15.h"
#include "spriteData/dolphinSculpture30.h"
#include "spriteData/dolphinSculpture45.h"
#include "spriteData/dolphinSculpture60.h"

#include "spriteData/orrery15.h"
#include "spriteData/orrery30.h"
#include "spriteData/orrery45.h"
#include "spriteData/orrery60.h"

#include "spriteData/shellGarden15.h"
#include "spriteData/shellGarden30.h"
#include "spriteData/shellGarden45.h"
#include "spriteData/shellGarden60.h"

#include "spriteData/storage15.h"
#include "spriteData/storage30.h"
#include "spriteData/storage45.h"
#include "spriteData/storage60.h"

#include "spriteData/tradingPostOverlay15.h"
#include "spriteData/tradingPostOverlay30.h"
#include "spriteData/tradingPostOverlay45.h"
#include "spriteData/tradingPostOverlay60.h"

#include "spriteData/warehouseOverlay15.h"
#include "spriteData/warehouseOverlay30.h"
#include "spriteData/warehouseOverlay45.h"
#include "spriteData/warehouseOverlay60.h"

#include "spriteData/fish15.h"
#include "spriteData/fish30.h"
#include "spriteData/fish45.h"
#include "spriteData/fish60.h"

#include "spriteData/urchin15.h"
#include "spriteData/urchin30.h"
#include "spriteData/urchin45.h"
#include "spriteData/urchin60.h"

#include "spriteData/theaterOverlay15.h"
#include "spriteData/theaterOverlay30.h"
#include "spriteData/theaterOverlay45.h"
#include "spriteData/theaterOverlay60.h"

#include "spriteData/fisheryBoatBuilding15.h"
#include "spriteData/fisheryBoatBuilding30.h"
#include "spriteData/fisheryBoatBuilding45.h"
#include "spriteData/fisheryBoatBuilding60.h"

#include "spriteData/fisheryOverlay15.h"
#include "spriteData/fisheryOverlay30.h"
#include "spriteData/fisheryOverlay45.h"
#include "spriteData/fisheryOverlay60.h"

#include "spriteData/urchinUnpackingOverlay15.h"
#include "spriteData/urchinUnpackingOverlay30.h"
#include "spriteData/urchinUnpackingOverlay45.h"
#include "spriteData/urchinUnpackingOverlay60.h"

#include "spriteData/fisheryUnpackingOverlay15.h"
#include "spriteData/fisheryUnpackingOverlay30.h"
#include "spriteData/fisheryUnpackingOverlay45.h"
#include "spriteData/fisheryUnpackingOverlay60.h"

#include "spriteData/stadiumOverlays115.h"
#include "spriteData/stadiumOverlays130.h"
#include "spriteData/stadiumOverlays145.h"
#include "spriteData/stadiumOverlays160.h"

#include "spriteData/sanctuaryOverlay15.h"
#include "spriteData/sanctuaryOverlay30.h"
#include "spriteData/sanctuaryOverlay45.h"
#include "spriteData/sanctuaryOverlay60.h"

#include "spriteData/stadiumOverlays215.h"
#include "spriteData/stadiumOverlays230.h"
#include "spriteData/stadiumOverlays245.h"
#include "spriteData/stadiumOverlays260.h"

#include "spriteData/sanctuaryFire15.h"
#include "spriteData/sanctuaryFire30.h"
#include "spriteData/sanctuaryFire45.h"
#include "spriteData/sanctuaryFire60.h"

#include "spriteData/masonryShopOverlays15.h"
#include "spriteData/masonryShopOverlays30.h"
#include "spriteData/masonryShopOverlays45.h"
#include "spriteData/masonryShopOverlays60.h"

#include "spriteData/waitingOverlay15.h"
#include "spriteData/waitingOverlay30.h"
#include "spriteData/waitingOverlay45.h"
#include "spriteData/waitingOverlay60.h"

#include "spriteData/vendorOverlays15.h"
#include "spriteData/vendorOverlays30.h"
#include "spriteData/vendorOverlays45.h"
#include "spriteData/vendorOverlays60.h"

#include "spriteData/wineVendorOverlay15.h"
#include "spriteData/wineVendorOverlay30.h"
#include "spriteData/wineVendorOverlay45.h"
#include "spriteData/wineVendorOverlay60.h"

#include "spriteData/fishPondOverlay15.h"
#include "spriteData/fishPondOverlay30.h"
#include "spriteData/fishPondOverlay45.h"
#include "spriteData/fishPondOverlay60.h"

#include "spriteData/watchPostOverlay15.h"
#include "spriteData/watchPostOverlay30.h"
#include "spriteData/watchPostOverlay45.h"
#include "spriteData/watchPostOverlay60.h"

#include "spriteData/palaceOverlay15.h"
#include "spriteData/palaceOverlay30.h"
#include "spriteData/palaceOverlay45.h"
#include "spriteData/palaceOverlay60.h"

#include "spriteData/zeusStatue15.h"
#include "spriteData/zeusStatue30.h"
#include "spriteData/zeusStatue45.h"
#include "spriteData/zeusStatue60.h"

#include "spriteData/poseidonStatue15.h"
#include "spriteData/poseidonStatue30.h"
#include "spriteData/poseidonStatue45.h"
#include "spriteData/poseidonStatue60.h"

#include "spriteData/hadesStatue15.h"
#include "spriteData/hadesStatue30.h"
#include "spriteData/hadesStatue45.h"
#include "spriteData/hadesStatue60.h"

#include "spriteData/demeterStatue15.h"
#include "spriteData/demeterStatue30.h"
#include "spriteData/demeterStatue45.h"
#include "spriteData/demeterStatue60.h"

#include "spriteData/athenaStatue15.h"
#include "spriteData/athenaStatue30.h"
#include "spriteData/athenaStatue45.h"
#include "spriteData/athenaStatue60.h"

#include "spriteData/artemisStatue15.h"
#include "spriteData/artemisStatue30.h"
#include "spriteData/artemisStatue45.h"
#include "spriteData/artemisStatue60.h"

#include "spriteData/apolloStatue15.h"
#include "spriteData/apolloStatue30.h"
#include "spriteData/apolloStatue45.h"
#include "spriteData/apolloStatue60.h"

#include "spriteData/aresStatue15.h"
#include "spriteData/aresStatue30.h"
#include "spriteData/aresStatue45.h"
#include "spriteData/aresStatue60.h"

#include "spriteData/hephaestusStatue15.h"
#include "spriteData/hephaestusStatue30.h"
#include "spriteData/hephaestusStatue45.h"
#include "spriteData/hephaestusStatue60.h"

#include "spriteData/aphroditeStatue15.h"
#include "spriteData/aphroditeStatue30.h"
#include "spriteData/aphroditeStatue45.h"
#include "spriteData/aphroditeStatue60.h"

#include "spriteData/hermesStatue15.h"
#include "spriteData/hermesStatue30.h"
#include "spriteData/hermesStatue45.h"
#include "spriteData/hermesStatue60.h"

#include "spriteData/dionysusStatue15.h"
#include "spriteData/dionysusStatue30.h"
#include "spriteData/dionysusStatue45.h"
#include "spriteData/dionysusStatue60.h"

#include "spriteData/blankStatue15.h"
#include "spriteData/blankStatue30.h"
#include "spriteData/blankStatue45.h"
#include "spriteData/blankStatue60.h"

#include "spriteData/atlasStatue15.h"
#include "spriteData/atlasStatue30.h"
#include "spriteData/atlasStatue45.h"
#include "spriteData/atlasStatue60.h"

#include "spriteData/heraStatue15.h"
#include "spriteData/heraStatue30.h"
#include "spriteData/heraStatue45.h"
#include "spriteData/heraStatue60.h"

#include "spriteData/zeusSanctuary115.h"
#include "spriteData/zeusSanctuary130.h"
#include "spriteData/zeusSanctuary145.h"
#include "spriteData/zeusSanctuary160.h"

#include "spriteData/zeusSanctuary215.h"
#include "spriteData/zeusSanctuary230.h"
#include "spriteData/zeusSanctuary245.h"
#include "spriteData/zeusSanctuary260.h"

#include "spriteData/zeusSanctuary315.h"
#include "spriteData/zeusSanctuary330.h"
#include "spriteData/zeusSanctuary345.h"
#include "spriteData/zeusSanctuary360.h"

#include "spriteData/orangeTendersLodge15.h"
#include "spriteData/orangeTendersLodge30.h"
#include "spriteData/orangeTendersLodge45.h"
#include "spriteData/orangeTendersLodge60.h"

#include "spriteData/waterPark15.h"
#include "spriteData/waterPark30.h"
#include "spriteData/waterPark45.h"
#include "spriteData/waterPark60.h"

#include "spriteData/baths15.h"
#include "spriteData/baths30.h"
#include "spriteData/baths45.h"
#include "spriteData/baths60.h"

#include "spriteData/birdBath15.h"
#include "spriteData/birdBath30.h"
#include "spriteData/birdBath45.h"
#include "spriteData/birdBath60.h"

#include "spriteData/shortObelisk15.h"
#include "spriteData/shortObelisk30.h"
#include "spriteData/shortObelisk45.h"
#include "spriteData/shortObelisk60.h"

#include "spriteData/agora15.h"
#include "spriteData/agora30.h"
#include "spriteData/agora45.h"
#include "spriteData/agora60.h"

#include "spriteData/granary15.h"
#include "spriteData/granary30.h"
#include "spriteData/granary45.h"
#include "spriteData/granary60.h"

#include "spriteData/pier115.h"
#include "spriteData/pier130.h"
#include "spriteData/pier145.h"
#include "spriteData/pier160.h"

#include "spriteData/pier215.h"
#include "spriteData/pier230.h"
#include "spriteData/pier245.h"
#include "spriteData/pier260.h"

#include "spriteData/warehouse15.h"
#include "spriteData/warehouse30.h"
#include "spriteData/warehouse45.h"
#include "spriteData/warehouse60.h"

#include "spriteData/tradingPost15.h"
#include "spriteData/tradingPost30.h"
#include "spriteData/tradingPost45.h"
#include "spriteData/tradingPost60.h"

#include "spriteData/chariotVendor15.h"
#include "spriteData/chariotVendor30.h"
#include "spriteData/chariotVendor45.h"
#include "spriteData/chariotVendor60.h"

#include "spriteData/chariotVendorOverlay15.h"
#include "spriteData/chariotVendorOverlay30.h"
#include "spriteData/chariotVendorOverlay45.h"
#include "spriteData/chariotVendorOverlay60.h"

#include "spriteData/interfaceSprites15.h"
#include "spriteData/interfaceSprites30.h"
#include "spriteData/interfaceSprites45.h"
#include "spriteData/interfaceSprites60.h"

#include "offsets/PoseidonImps.h"

#include "textures/espriteloader.h"

eBuildingTextures::eBuildingTextures(const int tileW, const int tileH,
                                     SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fEliteHouseHorses(renderer),

    fGymnasiumOverlay(renderer),
    fCollegeOverlay(renderer),
    fDramaSchoolOverlay(renderer),
    fPodiumOverlay(renderer),
    fTheaterOverlay(renderer),
    fStadiumOverlay1(renderer),
    fStadiumOverlay2(renderer),
    fStadiumOverlay3(renderer),
    fStadiumOverlay4W(renderer),
    fStadiumOverlay4H(renderer),
    fStadiumOverlay5W(renderer),
    fStadiumOverlay5H(renderer),
    fStadiumAudiance1W(renderer),
    fStadiumAudiance2W(renderer),
    fStadiumAudiance1H(renderer),
    fStadiumAudiance2H(renderer),

    fBibliothekeOverlay(renderer),
    fObservatoryOverlay(renderer),
    fUniversityOverlay(renderer),
    fLaboratoryOverlay(renderer),
    fInventorsWorkshopOverlay(renderer),
    fMuseumOverlay(renderer),

    fPalaceHOverlay(renderer),
    fPalaceWOverlay(renderer),

    fPalaceTiles(renderer),

    fFountainOverlay(renderer),
    fHospitalOverlay(renderer),

    fOliveTree(renderer),
    fVine(renderer),
    fOrangeTree(renderer),

    fWheat(renderer),
    fCarrots(renderer),
    fOnions(renderer),

    fHuntingLodgeOverlay(renderer),
    fFishery(renderer),
    fFisheryBoatBuildingW(renderer),
    fFisheryBoatBuildingH(renderer),
    fFisheryUnpackingOverlayTL(renderer),
    fFisheryUnpackingOverlayTR(renderer),
    fFisheryUnpackingOverlayBL(renderer),
    fFisheryUnpackingOverlayBR(renderer),
    fUrchinQuay(renderer),
    fUrchinQuayUnpackingOverlayTL(renderer),
    fUrchinQuayUnpackingOverlayTR(renderer),
    fUrchinQuayUnpackingOverlayBL(renderer),
    fUrchinQuayUnpackingOverlayBR(renderer),
    fCardingShedOverlay(renderer),
    fDairyOverlay(renderer),
    fGrowersLodgeOverlay(renderer),
//    fCorralOverlay(renderer),
    fOrangeTendersLodgeOverlay(renderer),

    fTimberMillOverlay(renderer),
    fMasonryShopStones(renderer),
    fMintOverlay(renderer),
    fFoundryOverlay(renderer),
    fArtisansGuildOverlay(renderer),
    fOlivePressOverlay(renderer),
    fWineryOverlay(renderer),
    fSculptureStudioOverlay(renderer),

    fTriremeWharf(renderer),
    fHorseRanchOverlay(renderer),
    fCorralOverlay(renderer),
    fCorralProcessingOverlay(renderer),
    fArmoryOverlay(renderer),

    fGatehouseW(renderer),
    fGatehouseH(renderer),
    fWall(renderer),

    fMaintenanceOfficeOverlay(renderer),
    fTaxOfficeOverlay(renderer),
    fWatchPostOverlay(renderer),

    fWaitingMeat(renderer),
    fWaitingCheese(renderer),
    fWaitingWheat(renderer),
    fWaitingOranges(renderer),
    fWaitingWood(renderer),
    fWaitingBronze(renderer),
    fWaitingGrapes(renderer),
    fWaitingOlives(renderer),
    fWaitingArmor(renderer),

    fAgoraRoad(renderer),
    fAgora(renderer),

    fFoodVendorOverlay2(renderer),
    fFleeceVendorOverlay2(renderer),
    fOilVendorOverlay2(renderer),
    fArmsVendorOverlay2(renderer),
    fWineVendorOverlay2(renderer),
    fHorseTrainerOverlay2(renderer),

    fChariotVendorOverlay2(renderer),

    fChariotFactoryOverlay(renderer),
    fChariotFactoryOverlay1(renderer),
    fChariotFactoryChariots(renderer),

    fWarehouseOverlay(renderer),

    fPier1(renderer),
    fTradingPostOverlay(renderer),

    fWarehouseUrchin(renderer),
    fWarehouseFish(renderer),
    fWarehouseMeat(renderer),
    fWarehouseCheese(renderer),
    fWarehouseCarrots(renderer),
    fWarehouseOnions(renderer),
    fWarehouseWheat(renderer),
    fWarehouseOranges(renderer),
    fWarehouseWood(renderer),
    fWarehouseBronze(renderer),
    fWarehouseMarble(renderer),
    fWarehouseGrapes(renderer),
    fWarehouseOlives(renderer),
    fWarehouseFleece(renderer),
    fWarehouseArmor(renderer),
    fWarehouseOliveOil(renderer),
    fWarehouseWine(renderer),

    fGranaryOverlay(renderer),

    fPark(renderer),
    fLargePark(renderer),
    fHugePark(renderer),

    fWaterPark1Overlay(renderer),
    fWaterPark2Overlay(renderer),
    fWaterPark3Overlay(renderer),
    fWaterPark4Overlay(renderer),
    fWaterPark5Overlay(renderer),
    fWaterPark6Overlay(renderer),
    fWaterPark7Overlay(renderer),
    fWaterPark8Overlay(renderer),

    fFishPondOverlay(renderer),

    fAvenueRoad(renderer),

    fCommemorative(renderer),

    fBirdBathOverlay(renderer),
    fSpring(renderer),
    fBathsOverlay(renderer),
    fStoneCircleOverlay(renderer),

    fZeusStatues(renderer),
    fPoseidonStatues(renderer),
    fHadesStatues(renderer),
    fDemeterStatues(renderer),
    fAthenaStatues(renderer),
    fArtemisStatues(renderer),
    fApolloStatues(renderer),
    fAresStatues(renderer),
    fHephaestusStatues(renderer),
    fAphroditeStatues(renderer),
    fHermesStatues(renderer),
    fDionysusStatues(renderer),

    fHeraStatues(renderer),
    fAtlasStatues(renderer),

    fSanctuaryTiles(renderer),
    fSanctuarySpace(renderer),

    fHeroStatues(renderer),

    fZeusMonuments(renderer),
    fPoseidonMonuments(renderer),
    fHadesMonuments(renderer),
    fDemeterMonuments(renderer),
    fAthenaMonuments(renderer),
    fArtemisMonuments(renderer),
    fApolloMonuments(renderer),
    fAresMonuments(renderer),
    fHephaestusMonuments(renderer),
    fAphroditeMonuments(renderer),
    fHermesMonuments(renderer),
    fDionysusMonuments(renderer),

    fHeraMonuments(renderer),
    fAtlasMonuments(renderer),

    fPoseidonSanctuary(renderer),

    fSanctuaryWOverlay(renderer),
    fSanctuaryHOverlay(renderer),
    fSanctuaryFire(renderer),

    fFish(renderer),
    fUrchin(renderer),

    fBridge(renderer),

    fColumn1(renderer),
    fColumn2(renderer),
    fColumn3(renderer),
    fColumn4(renderer),
    fColumn5(renderer),

    fSpawner(renderer) {}

void eBuildingTextures::loadCommonHouse() {
    if(fCommonHouseLoaded) return;
    fCommonHouseLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eCommonHouseSpriteData15,
                                 eCommonHouseSpriteData30,
                                 eCommonHouseSpriteData45,
                                 eCommonHouseSpriteData60);
    eSpriteLoader loader(fTileH, "commonHouse", sds,
                         nullptr, fRenderer);

    fHouseSpace = loader.load(1, 15);
    for(int i = 1; i < 15;) {
        auto& coll = fCommonHouse.emplace_back(fRenderer);
        for(int j = 0; j < 2; j++, i++) {
            loader.load(1, i, coll);
        }
    }
}

void eBuildingTextures::loadEliteHouse() {
    if(fEliteHouseLoaded) return;
    fEliteHouseLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEliteHouseSpriteData15,
                                 eEliteHouseSpriteData30,
                                 eEliteHouseSpriteData45,
                                 eEliteHouseSpriteData60);
    eSpriteLoader loader(fTileH, "eliteHouse", sds,
                         nullptr, fRenderer);

    for(int i = 16; i < 46;) {
        auto& coll = fEliteHouse.emplace_back(fRenderer);
        for(int j = 0; j < 5; j++, i++) {
            loader.load(16, i, coll);
        }
    }

    for(int i = 46; i < 50; i++) {
        loader.load(16, i, fEliteHouseHorses);
    }
}

void eBuildingTextures::loadCollege() {
    if(fCollegeLoaded) return;
    fCollegeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eCollegeSpriteData15,
                                 eCollegeSpriteData30,
                                 eCollegeSpriteData45,
                                 eCollegeSpriteData60);
    eSpriteLoader loader(fTileH, "college", sds,
                         nullptr, fRenderer);
    fCollege = loader.load(1, 1);

    for(int i = 2; i < 26; i++) {
        loader.load(1, i, fCollegeOverlay);
    }
}

void eBuildingTextures::loadGymnasium() {
    if(fGymnasiumLoaded) return;
    fGymnasiumLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGymnasiumSpriteData15,
                                 eGymnasiumSpriteData30,
                                 eGymnasiumSpriteData45,
                                 eGymnasiumSpriteData60);
    eSpriteLoader loader(fTileH, "gymnasium", sds,
                         nullptr, fRenderer);

    fGymnasium = loader.load(26, 26);

    for(int i = 27; i < 59; i++) {
        loader.load(26, i, fGymnasiumOverlay);
    }
}

void eBuildingTextures::loadDramaSchool() {
    if(fDramaSchoolLoaded) return;
    fDramaSchoolLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDramaSchoolSpriteData15,
                                 eDramaSchoolSpriteData30,
                                 eDramaSchoolSpriteData45,
                                 eDramaSchoolSpriteData60);
    eSpriteLoader loader(fTileH, "dramaSchool", sds,
                         nullptr, fRenderer);
    fDramaSchool = loader.load(59, 59);

    for(int i = 60; i < 84; i++) {
        loader.load(59, i, fDramaSchoolOverlay);
    }
}

void eBuildingTextures::loadPodium() {
    if(fPodiumLoaded) return;
    fPodiumLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePodiumSpriteData15,
                                 ePodiumSpriteData30,
                                 ePodiumSpriteData45,
                                 ePodiumSpriteData60);
    eSpriteLoader loader(fTileH, "podium", sds,
                         nullptr, fRenderer);
    fPodium = loader.load(84, 84);

    for(int i = 85; i < 109; i++) {
        loader.load(84, i, fPodiumOverlay);
    }
}

void eBuildingTextures::loadTheater() {
    if(fTheaterLoaded) return;
    fTheaterLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eTheaterSpriteData15,
                                     eTheaterSpriteData30,
                                     eTheaterSpriteData45,
                                     eTheaterSpriteData60);
        eSpriteLoader loader(fTileH, "theater", sds,
                             nullptr, fRenderer);
        fTheater = loader.load(109, 109);
    }


    {
        const auto& sds = spriteData(fTileH,
                                     eTheaterOverlaySpriteData15,
                                     eTheaterOverlaySpriteData30,
                                     eTheaterOverlaySpriteData45,
                                     eTheaterOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "theaterOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 656; i < 680; i++) {
            loader.load(656, i, fTheaterOverlay);
        }
    }
}

void eBuildingTextures::loadStadium() {
    if(fStadiumLoaded) return;
    fStadiumLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eStadiumSpriteData15,
                                     eStadiumSpriteData30,
                                     eStadiumSpriteData45,
                                     eStadiumSpriteData60);
        eSpriteLoader loader(fTileH, "stadium", sds,
                             nullptr, fRenderer);
        fStadium2H = loader.load(110, 110);
        fStadium1H = loader.load(110, 111);
        fStadium1W = loader.load(110, 112);
        fStadium2W = loader.load(110, 113);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStadiumOverlays1SpriteData15,
                                     eStadiumOverlays1SpriteData30,
                                     eStadiumOverlays1SpriteData45,
                                     eStadiumOverlays1SpriteData60);
        eSpriteLoader loader(fTileH, "stadiumOverlays1", sds,
                             &eSprAmbientOffset, fRenderer);


        for(int i = 1492; i < 1510; i++) {
            loader.load(1492, i, fStadiumOverlay1);
        }

        for(int i = 1510; i < 1530; i++) {
            loader.load(1492, i, fStadiumOverlay2);
        }

        for(int i = 1530; i < 1547; i++) {
            loader.load(1492, i, fStadiumOverlay3);
        }

        for(int i = 1547; i < 1629;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay4W;
                } else {
                    coll = &fStadiumOverlay4H;
                }
                loader.load(1492, i, *coll);
            }
        }

        for(int i = 1629; i < 1653; i++) {
            loader.load(1492, i, fStadiumAudiance1W);
        }

        for(int i = 1653; i < 1677; i++) {
            loader.load(1492, i, fStadiumAudiance2W);
        }

        for(int i = 1677; i < 1701; i++) {
            loader.load(1492, i, fStadiumAudiance1H);
        }

        for(int i = 1701; i < 1725; i++) {
            loader.load(1492, i, fStadiumAudiance2H);
        }
    }
    {

        const auto& sds = spriteData(fTileH,
                                     eStadiumOverlays2SpriteData15,
                                     eStadiumOverlays2SpriteData30,
                                     eStadiumOverlays2SpriteData45,
                                     eStadiumOverlays2SpriteData60);
        eSpriteLoader loader(fTileH, "stadiumOverlays2", sds,
                             &eSprAmbientOffset, fRenderer);


        for(int i = 1773; i < 1937;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay5W;
                } else {
                    coll = &fStadiumOverlay5H;
                }
                loader.load(1773, i, *coll);
            }
        }
    }
}

void eBuildingTextures::loadFountain() {
    if(fFountainLoaded) return;
    fFountainLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eFountainSpriteData15,
                                 eFountainSpriteData30,
                                 eFountainSpriteData45,
                                 eFountainSpriteData60);
    eSpriteLoader loader(fTileH, "fountain", sds,
                         nullptr, fRenderer);

    fFountain = loader.load(1, 1);
    for(int i = 2; i < 8; i++) {
        loader.load(1, i, fFountainOverlay);
    }
}

void eBuildingTextures::loadHospital() {
    if(fHospitalLoaded) return;
    fHospitalLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHospitalSpriteData15,
                                 eHospitalSpriteData30,
                                 eHospitalSpriteData45,
                                 eHospitalSpriteData60);
    eSpriteLoader loader(fTileH, "hospital", sds,
                         nullptr, fRenderer);
    fHospital = loader.load(8, 8);
    for(int i = 9; i < 21; i++) {
        loader.load(8, i, fHospitalOverlay);
    }
}

void eBuildingTextures::loadOliveTree() {
    if(fOliveTreeLoaded) return;
    fOliveTreeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOliveTreeSpriteData15,
                                 eOliveTreeSpriteData30,
                                 eOliveTreeSpriteData45,
                                 eOliveTreeSpriteData60);
    eSpriteLoader loader(fTileH, "oliveTree", sds,
                         nullptr, fRenderer);

    for(int i = 1; i < 7; i++) {
        loader.load(1, i, fOliveTree);
    }
}

void eBuildingTextures::loadVine() {
    if(fVineLoaded) return;
    fVineLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eVineSpriteData15,
                                 eVineSpriteData30,
                                 eVineSpriteData45,
                                 eVineSpriteData60);
    eSpriteLoader loader(fTileH, "vine", sds,
                         nullptr, fRenderer);

    for(int i = 7; i < 13; i++) {
        loader.load(7, i, fVine);
    }
}

void eBuildingTextures::loadPlantation() {
    if(fPlantationLoaded) return;
    fPlantationLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePlantationSpriteData15,
                                 ePlantationSpriteData30,
                                 ePlantationSpriteData45,
                                 ePlantationSpriteData60);
    eSpriteLoader loader(fTileH, "plantation", sds,
                         nullptr, fRenderer);

    fPlantation = loader.load(13, 13);

    for(int i = 14; i < 20; i++) {
        loader.load(13, i, fWheat);
    }

    for(int i = 20; i < 26; i++) {
        loader.load(13, i, fCarrots);
    }

    for(int i = 26; i < 32; i++) {
        loader.load(13, i, fOnions);
    }
}

void eBuildingTextures::loadHuntingLodge() {
    if(fHuntingLodgeLoaded) return;
    fHuntingLodgeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHuntingLodgeSpriteData15,
                                 eHuntingLodgeSpriteData30,
                                 eHuntingLodgeSpriteData45,
                                 eHuntingLodgeSpriteData60);
    eSpriteLoader loader(fTileH, "huntingLodge", sds,
                         nullptr, fRenderer);

    fHuntingLodge = loader.load(32, 32);
    for(int i = 33; i < 48; i++) {
        loader.load(32, i, fHuntingLodgeOverlay);
    }
}

void eBuildingTextures::loadFishery() {
    if(fFisheryLoaded) return;
    fFisheryLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eFisherySpriteData15,
                                     eFisherySpriteData30,
                                     eFisherySpriteData45,
                                     eFisherySpriteData60);
        eSpriteLoader loader(fTileH, "fishery", sds,
                             nullptr, fRenderer);

        for(int i = 48; i < 52; i++) {
            loader.load(48, i, fFishery);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eFisheryBoatBuildingSpriteData15,
                                     eFisheryBoatBuildingSpriteData30,
                                     eFisheryBoatBuildingSpriteData45,
                                     eFisheryBoatBuildingSpriteData60);
        eSpriteLoader loader(fTileH, "fisheryBoatBuilding", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 982; i < 992; i++) {
            loader.load(982, i, fFisheryBoatBuildingW);
        }
        for(int i = 992; i < 1002; i++) {
            loader.load(982, i, fFisheryBoatBuildingH);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eFisheryUnpackingOverlaySpriteData15,
                                     eFisheryUnpackingOverlaySpriteData30,
                                     eFisheryUnpackingOverlaySpriteData45,
                                     eFisheryUnpackingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "fisheryUnpackingOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 890; i < 910; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayTL);
        }

        for(int i = 910; i < 930; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayTR);
        }

        for(int i = 930; i < 950; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayBL);
        }

        for(int i = 950; i < 970; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayBR);
        }
    }

    loadFisheryOverlay();
}

void eBuildingTextures::loadFisheryOverlay() {
    if(fFisheryOverlayLoaded) return;
    fFisheryOverlayLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eFisheryOverlaySpriteData15,
                                 eFisheryOverlaySpriteData30,
                                 eFisheryOverlaySpriteData45,
                                 eFisheryOverlaySpriteData60);
    eSpriteLoader loader(fTileH, "fisheryOverlay", sds,
                         &eSprAmbientOffset, fRenderer);

    for(int j = 0; j < 8; j++) {
        fFisheryOverlay.emplace_back(fRenderer);
    }

    for(int i = 2117; i < 2213;) {
        for(int j = 0; j < 8; j++, i++) {
            if(j > 3 && j < 7) continue;
            loader.load(2117, i, fFisheryOverlay[j]);
        }
    }
    for(int i = 2117; i < 2213;) {
        for(int j = 0; j < 8; j++, i++) {
            if(j > 3 && j < 7) continue;
            loader.load(2117, i, fFisheryOverlay[j]);
        }
    }

    generateFlipped(fFisheryOverlay[0], fFisheryOverlay[6]);
    generateFlipped(fFisheryOverlay[1], fFisheryOverlay[5]);
    generateFlipped(fFisheryOverlay[2], fFisheryOverlay[4]);
}

void eBuildingTextures::loadUrchinQuay() {
    if(fUrchinQuayLoaded) return;
    fUrchinQuayLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eUrchinQuaySpriteData15,
                                     eUrchinQuaySpriteData30,
                                     eUrchinQuaySpriteData45,
                                     eUrchinQuaySpriteData60);
        eSpriteLoader loader(fTileH, "urchinQuay", sds,
                             nullptr, fRenderer);

        for(int i = 52; i < 56; i++) {
            loader.load(52, i, fUrchinQuay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eUrchinUnpackingOverlaySpriteData15,
                                     eUrchinUnpackingOverlaySpriteData30,
                                     eUrchinUnpackingOverlaySpriteData45,
                                     eUrchinUnpackingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "urchinUnpackingOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 680; i < 730; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayTL);
        }

        for(int i = 730; i < 780; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayTR);
        }

        for(int i = 780; i < 830; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayBL);
        }

        for(int i = 830; i < 880; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayBR);
        }
    }

    loadFisheryOverlay();
}

void eBuildingTextures::loadCardingShed() {
    if(fCardingShedLoaded) return;
    fCardingShedLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eCardingShedSpriteData15,
                                 eCardingShedSpriteData30,
                                 eCardingShedSpriteData45,
                                 eCardingShedSpriteData60);
    eSpriteLoader loader(fTileH, "cardingShed", sds,
                         nullptr, fRenderer);

    fCardingShed = loader.load(56, 56);
    for(int i = 57; i < 69; i++) {
        loader.load(56, i, fCardingShedOverlay);
    }
}

void eBuildingTextures::loadDairy() {
    if(fDairyLoaded) return;
    fDairyLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDairySpriteData15,
                                 eDairySpriteData30,
                                 eDairySpriteData45,
                                 eDairySpriteData60);
    eSpriteLoader loader(fTileH, "dairy", sds,
                         nullptr, fRenderer);

    fDairy = loader.load(69, 69);
    for(int i = 70; i < 91; i++) {
        loader.load(69, i, fDairyOverlay);
    }
}

void eBuildingTextures::loadGrowersLodge() {
    if(fGrowersLodgeLoaded) return;
    fGrowersLodgeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGrowersLodgeSpriteData15,
                                 eGrowersLodgeSpriteData30,
                                 eGrowersLodgeSpriteData45,
                                 eGrowersLodgeSpriteData60);
    eSpriteLoader loader(fTileH, "growersLodge", sds,
                         nullptr, fRenderer);

    fGrowersLodge = loader.load(91, 91);
    for(int i = 92; i < 102; i++) {
        loader.load(91, i, fGrowersLodgeOverlay);
    }
}

void eBuildingTextures::loadTimberMill() {
    if(fTimberMillLoaded) return;
    fTimberMillLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTimberMillSpriteData15,
                                 eTimberMillSpriteData30,
                                 eTimberMillSpriteData45,
                                 eTimberMillSpriteData60);
    eSpriteLoader loader(fTileH, "timberMill", sds,
                         nullptr, fRenderer);

    fTimberMill = loader.load(1, 1);
    for(int i = 2; i < 12; i++) {
        loader.load(1, i, fTimberMillOverlay);
    }
}

void eBuildingTextures::loadMasonryShop() {
    if(fMasonryShopLoaded) return;
    fMasonryShopLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eMasonryShopSpriteData15,
                                     eMasonryShopSpriteData30,
                                     eMasonryShopSpriteData45,
                                     eMasonryShopSpriteData60);
        eSpriteLoader loader(fTileH, "masonryShop", sds,
                             nullptr, fRenderer);

        fMasonryShop = loader.load(12, 12);
        for(int i = 13; i < 21; i++) {
            loader.load(12, i, fMasonryShopStones);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eMasonryShopOverlaysSpriteData15,
                                     eMasonryShopOverlaysSpriteData30,
                                     eMasonryShopOverlaysSpriteData45,
                                     eMasonryShopOverlaysSpriteData60);
        eSpriteLoader loader(fTileH, "masonryShopOverlays", sds,
                             &eSprAmbientOffset, fRenderer);

        loader.loadSkipFlipped(1937, 1937, 2017, fMasonryShopOverlay1);
        loader.loadSkipFlipped(1937, 2017, 2097, fMasonryShopOverlay2);
    }
}

void eBuildingTextures::loadMint() {
    if(fMintLoaded) return;
    fMintLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eMintSpriteData15,
                                 eMintSpriteData30,
                                 eMintSpriteData45,
                                 eMintSpriteData60);
    eSpriteLoader loader(fTileH, "mint", sds,
                         nullptr, fRenderer);

    fMint = loader.load(21, 21);
    for(int i = 22; i < 32; i++) {
        loader.load(21, i, fMintOverlay);
    }
}

void eBuildingTextures::loadFoundry() {
    if(fFoundryLoaded) return;
    fFoundryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eFoundrySpriteData15,
                                 eFoundrySpriteData30,
                                 eFoundrySpriteData45,
                                 eFoundrySpriteData60);
    eSpriteLoader loader(fTileH, "foundry", sds,
                         nullptr, fRenderer);

    fFoundry = loader.load(36, 36);
    for(int i = 37; i < 49; i++) {
        loader.load(36, i, fFoundryOverlay);
    }
}

void eBuildingTextures::loadArtisansGuild() {
    if(fArtisansGuildLoaded) return;
    fArtisansGuildLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eArtisansGuildSpriteData15,
                                 eArtisansGuildSpriteData30,
                                 eArtisansGuildSpriteData45,
                                 eArtisansGuildSpriteData60);
    eSpriteLoader loader(fTileH, "artisansGuild", sds,
                         nullptr, fRenderer);

    fArtisansGuild = loader.load(49, 49);
    for(int i = 50; i < 60; i++) {
        loader.load(49, i, fArtisansGuildOverlay);
    }
}

void eBuildingTextures::loadOlivePress() {
    if(fOlivePressLoaded) return;
    fOlivePressLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOlivePressSpriteData15,
                                 eOlivePressSpriteData30,
                                 eOlivePressSpriteData45,
                                 eOlivePressSpriteData60);
    eSpriteLoader loader(fTileH, "olivePress", sds,
                         nullptr, fRenderer);

    fOlivePress = loader.load(60, 60);
    for(int i = 61; i < 73; i++) {
        loader.load(60, i, fOlivePressOverlay);
    }
}

void eBuildingTextures::loadWinery() {
    if(fWineryLoaded) return;
    fWineryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eWinerySpriteData15,
                                 eWinerySpriteData30,
                                 eWinerySpriteData45,
                                 eWinerySpriteData60);
    eSpriteLoader loader(fTileH, "winery", sds,
                         nullptr, fRenderer);

    fWinery = loader.load(73, 73);
    for(int i = 74; i < 86; i++) {
        loader.load(73, i, fWineryOverlay);
    }
}

void eBuildingTextures::loadSculptureStudio() {
    if(fSculptureStudioLoaded) return;
    fSculptureStudioLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eSculptureStudioSpriteData15,
                                 eSculptureStudioSpriteData30,
                                 eSculptureStudioSpriteData45,
                                 eSculptureStudioSpriteData60);
    eSpriteLoader loader(fTileH, "sculptureStudio", sds,
                         nullptr, fRenderer);

    fSculptureStudio = loader.load(86, 86);
    for(int i = 87; i < 122; i++) {
        loader.load(86, i, fSculptureStudioOverlay);
    }
}

void eBuildingTextures::loadTriremeWharf() {
    if(fTriremeWharfLoaded) return;
    fTriremeWharfLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTriremeWharfSpriteData15,
                                 eTriremeWharfSpriteData30,
                                 eTriremeWharfSpriteData45,
                                 eTriremeWharfSpriteData60);
    eSpriteLoader loader(fTileH, "triremeWharf", sds,
                         nullptr, fRenderer);

    for(int i = 1; i < 5; i++) {
        loader.load(1, i, fTriremeWharf);
    }
}

void eBuildingTextures::loadHorseRanch() {
    if(fHorseRanchLoaded) return;
    fHorseRanchLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eHorseRanchSpriteData15,
                                     eHorseRanchSpriteData30,
                                     eHorseRanchSpriteData45,
                                     eHorseRanchSpriteData60);
        eSpriteLoader loader(fTileH, "horseRanch", sds,
                             nullptr, fRenderer);

        fHorseRanch = loader.load(5, 5);
        for(int i = 6; i < 22; i++) {
            loader.load(5, i, fHorseRanchOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eHorseRanchEnclosureSpriteData15,
                                     eHorseRanchEnclosureSpriteData30,
                                     eHorseRanchEnclosureSpriteData45,
                                     eHorseRanchEnclosureSpriteData60);
        eSpriteLoader loader(fTileH, "horseRanchEnclosure", sds,
                             nullptr, fRenderer);

        fHorseRanchEnclosure = loader.load(41, 41);
    }
}

void eBuildingTextures::loadArmory() {
    if(fArmoryLoaded) return;
    fArmoryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eArmorySpriteData15,
                                 eArmorySpriteData30,
                                 eArmorySpriteData45,
                                 eArmorySpriteData60);
    eSpriteLoader loader(fTileH, "armory", sds,
                         nullptr, fRenderer);

    fArmory = loader.load(22, 22);
    for(int i = 23; i < 41; i++) {
        loader.load(22, i, fArmoryOverlay);
    }
}

void eBuildingTextures::loadGatehouseAndTower() {
    if(fGatehouseAndTowerLoaded) return;
    fGatehouseAndTowerLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGatehouseAndTowerSpriteData15,
                                 eGatehouseAndTowerSpriteData30,
                                 eGatehouseAndTowerSpriteData45,
                                 eGatehouseAndTowerSpriteData60);
    eSpriteLoader loader(fTileH, "gatehouseAndTower", sds,
                         nullptr, fRenderer);

    loader.load(50, 50, fGatehouseW);
    loader.load(50, 52, fGatehouseW);
    loader.load(50, 54, fGatehouseW);
    loader.load(50, 57, fGatehouseW);

    loader.load(50, 51, fGatehouseH);
    loader.load(50, 53, fGatehouseH);
    loader.load(50, 55, fGatehouseH);
    loader.load(50, 58, fGatehouseH);

    fTower = loader.load(50, 56);
}

void eBuildingTextures::loadWall() {
    if(fWallLoaded) return;
    fWallLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eWallSpriteData15,
                                 eWallSpriteData30,
                                 eWallSpriteData45,
                                 eWallSpriteData60);
    eSpriteLoader loader(fTileH, "wall", sds,
                         nullptr, fRenderer);

    for(int i = 59; i < 95; i++) {
        loader.load(59, i, fWall);
    }
}

void eBuildingTextures::loadMaintenanceOffice() {
    if(fMaintenanceOfficeLoaded) return;
    fMaintenanceOfficeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eMaintenanceOfficeSpriteData15,
                                 eMaintenanceOfficeSpriteData30,
                                 eMaintenanceOfficeSpriteData45,
                                 eMaintenanceOfficeSpriteData60);
    eSpriteLoader loader(fTileH, "maintenanceOffice", sds,
                         nullptr, fRenderer);

    fMaintenanceOffice = loader.load(1, 1);
    for(int i = 2; i < 46; i++) {
        loader.load(1, i, fMaintenanceOfficeOverlay);
    }
}

void eBuildingTextures::loadTaxOffice() {
    if(fTaxOfficeLoaded) return;
    fTaxOfficeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTaxOfficeSpriteData15,
                                 eTaxOfficeSpriteData30,
                                 eTaxOfficeSpriteData45,
                                 eTaxOfficeSpriteData60);
    eSpriteLoader loader(fTileH, "taxOffice", sds,
                         nullptr, fRenderer);

    fTaxOffice = loader.load(46, 46);
    for(int i = 47; i < 65; i++) {
        loader.load(46, i, fTaxOfficeOverlay);
    }
}

void eBuildingTextures::loadWatchpost() {
    if(fWatchpostLoaded) return;
    fWatchpostLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eWatchpostSpriteData15,
                                     eWatchpostSpriteData30,
                                     eWatchpostSpriteData45,
                                     eWatchpostSpriteData60);
        eSpriteLoader loader(fTileH, "watchpost", sds,
                             nullptr, fRenderer);

        fWatchPost = loader.load(65, 65);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eWatchPostOverlaySpriteData15,
                                     eWatchPostOverlaySpriteData30,
                                     eWatchPostOverlaySpriteData45,
                                     eWatchPostOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "watchPostOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2958; i < 3011; i++) {
            loader.load(2958, i, fWatchPostOverlay);
        }
    }
}

void eBuildingTextures::loadRoadblock() {
    if(fRoadblockLoaded) return;
    fRoadblockLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eRoadblockSpriteData15,
                                 eRoadblockSpriteData30,
                                 eRoadblockSpriteData45,
                                 eRoadblockSpriteData60);
    eSpriteLoader loader(fTileH, "roadblock", sds,
                         nullptr, fRenderer);

    fRoadblock = loader.load(76, 76);
}

void eBuildingTextures::loadBridge() {
    if(fBridgeLoaded) return;
    fBridgeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBridgeSpriteData15,
                                 eBridgeSpriteData30,
                                 eBridgeSpriteData45,
                                 eBridgeSpriteData60);
    eSpriteLoader loader(fTileH, "bridge", sds,
                         nullptr, fRenderer);

    for(int i = 77; i < 89; i++) {
        loader.load(77, i, fBridge);
    }
}

void eBuildingTextures::loadPalaceTiles() {
    if(fPalaceTilesLoaded) return;
    fPalaceTilesLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePalaceTilesSpriteData15,
                                 ePalaceTilesSpriteData30,
                                 ePalaceTilesSpriteData45,
                                 ePalaceTilesSpriteData60);
    eSpriteLoader loader(fTileH, "palaceTiles", sds,
                         nullptr, fRenderer);

    loader.load(25, 25, fPalaceTiles);
    loader.load(26, 26, fPalaceTiles);
}

void eBuildingTextures::loadPalace() {
    if(fPalaceLoaded) return;
    fPalaceLoaded = true;

    loadPalaceTiles();

    {
        const auto& sds = spriteData(fTileH,
                                     eMun_PalaceSpriteData15,
                                     eMun_PalaceSpriteData30,
                                     eMun_PalaceSpriteData45,
                                     eMun_PalaceSpriteData60);
        eSpriteLoader loader(fTileH, "mun_Palace", sds,
                             nullptr, fRenderer);

        fPalace2H = loader.load(1, 1);
        fPalace1H = loader.load(1, 12);
        fPalace1W = loader.load(1, 13);
        fPalace2W = loader.load(1, 14);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePalaceOverlaySpriteData15,
                                     ePalaceOverlaySpriteData30,
                                     ePalaceOverlaySpriteData45,
                                     ePalaceOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "palaceOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 3011; i < 3035; i++) {
            loader.load(3011, i, fPalaceHOverlay);
        }

        generateFlipped(fPalaceHOverlay, fPalaceWOverlay);
    }
}

void eBuildingTextures::loadSanctuary() {
    if(fSanctuaryLoaded) return;
    fSanctuaryLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuaryElementsSpriteData15,
                                     eZeusSanctuaryElementsSpriteData30,
                                     eZeusSanctuaryElementsSpriteData45,
                                     eZeusSanctuaryElementsSpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuaryElements", sds,
                             nullptr, fRenderer);

        int i = 1;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                loader.load(1, i, coll);
            }
        };
        loadStatues(fZeusStatues);
        {
            // loadStatues(fPoseidonStatues);
            i += 4;
        }
        loadStatues(fHadesStatues);
        loadStatues(fDemeterStatues);
        loadStatues(fAthenaStatues);
        loadStatues(fArtemisStatues);
        loadStatues(fApolloStatues);
        loadStatues(fAresStatues);
        loadStatues(fHephaestusStatues);
        loadStatues(fAphroditeStatues);
        loadStatues(fHermesStatues);
        loadStatues(fDionysusStatues);

        for(int i = 49; i < 55; i++) {
            loader.load(1, i, fSanctuaryTiles);
        }
        for(int i = 55; i < 61; i++) {
            loader.load(1, i, fSanctuarySpace);
        }

        fSanctuaryAltar = loader.load(1, 61);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonStatues1SpriteData15,
                                     ePoseidonStatues1SpriteData30,
                                     ePoseidonStatues1SpriteData45,
                                     ePoseidonStatues1SpriteData60);
        eSpriteLoader loader(fTileH, "poseidonStatues1", sds,
                             nullptr, fRenderer);

        int i = 1;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                loader.load(1, i, coll);
            }
        };

        loadStatues(fHeraStatues);
        loadStatues(fAtlasStatues);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonStatues2SpriteData15,
                                     ePoseidonStatues2SpriteData30,
                                     ePoseidonStatues2SpriteData45,
                                     ePoseidonStatues2SpriteData60);
        eSpriteLoader loader(fTileH, "poseidonStatues2", sds,
                             nullptr, fRenderer);

        int i = 11;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                loader.load(11, i, coll);
            }
        };

        loadStatues(fPoseidonStatues);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eSanctuaryFireSpriteData15,
                                     eSanctuaryFireSpriteData30,
                                     eSanctuaryFireSpriteData45,
                                     eSanctuaryFireSpriteData60);
        eSpriteLoader loader(fTileH, "sanctuaryFire", sds,
                             &eSprAmbientOffset, fRenderer);


        for(int i = 2105; i < 2117; i++) {
            loader.load(2105, i, fSanctuaryFire);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eSanctuaryOverlaySpriteData15,
                                     eSanctuaryOverlaySpriteData30,
                                     eSanctuaryOverlaySpriteData45,
                                     eSanctuaryOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "sanctuaryOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 1725; i < 1773; i++) {
            loader.load(1725, i, fSanctuaryHOverlay);
        }

        generateFlipped(fSanctuaryHOverlay, fSanctuaryWOverlay);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eBlankStatueSpriteData15,
                                     eBlankStatueSpriteData30,
                                     eBlankStatueSpriteData45,
                                     eBlankStatueSpriteData60);
        eSpriteLoader loader(fTileH, "blankStatue", sds,
                             nullptr, fRenderer);

        fBlankMonument = loader.load(1, 1);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuary1SpriteData15,
                                     eZeusSanctuary1SpriteData30,
                                     eZeusSanctuary1SpriteData45,
                                     eZeusSanctuary1SpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuary1", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            auto& coll = fSanctuary.emplace_back(fRenderer);
            loader.load(1, i, coll);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuary2SpriteData15,
                                     eZeusSanctuary2SpriteData30,
                                     eZeusSanctuary2SpriteData45,
                                     eZeusSanctuary2SpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuary2", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            auto& coll = fSanctuary[i - 1];
            loader.load(1, i, coll);
        }
    }
}

void eBuildingTextures::loadZeusSanctuary() {
    if(fZeusSanctuaryLoaded) return;
    fZeusSanctuaryLoaded = true;

    if(fSanctuary.empty()) loadSanctuary();

    const auto& sds = spriteData(fTileH,
                                 eZeusSanctuary3SpriteData15,
                                 eZeusSanctuary3SpriteData30,
                                 eZeusSanctuary3SpriteData45,
                                 eZeusSanctuary3SpriteData60);
    eSpriteLoader loader(fTileH, "zeusSanctuary3", sds,
                         nullptr, fRenderer);

    for(int i = 1; i < 5; i++) {
        auto& coll = fSanctuary[i - 1];
        loader.load(1, i, coll);
    }
}

void eBuildingTextures::loadHerosHall() {
    if(fHerosHallLoaded) return;
    fHerosHallLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusHerosHallSpriteData15,
                                     eZeusHerosHallSpriteData30,
                                     eZeusHerosHallSpriteData45,
                                     eZeusHerosHallSpriteData60);
        eSpriteLoader loader(fTileH, "zeusHerosHall", sds,
                             nullptr, fRenderer);

        fHeroHall = loader.load(62, 62);
        for(int i = 63; i < 69; i++) {
            loader.load(62, i, fHeroStatues);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonHerosHallSpriteData15,
                                     ePoseidonHerosHallSpriteData30,
                                     ePoseidonHerosHallSpriteData45,
                                     ePoseidonHerosHallSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonHerosHall", sds,
                             nullptr, fRenderer);

        for(int i = 9; i < 11; i++) {
            loader.load(9, i, fHeroStatues);
        }
    }
}

void eBuildingTextures::loadWaitingOverlay() {
    if(fWaitingOverlayLoaded) return;
    fWaitingOverlayLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eWaitingOverlaySpriteData15,
                                 eWaitingOverlaySpriteData30,
                                 eWaitingOverlaySpriteData45,
                                 eWaitingOverlaySpriteData60);
    eSpriteLoader loader(fTileH, "waitingOverlay", sds,
                         &eSprAmbientOffset, fRenderer);

    loader.loadSkipFlipped(2277, 2277, 2437, fWaitingOverlay0);
    loader.loadSkipFlipped(2277, 2437, 2533, fWaitingOverlay1);
}

void eBuildingTextures::loadOrangeTendersLodge() {
    if(fOrangeTendersLodgeLoaded) return;
    fOrangeTendersLodgeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOrangeTendersLodgeSpriteData15,
                                 eOrangeTendersLodgeSpriteData30,
                                 eOrangeTendersLodgeSpriteData45,
                                 eOrangeTendersLodgeSpriteData60);
    eSpriteLoader loader(fTileH, "orangeTendersLodge", sds,
                         nullptr, fRenderer);

    fOrangeTendersLodge = loader.load(51, 51);

    for(int i = 52; i < 87; i++) {
        loader.load(51, i, fOrangeTendersLodgeOverlay);
    }
}

void eBuildingTextures::loadWaterPark() {
    if(fWaterParkLoaded) return;
    fWaterParkLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eWaterParkSpriteData15,
                                 eWaterParkSpriteData30,
                                 eWaterParkSpriteData45,
                                 eWaterParkSpriteData60);
    eSpriteLoader loader(fTileH, "waterPark", sds,
                         nullptr, fRenderer);

    const auto loadWaterPark = [&](const int i,
                                   std::shared_ptr<eTexture>& tex,
                                   eTextureCollection& overlay) {
        tex = loader.load(64, i);
        const int jMax = i + 8;
        for(int j = i + 1; j < jMax; j++) {
            loader.load(64, j, overlay);
        }
    };

    loadWaterPark(64, fWaterPark1, fWaterPark1Overlay);
    loadWaterPark(72, fWaterPark2, fWaterPark2Overlay);
    loadWaterPark(80, fWaterPark3, fWaterPark3Overlay);
    loadWaterPark(88, fWaterPark4, fWaterPark4Overlay);
    loadWaterPark(96, fWaterPark5, fWaterPark5Overlay);
    loadWaterPark(104, fWaterPark6, fWaterPark6Overlay);
    loadWaterPark(112, fWaterPark7, fWaterPark7Overlay);
    loadWaterPark(120, fWaterPark8, fWaterPark8Overlay);
}

void eBuildingTextures::loadBaths() {
    if(fBathsLoaded) return;
    fBathsLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBathsSpriteData15,
                                 eBathsSpriteData30,
                                 eBathsSpriteData45,
                                 eBathsSpriteData60);
    eSpriteLoader loader(fTileH, "baths", sds,
                         nullptr, fRenderer);

    fBaths = loader.load(36, 36);
    for(int i = 37; i < 53; i++) {
        loader.load(36, i, fBathsOverlay);
    }
}

void eBuildingTextures::loadShellGarden() {
    if(fShellGardenLoaded) return;
    fShellGardenLoaded = true;


    const auto& sds = spriteData(fTileH,
                                 eShellGardenSpriteData15,
                                 eShellGardenSpriteData30,
                                 eShellGardenSpriteData45,
                                 eShellGardenSpriteData60);
    eSpriteLoader loader(fTileH, "shellGarden", sds,
                         nullptr, fRenderer);

    fShellGarden = loader.load(35, 35);
}

void eBuildingTextures::loadOrrery() {
    if(fOrreryLoaded) return;
    fOrreryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOrrerySpriteData15,
                                 eOrrerySpriteData30,
                                 eOrrerySpriteData45,
                                 eOrrerySpriteData60);
    eSpriteLoader loader(fTileH, "orrery", sds,
                         nullptr, fRenderer);

    fOrrery = loader.load(34, 34);
}

void eBuildingTextures::loadDolphinSculpture() {
    if(fDolphinSculptureLoaded) return;
    fDolphinSculptureLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDolphinSculptureSpriteData15,
                                 eDolphinSculptureSpriteData30,
                                 eDolphinSculptureSpriteData45,
                                 eDolphinSculptureSpriteData60);
    eSpriteLoader loader(fTileH, "dolphinSculpture", sds,
                         nullptr, fRenderer);

    fDolphinSculpture = loader.load(33, 33);
}

void eBuildingTextures::loadStoneCircle() {
    if(fStoneCircleLoaded) return;
    fStoneCircleLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eStoneCircleSpriteData15,
                                 eStoneCircleSpriteData30,
                                 eStoneCircleSpriteData45,
                                 eStoneCircleSpriteData60);
    eSpriteLoader loader(fTileH, "stoneCircle", sds,
                         nullptr, fRenderer);

    fStoneCircle = loader.load(27, 27);
    for(int i = 28; i < 33; i++) {
        loader.load(27, i, fStoneCircleOverlay);
    }
}

void eBuildingTextures::loadSpring() {
    if(fSpringLoaded) return;
    fSpringLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eSpringSpriteData15,
                                 eSpringSpriteData30,
                                 eSpringSpriteData45,
                                 eSpringSpriteData60);
    eSpriteLoader loader(fTileH, "spring", sds,
                         nullptr, fRenderer);

    for(int i = 20; i < 27; i++) {
        loader.load(20, i, fSpring);
    }
}

void eBuildingTextures::loadTopiary() {
    if(fTopiaryLoaded) return;
    fTopiaryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTopiarySpriteData15,
                                 eTopiarySpriteData30,
                                 eTopiarySpriteData45,
                                 eTopiarySpriteData60);
    eSpriteLoader loader(fTileH, "topiary", sds,
                         nullptr, fRenderer);

    fTopiary = loader.load(19, 19);
}

void eBuildingTextures::loadSundial() {
    if(fSundialLoaded) return;
    fSundialLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eSundialSpriteData15,
                                 eSundialSpriteData30,
                                 eSundialSpriteData45,
                                 eSundialSpriteData60);
    eSpriteLoader loader(fTileH, "sundial", sds,
                         nullptr, fRenderer);

    fSundial = loader.load(18, 18);
}

void eBuildingTextures::loadTallObelisk() {
    if(fTallObeliskLoaded) return;
    fTallObeliskLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eTallObeliskSpriteData15,
                                 eTallObeliskSpriteData30,
                                 eTallObeliskSpriteData45,
                                 eTallObeliskSpriteData60);
    eSpriteLoader loader(fTileH, "tallObelisk", sds,
                         nullptr, fRenderer);

    fTallObelisk = loader.load(17, 17);
}

void eBuildingTextures::loadAvenue() {
    if(fAvenueLoaded) return;
    fAvenueLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eAvenueSpriteData15,
                                 eAvenueSpriteData30,
                                 eAvenueSpriteData45,
                                 eAvenueSpriteData60);
    eSpriteLoader loader(fTileH, "avenue", sds,
                         nullptr, fRenderer);

    for(int i = 39; i < 88; i++) {
        loader.load(39, i, fAvenueRoad);
    }

    fAvenue.emplace_back(fRenderer);
    for(int i = 88; i < 97; i++) {
        loader.load(39, i, fAvenue[0]);
    }

    fAvenue.emplace_back(fRenderer);
    for(int i = 97; i < 106; i++) {
        loader.load(39, i, fAvenue[1]);
    }

    fAvenue.emplace_back(fRenderer);
    for(int i = 106; i < 115; i++) {
        loader.load(39, i, fAvenue[2]);
    }

    fAvenue.emplace_back(fRenderer);
    for(int i = 115; i < 124; i++) {
        loader.load(39, i, fAvenue[3]);
    }

    fAvenue.emplace_back(fRenderer);
    for(int i = 124; i < 132; i++) {
        loader.load(39, i, fAvenue[4]);
    }
}

void eBuildingTextures::loadColumns() {
    if(fColumnsLoaded) return;
    fColumnsLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eColumnsSpriteData15,
                                 eColumnsSpriteData30,
                                 eColumnsSpriteData45,
                                 eColumnsSpriteData60);
    eSpriteLoader loader(fTileH, "columns", sds,
                         nullptr, fRenderer);

    fDoricColumn = loader.load(34, 34);
    fIonicColumn = loader.load(34, 35);
    fCorinthianColumn = loader.load(34, 36);

    fColumnConnectionH = loader.load(34, 37);
    fColumnConnectionW = loader.load(34, 38);
}

void eBuildingTextures::loadCommemorative() {
    if(fCommemorativeLoaded) return;
    fCommemorativeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eCommemorativeSpriteData15,
                                 eCommemorativeSpriteData30,
                                 eCommemorativeSpriteData45,
                                 eCommemorativeSpriteData60);
    eSpriteLoader loader(fTileH, "commemorative", sds,
                         nullptr, fRenderer);

    for(int i = 25; i < 34; i++) {
        loader.load(25, i, fCommemorative);
    }
}

void eBuildingTextures::loadFishPond() {
    if(fFishPondLoaded) return;
    fFishPondLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eFishPondSpriteData15,
                                     eFishPondSpriteData30,
                                     eFishPondSpriteData45,
                                     eFishPondSpriteData60);
        eSpriteLoader loader(fTileH, "fishPond", sds,
                             nullptr, fRenderer);

        fFishPond = loader.load(24, 24);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eFishPondOverlaySpriteData15,
                                     eFishPondOverlaySpriteData30,
                                     eFishPondOverlaySpriteData45,
                                     eFishPondOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "fishPondOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2759; i < 2790; i++) {
            loader.load(2759, i, fFishPondOverlay);
        }
    }
}

void eBuildingTextures::loadHedgeMaze() {
    if(fHedgeMazeLoaded) return;
    fHedgeMazeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHedgeMazeSpriteData15,
                                 eHedgeMazeSpriteData30,
                                 eHedgeMazeSpriteData45,
                                 eHedgeMazeSpriteData60);
    eSpriteLoader loader(fTileH, "hedgeMaze", sds,
                         nullptr, fRenderer);

    fHedgeMaze = loader.load(23, 23);
}

void eBuildingTextures::loadGazebo() {
    if(fGazeboLoaded) return;
    fGazeboLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGazeboSpriteData15,
                                 eGazeboSpriteData30,
                                 eGazeboSpriteData45,
                                 eGazeboSpriteData60);
    eSpriteLoader loader(fTileH, "gazebo", sds,
                         nullptr, fRenderer);

    fGazebo = loader.load(22, 22);
}

void eBuildingTextures::loadFlowerGarden() {
    if(fFlowerGardenLoaded) return;
    fFlowerGardenLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eFlowerGardenSpriteData15,
                                 eFlowerGardenSpriteData30,
                                 eFlowerGardenSpriteData45,
                                 eFlowerGardenSpriteData60);
    eSpriteLoader loader(fTileH, "flowerGarden", sds,
                         nullptr, fRenderer);

    fFlowerGarden = loader.load(21, 21);
}

void eBuildingTextures::loadBench() {
    if(fBenchLoaded) return;
    fBenchLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBenchSpriteData15,
                                 eBenchSpriteData30,
                                 eBenchSpriteData45,
                                 eBenchSpriteData60);
    eSpriteLoader loader(fTileH, "bench", sds,
                         nullptr, fRenderer);

    fBench = loader.load(20, 20);
}

void eBuildingTextures::loadPark() {
    if(fParkLoaded) return;
    fParkLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eParkSpriteData15,
                                 eParkSpriteData30,
                                 eParkSpriteData45,
                                 eParkSpriteData60);
    eSpriteLoader loader(fTileH, "park", sds,
                         nullptr, fRenderer);

    for(int i = 12; i < 16; i++) {
        loader.load(12, i, fPark);
    }
    for(int i = 16; i < 19; i++) {
        loader.load(12, i, fLargePark);
    }
    loader.load(12, 19, fHugePark);
}

void eBuildingTextures::loadBirdBath() {
    if(fBirdBathLoaded) return;
    fBirdBathLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBirdBathSpriteData15,
                                 eBirdBathSpriteData30,
                                 eBirdBathSpriteData45,
                                 eBirdBathSpriteData60);
    eSpriteLoader loader(fTileH, "birdBath", sds,
                         nullptr, fRenderer);

    fBirdBath = loader.load(53, 53);
    for(int i = 54; i < 63; i++) {
        loader.load(53, i, fBirdBathOverlay);
    }
}

void eBuildingTextures::loadShortObelisk() {
    if(fShortObeliskLoaded) return;
    fShortObeliskLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eShortObeliskSpriteData15,
                                 eShortObeliskSpriteData30,
                                 eShortObeliskSpriteData45,
                                 eShortObeliskSpriteData60);
    eSpriteLoader loader(fTileH, "shortObelisk", sds,
                         nullptr, fRenderer);

    fShortObelisk = loader.load(63, 63);
}

void eBuildingTextures::loadZeusMonuments() {
    if(fZeusMonumentsLoaded) return;
    fZeusMonumentsLoaded = true;
    loadGodMonuments(eZeusStatueSpriteData15,
                     eZeusStatueSpriteData30,
                     eZeusStatueSpriteData45,
                     eZeusStatueSpriteData60,
                     "zeusStatue",
                     fZeusMonuments);
}

void eBuildingTextures::loadPoseidonMonuments() {
    if(fPoseidonMonumentsLoaded) return;
    fPoseidonMonumentsLoaded = true;
    loadGodMonuments(ePoseidonStatueSpriteData15,
                     ePoseidonStatueSpriteData30,
                     ePoseidonStatueSpriteData45,
                     ePoseidonStatueSpriteData60,
                     "poseidonStatue",
                     fPoseidonMonuments);
}

void eBuildingTextures::loadHadesMonuments() {
    if(fHadesMonumentsLoaded) return;
    fHadesMonumentsLoaded = true;
    loadGodMonuments(eHadesStatueSpriteData15,
                     eHadesStatueSpriteData30,
                     eHadesStatueSpriteData45,
                     eHadesStatueSpriteData60,
                     "hadesStatue",
                     fHadesMonuments);
}

void eBuildingTextures::loadDemeterMonuments() {
    if(fDemeterMonumentsLoaded) return;
    fDemeterMonumentsLoaded = true;
    loadGodMonuments(eDemeterStatueSpriteData15,
                     eDemeterStatueSpriteData30,
                     eDemeterStatueSpriteData45,
                     eDemeterStatueSpriteData60,
                     "demeterStatue",
                     fDemeterMonuments);
}

void eBuildingTextures::loadAthenaMonuments() {
    if(fAthenaMonumentsLoaded) return;
    fAthenaMonumentsLoaded = true;
    loadGodMonuments(eAthenaStatueSpriteData15,
                     eAthenaStatueSpriteData30,
                     eAthenaStatueSpriteData45,
                     eAthenaStatueSpriteData60,
                     "athenaStatue",
                     fAthenaMonuments);
}

void eBuildingTextures::loadArtemisMonuments() {
    if(fArtemisMonumentsLoaded) return;
    fArtemisMonumentsLoaded = true;
    loadGodMonuments(eArtemisStatueSpriteData15,
                     eArtemisStatueSpriteData30,
                     eArtemisStatueSpriteData45,
                     eArtemisStatueSpriteData60,
                     "artemisStatue",
                     fArtemisMonuments);
}

void eBuildingTextures::loadApolloMonuments() {
    if(fApolloMonumentsLoaded) return;
    fApolloMonumentsLoaded = true;
    loadGodMonuments(eApolloStatueSpriteData15,
                     eApolloStatueSpriteData30,
                     eApolloStatueSpriteData45,
                     eApolloStatueSpriteData60,
                     "apolloStatue",
                     fApolloMonuments);
}

void eBuildingTextures::loadAresMonuments() {
    if(fAresMonumentsLoaded) return;
    fAresMonumentsLoaded = true;
    loadGodMonuments(eAresStatueSpriteData15,
                     eAresStatueSpriteData30,
                     eAresStatueSpriteData45,
                     eAresStatueSpriteData60,
                     "aresStatue",
                     fAresMonuments);
}

void eBuildingTextures::loadHephaestusMonuments() {
    if(fHephaestusMonumentsLoaded) return;
    fHephaestusMonumentsLoaded = true;
    loadGodMonuments(eHephaestusStatueSpriteData15,
                     eHephaestusStatueSpriteData30,
                     eHephaestusStatueSpriteData45,
                     eHephaestusStatueSpriteData60,
                     "hephaestusStatue",
                     fHephaestusMonuments);
}

void eBuildingTextures::loadAphroditeMonuments() {
    if(fAphroditeMonumentsLoaded) return;
    fAphroditeMonumentsLoaded = true;
    loadGodMonuments(eAphroditeStatueSpriteData15,
                     eAphroditeStatueSpriteData30,
                     eAphroditeStatueSpriteData45,
                     eAphroditeStatueSpriteData60,
                     "aphroditeStatue",
                     fAphroditeMonuments);
}

void eBuildingTextures::loadHermesMonuments() {
    if(fHermesMonumentsLoaded) return;
    fHermesMonumentsLoaded = true;
    loadGodMonuments(eHermesStatueSpriteData15,
                     eHermesStatueSpriteData30,
                     eHermesStatueSpriteData45,
                     eHermesStatueSpriteData60,
                     "hermesStatue",
                     fHermesMonuments);
}

void eBuildingTextures::loadDionysusMonuments() {
    if(fDionysusMonumentsLoaded) return;
    fDionysusMonumentsLoaded = true;
    loadGodMonuments(eDionysusStatueSpriteData15,
                     eDionysusStatueSpriteData30,
                     eDionysusStatueSpriteData45,
                     eDionysusStatueSpriteData60,
                     "dionysusStatue",
                     fDionysusMonuments);
}

void eBuildingTextures::loadAtlasMonuments() {
    if(fAtlasMonumentsLoaded) return;
    fAtlasMonumentsLoaded = true;
    loadGodMonuments(eAtlasStatueSpriteData15,
                     eAtlasStatueSpriteData30,
                     eAtlasStatueSpriteData45,
                     eAtlasStatueSpriteData60,
                     "atlasStatue",
                     fAtlasMonuments);
}

void eBuildingTextures::loadHeraMonuments() {
    if(fHeraMonumentsLoaded) return;
    fHeraMonumentsLoaded = true;
    loadGodMonuments(eHeraStatueSpriteData15,
                     eHeraStatueSpriteData30,
                     eHeraStatueSpriteData45,
                     eHeraStatueSpriteData60,
                     "heraStatue",
                     fHeraMonuments);
}

void eBuildingTextures::loadAgora() {
    if(fAgoraLoaded) return;
    fAgoraLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eAgoraSpriteData15,
                                     eAgoraSpriteData30,
                                     eAgoraSpriteData45,
                                     eAgoraSpriteData60);
        eSpriteLoader loader(fTileH, "agora", sds,
                             nullptr, fRenderer);

        fFoodVendor = loader.load(1, 1);
        fFoodVendorOverlay = loader.load(1, 2);
        fFleeceVendor = loader.load(1, 3);
        fFleeceVendorOverlay = loader.load(1, 4);
        fOilVendor = loader.load(1, 5);
        fOilVendorOverlay = loader.load(1, 6);
        fWineVendor = loader.load(1, 7);
        fWineVendorOverlay = loader.load(1, 8);
        fArmsVendor = loader.load(1, 9);
        fArmsVendorOverlay = loader.load(1, 10);
        fHorseTrainer = loader.load(1, 11);
        fHorseTrainerOverlay = loader.load(1, 12);

        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fAgoraRoad);
        }
        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fAgora);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eVendorOverlaysSpriteData15,
                                     eVendorOverlaysSpriteData30,
                                     eVendorOverlaysSpriteData45,
                                     eVendorOverlaysSpriteData60);
        eSpriteLoader loader(fTileH, "vendorOverlays", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2639; i < 2651; i++) {
            loader.load(2639, i, fFleeceVendorOverlay2);
        }

        for(int i = 2651; i < 2663; i++) {
            loader.load(2639, i, fFoodVendorOverlay2);
        }

        for(int i = 2663; i < 2679; i++) {
            loader.load(2639, i, fHorseTrainerOverlay2);
        }

        for(int i = 2679; i < 2719; i++) {
            loader.load(2639, i, fOilVendorOverlay2);
        }

        for(int i = 2719; i < 2759; i++) {
            loader.load(2639, i, fArmsVendorOverlay2);
        }
    }
}

void eBuildingTextures::loadChariotVendor() {
    if(fChariotVendorLoaded) return;
    fChariotVendorLoaded = true;
    {
        const auto& sds = spriteData(fTileH,
                                     eChariotVendorSpriteData15,
                                     eChariotVendorSpriteData30,
                                     eChariotVendorSpriteData45,
                                     eChariotVendorSpriteData60);
        eSpriteLoader loader(fTileH, "chariotVendor", sds,
                             nullptr, fRenderer);

        fChariotVendor = loader.load(49, 49);
        fChariotVendorOverlay = loader.load(49, 50);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eChariotVendorOverlaySpriteData15,
                                     eChariotVendorOverlaySpriteData30,
                                     eChariotVendorOverlaySpriteData45,
                                     eChariotVendorOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "chariotVendorOverlay", sds,
                             &ePoseidonImpsOffset, fRenderer);

        for(int i = 3674; i < 3718; i++) {
            loader.load(3674, i, fChariotVendorOverlay2);
        }
    }
}

void eBuildingTextures::loadWineVendor() {
    if(fWIneVendorLoaded) return;
    fWIneVendorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eWineVendorOverlaySpriteData15,
                                 eWineVendorOverlaySpriteData30,
                                 eWineVendorOverlaySpriteData45,
                                 eWineVendorOverlaySpriteData60);
    eSpriteLoader loader(fTileH, "wineVendorOverlay", sds,
                         &eSprAmbientOffset, fRenderer);

    for(int i = 429; i < 453; i++) {
        loader.load(429, i, fWineVendorOverlay2);
    }
}

void eBuildingTextures::loadGranary() {
    if(fGranaryLoaded) return;
    fGranaryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eGranarySpriteData15,
                                 eGranarySpriteData30,
                                 eGranarySpriteData45,
                                 eGranarySpriteData60);
    eSpriteLoader loader(fTileH, "granary", sds,
                         nullptr, fRenderer);

    fGranary = loader.load(29, 29);
    for(int i = 30; i < 46; i++) {
        loader.load(29, i, fGranaryOverlay);
    }

    fGranaryUrchin = loader.load(29, 46);
    fGranaryFish = loader.load(29, 47);
    fGranaryMeat = loader.load(29, 48);
    fGranaryCheese = loader.load(29, 49);
    fGranaryCheese->setOffset(-3, 2);
    fGranaryCarrots = loader.load(29, 50);
    fGranaryOnions = loader.load(29, 51);
    fGranaryOnions->setOffset(-4, 0);
    fGranaryWheat = loader.load(29, 52);
}

void eBuildingTextures::loadPier() {
    if(fPierLoaded) return;
    fPierLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     ePier1SpriteData15,
                                     ePier1SpriteData30,
                                     ePier1SpriteData45,
                                     ePier1SpriteData60);
        eSpriteLoader loader(fTileH, "pier1", sds,
                             nullptr, fRenderer);

        for(int i = 19; i < 23; i++) {
            loader.load(19, i, fPier1);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePier2SpriteData15,
                                     ePier2SpriteData30,
                                     ePier2SpriteData45,
                                     ePier2SpriteData60);
        eSpriteLoader loader(fTileH, "pier2", sds,
                             nullptr, fRenderer);


        fPier2 = loader.load(25, 25);
        fPier2->setOffset(-88, 90);
    }
}

void eBuildingTextures::loadTradingPost() {
    if(fTradingPostLoaded) return;
    fTradingPostLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eTradingPostOverlaySpriteData15,
                                     eTradingPostOverlaySpriteData30,
                                     eTradingPostOverlaySpriteData45,
                                     eTradingPostOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "tradingPostOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 43; i < 82; i++) {
            loader.load(43, i, fTradingPostOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eTradingPostSpriteData15,
                                     eTradingPostSpriteData30,
                                     eTradingPostSpriteData45,
                                     eTradingPostSpriteData60);
        eSpriteLoader loader(fTileH, "tradingPost", sds,
                             nullptr, fRenderer);

        fTradingPost = loader.load(27, 27);
        fTradingPost->setOffset(-88, 90);
    }
}

void eBuildingTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eWarehouseOverlaySpriteData15,
                                     eWarehouseOverlaySpriteData30,
                                     eWarehouseOverlaySpriteData45,
                                     eWarehouseOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "warehouseOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 269; i < 293; i++) {
            loader.load(269, i, fWarehouseOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eFishSpriteData15,
                                     eFishSpriteData30,
                                     eFishSpriteData45,
                                     eFishSpriteData60);
        eSpriteLoader loader(fTileH, "fish", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 453; i < 493; i++) {
            loader.load(453, i, fFish);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eUrchinSpriteData15,
                                     eUrchinSpriteData30,
                                     eUrchinSpriteData45,
                                     eUrchinSpriteData60);
        eSpriteLoader loader(fTileH, "urchin", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 3035; i < 3051; i++) {
            loader.load(3035, i, fUrchin);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStor_baysSpriteData15,
                                     eStor_baysSpriteData30,
                                     eStor_baysSpriteData45,
                                     eStor_baysSpriteData60);
        eSpriteLoader loader(fTileH, "stor_bays", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            loader.load(1, i, fWarehouseUrchin);
        }
        for(int i = 5; i < 9; i++) {
            loader.load(1, i, fWarehouseFish);
        }
        for(int i = 9; i < 13; i++) {
            loader.load(1, i, fWarehouseMeat);
        }
        for(int i = 13; i < 17; i++) {
            loader.load(1, i, fWarehouseCheese);
        }
        for(int i = 17; i < 21; i++) {
            loader.load(1, i, fWarehouseCarrots);
        }
        for(int i = 21; i < 25; i++) {
            loader.load(1, i, fWarehouseOnions);
        }
        for(int i = 25; i < 29; i++) {
            loader.load(1, i, fWarehouseWheat);
        }
        for(int i = 29; i < 33; i++) {
            loader.load(1, i, fWarehouseWood);
        }
        for(int i = 33; i < 37; i++) {
            loader.load(1, i, fWarehouseBronze);
        }
        for(int i = 37; i < 41; i++) {
            loader.load(1, i, fWarehouseMarble);
        }
        for(int i = 41; i < 45; i++) {
            loader.load(1, i, fWarehouseGrapes);
        }
        for(int i = 45; i < 49; i++) {
            loader.load(1, i, fWarehouseOlives);
        }
        for(int i = 49; i < 53; i++) {
            loader.load(1, i, fWarehouseFleece);
        }
        for(int i = 53; i < 57; i++) {
            loader.load(1, i, fWarehouseArmor);
        }
        fWarehouseSculpture = loader.load(1, 57);
        for(int i = 58; i < 62; i++) {
            loader.load(1, i, fWarehouseOliveOil);
        }
        for(int i = 62; i < 66; i++) {
            loader.load(1, i, fWarehouseWine);
        }


        for(int i = 71; i < 76; i++) {
            loader.load(1, i, fWaitingMeat);
        }
        for(int i = 76; i < 81; i++) {
            loader.load(1, i, fWaitingCheese);
        }
        for(int i = 81; i < 89; i++) {
            loader.load(1, i, fWaitingWheat);
        }
        for(int i = 89; i < 94; i++) {
            loader.load(1, i, fWaitingWood);
        }
        for(int i = 94; i < 99; i++) {
            loader.load(1, i, fWaitingBronze);
        }
        for(int i = 99; i < 102; i++) {
            loader.load(1, i, fWaitingGrapes);
        }
        for(int i = 102; i < 105; i++) {
            loader.load(1, i, fWaitingOlives);
        }
        for(int i = 105; i < 110; i++) {
            loader.load(1, i, fWaitingArmor);
        }

        fWarehouseEmpty = loader.load(1, 115);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eWarehouseSpriteData15,
                                     eWarehouseSpriteData30,
                                     eWarehouseSpriteData45,
                                     eWarehouseSpriteData60);
        eSpriteLoader loader(fTileH, "warehouse", sds,
                             nullptr, fRenderer);

        fWarehouse = loader.load(23, 23);
        fWarehouse->setOffset(-58, 60);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStorageSpriteData15,
                                     eStorageSpriteData30,
                                     eStorageSpriteData45,
                                     eStorageSpriteData60);
        eSpriteLoader loader(fTileH, "storage", sds,
                             nullptr, fRenderer);


//        fCorral = std::make_shared<eTexture>();
//        fCorral->load(fRenderer, pathBase + "00001.png");

//        for(int i = 2; i < 49; i++) {
//            eTextureLoadingHelpers::loadTex(pathBase, i, fCorralOverlay);
//        }

        for(int i = 87; i < 91; i++) {
            loader.load(87, i, fWarehouseOranges);
        }

        for(int i = 99; i < 104; i++) {
            loader.load(87, i, fWaitingOranges);
        }

        for(int i = 110; i < 114; i++) {
            loader.load(87, i, fChariotFactoryChariots);
        }

        fGranaryOranges = loader.load(87, 122);
        fGranaryOranges->setOffset(-3, -3);

        for(int i = 123; i < 129; i++) {
            loader.load(87, i, fOrangeTree);
        }
    }


    {
        const auto& sds = spriteData(fTileH,
                                     eInterfaceSpritesSpriteData15,
                                     eInterfaceSpritesSpriteData30,
                                     eInterfaceSpritesSpriteData45,
                                     eInterfaceSpritesSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceSprites", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 4; i++) {
            loader.load(1, i, fColumn1);
        }
        for(int i = 4; i < 7; i++) {
            loader.load(1, i, fColumn2);
        }
        for(int i = 7; i < 10; i++) {
            loader.load(1, i, fColumn3);
        }
        for(int i = 10; i < 13; i++) {
            loader.load(1, i, fColumn4);
        }
        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fColumn5);
        }

        for(int i = 20; i < 28; i++) {
            loader.load(1, i, fSpawner);
        }
        fDisasterPoint = loader.load(1, 28);
        fLandInvasionPoint = loader.load(1, 29);
        fEntryPoint = loader.load(1, 30);
        fExitPoint = loader.load(1, 31);
        fRiverEntryPoint = loader.load(1, 32);
        fRiverExitPoint = loader.load(1, 33);
        fFishPoint = loader.load(1, 34);
        fUrchinPoint = loader.load(1, 35);
        fWolfPoint = loader.load(1, 36);
        fBoarPoint = loader.load(1, 37);
        fMonsterPoint = loader.load(1, 38);
    }
}

void eBuildingTextures::loadGodMonuments(
        const std::vector<eSpriteData>& sd15,
        const std::vector<eSpriteData>& sd30,
        const std::vector<eSpriteData>& sd45,
        const std::vector<eSpriteData>& sd60,
        const std::string& name,
        eTextureCollection& coll) {
    const auto& sds = spriteData(fTileH, sd15, sd30, sd45, sd60);
    eSpriteLoader loader(fTileH, name, sds, nullptr, fRenderer);
    for(int i = 1; i < 5; i++) {
        loader.load(1, i, coll);
    }
}

void eBuildingTextures::generateFlipped(const eTextureCollection& src,
                                        eTextureCollection& dst) {
    for(int i = 0; i < src.size(); i++) {
        auto& tex = dst.addTexture();
        const auto& srcTex = src.getTexture(i);
        const int w = srcTex->width();
        const int ox = srcTex->offsetX();
        const int oy = srcTex->offsetY();
        tex->setOffset(w - ox, oy);
        tex->setFlipTex(srcTex);
    }
}
