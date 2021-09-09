#include "edifficulty.h"

std::string eDifficultyHelpers::name(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return "beginner";
    case eDifficulty::mortal:
        return "mortal";
    case eDifficulty::hero:
        return "hero";
    case eDifficulty::titan:
        return "titan";
    case eDifficulty::olympian:
        return "olympian";
    }
}

int buildingBaseCost(const eBuildingType type) {
    switch(type) {
    case eBuildingType::none:
        return 0;
    case eBuildingType::erase:
        return 1;
    case eBuildingType::road:
        return 2;
    case eBuildingType::commonHouse:
        return 10;
    case eBuildingType::eliteHousing:
        return 100;

    case eBuildingType::vine:
    case eBuildingType::oliveTree:
    case eBuildingType::orangeTree:
        return 3;

    case eBuildingType::goat:
    case eBuildingType::sheep:
        return 4;

    case eBuildingType::carrotsFarm:
    case eBuildingType::onionsFarm:
    case eBuildingType::wheatFarm:
        return 20;
    case eBuildingType::cardingShed:
        return 16;
    case eBuildingType::dairy:
        return 16;
    case eBuildingType::fishery:
        return 30;
    case eBuildingType::growersLodge:
        return 25;
    case eBuildingType::orangeTendersLodge:
        return 20;
    case eBuildingType::huntingLodge:
        return 20;
    case eBuildingType::urchinQuay:
        return 30;

    case eBuildingType::foundry:
        return 60;
    case eBuildingType::masonryShop:
        return 75;
    case eBuildingType::mint:
        return 100;
    case eBuildingType::olivePress:
        return 45;
    case eBuildingType::sculptureStudio:
        return 100;
    case eBuildingType::timberMill:
        return 35;
    case eBuildingType::winery:
        return 45;

    case eBuildingType::granary:
        return 50;
    case eBuildingType::warehouse:
        return 25;

    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::horseTrainer:
        return 20;

    case eBuildingType::fountain:
        return 16;
    case eBuildingType::hospital:
        return 35;
    case eBuildingType::maintenanceOffice:
        return 10;
    case eBuildingType::watchPost:
        return 20;

    case eBuildingType::palace1:
    case eBuildingType::palace2:
        return 125;
    case eBuildingType::taxOffice:
        return 25;

    case eBuildingType::college:
        return 30;
    case eBuildingType::dramaSchool:
        return 16;
    case eBuildingType::gymnasium:
        return 30;
    case eBuildingType::stadium1:
    case eBuildingType::stadium2:
        return 200;
    case eBuildingType::podium:
        return 15;
    case eBuildingType::theater:
        return 60;

    case eBuildingType::artisansGuild:
        return 35;

    case eBuildingType::armory:
        return 40;
    case eBuildingType::triremeWharf:
        return 75;
    case eBuildingType::horseRanch:
        return 100;

    case eBuildingType::park:
        return 6;
    case eBuildingType::doricColumn:
    case eBuildingType::ionicColumn:
    case eBuildingType::corinthianColumn:
        return 8;

    case eBuildingType::bench:
        return 6;
    case eBuildingType::flowerGarden:
        return 20;
    case eBuildingType::gazebo:
        return 24;
    case eBuildingType::hedgeMaze:
        return 40;
    case eBuildingType::fishPond:
        return 60;

    case eBuildingType::waterPark:
        return 16;

    case eBuildingType::birdBath:
        return 6;
    case eBuildingType::shortObelisk:
        return 10;
    case eBuildingType::tallObelisk:
        return 12;
    case eBuildingType::shellGarden:
        return 20;
    case eBuildingType::sundial:
        return 20;
    case eBuildingType::dolphinSculpture:
        return 40;
    case eBuildingType::spring:
        return 40;
    case eBuildingType::topiary:
        return 38;
    case eBuildingType::baths:
        return 60;
    case eBuildingType::stoneCircle:
        return 60;

    default:
        return 0;
    }
}

double eDifficultyHelpers::costMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1;
    case eDifficulty::mortal:
        return 1.8;
    case eDifficulty::hero:
        return 2.25;
    case eDifficulty::titan:
        return 2.75;
    case eDifficulty::olympian:
        return 3.25;
    }
}

int eDifficultyHelpers::buildingCost(
        const eDifficulty diff,
        const eBuildingType type) {
    const double costMult = costMultiplier(diff);
    const int baseCost = buildingBaseCost(type);

    return std::round(costMult*baseCost);
}
