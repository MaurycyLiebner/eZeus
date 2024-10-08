#include "ebuildingmode.h"

eBuildingType eBuildingModeHelpers::toBuildingType(const eBuildingMode mode) {
    switch(mode) {
    case eBuildingMode::none:
        return eBuildingType::none;
    case eBuildingMode::erase:
        return eBuildingType::erase;

    case eBuildingMode::road:
        return eBuildingType::road;

    case eBuildingMode::commonHousing:
        return eBuildingType::commonHouse;
    case eBuildingMode::eliteHousing:
        return eBuildingType::eliteHousing;

    case eBuildingMode::wheatFarm:
        return eBuildingType::wheatFarm;
    case eBuildingMode::carrotFarm:
        return eBuildingType::carrotsFarm;
    case eBuildingMode::onionFarm:
        return eBuildingType::onionsFarm;

    case eBuildingMode::vine:
        return eBuildingType::vine;
    case eBuildingMode::oliveTree:
        return eBuildingType::oliveTree;
    case eBuildingMode::orangeTree:
        return eBuildingType::orangeTree;
    case eBuildingMode::orangeTendersLodge:
        return eBuildingType::orangeTendersLodge;
    case eBuildingMode::growersLodge:
        return eBuildingType::growersLodge;

    case eBuildingMode::dairy:
        return eBuildingType::dairy;
    case eBuildingMode::goat:
        return eBuildingType::goat;
    case eBuildingMode::cardingShed:
        return eBuildingType::cardingShed;
    case eBuildingMode::sheep:
        return eBuildingType::sheep;
    case eBuildingMode::cattle:
        return eBuildingType::cattle;

    case eBuildingMode::fishery:
        return eBuildingType::fishery;
    case eBuildingMode::urchinQuay:
        return eBuildingType::urchinQuay;
    case eBuildingMode::huntingLodge:
        return eBuildingType::huntingLodge;
    case eBuildingMode::corral:
        return eBuildingType::corral;

    case eBuildingMode::mint:
        return eBuildingType::mint;
    case eBuildingMode::foundry:
        return eBuildingType::foundry;
    case eBuildingMode::timberMill:
        return eBuildingType::timberMill;
    case eBuildingMode::masonryShop:
        return eBuildingType::masonryShop;

    case eBuildingMode::winery:
        return eBuildingType::winery;
    case eBuildingMode::olivePress:
        return eBuildingType::olivePress;
    case eBuildingMode::sculptureStudio:
        return eBuildingType::sculptureStudio;
    case eBuildingMode::artisansGuild:
        return eBuildingType::artisansGuild;
    case eBuildingMode::armory:
        return eBuildingType::armory;
    case eBuildingMode::horseRanch:
        return eBuildingType::horseRanch;
    case eBuildingMode::chariotFactory:
        return eBuildingType::chariotFactory;

    case eBuildingMode::wall:
        return eBuildingType::wall;
    case eBuildingMode::tower:
        return eBuildingType::tower;
    case eBuildingMode::gatehouse:
        return eBuildingType::gatehouse;

    case eBuildingMode::podium:
        return eBuildingType::podium;
    case eBuildingMode::college:
        return eBuildingType::college;

    case eBuildingMode::theater:
        return eBuildingType::theater;
    case eBuildingMode::dramaSchool:
        return eBuildingType::dramaSchool;

    case eBuildingMode::gymnasium:
        return eBuildingType::gymnasium;
    case eBuildingMode::stadium:
        return eBuildingType::stadium;

    case eBuildingMode::bibliotheke:
        return eBuildingType::bibliotheke;

    case eBuildingMode::observatory:
        return eBuildingType::observatory;
    case eBuildingMode::university:
        return eBuildingType::university;

    case eBuildingMode::laboratory:
        return eBuildingType::laboratory;
    case eBuildingMode::inventorsWorkshop:
        return eBuildingType::inventorsWorkshop;

    case eBuildingMode::museum:
        return eBuildingType::museum;

    case eBuildingMode::granary:
        return eBuildingType::granary;
    case eBuildingMode::warehouse:
        return eBuildingType::warehouse;

    case eBuildingMode::tradePost:
        return eBuildingType::tradePost;
    case eBuildingMode::pier:
        return eBuildingType::pier;


    case eBuildingMode::commonAgora:
        return eBuildingType::commonAgora;
    case eBuildingMode::grandAgora:
        return eBuildingType::grandAgora;
    case eBuildingMode::foodVendor:
        return eBuildingType::foodVendor;
    case eBuildingMode::fleeceVendor:
        return eBuildingType::fleeceVendor;
    case eBuildingMode::oilVendor:
        return eBuildingType::oilVendor;
    case eBuildingMode::wineVendor:
        return eBuildingType::wineVendor;
    case eBuildingMode::armsVendor:
        return eBuildingType::armsVendor;
    case eBuildingMode::horseTrainer:
        return eBuildingType::horseTrainer;
    case eBuildingMode::chariotVendor:
        return eBuildingType::chariotVendor;

    case eBuildingMode::maintenanceOffice:
        return eBuildingType::maintenanceOffice;
    case eBuildingMode::fountain:
        return eBuildingType::fountain;
    case eBuildingMode::hospital:
        return eBuildingType::hospital;
    case eBuildingMode::watchpost:
        return eBuildingType::watchPost;

    case eBuildingMode::taxOffice:
        return eBuildingType::taxOffice;
    case eBuildingMode::palace:
        return eBuildingType::palace;
    case eBuildingMode::bridge:
        return eBuildingType::bridge;

    case eBuildingMode::park:
        return eBuildingType::park;
    case eBuildingMode::doricColumn:
        return eBuildingType::doricColumn;
    case eBuildingMode::ionicColumn:
        return eBuildingType::ionicColumn;
    case eBuildingMode::corinthianColumn:
        return eBuildingType::corinthianColumn;
    case eBuildingMode::avenue:
        return eBuildingType::avenue;

    case eBuildingMode::populationMonument:
    case eBuildingMode::victoryMonument:
    case eBuildingMode::colonyMonument:
    case eBuildingMode::athleteMonument:
    case eBuildingMode::conquestMonument:
    case eBuildingMode::happinessMonument:
    case eBuildingMode::heroicFigureMonument:
    case eBuildingMode::diplomacyMonument:
    case eBuildingMode::scholarMonument:
        return eBuildingType::commemorative;

    case eBuildingMode::aphroditeMonument:
    case eBuildingMode::apolloMonument:
    case eBuildingMode::aresMonument:
    case eBuildingMode::artemisMonument:
    case eBuildingMode::athenaMonument:
    case eBuildingMode::atlasMonument:
    case eBuildingMode::demeterMonument:
    case eBuildingMode::dionysusMonument:
    case eBuildingMode::hadesMonument:
    case eBuildingMode::hephaestusMonument:
    case eBuildingMode::heraMonument:
    case eBuildingMode::hermesMonument:
    case eBuildingMode::poseidonMonument:
    case eBuildingMode::zeusMonument:
        return eBuildingType::godMonument;

    case eBuildingMode::bench:
        return eBuildingType::bench;
    case eBuildingMode::flowerGarden:
        return eBuildingType::flowerGarden;
    case eBuildingMode::gazebo:
        return eBuildingType::gazebo;
    case eBuildingMode::hedgeMaze:
        return eBuildingType::hedgeMaze;
    case eBuildingMode::fishPond:
        return eBuildingType::fishPond;

    case eBuildingMode::waterPark:
        return eBuildingType::waterPark;

    case eBuildingMode::birdBath:
        return eBuildingType::birdBath;
    case eBuildingMode::shortObelisk:
        return eBuildingType::shortObelisk;
    case eBuildingMode::tallObelisk:
        return eBuildingType::tallObelisk;
    case eBuildingMode::shellGarden:
        return eBuildingType::shellGarden;
    case eBuildingMode::sundial:
        return eBuildingType::sundial;
    case eBuildingMode::dolphinSculpture:
        return eBuildingType::dolphinSculpture;
    case eBuildingMode::orrery:
        return eBuildingType::orrery;
    case eBuildingMode::spring:
        return eBuildingType::spring;
    case eBuildingMode::topiary:
        return eBuildingType::topiary;
    case eBuildingMode::baths:
        return eBuildingType::baths;
    case eBuildingMode::stoneCircle:
        return eBuildingType::stoneCircle;

    case eBuildingMode::templeAphrodite:
        return eBuildingType::templeAphrodite;
    case eBuildingMode::templeApollo:
        return eBuildingType::templeApollo;
    case eBuildingMode::templeAres:
        return eBuildingType::templeAres;
    case eBuildingMode::templeArtemis:
        return eBuildingType::templeArtemis;
    case eBuildingMode::templeAthena:
        return eBuildingType::templeAthena;
    case eBuildingMode::templeAtlas:
        return eBuildingType::templeAtlas;
    case eBuildingMode::templeDemeter:
        return eBuildingType::templeDemeter;
    case eBuildingMode::templeDionysus:
        return eBuildingType::templeDionysus;
    case eBuildingMode::templeHades:
        return eBuildingType::templeHades;
    case eBuildingMode::templeHephaestus:
        return eBuildingType::templeHephaestus;
    case eBuildingMode::templeHera:
        return eBuildingType::templeHera;
    case eBuildingMode::templeHermes:
        return eBuildingType::templeHermes;
    case eBuildingMode::templePoseidon:
        return eBuildingType::templePoseidon;
    case eBuildingMode::templeZeus:
        return eBuildingType::templeZeus;

    case eBuildingMode::achillesHall:
        return eBuildingType::achillesHall;
    case eBuildingMode::atalantaHall:
        return eBuildingType::atalantaHall;
    case eBuildingMode::bellerophonHall:
        return eBuildingType::bellerophonHall;
    case eBuildingMode::herculesHall:
        return eBuildingType::herculesHall;
    case eBuildingMode::jasonHall:
        return eBuildingType::jasonHall;
    case eBuildingMode::odysseusHall:
        return eBuildingType::odysseusHall;
    case eBuildingMode::perseusHall:
        return eBuildingType::perseusHall;
    case eBuildingMode::theseusHall:
        return eBuildingType::theseusHall;

    default:
        return eBuildingType::none;
    }
}

int eBuildingModeHelpers::toCommemorativeId(const eBuildingMode mode) {
    switch(mode) {
    case eBuildingMode::populationMonument:
        return 0;
    case eBuildingMode::victoryMonument:
        return 1;
    case eBuildingMode::colonyMonument:
        return 2;
    case eBuildingMode::athleteMonument:
        return 3;
    case eBuildingMode::conquestMonument:
        return 4;
    case eBuildingMode::happinessMonument:
        return 5;
    case eBuildingMode::heroicFigureMonument:
        return 6;
    case eBuildingMode::diplomacyMonument:
        return 7;
    case eBuildingMode::scholarMonument:
        return 8;
    default:
        return -1;
    }
    return -1;
}

eGodType eBuildingModeHelpers::toGodType(const eBuildingMode mode) {
    const auto am = eBuildingMode::aphroditeMonument;
    const int id = static_cast<int>(mode) -
                   static_cast<int>(am);
    const auto gt = static_cast<eGodType>(id);
    return gt;
}
