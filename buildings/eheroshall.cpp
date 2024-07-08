#include "eheroshall.h"

#include "textures/egametextures.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "buildings/epalace.h"
#include "eiteratesquare.h"
#include "engine/epathfinder.h"
#include "etilehelper.h"
#include "characters/actions/eheroaction.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "characters/actions/emovetoaction.h"
#include "estringhelpers.h"

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

std::string eHerosHall::sHeroRequirementText(const eHeroRequirement& hr) {
    const std::string cstr = std::to_string(hr.fRequiredCount);
    switch(hr.fType) {
    case eHeroRequirementType::armor:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::armor);
    case eHeroRequirementType::hoplite:
        return cstr + " " + eLanguage::zeusText(64, 12) + " " + eLanguage::zeusText(185, 17);
    case eHeroRequirementType::sanctuaryAthena:
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(eGodType::athena);
    case eHeroRequirementType::noUnrest:
        return eLanguage::zeusText(185, 48);;
    case eHeroRequirementType::wine:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::wine);

    case eHeroRequirementType::hallCultureAccess:
        return eLanguage::zeusText(185, 49);
    case eHeroRequirementType::panHellenicGameWin:
        return eLanguage::zeusText(185, 50);;
    case eHeroRequirementType::cityGymnasiumAccess:
        return eLanguage::zeusText(185, 51);;
    case eHeroRequirementType::people:
        return cstr + " " + eLanguage::zeusText(185, 52);;

    case eHeroRequirementType::horsemen:
        return cstr + " " + eLanguage::zeusText(64, 13) + " " + eLanguage::zeusText(185, 17);
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

    case eHeroRequirementType::sanctuaryHades:
        return eLanguage::zeusText(185, 47) + " " + eGod::sGodName(eGodType::hades);
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
    case eHeroRequirementType::stadium:
        return eLanguage::zeusText(185, 126);
    case eHeroRequirementType::meat:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::meat);
    case eHeroRequirementType::wood:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::wood);
    case eHeroRequirementType::soldiers:
        return cstr + " " + eLanguage::zeusText(138, 36) + " " + eLanguage::zeusText(185, 17);

    case eHeroRequirementType::taxes:
        return eLanguage::zeusText(185, 124);
    case eHeroRequirementType::bronze:
        return cstr + " " + eResourceTypeHelpers::typeLongName(eResourceType::bronze);
    }
    return "";
}

std::string eHerosHall::sHeroRequirementStatusText(const eHeroRequirement& hr) {
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
    case eHeroRequirementType::bronze:
    case eHeroRequirementType::marble:
        return cstr + " " + eLanguage::zeusText(185, 16);
    case eHeroRequirementType::hoplite:
        return cstr + " " + eLanguage::zeusText(185, 17);
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

    case eHeroRequirementType::cityGymnasiumAccess:
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
    case eHeroRequirementType::panHellenicGameWin: {
        if(id == 0) {
            return eLanguage::zeusText(185, 24); // no victories
        } else { // 1
            return eLanguage::zeusText(185, 25); // victorious
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

    case eHeroRequirementType::sanctuaryAthena:
    case eHeroRequirementType::sanctuaryHades:
    case eHeroRequirementType::sanctuaryArtemis: {
        return cstr + "% " + eLanguage::zeusText(185, 18);
    } break;
    case eHeroRequirementType::stadium: {
        if(id == 0) {
            return eLanguage::zeusText(185, 127); // no stadium
        } else {
            return eLanguage::zeusText(185, 128); // working stadium
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
    mArrivalCountdown = 15000;
}

void eHerosHall::arrive() {
    auto& board = getBoard();

    mStage = eHeroSummoningStage::arrived;

    spawnHero();

    eEventData ed;
    ed.fHero = mType;
    ed.fChar = mHero;
    ed.fTile = mHero ? mHero->tile() : nullptr;
    board.event(eEvent::heroArrival, ed);
}

eHero* eHerosHall::spawnHero() {
    if(mHero) mHero->kill();
    auto& board = getBoard();
    const auto c = eHero::sCreateHero(mType, board);
    mHero = c.get();
    const auto ct = centerTile();
    const int tx = ct->x();
    const int ty = ct->y();
    const auto cr = eTileHelper::closestRoad(tx, ty, board);
    mHero->changeTile(cr);
    const auto ha = e::make_shared<eHeroAction>(c.get());
    mHero->setAction(ha);
    mSpawnWait = 5000;
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
}

void eHerosHall::write(eWriteStream& dst) const {
    eBuilding::write(dst);
    dst << mStage;
    dst << mArrivalCountdown;
    dst << mPhilosophers;
    dst << mActors;
    dst << mAthletes;
    dst << mUpdateCulture;
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
        board.showTip(eLanguage::zeusText(19, string));
        board.showTip(eLanguage::zeusText(19, 242));
    }
}

void eHerosHall::updateRequirementStatus(eHeroRequirement& hr) {
    const auto t = centerTile();
    if(!t) return;
    const int tx = t->x();
    const int ty = t->y();
    const auto& board = getBoard();
    int& sc = hr.fStatusCount;
    switch(hr.fType) {
    case eHeroRequirementType::armor:
        sc = board.resourceCount(eResourceType::armor);
        return;
    case eHeroRequirementType::hoplite: {
        sc = board.countBanners(eBannerType::hoplite);
    } break;
    case eHeroRequirementType::sanctuaryAthena: {
        const auto sts = board.sanctuary(eGodType::athena);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::noUnrest: {
        const int u = board.unrest();
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
        sc = board.resourceCount(eResourceType::wine);
        break;

    case eHeroRequirementType::hallCultureAccess:
        sc = 0;
        sc += mPhilosophers > 0 ? 1 : 0;
        sc += mActors > 0 ? 1 : 0;
        sc += mAthletes > 0 ? 1 : 0;
        break;
    case eHeroRequirementType::panHellenicGameWin:
        sc = board.wonGames() > 0 ? 1 : 0;
        break;
    case eHeroRequirementType::cityGymnasiumAccess: {
        const int ac = board.athleticsLearningCoverage();
        sc = ac/24;
    } break;
    case eHeroRequirementType::people:
        sc = board.population();
        break;
    case eHeroRequirementType::horsemen: {
        sc = board.countBanners(eBannerType::horseman);
    } break;
    case eHeroRequirementType::horses:
        sc = board.horses();
        break;
    case eHeroRequirementType::food:
        sc = board.resourceCount(eResourceType::food);
        break;

    case eHeroRequirementType::popularity: {
        const int p = board.popularity();
        sc = p/12;
    } break;
    case eHeroRequirementType::health: {
        const int p = board.health();
        sc = p/7;
    } break;
    case eHeroRequirementType::eliteHouses:
        sc = board.eliteHouses();
        break;
    case eHeroRequirementType::oil:
        sc = board.resourceCount(eResourceType::oliveOil);
        break;

    case eHeroRequirementType::sanctuaryHades: {
        const auto sts = board.sanctuary(eGodType::hades);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::drachmas:
        sc = board.drachmas();
        break;
    case eHeroRequirementType::fleece:
        sc = board.resourceCount(eResourceType::fleece);
        break;
    case eHeroRequirementType::sculpture:
        sc = board.resourceCount(eResourceType::sculpture);
        break;

    case eHeroRequirementType::nearPalace: {
        const auto p = board.palace();
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

            for(int k = 0; k < 5; k++) {
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
        const int dx = t->dx();
        const int dy = t->dy();
        const double a = board.appeal(dx, dy);
        if(a < 1.) {
            sc = 0;
        } else if(a < 2.) {
            sc = 1;
        } else if(a < 3.) {
            sc = 2;
        } else if(a < 4.) {
            sc = 3;
        } else {
            sc = 4;
        }
    } break;
    case eHeroRequirementType::walls: {
        ePathFinder p([](eTileBase* const t) {
            const auto bt = t->underBuildingType();
            return bt != eBuildingType::road &&
                   bt != eBuildingType::wall;
        }, [&](eTileBase* const t) {
            const int dx = t->x() - tx;
            const int dy = t->y() == ty;
            return sqrt(dx*dx + dy*dy) > 10;
        });
        const auto startTile = board.tile(tx, ty);
        const int w = board.width();
        const int h = board.height();
        const bool r = p.findPath(startTile, 100, true, w, h);
        sc = r ? 0 : 1;
    } break;
    case eHeroRequirementType::marble:
        sc = board.resourceCount(eResourceType::marble);
        break;

    case eHeroRequirementType::sanctuaryArtemis: {
        const auto sts = board.sanctuary(eGodType::artemis);
        sc = sts ? sts->progress() : 0;
    } break;
    case eHeroRequirementType::stadium:
        sc = board.hasStadium() ? 1 : 0;
        break;
    case eHeroRequirementType::meat:
        sc = board.resourceCount(eResourceType::meat);
        break;
    case eHeroRequirementType::wood:
        sc = board.resourceCount(eResourceType::wood);
        break;
    case eHeroRequirementType::soldiers:
        sc = board.banners().size();
        break;
    case eHeroRequirementType::taxes: {
        const int tc = board.taxesCoverage();
        sc = tc/22;
    } break;
    case eHeroRequirementType::bronze:
        sc = board.resourceCount(eResourceType::bronze);
        break;
    }
}

eHerosHall::eHerosHall(const eHeroType type, eGameBoard& board) :
    eBuilding(board, sHeroTypeToHallType(type), 4, 4),
    mType(type) {
    eGameTextures::loadHerosHall();
    board.registerHeroHall(this);
    setOverlayEnabledFunc([]() { return true; });

    switch(mType) {
    case eHeroType::achilles:
        addRequirement({eHeroRequirementType::armor, 32});
        addRequirement({eHeroRequirementType::hoplite, 3});
        addRequirement({eHeroRequirementType::sanctuaryAthena, 1});
        addRequirement({eHeroRequirementType::noUnrest, 1});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    case eHeroType::atalanta:
        addRequirement({eHeroRequirementType::sanctuaryArtemis, 1});
        addRequirement({eHeroRequirementType::stadium, 1});
        addRequirement({eHeroRequirementType::meat, 32});
        addRequirement({eHeroRequirementType::wood, 32});
        addRequirement({eHeroRequirementType::soldiers, 8});
        break;
    case eHeroType::bellerophon:
        addRequirement({eHeroRequirementType::horses, 15});
        addRequirement({eHeroRequirementType::taxes, 5});
        addRequirement({eHeroRequirementType::drachmas, 10000});
        addRequirement({eHeroRequirementType::bronze, 24});
        addRequirement({eHeroRequirementType::wine, 24});
        break;
    case eHeroType::hercules:
        addRequirement({eHeroRequirementType::hallCultureAccess, 3});
        addRequirement({eHeroRequirementType::panHellenicGameWin, 1});
        addRequirement({eHeroRequirementType::cityGymnasiumAccess, 3});
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
        addRequirement({eHeroRequirementType::popularity, 2});
        addRequirement({eHeroRequirementType::health, 2});
        addRequirement({eHeroRequirementType::eliteHouses, 8});
        addRequirement({eHeroRequirementType::oil, 32});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    case eHeroType::perseus:
        addRequirement({eHeroRequirementType::sanctuaryHades, 2});
        addRequirement({eHeroRequirementType::drachmas, 3000});
        addRequirement({eHeroRequirementType::fleece, 16});
        addRequirement({eHeroRequirementType::sculpture, 6});
        break;
    case eHeroType::theseus:
        addRequirement({eHeroRequirementType::nearPalace, 2});
        addRequirement({eHeroRequirementType::appeal, 2});
        addRequirement({eHeroRequirementType::walls, 1});
        addRequirement({eHeroRequirementType::marble, 32});
        addRequirement({eHeroRequirementType::wine, 16});
        break;
    }
    updateRequirementsStatus();
}

eHerosHall::~eHerosHall() {
    auto& board = getBoard();
    board.destroyed(type());
    board.unregisterHeroHall(this);
    if(mHero) mHero->kill();
}

std::shared_ptr<eTexture> eHerosHall::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    auto& board = getBoard();
    if(board.poseidonMode()) {
        eGameTextures::loadPoseidonHerosHall();
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

    const int cupdate = 5000;
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
