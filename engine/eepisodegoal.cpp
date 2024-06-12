#include "eepisodegoal.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "characters/gods/egod.h"
#include "characters/esoldierbanner.h"
#include "engine/eworldcity.h"
#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "engine/egameboard.h"

void eEpisodeGoal::read(eReadStream& src) {
    src >> fType;
    src >> fEnumInt1;
    src >> fEnumInt2;
    src >> fRequiredCount;
    src >> fStatusCount;
}

void eEpisodeGoal::write(eWriteStream& dst) const {
    dst << fType;
    dst << fEnumInt1;
    dst << fEnumInt2;
    dst << fRequiredCount;
    dst << fStatusCount;
}

bool eEpisodeGoal::met() const {
    return fStatusCount >= fRequiredCount;
}

std::string eEpisodeGoal::text(const bool colonyEpisode,
                               const bool atlantean) const {
    switch(fType) {
    case eEpisodeGoalType::population: {
        auto t = eLanguage::zeusText(194, 17);
        eStringHelpers::replace(t, "[amount]", std::to_string(fRequiredCount));
        return t;
    } break;
    case eEpisodeGoalType::treasury: {
        auto t = eLanguage::zeusText(194, 18);
        eStringHelpers::replace(t, "[amount]", std::to_string(fRequiredCount));
        return t;
    } break;
    case eEpisodeGoalType::sanctuary: {
        auto t = eLanguage::zeusText(194, 19);
        const auto type = static_cast<eGodType>(fEnumInt1);
        eStringHelpers::replace(t, "[god]", eGod::sGodName(type));
        return t;
    } break;
    case eEpisodeGoalType::support: {
        auto t = eLanguage::zeusText(194, 24);
        const auto type = static_cast<eBannerType>(fEnumInt1);
        eStringHelpers::replace(t, "[amount]", std::to_string(fRequiredCount));
        std::string name;
        if(atlantean) {
            switch(type) {
            case eBannerType::hoplite:
                name = eLanguage::zeusText(138, 79);
                break;
            case eBannerType::rockThrower:
                name = eLanguage::zeusText(138, 77);
                break;
            case eBannerType::horseman:
                name = eLanguage::zeusText(138, 80);
                break;
            default:
                break;
            }
        } else {
            switch(type) {
            case eBannerType::hoplite:
                name = eLanguage::zeusText(138, 72);
                break;
            case eBannerType::rockThrower:
                name = eLanguage::zeusText(138, 74);
                break;
            case eBannerType::horseman:
                name = eLanguage::zeusText(138, 71);
                break;
            default:
                break;
            }
        }

        eStringHelpers::replace(t, "[military_or_better]", name);
        return t;
    } break;
    case eEpisodeGoalType::quest: {
        return eLanguage::zeusText(194, 26);
    } break;
    case eEpisodeGoalType::slay: {
        return eLanguage::zeusText(194, 27);
    } break;
    case eEpisodeGoalType::rule: {
        auto t = eLanguage::zeusText(194, 31);
        const auto n = fCity ? fCity->name() : "";
        eStringHelpers::replace(t, "[city]", n);
        return t;
    } break;
    case eEpisodeGoalType::housing: {
        auto t = eLanguage::zeusText(194, 33);
        eStringHelpers::replace(t, "[amount]", std::to_string(fRequiredCount));
        std::string level;
        const auto type = static_cast<eBuildingType>(fEnumInt1);
        switch(type) {
        case eBuildingType::commonHouse:
            eSmallHouse::sName(fEnumInt2);
            break;
        case eBuildingType::eliteHousing:
            eEliteHousing::sName(fEnumInt2);
            break;
        default:
            break;
        }

        eStringHelpers::replace(t, "[house_level]", level);
        return t;
    } break;
    case eEpisodeGoalType::setAsideGoods: {
        auto t = colonyEpisode ? eLanguage::zeusText(194, 35) :
                                 eLanguage::zeusText(194, 36);
        eStringHelpers::replace(t, "[amount]", std::to_string(fRequiredCount));
        const auto res = static_cast<eResourceType>(fEnumInt1);
        const auto resName = eResourceTypeHelpers::typeLongName(res);
        eStringHelpers::replace(t, "[item]", resName);
        return t;
    } break;
    }
}

void eEpisodeGoal::update(eGameBoard* const b) {
    switch(fType) {
    case eEpisodeGoalType::population: {
        fStatusCount = b->population();
    } break;
    case eEpisodeGoalType::treasury: {
        fStatusCount = b->drachmas();
    } break;
    case eEpisodeGoalType::sanctuary: {
        const auto type = static_cast<eGodType>(fEnumInt1);
        const auto s = b->sanctuary(type);
        fStatusCount = s ? s->progress() : 0;
    } break;
    case eEpisodeGoalType::support: {
        const auto type = static_cast<eBannerType>(fEnumInt1);
        fStatusCount = b->countSoldiers(type);
    } break;
    case eEpisodeGoalType::quest: {

    } break;
    case eEpisodeGoalType::slay: {

    } break;
    case eEpisodeGoalType::rule: {
        fStatusCount = fCity->isVassal() ? 1 : 0;
    } break;
    case eEpisodeGoalType::housing: {
        fStatusCount = 0;
        const auto type = static_cast<eBuildingType>(fEnumInt1);
        b->buildings([&](eBuilding* const b) {
            const auto btype = b->type();
            if(btype != type) return false;
            const auto h = static_cast<eHouseBase*>(b);
            const int l = h->level();
            if(l >= fEnumInt2) {
                fStatusCount += h->people();
            }
            return false;
        });
    } break;
    case eEpisodeGoalType::setAsideGoods: {
        const auto res = static_cast<eResourceType>(fEnumInt1);
        fStatusCount = b->resourceCount(res);
    } break;
    }
}
