#include "eviewmode.h"

bool eViewModeHelpers::buildingVisible(
        const eViewMode viewMode,
        const eBuildingType b) {
    if(b == eBuildingType::road) return true;
    if(b == eBuildingType::ruins) return true;

    switch(viewMode) {
    case eViewMode::defaultView: {
        return true;
    } break;

    case eViewMode::patrolBuilding: {
        return false;
    } break;

    case eViewMode::supplies: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing;
    } break;

    case eViewMode::water: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::fountain;
    } break;
    case eViewMode::hygiene: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::hospital;
    } break;
    case eViewMode::hazards: {
        return true;
    } break;
    case eViewMode::unrest: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::watchPost;
    } break;

    case eViewMode::actors: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::dramaSchool ||
               b == eBuildingType::theater;
    } break;
    case eViewMode::athletes: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::gymnasium ||
               b == eBuildingType::stadium1 ||
               b == eBuildingType::stadium2;
    } break;
    case eViewMode::philosophers: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::college ||
               b == eBuildingType::podium;
    } break;
    case eViewMode::allCulture: {
        return b == eBuildingType::commonHouse ||
               b == eBuildingType::eliteHousing ||
               b == eBuildingType::dramaSchool ||
               b == eBuildingType::theater ||
               b == eBuildingType::college ||
               b == eBuildingType::podium ||
               b == eBuildingType::gymnasium ||
               b == eBuildingType::stadium1 ||
               b == eBuildingType::stadium2;
    } break;

    case eViewMode::appeal: {
        return false;
    } break;
    }

    return false;
}

bool eViewModeHelpers::characterVisible(
        const eViewMode viewMode,
        const eCharacterType c) {
    switch(viewMode) {
    case eViewMode::defaultView: {
        return true;
    } break;

    case eViewMode::patrolBuilding: {
        return true;
    } break;

    case eViewMode::supplies: {
        return c == eCharacterType::waterDistributor ||
               c == eCharacterType::foodVendor ||
               c == eCharacterType::fleeceVendor ||
               c == eCharacterType::oilVendor ||
               c == eCharacterType::wineVendor ||
               c == eCharacterType::armsVendor ||
               c == eCharacterType::horseTrainer;
    } break;

    case eViewMode::water: {
        return c == eCharacterType::waterDistributor;
    } break;
    case eViewMode::hygiene: {
        return c == eCharacterType::healer;
    } break;
    case eViewMode::hazards: {
        return c == eCharacterType::fireFighter;
    } break;
    case eViewMode::unrest: {
        return c == eCharacterType::watchman;
    } break;

    case eViewMode::actors: {
        return c == eCharacterType::actor;
    } break;
    case eViewMode::athletes: {
        return c == eCharacterType::gymnast;
    } break;
    case eViewMode::philosophers: {
        return c == eCharacterType::philosopher;
    } break;
    case eViewMode::allCulture: {
        return c == eCharacterType::actor ||
               c == eCharacterType::gymnast ||
               c == eCharacterType::philosopher;
    } break;

    case eViewMode::appeal: {
        return false;
    } break;
    }

    return false;
}
