#include "ebuildingmode.h"

eBuildingType eBuildingModeHelpers::toBuildingType(const eBuildingMode mode) {
    switch(mode) {
    case eBuildingMode::none:
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
        return eBuildingType::stadium1;

    case eBuildingMode::granary:
        return eBuildingType::granary;
    case eBuildingMode::warehouse:
        return eBuildingType::warehouse;

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
        return eBuildingType::palace1;
    }
}
