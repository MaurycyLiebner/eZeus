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
        return cstr + " " + eLanguage::text("suits_of_armor");
    case eHeroRequirementType::hoplite:
        return cstr + " " + eLanguage::text("hoplite_companies");
    case eHeroRequirementType::sanctuary:
        return cstr + " " + eLanguage::text("sanctuaries");
    case eHeroRequirementType::noUnrest:
        return eLanguage::text("no_unrest");
    case eHeroRequirementType::wine:
        return eLanguage::text("amphorae_of_wine");

    case eHeroRequirementType::hallCultureAccess:
        return eLanguage::text("excellent_hall_culture_access");
    case eHeroRequirementType::panHellenicGameWin:
        return eLanguage::text("win_pan_hellenic_game");
    case eHeroRequirementType::cityGymnasiumAccess:
        return eLanguage::text("excellent_city_gymnasium_access");
    case eHeroRequirementType::people:
        return cstr + " " + eLanguage::text("people_in_city");

    case eHeroRequirementType::horsemen:
        return cstr + " " + eLanguage::text("horsemen_companies");
    case eHeroRequirementType::horses:
        return cstr + " " + eLanguage::text("horses_in_city");
    case eHeroRequirementType::food:
        return cstr + " " + eLanguage::text("crates_of_food");

    case eHeroRequirementType::popularity:
        return eLanguage::text("excellect_popularity");
    case eHeroRequirementType::health:
        return eLanguage::text("excellect_health");
    case eHeroRequirementType::eliteHouses:
        return cstr + " " + eLanguage::text("elite_houses");
    case eHeroRequirementType::oil:
        return cstr + " " + eLanguage::text("jugs_of_oil");

    case eHeroRequirementType::drachmas:
        return cstr + " " + eLanguage::text("drachmas");
    case eHeroRequirementType::fleece:
        return cstr + " " + eLanguage::text("skeins_of_fleece");
    case eHeroRequirementType::sculpture:
        return cstr + " " + eLanguage::text("pieces_of_sculpture");

    case eHeroRequirementType::nearPalace:
        return eLanguage::text("hall_near_palace");
    case eHeroRequirementType::appeal:
        return eLanguage::text("good_appeal_around_hall");
    case eHeroRequirementType::walls:
        return eLanguage::text("hall_protected_by_walls");
    case eHeroRequirementType::marble:
        return cstr + " " + eLanguage::text("slabs_of_marble");

    case eHeroRequirementType::sanctuaryArtemis:
        return eLanguage::text("sanctuary_to_artemis");
    case eHeroRequirementType::stadium:
        return eLanguage::text("working_stadium");
    case eHeroRequirementType::meat:
        return cstr + " " + eLanguage::text("sides_of_meat");
    case eHeroRequirementType::wood:
        return cstr + " " + eLanguage::text("planks_of_wood");
    case eHeroRequirementType::soldiers:
        return cstr + " " + eLanguage::text("companies_of_soldiers");

    case eHeroRequirementType::taxes:
        return eLanguage::text("excellent_city_tax_coverage");
    case eHeroRequirementType::bronze:
        return cstr + " " + eLanguage::text("bars_of_bronze");
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
        return cstr + " " + eLanguage::text("in_storage");
    case eHeroRequirementType::hoplite:
        return cstr + " " + eLanguage::text("hoplite_companies");
    case eHeroRequirementType::sanctuary:
        return cstr + " " + eLanguage::text("sanctuaries");
    case eHeroRequirementType::noUnrest: {
        if(id == 0) {
            return eLanguage::text("some_unrest");
        } else {
            return eLanguage::text("no_unrest");
        }
    } break;

    case eHeroRequirementType::cityGymnasiumAccess:
    case eHeroRequirementType::hallCultureAccess: {
        if(id == 0) {
            return eLanguage::text("no_access");
        } else if(id == 1) {
            return eLanguage::text("some_access");
        } else if(id == 2) {
            return eLanguage::text("good_access");
        } else { // 3
            return eLanguage::text("excellent_access");
        }
    } break;
    case eHeroRequirementType::panHellenicGameWin: {
        if(id == 0) {
            return eLanguage::text("lost");
        } else { // 1
            return eLanguage::text("victorious");
        }
    } break;
    case eHeroRequirementType::people:
        return cstr + " " + eLanguage::text("people_in_city");

    case eHeroRequirementType::horsemen:
        return cstr + " " + eLanguage::text("horsemen_companies");
    case eHeroRequirementType::horses:
        return cstr + " " + eLanguage::text("horses_in_city");

    case eHeroRequirementType::popularity: {
        if(id == 0) {
            return eLanguage::text("bad_popularity");
        } else if(id == 1) {
            return eLanguage::text("good_popularity");
        } else { // 2
            return eLanguage::text("excellect_popularity");
        }
    } break;
    case eHeroRequirementType::health: {
        if(id == 0) {
            return eLanguage::text("bad_health");
        } else if(id == 1) {
            return eLanguage::text("good_health");
        } else { // 2
            return eLanguage::text("excellect_health");
        }
    } break;
    case eHeroRequirementType::eliteHouses:
        return cstr + " " + eLanguage::text("elite_houses");

    case eHeroRequirementType::drachmas:
        return cstr + " " + eLanguage::text("drachmas");

    case eHeroRequirementType::nearPalace: {
        if(id == 0) {
            return eLanguage::text("no_palace");
        } else if(id == 1) {
            return eLanguage::text("too_far");
        } else {
            return eLanguage::text("near");
        }
    } break;
    case eHeroRequirementType::appeal: {
        if(id == 0) {
            return eLanguage::text("no_appeal");
        } else if(id == 1) {
            return eLanguage::text("some_appeal");
        } else { // 2
            return eLanguage::text("good_appeal");
        }
    } break;
    case eHeroRequirementType::walls: {
        if(id == 0) {
            return eLanguage::text("unprotected");
        } else {
            return eLanguage::text("protected");
        }
    } break;

    case eHeroRequirementType::sanctuaryArtemis: {
        return cstr + "% " + eLanguage::text("complete");
    } break;
    case eHeroRequirementType::stadium: {
        if(id == 0) {
            return eLanguage::text("no_stadium");
        } else {
            return eLanguage::text("working_stadium");
        }
    } break;
    case eHeroRequirementType::soldiers:
        return cstr + " " + eLanguage::text("companies_of_soldiers");

    case eHeroRequirementType::taxes: {
        if(id == 0) {
            return eLanguage::text("terrible_coverage");
        } else if(id == 1) {
            return eLanguage::text("poor_coverage");
        } else if(id == 2) {
            return eLanguage::text("not_bad_coverage");
        } else if(id == 3) {
            return eLanguage::text("ok_coverage");
        } else if(id == 4) {
            return eLanguage::text("good_coverage");
        } else { // 5
            return eLanguage::text("excellent_coverage");
        }
    } break;
    }
    return "";
}

std::string eHerosHall::sTitle(const eHeroType ht) {
    const auto name = eHero::sHeroName(ht);
    const auto hhf = eLanguage::text("heros_hall_for");
    const auto title = hhf + " " + name;
    return title;
}

void eHerosHall::summon() {
    mStage = eHeroSummoningStage::summoned;
    mArrivalCountdown = 15000;
}

void eHerosHall::arrive() {
    auto& board = getBoard();
    eEvent e;
    switch(mType) {
    case eHeroType::achilles:
        e = eEvent::achillesArrival;
        break;
    case eHeroType::atalanta:
        e = eEvent::atalantaArrival;
        break;
    case eHeroType::bellerophon:
        e = eEvent::bellerophonArrival;
        break;
    case eHeroType::hercules:
        e = eEvent::herculesArrival;
        break;
    case eHeroType::jason:
        e = eEvent::jasonArrival;
        break;
    case eHeroType::odysseus:
        e = eEvent::odysseusArrival;
        break;
    case eHeroType::perseus:
        e = eEvent::perseusArrival;
        break;
    case eHeroType::theseus:
        e = eEvent::theseusArrival;
        break;
    }

    mStage = eHeroSummoningStage::arrived;

    spawnHero();

    eEventData ed;
    ed.fTile = mHero ? mHero->tile() : nullptr;
    board.event(e, ed);
}

void eHerosHall::spawnHero() {
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
    for(auto& r : mRequirements) {
        updateRequirementStatus(r);
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
    case eHeroRequirementType::sanctuary: {
        const auto sts = board.sanctuaries();
        sc = sts.size();
    } break;
    case eHeroRequirementType::noUnrest:
        sc = board.unrest() == 0 ? 1 : 0;
        break;
    case eHeroRequirementType::wine:
        sc = board.resourceCount(eResourceType::wine);
        break;

    case eHeroRequirementType::hallCultureAccess:
        sc = 0;
        sc += mPhilosophers ? 1 : 0;
        sc += mActors ? 1 : 0;
        sc += mAthletes ? 1 : 0;
        break;
    case eHeroRequirementType::panHellenicGameWin:
        sc = board.wonGames() > 0 ? 1 : 0;
        break;
    case eHeroRequirementType::cityGymnasiumAccess: {
        const int ac = board.athleticsCoverage();
        sc = ac/30;
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
        sc = p/30;
    } break;
    case eHeroRequirementType::health: {
        const int p = board.health();
        sc = p/30;
    } break;
    case eHeroRequirementType::eliteHouses:
        sc = board.eliteHouses();
        break;
    case eHeroRequirementType::oil:
        sc = board.resourceCount(eResourceType::oliveOil);
        break;

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
        const double a = board.appeal(tx, ty);
        if(a < 2.) {
            sc = 0;
        } else if(a < 4.) {
            sc = 1;
        } else {
            sc = 2;
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
        sc = tc/18;
    } break;
    case eHeroRequirementType::bronze:
        sc = board.resourceCount(eResourceType::bronze);
        break;
    }
}

eHerosHall::eHerosHall(const eHeroType type, eGameBoard& board) :
    eBuilding(board, sHeroTypeToHallType(type), 4, 4),
    mType(type) {
    setOverlayEnabledFunc([]() { return true; });

    switch(mType) {
    case eHeroType::achilles:
        addRequirement({eHeroRequirementType::armor, 32});
        addRequirement({eHeroRequirementType::hoplite, 3});
        addRequirement({eHeroRequirementType::sanctuary, 1});
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
        addRequirement({eHeroRequirementType::sanctuary, 2});
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
}

std::shared_ptr<eTexture> eHerosHall::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    return texs.fHeroHall;
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
    const int wait = 10000;
    mRequirementsUpdate += by;
    if(mRequirementsUpdate > wait) {
        mRequirementsUpdate -= wait;
        updateRequirementsStatus();
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
        if(!mHero) {
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
    case eProvide::philosopher:
        value = &mPhilosophers;
        break;
    case eProvide::actor:
        value = &mActors;
        break;
    case eProvide::gymnast:
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
