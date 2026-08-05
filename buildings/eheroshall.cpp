#include "eheroshall.h"

#include "textures/egametextures.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "buildings/epalace.h"
#include "buildings/eroad.h"
#include "eiteratesquare.h"
#include "engine/epathfinder.h"
#include "etilehelper.h"
#include "characters/actions/eheroaction.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "enumbers.h"

#include <algorithm>

eBuildingType eHerosHall::sHeroTypeToHallType(const eHeroType type) {
    switch(type) {
    case eHeroType::achilles: return eBuildingType::achillesHall;
    case eHeroType::atalanta: return eBuildingType::atalantaHall;
    case eHeroType::bellerophon: return eBuildingType::bellerophonHall;
    case eHeroType::hercules: return eBuildingType::herculesHall;
    case eHeroType::jason: return eBuildingType::jasonHall;
    case eHeroType::odysseus: return eBuildingType::odysseusHall;
    case eHeroType::perseus: return eBuildingType::perseusHall;
    case eHeroType::theseus: return eBuildingType::theseusHall;
    }
    return eBuildingType::theseusHall;
}

eHeroType eHerosHall::sHallTypeToHeroType(const eBuildingType type,
                                          bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eBuildingType::achillesHall: return eHeroType::achilles;
    case eBuildingType::atalantaHall: return eHeroType::atalanta;
    case eBuildingType::bellerophonHall: return eHeroType::bellerophon;
    case eBuildingType::herculesHall: return eHeroType::hercules;
    case eBuildingType::jasonHall: return eHeroType::jason;
    case eBuildingType::odysseusHall: return eHeroType::odysseus;
    case eBuildingType::perseusHall: return eHeroType::perseus;
    case eBuildingType::theseusHall: return eHeroType::theseus;
    default: break;
    }
    if(valid) *valid = false;
    return eHeroType::achilles;
}

eGodType athenaHephaestus(eBoardCity& c) {
    const bool athena = c.availableBuilding(eBuildingType::templeAthena) ||
                        c.hasBuilding(eBuildingType::templeAthena);
    if(athena) return eGodType::athena;
    return eGodType::hephaestus;
}

std::pair<eGodType, eGodType> athenaHermesZeusHades(eBoardCity& c) {
    std::vector<eGodType> allowed;
    const bool athena = c.availableBuilding(eBuildingType::templeAthena) ||
                        c.hasBuilding(eBuildingType::templeAthena);
    if(athena) allowed.push_back(eGodType::athena);
    const bool hermes = c.availableBuilding(eBuildingType::templeHermes) ||
                        c.hasBuilding(eBuildingType::templeHermes);
    if(hermes) allowed.push_back(eGodType::hermes);
    const bool hades = c.availableBuilding(eBuildingType::templeHades) ||
                       c.hasBuilding(eBuildingType::templeHades);
    if(hades) allowed.push_back(eGodType::hades);
    const bool zeus = c.availableBuilding(eBuildingType::templeZeus) ||
                      c.hasBuilding(eBuildingType::templeZeus);
    if(zeus) allowed.push_back(eGodType::zeus);
    if(allowed.size() >= 2) {
        return {allowed[0], allowed[1]};
    } else if(allowed.size() == 1) {
        return {allowed[0], allowed[0]};
    } else {
        return {eGodType::athena, eGodType::hermes};
    }
}

std::string eHerosHall::sHeroRequirementText(const eHeroRequirement& hr,
                                             eBoardCity& c) {
    const bool atlantean = c.atlantean();
    const std::string cstr = std::to_string(hr.fRequiredCount);
    switch(hr.fType) {
    case eHeroRequirementType::armor:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::armor);
    case eHeroRequirementType::hoplite:
        if(atlantean) {
            return cstr + " " + eLanguage::zeusText(51, 87) + " " + eLanguage::zeusText(185, 17);
        } else {
            return cstr + " " + eLanguage::zeusText(64, 12) + " " + eLanguage::zeusText(185, 17);
        }
    case eHeroRequirementType::sanctuaryAthenaOrHephaestus: {
        const auto god = athenaHephaestus(c);
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(god);
    } break;
    case eHeroRequirementType::noUnrest:
        return eLanguage::zeusText(185, 48);;
    case eHeroRequirementType::wine:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::wine);

    case eHeroRequirementType::hallCultureAccess:
        if(atlantean) {
            return eLanguage::zeusText(185, 116);
        } else {
            return eLanguage::zeusText(185, 49);
        }
    case eHeroRequirementType::panHellenicGameWinHippodrome:
        if(atlantean) {
            return eLanguage::zeusText(185, 117);
        } else {
            return eLanguage::zeusText(185, 50);
        }
    case eHeroRequirementType::cityGymnasiumObservatoryAccess:
        if(atlantean) {
            return eLanguage::zeusText(185, 120);
        } else {
            return eLanguage::zeusText(185, 51);
        }
    case eHeroRequirementType::people:
        return cstr + " " + eLanguage::zeusText(185, 52);;

    case eHeroRequirementType::horsemen:
        if(atlantean) {
            return cstr + " " + eLanguage::zeusText(51, 86) + " " + eLanguage::zeusText(185, 17);
        } else {
            return cstr + " " + eLanguage::zeusText(64, 13) + " " + eLanguage::zeusText(185, 17);
        }
    case eHeroRequirementType::horses:
        return cstr + " " + eResourceTypeHelpers::typeName(eResourceType::horse) + eLanguage::zeusText(185, 31);
    case eHeroRequirementType::food:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::food);

    case eHeroRequirementType::popularity:
        return eLanguage::zeusText(185, 54);
    case eHeroRequirementType::health:
        return eLanguage::zeusText(185, 55);
    case eHeroRequirementType::eliteHouses:
        return cstr + " " + eLanguage::zeusText(185, 35);
    case eHeroRequirementType::oil:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::oliveOil);

    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades1: {
        const auto types = athenaHermesZeusHades(c);
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(types.first);
    } break;
    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades2: {
        const auto types = athenaHermesZeusHades(c);
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(types.second);
    } break;
    case eHeroRequirementType::drachmas:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::drachmas);
    case eHeroRequirementType::fleece:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::fleece);
    case eHeroRequirementType::sculpture:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::sculpture);

    case eHeroRequirementType::nearPalace:
        return eLanguage::zeusText(185, 56);
    case eHeroRequirementType::appeal:
        return eLanguage::zeusText(185, 57);
    case eHeroRequirementType::walls:
        return eLanguage::zeusText(185, 58);
    case eHeroRequirementType::marble:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::marble);

    case eHeroRequirementType::sanctuaryArtemis:
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(eGodType::artemis);
    case eHeroRequirementType::stadiumMuseum:
        if(atlantean) {
            return eLanguage::zeusText(185, 129);
        } else {
            return eLanguage::zeusText(185, 126);
        }
    case eHeroRequirementType::meat:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::meat);
    case eHeroRequirementType::wood:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::wood);
    case eHeroRequirementType::soldiers:
        return cstr + " " + eLanguage::zeusText(138, 36) + " " + eLanguage::zeusText(185, 17);

    case eHeroRequirementType::taxes:
        return eLanguage::zeusText(185, 124);
    case eHeroRequirementType::bronzeOrichalc:
        if(atlantean) {
            return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::orichalc);
        } else {
            return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::bronze);
        }
    }
    return "";
}

std::string eHerosHall::sHeroRequirementStatusText(const eHeroRequirement& hr,
                                                   eBoardCity &c) {
    const bool atlantean = c.atlantean();
    const int sc = hr.fStatusCount;
    const std::string cstr = std::to_string(sc);
    const int id = sc;
    switch(hr.fType) {
    case eHeroRequirementType::armor:
    case eHeroRequirementType::wine:
    case eHeroRequirementType::food:
    case eHeroRequirementType::oil:
    case eHeroRequirementType::fleece:
    case eHeroRequirementType::sculpture:
    case eHeroRequirementType::meat:
    case eHeroRequirementType::wood:
    case eHeroRequirementType::bronzeOrichalc:
    case eHeroRequirementType::marble:
        return cstr + " " + eLanguage::zeusText(185, 16); // in storage
    case eHeroRequirementType::hoplite:
        return cstr + " " + eLanguage::zeusText(185, 17); // companies
    case eHeroRequirementType::noUnrest: {
        if(id == 0) {
            return eLanguage::zeusText(66, 46); // extremely high
        } else if(id == 1) {
            return eLanguage::zeusText(66, 45); // somewhat high
        } else if(id == 2) {
            return eLanguage::zeusText(66, 44); // some
        } else if(id == 3) {
            return eLanguage::zeusText(66, 43); // low
        } else if(id == 4) {
            return eLanguage::zeusText(66, 42); // very low
        } else { // 5
            return eLanguage::zeusText(66, 41); // no unrest
        }
    } break;

    case eHeroRequirementType::cityGymnasiumObservatoryAccess:
    case eHeroRequirementType::hallCultureAccess: {
        if(id == 0) {
            return eLanguage::zeusText(185, 19); // no access
        } else if(id == 1) {
            return eLanguage::zeusText(185, 20); // low access
        } else if(id == 2) {
            return eLanguage::zeusText(185, 21); // some access
        } else if(id == 3) {
            return eLanguage::zeusText(185, 22); // good access
        } else { // 4
            return eLanguage::zeusText(185, 23); // excellent access
        }
    } break;
    case eHeroRequirementType::panHellenicGameWinHippodrome: {
        if(atlantean) {
            if(id == 0) {
                return eLanguage::zeusText(185, 118); // no hippodrome
            } else { // 1
                return eLanguage::zeusText(185, 119); // working hippodrome
            }
        } else {
            if(id == 0) {
                return eLanguage::zeusText(185, 24); // no victories
            } else { // 1
                return eLanguage::zeusText(185, 25); // victorious
            }
        }
    } break;
    case eHeroRequirementType::people:
        return cstr + " " + eLanguage::zeusText(185, 52);

    case eHeroRequirementType::horsemen:
        return cstr + " " + eLanguage::zeusText(185, 17);
    case eHeroRequirementType::horses:
        return cstr + " " + eResourceTypeHelpers::typeName(eResourceType::horse);

    case eHeroRequirementType::popularity: {
        if(id == 0) {
            return eLanguage::zeusText(61, 27); // terrible
        } else if(id == 1) {
            return eLanguage::zeusText(61, 28); // awful
        } else if(id == 2) {
            return eLanguage::zeusText(61, 30); // bad
        } else if(id == 3) {
            return eLanguage::zeusText(61, 32); // poor
        } else if(id == 4) {
            return eLanguage::zeusText(61, 33); // ok
        } else if(id == 5) {
            return eLanguage::zeusText(61, 34); // good
        } else if(id == 6) {
            return eLanguage::zeusText(61, 36); // high
        } else if(id == 7) {
            return eLanguage::zeusText(61, 37); // great
        } else { // 8
            return eLanguage::zeusText(61, 38); // superb
        }
    } break;
    case eHeroRequirementType::health: {
        if(id == 0) {
            return eLanguage::zeusText(56, 2); // appalling
        } else if(id == 1) {
            return eLanguage::zeusText(56, 3); // terrible
        } else if(id == 2) {
            return eLanguage::zeusText(56, 4); // bad
        } else if(id == 3) {
            return eLanguage::zeusText(56, 5); // poor
        } else if(id == 4) {
            return eLanguage::zeusText(56, 6); // not good
        } else if(id == 5) {
            return eLanguage::zeusText(56, 7); // ok
        } else if(id == 6) {
            return eLanguage::zeusText(56, 8); // good
        } else if(id == 7) {
            return eLanguage::zeusText(56, 9); // very good
        } else if(id == 8) {
            return eLanguage::zeusText(56, 10); // excellent
        } else if(id == 9) {
            return eLanguage::zeusText(56, 11); // near perfect
        } else { // 10
            return eLanguage::zeusText(56, 12); // perfect
        }
    } break;
    case eHeroRequirementType::eliteHouses:
        return cstr + " " + eLanguage::zeusText(185, 35);

    case eHeroRequirementType::drachmas:
        return cstr + " " + eResourceTypeHelpers::typeName(eResourceType::drachmas);

    case eHeroRequirementType::nearPalace: {
        if(id == 0) {
            return eLanguage::zeusText(185, 37); // no palace
        } else if(id == 1) {
            return eLanguage::zeusText(185, 38); // too far
        } else {
            return eLanguage::zeusText(185, 39); // near
        }
    } break;
    case eHeroRequirementType::appeal: {
        if(id == 0) {
            return eLanguage::zeusText(185, 40); // poor appeal
        } else if(id == 1) {
            return eLanguage::zeusText(185, 41); // low appeal
        } else if(id == 2) {
            return eLanguage::zeusText(185, 42); // some appeal
        } else if(id == 3) {
            return eLanguage::zeusText(185, 43); // good appeal
        } else { // 4
            return eLanguage::zeusText(185, 44); // excellent appeal
        }
    } break;
    case eHeroRequirementType::walls: {
        if(id == 0) {
            return eLanguage::zeusText(185, 45); // unprotected
        } else {
            return eLanguage::zeusText(185, 46); // protected
        }
    } break;

    case eHeroRequirementType::sanctuaryAthenaOrHephaestus:
    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades1:
    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades2:
    case eHeroRequirementType::sanctuaryArtemis: {
        return cstr + "% " + eLanguage::zeusText(185, 18);
    } break;
    case eHeroRequirementType::stadiumMuseum: {
        if(atlantean) {
            if(id == 0) {
                return eLanguage::zeusText(185, 130); // no museum
            } else {
                return eLanguage::zeusText(185, 129); // working museum
            }
        } else {
            if(id == 0) {
                return eLanguage::zeusText(185, 127); // no stadium
            } else {
                return eLanguage::zeusText(185, 128); // working stadium
            }
        }
    } break;
    case eHeroRequirementType::soldiers:
        return cstr + " " + eLanguage::zeusText(185, 17);

    case eHeroRequirementType::taxes: {
        if(id == 0) {
            return eLanguage::zeusText(185, 26); // no coverage
        } else if(id == 1) {
            return eLanguage::zeusText(185, 27); // low coverage
        } else if(id == 2) {
            return eLanguage::zeusText(185, 28); // some coverage
        } else if(id == 3) {
            return eLanguage::zeusText(185, 29); // good coverage
        } else { // 4
            return eLanguage::zeusText(185, 30); // excellect coverage
        }
    } break;
    }
    return "";
}

void eHerosHall::summon() {
    mStage = eHeroSummoningStage::summoned;
    mArrivalCountdown = eNumbers::sHerosHallArrivalPeriod;
}

void eHerosHall::arrive() {
    auto& board = getBoard();

    mStage = eHeroSummoningStage::arrived;

    spawnHero();

    eEventData ed(cityId());
    ed.fHero = mType;
    ed.fChar = mHero;
    ed.fTile = mHero ? mHero->tile() : nullptr;
    board.event(eEvent::heroArrival, ed);
    board.heroSummoned(cityId(), mType);
}

eHero* eHerosHall::spawnHero() {
    if(mHero) mHero->kill();
    auto& board = getBoard();
    const auto c = eHero::sCreateHero(mType, board);
    c->setBothCityIds(cityId());
    mHero = c.get();
    const auto ct = centerTile();
    const int tx = ct->x();
    const int ty = ct->y();
    const auto cr = eTileHelper::closestRoad(tx, ty, board);
    mHero->changeTile(cr);
    const auto ha = e::make_shared<eHeroAction>(c.get());
    mHero->setAction(ha);
    mSpawnWait = eNumbers::sHerosHallSpawnPeriod;
    return mHero;
}

void eHerosHall::setHeroOnQuest(const bool b) {
    mHeroOnQuest = b;
}

void eHerosHall::sendHeroOnQuest() {
    setHeroOnQuest(true);
    if(!mHero) spawnHero();
    if(!mHero) return;
    const auto ca = mHero->action();
    if(const auto ha = dynamic_cast<eHeroAction*>(ca)) {
        ha->sendOnQuest();
    } else {
        mHero->kill();
    }
}

void eHerosHall::read(eReadStream& src) {
    eBuilding::read(src);
    src >> mStage;
    src >> mArrivalCountdown;
    src >> mPhilosophers;
    src >> mActors;
    src >> mAthletes;
    src >> mUpdateCulture;
    src >> mHeroOnQuest;
    src >> mSpawnWait;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mHero = static_cast<eHero*>(c);
    });
}

void eHerosHall::write(eWriteStream& dst) const {
    eBuilding::write(dst);
    dst << mStage;
    dst << mArrivalCountdown;
    dst << mPhilosophers;
    dst << mActors;
    dst << mAthletes;
    dst << mUpdateCulture;
    dst << mHeroOnQuest;
    dst << mSpawnWait;
    dst.writeCharacter(mHero);
}

void eHerosHall::addRequirement(const eHeroRequirement& hr) {
    mRequirements.push_back(hr);
}

void eHerosHall::updateRequirementsStatus() {
    int met = 0;
    for(auto& r : mRequirements) {
        updateRequirementStatus(r);
        const bool m = r.met();
        if(m) met++;
    }
    const int nReqs = mRequirements.size();
    if(!mShownReadyTip && met == nReqs) {
        mShownReadyTip = true;
        int string = -1;
        switch(mType) {
        case eHeroType::achilles:
            string = 234;
            break;
        case eHeroType::hercules:
            string = 235;
            break;
        case eHeroType::jason:
            string = 236;
            break;
        case eHeroType::odysseus:
            string = 237;
            break;
        case eHeroType::perseus:
            string = 238;
            break;
        case eHeroType::theseus:
            string = 239;
            break;
        case eHeroType::bellerophon:
            string = 241;
            break;
        case eHeroType::atalanta:
            string = 240;
            break;
        }
        auto& board = getBoard();
        const auto cid = cityId();
        board.showTip(cid, eLanguage::zeusText(19, string));
        board.showTip(cid, eLanguage::zeusText(19, 242));
    }
}

void eHerosHall::updateRequirementStatus(eHeroRequirement& hr) {
    const auto t = centerTile();
    if(!t) return;
    const int tx = t->x();
    const int ty = t->y();
    const auto& board = getBoard();
    const auto cid = cityId();
    const auto c = board.boardCityWithId(cid);
    const bool atlentean = c->atlantean();
    const auto pid = playerId();
    int& sc = hr.fStatusCount;
    switch(hr.fType) {
    case eHeroRequirementType::armor:
        sc = board.resourceCount(cid, eResourceType::armor);
        return;
    case eHeroRequirementType::hoplite: {
        sc = board.countBanners(eBannerType::hoplite, cid) +
             board.countBanners(eBannerType::horseman, cid);
    } break;
    case eHeroRequirementType::sanctuaryAthenaOrHephaestus: {
        const auto god = athenaHephaestus(*c);
        const auto sts = board.sanctuary(cid, god);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::noUnrest: {
        const int u = board.unrest(cid);
        if(u == 0) {
            sc = 5;
        } else if(u < 2) {
            sc = 4;
        } else if(u < 4) {
            sc = 3;
        } else if(u < 8) {
            sc = 2;
        } else if(u < 15) {
            sc = 1;
        } else {
            sc = 0;
        }
    } break;
    case eHeroRequirementType::wine:
        sc = board.resourceCount(cid, eResourceType::wine);
        break;

    case eHeroRequirementType::hallCultureAccess:
        sc = 0;
        sc += mPhilosophers > 0 ? 1 : 0;
        sc += mActors > 0 ? 1 : 0;
        sc += mAthletes > 0 ? 1 : 0;
        break;
    case eHeroRequirementType::panHellenicGameWinHippodrome:
        if(atlentean) {
            sc = c->workingHippodrome();
        } else {
            sc = board.wonGames(cid) > 0 ? 1 : 0;
        }
        break;
    case eHeroRequirementType::cityGymnasiumObservatoryAccess: {
        if(atlentean) {
            const int ac = board.dramaAstronomyCoverage(cid);
            sc = ac/24;
        } else {
            const int ac = board.athleticsLearningCoverage(cid);
            sc = ac/24;
        }
    } break;
    case eHeroRequirementType::people:
        sc = board.population(pid);
        break;
    case eHeroRequirementType::horsemen: {
        sc = board.countBanners(eBannerType::horseman, cid);
    } break;
    case eHeroRequirementType::horses:
        sc = board.horses();
        break;
    case eHeroRequirementType::food:
        sc = board.resourceCount(cid, eResourceType::food);
        break;

    case eHeroRequirementType::popularity: {
        const int p = board.popularity(cid);
        sc = p/10;
    } break;
    case eHeroRequirementType::health: {
        const int p = board.health(cid);
        sc = p/7;
    } break;
    case eHeroRequirementType::eliteHouses:
        sc = board.eliteHouses(cid);
        break;
    case eHeroRequirementType::oil:
        sc = board.resourceCount(cid, eResourceType::oliveOil);
        break;

    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades1: {
        const auto types = athenaHermesZeusHades(*c);
        const auto sts = board.sanctuary(cid, types.first);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::sanctuaryAthenaHermesZeusHades2: {
        const auto types = athenaHermesZeusHades(*c);
        const auto sts = board.sanctuary(cid, types.second);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::drachmas:
        sc = board.drachmas(pid);
        break;
    case eHeroRequirementType::fleece:
        sc = board.resourceCount(cid, eResourceType::fleece);
        break;
    case eHeroRequirementType::sculpture:
        sc = board.resourceCount(cid, eResourceType::sculpture);
        break;

    case eHeroRequirementType::nearPalace: {
        const auto p = board.palace(cid);
        if(!p) {
            sc = 0;
        } else {
            bool found = false;
            const auto prcsTile = [&](const int i, const int j) {
                const int ttx = tx + i;
                const int tty = ty + j;
                const auto tt = board.tile(ttx, tty);
                if(!tt) return false;
                const auto ub = tt->underBuilding();
                if(ub == p) {
                    found = true;
                    return true;
                }
                return false;
            };

            for(int k = 0; k < 10; k++) {
                eIterateSquare::iterateSquare(k, prcsTile, 1);
                if(found) break;
            }
            if(found) {
                sc = 2;
            } else {
                sc = 1;
            }
        }
    } break;
    case eHeroRequirementType::appeal: {
        const double a = eBuilding::appeal();
        if(a < 12.) {
            sc = 0;
        } else if(a < 14.5) {
            sc = 1;
        } else if(a < 15.5) {
            sc = 2;
        } else if(a < 17.) {
            sc = 3;
        } else {
            sc = 4;
        }
    } break;
    case eHeroRequirementType::walls: {
        ePathFinder p([](eTileBase* const t) {
            const auto bt = t->underBuildingType();
            if(bt == eBuildingType::road) {
                const auto tt = static_cast<eTile*>(t);
                const auto ub = static_cast<eRoad*>(tt->underBuilding());
                if(ub->underGatehouse()) return false;
                return true;
            }

            return bt != eBuildingType::wall &&
                   bt != eBuildingType::gatehouse;
        }, [&](eTileBase* const t) {
            const int dx = t->x() - tx;
            const int dy = t->y() - ty;
            return sqrt(dx*dx + dy*dy) > 30;
        });
        const auto startTile = board.tile(tx, ty);
        const int w = board.width();
        const int h = board.height();
        const bool r = p.findPath({0, 0, w, h}, startTile, 200, true, w, h);
        sc = r ? 0 : 1;
    } break;
    case eHeroRequirementType::marble:
        sc = board.resourceCount(cid, eResourceType::marble);
        break;

    case eHeroRequirementType::sanctuaryArtemis: {
        const auto sts = board.sanctuary(cid, eGodType::artemis);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::stadiumMuseum:
        if(atlentean) {
            sc = board.hasMuseum(cid) ? 1 : 0;
        } else {
            sc = board.hasStadium(cid) ? 1 : 0;
        }
        break;
    case eHeroRequirementType::meat:
        sc = board.resourceCount(cid, eResourceType::meat);
        break;
    case eHeroRequirementType::wood:
        sc = board.resourceCount(cid, eResourceType::wood);
        break;
    case eHeroRequirementType::soldiers:
        sc = board.banners(cid).size();
        break;
    case eHeroRequirementType::taxes: {
        const int tc = board.taxesCoverage(cid);
        sc = tc/22;
    } break;
    case eHeroRequirementType::bronzeOrichalc:
        if(atlentean) {
            sc = board.resourceCount(cid, eResourceType::orichalc);
        } else {
            sc = board.resourceCount(cid, eResourceType::bronze);
        }
        break;
    }
}

eHerosHall::eHerosHall(const eHeroType type, eGameBoard& board,
                       const eCityId cid) :
    eBuilding(board, sHeroTypeToHallType(type), 4, 4, cid),
    mType(type) {
    eGameTextures::loadHerosHall();
    if(atlantean()) {
        eGameTextures::loadPoseidonHerosHall();
    } else {
    }
    board.registerHeroHall(this);
    setOverlayEnabledFunc([]() { return true; });

    switch(mType) {
    case eHeroType::achilles:
        addRequirement({eHeroRequirementType::armor, 32});
        addRequirement({eHeroRequirementType::hoplite, 3});
        addRequirement({eHeroRequirementType::sanctuaryAthenaOrHephaestus, 100});
        addRequirement({eHeroRequirementType::noUnrest, 5});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    case eHeroType::atalanta:
        addRequirement({eHeroRequirementType::sanctuaryArtemis, 100});
        addRequirement({eHeroRequirementType::stadiumMuseum, 1});
        addRequirement({eHeroRequirementType::meat, 32});
        addRequirement({eHeroRequirementType::wood, 32});
        addRequirement({eHeroRequirementType::soldiers, 8});
        break;
    case eHeroType::bellerophon:
        addRequirement({eHeroRequirementType::horses, 15});
        addRequirement({eHeroRequirementType::taxes, 4});
        addRequirement({eHeroRequirementType::drachmas, 10000});
        addRequirement({eHeroRequirementType::bronzeOrichalc, 24});
        addRequirement({eHeroRequirementType::wine, 24});
        break;
    case eHeroType::hercules:
        addRequirement({eHeroRequirementType::hallCultureAccess, 3});
        addRequirement({eHeroRequirementType::panHellenicGameWinHippodrome, 1});
        addRequirement({eHeroRequirementType::cityGymnasiumObservatoryAccess, 3});
        addRequirement({eHeroRequirementType::people, 1500});
        addRequirement({eHeroRequirementType::wine, 32});
        break;
    case eHeroType::jason:
        addRequirement({eHeroRequirementType::horsemen, 2});
        addRequirement({eHeroRequirementType::horses, 8});
        addRequirement({eHeroRequirementType::food, 64});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    case eHeroType::odysseus:
        addRequirement({eHeroRequirementType::popularity, 8});
        addRequirement({eHeroRequirementType::health, 10});
        addRequirement({eHeroRequirementType::eliteHouses, 8});
        addRequirement({eHeroRequirementType::oil, 32});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    case eHeroType::perseus:
        addRequirement({eHeroRequirementType::sanctuaryAthenaHermesZeusHades1, 100});
        addRequirement({eHeroRequirementType::sanctuaryAthenaHermesZeusHades2, 100});
        addRequirement({eHeroRequirementType::drachmas, 3000});
        addRequirement({eHeroRequirementType::fleece, 16});
        addRequirement({eHeroRequirementType::sculpture, 6});
        break;
    case eHeroType::theseus:
        addRequirement({eHeroRequirementType::nearPalace, 2});
        addRequirement({eHeroRequirementType::appeal, 4});
        addRequirement({eHeroRequirementType::walls, 1});
        addRequirement({eHeroRequirementType::marble, 32});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    }
    updateRequirementsStatus();

    const bool s = board.wasHeroSummoned(cid, type);
    if(s) mStage = eHeroSummoningStage::arrived;
}

eHerosHall::~eHerosHall() {
    auto& board = getBoard();
    board.destroyed(cityId(), type());
    board.unregisterHeroHall(this);
    if(mHero) mHero->kill();
}

std::shared_ptr<eTexture> eHerosHall::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    if(atlantean()) {
        return texs.fPoseidonHeroHall;
    } else {
        return texs.fHeroHall;
    }
}

std::vector<eOverlay> eHerosHall::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const auto& statues = texs.fHeroStatues;
    int id;
    switch(mType) {
    case eHeroType::achilles:
        id = 0;
        break;
    case eHeroType::hercules:
        id = 1;
        break;
    case eHeroType::jason:
        id = 2;
        break;
    case eHeroType::odysseus:
        id = 3;
        break;
    case eHeroType::perseus:
        id = 4;
        break;
    case eHeroType::theseus:
        id = 5;
        break;
    case eHeroType::bellerophon:
        id = 6;
        break;
    case eHeroType::atalanta:
        id = 7;
        break;
    }
    eOverlay o;
    o.fTex = statues.getTexture(id);
    o.fX = 0;
    o.fY = -1.5;
    o.fAlignTop = true;
    return {o};
}

void eHerosHall::timeChanged(const int by) {
    if(mStage == eHeroSummoningStage::none) {
        const int wait = 10000;
        mRequirementsUpdate += by;
        if(mRequirementsUpdate > wait) {
            mRequirementsUpdate -= wait;
            updateRequirementsStatus();
        }
    }

    const int cupdate = eNumbers::sHouseCultureDecrementPeriod;
    mUpdateCulture += by;
    if(mUpdateCulture > cupdate) {
        mUpdateCulture -= cupdate;
        mPhilosophers = std::max(0, mPhilosophers - 1);
        mActors = std::max(0, mActors - 1);
        mAthletes = std::max(0, mAthletes - 1);
    }

    if(mStage == eHeroSummoningStage::summoned) {
        mArrivalCountdown -= by;
        if(mArrivalCountdown < 0) {
            arrive();
        }
    }
    if(mStage == eHeroSummoningStage::arrived) {
        if(!mHero && !mHeroOnQuest) {
            mSpawnWait -= by;
            if(mSpawnWait <= 0) {
                spawnHero();
            }
        }
    }

    eBuilding::timeChanged(by);
}

int eHerosHall::provide(const eProvide p, const int n) {
    const int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::philosopherInventor:
        value = &mPhilosophers;
        break;
    case eProvide::actorAstronomer:
        value = &mActors;
        break;
    case eProvide::gymnastScholar:
        value = &mAthletes;
        break;
    default:
        return eBuilding::provide(p, n);
    }
    int add = 0;
    if(value) {
        add = std::clamp(n, 0, max - *value);
        *value += add;
    }
    return add;
}
