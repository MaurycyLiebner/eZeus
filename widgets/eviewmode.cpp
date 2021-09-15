#include "eviewmode.h"

bool eViewModeHelpers::buildingVisible(
        const eViewMode viewMode,
        const eBuilding* const b) {
    if(!b) return false;
    const auto bt = b->type();
    if(bt == eBuildingType::road) return true;
    if(bt == eBuildingType::ruins) return true;

    switch(viewMode) {
    case eViewMode::defaultView: {
        return true;
    } break;

    case eViewMode::patrolBuilding: {
        return false;
    } break;

    case eViewMode::supplies: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing;
    } break;

    case eViewMode::water: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::fountain;
    } break;
    case eViewMode::hygiene: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::hospital;
    } break;
    case eViewMode::hazards: {
        return b->maintenance() < 90;
    } break;
    case eViewMode::unrest: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::watchPost;
    } break;

    case eViewMode::actors: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::dramaSchool ||
               bt == eBuildingType::theater;
    } break;
    case eViewMode::athletes: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::gymnasium ||
               bt == eBuildingType::stadium;
    } break;
    case eViewMode::philosophers: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::college ||
               bt == eBuildingType::podium;
    } break;
    case eViewMode::allCulture: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::dramaSchool ||
               bt == eBuildingType::theater ||
               bt == eBuildingType::college ||
               bt == eBuildingType::podium ||
               bt == eBuildingType::gymnasium ||
               bt == eBuildingType::stadium;
    } break;

    case eViewMode::appeal: {
        return bt == eBuildingType::park ||
               bt == eBuildingType::doricColumn ||
               bt == eBuildingType::ionicColumn ||
               bt == eBuildingType::corinthianColumn ||

               bt == eBuildingType::bench ||
               bt == eBuildingType::flowerGarden ||
               bt == eBuildingType::gazebo ||
               bt == eBuildingType::hedgeMaze ||
               bt == eBuildingType::fishPond ||

               bt == eBuildingType::waterPark ||

               bt == eBuildingType::birdBath ||
               bt == eBuildingType::shortObelisk ||
               bt == eBuildingType::tallObelisk ||
               bt == eBuildingType::shellGarden ||
               bt == eBuildingType::sundial ||
               bt == eBuildingType::dolphinSculpture ||
               bt == eBuildingType::spring ||
               bt == eBuildingType::topiary ||
               bt == eBuildingType::baths ||
               bt == eBuildingType::stoneCircle;
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
