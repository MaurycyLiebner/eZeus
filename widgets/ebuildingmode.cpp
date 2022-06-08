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

    case eBuildingMode::fishery:
        return eBuildingType::fishery;
    case eBuildingMode::urchinQuay:
        return eBuildingType::urchinQuay;
    case eBuildingMode::huntingLodge:
        return eBuildingType::huntingLodge;

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

    case eBuildingMode::granary:
        return eBuildingType::granary;
    case eBuildingMode::warehouse:
        return eBuildingType::warehouse;

    case eBuildingMode::tradePost:
        return eBuildingType::tradePost;

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
    case eBuildingMode::commemorative2:
    case eBuildingMode::colonyMonument:
    case eBuildingMode::athleteMonument:
    case eBuildingMode::conquestMonument:
    case eBuildingMode::happinessMonument:
    case eBuildingMode::commemorative7:
    case eBuildingMode::commemorative8:
    case eBuildingMode::scholarMonument:
        return eBuildingType::commemorative;

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
    case eBuildingMode::spring:
        return eBuildingType::spring;
    case eBuildingMode::topiary:
        return eBuildingType::topiary;
    case eBuildingMode::baths:
        return eBuildingType::baths;
    case eBuildingMode::stoneCircle:
        return eBuildingType::stoneCircle;

    case eBuildingMode::templeArtemis:
        return eBuildingType::templeArtemis;
    case eBuildingMode::templeHephaestus:
        return eBuildingType::templeHephaestus;

    default:
        return eBuildingType::none;
    }
}
