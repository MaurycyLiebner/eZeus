#include "eviewmode.h"

#include "engine/egameboard.h"
#include "engine/edifficulty.h"

bool eViewModeHelpers::buildingVisible(
        const eViewMode viewMode,
        const eBuilding* const b) {
    if(!b) return false;
    const auto bt = b->type();
    if(eBuilding::sFlatBuilding(bt)) return true;

    switch(viewMode) {
    case eViewMode::defaultView: {
        return true;
    } break;
    case eViewMode::problems: {
        return false;
    } break;

    case eViewMode::security: {
        return bt == eBuildingType::wall ||
               bt == eBuildingType::tower ||
               bt == eBuildingType::gatehouse;
    } break;

    case eViewMode::husbandry: {
        return bt == eBuildingType::oliveTree ||
               bt == eBuildingType::vine ||
               bt == eBuildingType::orangeTree ||
               bt == eBuildingType::wheatFarm ||
               bt == eBuildingType::carrotsFarm ||
               bt == eBuildingType::onionsFarm ||
               bt == eBuildingType::huntingLodge ||
               bt == eBuildingType::corral ||
               bt == eBuildingType::fishery ||
               bt == eBuildingType::urchinQuay ||
               bt == eBuildingType::cardingShed ||
               bt == eBuildingType::dairy ||
               bt == eBuildingType::growersLodge ||
               bt == eBuildingType::orangeTendersLodge;
    } break;

    case eViewMode::immortals: {
        const int iMin = static_cast<int>(eBuildingType::templeAphrodite);
        const int iMax = static_cast<int>(eBuildingType::theseusHall);
        const int ibt = static_cast<int>(bt);
        return ibt >= iMin && ibt <= iMax;
    } break;

    case eViewMode::roads: {
        return false;
    } break;

    case eViewMode::industry: {
        return bt == eBuildingType::timberMill ||
               bt == eBuildingType::masonryShop ||
               bt == eBuildingType::mint ||
               bt == eBuildingType::foundry ||
               bt == eBuildingType::winery ||
               bt == eBuildingType::sculptureStudio ||
               bt == eBuildingType::armory;
    } break;

    case eViewMode::distribution: {
        return bt == eBuildingType::tradePost ||
               bt == eBuildingType::pier ||
               bt == eBuildingType::granary ||
               bt == eBuildingType::warehouse;
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
        auto& board = b->getBoard();
        const auto diff = board.difficulty();
        const int fr = eDifficultyHelpers::fireRisk(diff, bt);
        const int dr = eDifficultyHelpers::damageRisk(diff, bt);
        return (fr || dr) && b->maintenance() < 90;
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
    case eViewMode::competitors: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::gymnasium ||
               bt == eBuildingType::stadium;
    } break;

    case eViewMode::astronomers: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::university ||
               bt == eBuildingType::observatory;
    } break;
    case eViewMode::scholars: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::bibliotheke;
    } break;
    case eViewMode::inventors: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::inventorsWorkshop ||
               bt == eBuildingType::laboratory;
    } break;
    case eViewMode::curators: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::university ||
               bt == eBuildingType::museum;
    } break;
    case eViewMode::allScience: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::university ||
               bt == eBuildingType::observatory ||
               bt == eBuildingType::museum ||
               bt == eBuildingType::inventorsWorkshop ||
               bt == eBuildingType::laboratory ||
               bt == eBuildingType::bibliotheke;
    } break;

    case eViewMode::appeal: {
        return eBuilding::sAestheticsBuilding(bt);
    } break;

    case eViewMode::taxes: {
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::eliteHousing ||
               bt == eBuildingType::taxOffice;
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

    case eViewMode::security: {
        const int ic = static_cast<int>(c);
        const int godMin = static_cast<int>(eCharacterType::aphrodite);
        const int godMax = static_cast<int>(eCharacterType::zeus);
        if(ic >= godMin && ic <= godMax) return true;
        const int monsterMin = static_cast<int>(eCharacterType::calydonianBoar);
        const int monsterMax = static_cast<int>(eCharacterType::talos);
        if(ic >= monsterMin && ic <= monsterMax) return true;
        const int heroMin = static_cast<int>(eCharacterType::achilles);
        const int heroMax = static_cast<int>(eCharacterType::theseus);
        if(ic >= heroMin && ic <= heroMax) return true;
        const int iMin = static_cast<int>(eCharacterType::rockThrower);
        const int iMax = static_cast<int>(eCharacterType::greekHorseman);
        if(ic >= iMin && ic <= iMax) return true;
        return c == eCharacterType::watchman;
    } break;

    case eViewMode::patrolBuilding: {
        return true;
    } break;

    case eViewMode::industry: {
        return c == eCharacterType::marbleMiner ||
               c == eCharacterType::lumberjack ||
               c == eCharacterType::bronzeMiner ||
               c == eCharacterType::silverMiner;
    } break;

    case eViewMode::husbandry: {
        return c == eCharacterType::grower ||
               c == eCharacterType::boar ||
               c == eCharacterType::deer ||
               c == eCharacterType::wolf ||
               c == eCharacterType::shepherd ||
               c == eCharacterType::goatherd ||
               c == eCharacterType::sheep ||
               c == eCharacterType::goat ||
               c == eCharacterType::cattle1 ||
               c == eCharacterType::cattle2 ||
               c == eCharacterType::cattle3 ||
               c == eCharacterType::bull ||
               c == eCharacterType::horse ||
               c == eCharacterType::butcher ||
               c == eCharacterType::hunter ||
               c == eCharacterType::fishingBoat;
    } break;

    case eViewMode::immortals: {
        const int ic = static_cast<int>(c);
        const int godMin = static_cast<int>(eCharacterType::aphrodite);
        const int godMax = static_cast<int>(eCharacterType::zeus);
        if(ic >= godMin && ic <= godMax) return true;
        const int monsterMin = static_cast<int>(eCharacterType::calydonianBoar);
        const int monsterMax = static_cast<int>(eCharacterType::talos);
        if(ic >= monsterMin && ic <= monsterMax) return true;
        const int heroMin = static_cast<int>(eCharacterType::achilles);
        const int heroMax = static_cast<int>(eCharacterType::theseus);
        if(ic >= heroMin && ic <= heroMax) return true;
        return false;
    } break;

    case eViewMode::distribution: {
        return c == eCharacterType::cartTransporter ||
               c == eCharacterType::porter ||
               c == eCharacterType::ox ||
               c == eCharacterType::trailer ||
               c == eCharacterType::tradeBoat ||
               c == eCharacterType::trader ||
               c == eCharacterType::donkey;
    } break;

    case eViewMode::problems: {
        return c == eCharacterType::disgruntled ||
               c == eCharacterType::sick;
    } break;

    case eViewMode::roads: {
        return true;
    } break;

    case eViewMode::supplies: {
        return c == eCharacterType::waterDistributor ||
               c == eCharacterType::cartTransporter ||
               c == eCharacterType::peddler;
    } break;

    case eViewMode::water: {
        return c == eCharacterType::waterDistributor;
    } break;
    case eViewMode::hygiene: {
        return c == eCharacterType::healer ||
               c == eCharacterType::sick;
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
    case eViewMode::competitors: {
        return c == eCharacterType::competitor;
    } break;
    case eViewMode::philosophers: {
        return c == eCharacterType::philosopher;
    } break;
    case eViewMode::allCulture: {
        return c == eCharacterType::actor ||
               c == eCharacterType::gymnast ||
               c == eCharacterType::philosopher;
    } break;

    case eViewMode::astronomers: {
        return c == eCharacterType::astronomer;
    } break;
    case eViewMode::scholars: {
        return c == eCharacterType::scholar;
    } break;
    case eViewMode::inventors: {
        return c == eCharacterType::inventor;
    } break;
    case eViewMode::curators: {
        return c == eCharacterType::curator;
    } break;
    case eViewMode::allScience: {
        return c == eCharacterType::astronomer ||
               c == eCharacterType::scholar ||
               c == eCharacterType::inventor ||
               c == eCharacterType::curator;
    } break;
    case eViewMode::appeal: {
        return false;
    } break;

    case eViewMode::taxes: {
        return c == eCharacterType::taxCollector;
    } break;
    }

    return false;
}
