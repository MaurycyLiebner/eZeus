#include "edifficulty.h"

#include "characters/echaracterbase.h"

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

int costBase(const eBuildingType type) {
    switch(type) {
    case eBuildingType::none:
        return 0;
    case eBuildingType::erase:
        return 1;
    case eBuildingType::road:
        return 2;
    case eBuildingType::bridge:
        return 5;
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

    case eBuildingType::wall:
        return 2;
    case eBuildingType::gatehouse:
        return 20;
    case eBuildingType::tower:
        return 50;


    case eBuildingType::granary:
        return 50;
    case eBuildingType::warehouse:
        return 25;

    case eBuildingType::tradePost:
        return 100;
    case eBuildingType::pier:
        return 100;


    case eBuildingType::commonAgora:
        return 25;
    case eBuildingType::grandAgora:
        return 50;
    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::horseTrainer:
        return 10;

    case eBuildingType::fountain:
        return 16;
    case eBuildingType::hospital:
        return 35;
    case eBuildingType::maintenanceOffice:
        return 10;
    case eBuildingType::watchPost:
        return 20;

    case eBuildingType::palace:
        return 125;
    case eBuildingType::taxOffice:
        return 25;

    case eBuildingType::college:
        return 30;
    case eBuildingType::dramaSchool:
        return 16;
    case eBuildingType::gymnasium:
        return 30;
    case eBuildingType::stadium:
        return 200;
    case eBuildingType::podium:
        return 15;
    case eBuildingType::theater:
        return 60;

    case eBuildingType::bibliotheke:
        return 18;
    case eBuildingType::observatory:
        return 75;
    case eBuildingType::university:
        return 30;
    case eBuildingType::laboratory:
        return 65;
    case eBuildingType::inventorsWorkshop:
        return 40;
    case eBuildingType::museum:
        return 225;

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
    case eBuildingType::avenue:
        return 10;

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
    case eBuildingType::orrery:
        return 40;
    case eBuildingType::spring:
        return 40;
    case eBuildingType::topiary:
        return 38;
    case eBuildingType::baths:
        return 60;
    case eBuildingType::stoneCircle:
        return 60;

    case eBuildingType::templeZeus:
        return 2920;
    case eBuildingType::templePoseidon:
        return 2480;
    case eBuildingType::templeHades:
        return 1320;
    case eBuildingType::templeHera:
        return 1760;
    case eBuildingType::templeDemeter:
        return 840;
    case eBuildingType::templeAthena:
        return 2160;
    case eBuildingType::templeArtemis:
        return 1520;
    case eBuildingType::templeApollo:
        return 920;
    case eBuildingType::templeAtlas:
        return 1760;
    case eBuildingType::templeAres:
        return 960;
    case eBuildingType::templeHephaestus:
        return 760;
    case eBuildingType::templeAphrodite:
        return 720;
    case eBuildingType::templeHermes:
        return 640;
    case eBuildingType::templeDionysus:
        return 400;

    default:
        return 0;
    }
}

double costMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1.0;
    case eDifficulty::mortal:
        return 1.8;
    case eDifficulty::hero:
        return 2.25;
    case eDifficulty::titan:
        return 2.75;
    case eDifficulty::olympian:
        return 3.25;
    }
    return 1;
}

int eDifficultyHelpers::buildingCost(
        const eDifficulty diff,
        const eBuildingType type) {
    const int base = costBase(type);
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(type);
    if(bi >= min && bi <= max) return base;
    const double mult = costMultiplier(diff);
    return std::round(mult*base);
}

int fireRiskBase(const eBuildingType type) {
    switch(type) {
    case eBuildingType::commonHouse:
        return 8;
    case eBuildingType::eliteHousing:
        return 8;

    case eBuildingType::carrotsFarm:
    case eBuildingType::onionsFarm:
    case eBuildingType::wheatFarm:
        return 5;
    case eBuildingType::cardingShed:
        return 5;
    case eBuildingType::dairy:
        return 5;
    case eBuildingType::fishery:
        return 5;
    case eBuildingType::growersLodge:
        return 5;
    case eBuildingType::orangeTendersLodge:
        return 8;
    case eBuildingType::huntingLodge:
        return 8;
    case eBuildingType::urchinQuay:
        return 5;

    case eBuildingType::sculptureStudio:
        return 1;
    case eBuildingType::timberMill:
        return 10;

    case eBuildingType::granary:
        return 8;
    case eBuildingType::warehouse:
        return 5;

    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::horseTrainer:
        return 6;

    case eBuildingType::hospital:
        return 5;
    case eBuildingType::maintenanceOffice:
        return 3;

    case eBuildingType::palace:
        return 3;
    case eBuildingType::taxOffice:
        return 5;

    case eBuildingType::artisansGuild:
        return 5;

    case eBuildingType::armory:
        return 8;
    case eBuildingType::triremeWharf:
        return 5;
    case eBuildingType::horseRanch:
        return 5;

    default:
        return 0;
    }
}

double fireRiskMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1.0;
    case eDifficulty::mortal:
        return 1.5;
    case eDifficulty::hero:
        return 1.875;
    case eDifficulty::titan:
        return 2.25;
    case eDifficulty::olympian:
        return 2.5;
    }
    return 1;
}

int eDifficultyHelpers::fireRisk(
        const eDifficulty diff,
        const eBuildingType type) {
    const double mult = fireRiskMultiplier(diff);
    const int base = fireRiskBase(type);
    return std::round(mult*base);
}

double plagueRiskMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1.0;
    case eDifficulty::mortal:
        return 1.5;
    case eDifficulty::hero:
        return 1.875;
    case eDifficulty::titan:
        return 2.25;
    case eDifficulty::olympian:
        return 2.5;
    }
    return 1;
}

int eDifficultyHelpers::plagueRisk(const eDifficulty diff) {
    return plagueRiskMultiplier(diff);
}

double crimeRiskMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1.0;
    case eDifficulty::mortal:
        return 1.5;
    case eDifficulty::hero:
        return 1.875;
    case eDifficulty::titan:
        return 2.25;
    case eDifficulty::olympian:
        return 2.5;
    }
    return 1;
}

int eDifficultyHelpers::crimeRisk(const eDifficulty diff) {
    return crimeRiskMultiplier(diff);
}

int damageRiskBase(const eBuildingType type) {
    switch(type) {
    case eBuildingType::carrotsFarm:
    case eBuildingType::onionsFarm:
    case eBuildingType::wheatFarm:
        return 5;

    case eBuildingType::fishery:
        return 5;
    case eBuildingType::huntingLodge:
        return 5;
    case eBuildingType::urchinQuay:
        return 5;

    case eBuildingType::foundry:
        return 10;
    case eBuildingType::masonryShop:
        return 10;
    case eBuildingType::mint:
        return 10;
    case eBuildingType::olivePress:
        return 8;
    case eBuildingType::sculptureStudio:
        return 2;
    case eBuildingType::winery:
        return 5;

    case eBuildingType::granary:
        return 8;

    case eBuildingType::fountain:
        return 8;
    case eBuildingType::hospital:
        return 5;
    case eBuildingType::watchPost:
        return 5;

    case eBuildingType::palace:
        return 5;

    case eBuildingType::college:
        return 6;
    case eBuildingType::dramaSchool:
        return 8;
    case eBuildingType::gymnasium:
        return 5;
    case eBuildingType::stadium:
        return 8;
    case eBuildingType::podium:
        return 5;
    case eBuildingType::theater:
        return 8;

    case eBuildingType::triremeWharf:
        return 5;

    default:
        return 0;
    }
}

double damageRiskMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1.0;
    case eDifficulty::mortal:
        return 1.25;
    case eDifficulty::hero:
        return 1.5;
    case eDifficulty::titan:
        return 2.0;
    case eDifficulty::olympian:
        return 2.5;
    }
    return 1;
}

int eDifficultyHelpers::damageRisk(
        const eDifficulty diff,
        const eBuildingType type) {
    const double mult = damageRiskMultiplier(diff);
    const int base = damageRiskBase(type);
    return std::round(mult*base);
}

int eDifficultyHelpers::taxMultiplier(
        const eDifficulty diff,
        const eBuildingType type,
        const int level) {
    if(type == eBuildingType::commonHouse) {
        if(level < 3) {
            return 1;
        } else if(level == 3) {
            if(diff == eDifficulty::titan ||
               diff == eDifficulty::olympian) {
                return 1;
            } else {
                return 2;
            }
        } else {
            return 2;
        }
    } else if(type == eBuildingType::eliteHousing) {
        switch(diff) {
        case eDifficulty::beginner:
            return 22;
        case eDifficulty::mortal:
            return 18;
        case eDifficulty::hero:
            return 16;
        case eDifficulty::titan:
            return 14;
        case eDifficulty::olympian:
            return 12;
        }
    }
    return 0;
}

int eDifficultyHelpers::taxSentiment(
        const eDifficulty diff,
        const eTaxRate taxRate) {
    const int id = static_cast<int>(taxRate);
    switch(diff) {
    case eDifficulty::beginner: {
        const int vals[]{7, 5, 3, 2, 0, -1, -2};
        return vals[id];
    }
    case eDifficulty::mortal: {
        const int vals[]{4, 3, 1, 0, 0, -2, -4};
        return vals[id];
    }
    case eDifficulty::hero: {
        const int vals[]{3, 2, 1, 0, -1, -3, -5};
        return vals[id];
    }
    case eDifficulty::titan: {
        const int vals[]{2, 1, 0, 0, -2, -4, -6};
        return vals[id];
    }
    case eDifficulty::olympian: {
        const int vals[]{1, 1, 0, 0, -3, -5, -7};
        return vals[id];
    }
    }
}

double eDifficultyHelpers::workerFrac(
        const eDifficulty diff, const eWageRate wageRate) {
    switch(wageRate) {
    case eWageRate::none:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.42;
        case eDifficulty::mortal:
            return 0.37;
        case eDifficulty::hero:
            return 0.32;
        case eDifficulty::titan:
            return 0.29;
        case eDifficulty::olympian:
            return 0.27;
        }
    }
    case eWageRate::veryLow:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.46;
        case eDifficulty::mortal:
            return 0.41;
        case eDifficulty::hero:
            return 0.36;
        case eDifficulty::titan:
            return 0.33;
        case eDifficulty::olympian:
            return 0.31;
        }
    }
    case eWageRate::low:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.49;
        case eDifficulty::mortal:
            return 0.44;
        case eDifficulty::hero:
            return 0.39;
        case eDifficulty::titan:
            return 0.36;
        case eDifficulty::olympian:
            return 0.34;
        }
    }
    case eWageRate::normal:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.52;
        case eDifficulty::mortal:
            return 0.47;
        case eDifficulty::hero:
            return 0.42;
        case eDifficulty::titan:
            return 0.39;
        case eDifficulty::olympian:
            return 0.37;
        }
    }
    case eWageRate::high:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.55;
        case eDifficulty::mortal:
            return 0.50;
        case eDifficulty::hero:
            return 0.45;
        case eDifficulty::titan:
            return 0.42;
        case eDifficulty::olympian:
            return 0.4;
        }
    }
    case eWageRate::veryHigh:
    {
        switch(diff) {
        case eDifficulty::beginner:
            return 0.57;
        case eDifficulty::mortal:
            return 0.52;
        case eDifficulty::hero:
            return 0.47;
        case eDifficulty::titan:
            return 0.44;
        case eDifficulty::olympian:
            return 0.42;
        }
    }
    }
    return 0;
}


int soliderBribeMultiplier(const eDifficulty diff) {
    switch(diff) {
    case eDifficulty::beginner:
        return 1;
    case eDifficulty::mortal:
        return 3;
    case eDifficulty::hero:
        return 4;
    case eDifficulty::titan:
        return 5;
    case eDifficulty::olympian:
        return 7;
    }
    return 1;
}

int eDifficultyHelpers::soliderBribe(const eDifficulty diff,
                                     const eCharacterType type) {
    const int mult = soliderBribeMultiplier(diff);
    int base = 0;
    switch(type) {
    case eCharacterType::rockThrower:
        base = 25;
        break;
    case eCharacterType::hoplite:
        base = 25;
        break;
    case eCharacterType::horseman:
        base = 50;
        break;
    default:
        return 0;
    }
    return mult*base;
}
