#include "ebuilding.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "engine/etile.h"
#include "eruins.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "buildings/eaestheticsbuilding.h"

#include "buildings/allbuildings.h"

#include "evectorhelpers.h"

#include "elanguage.h"

eBuilding::eBuilding(eGameBoard& board,
                     const eBuildingType type,
                     const int sw, const int sh) :
    eObject(board),
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {
    getBoard().registerBuilding(this);
}

eBuilding::~eBuilding() {
    getBoard().unregisterBuilding(this);
}

eTextureSpace eBuilding::getTextureSpace(const int tx, const int ty,
                                         const eTileSize size) const {
    const SDL_Point p{tx, ty};
    const auto r = tileRect();
    if(!SDL_PointInRect(&p, &r)) return {nullptr};
    const auto tex = getTexture(size);
    return eTextureSpace{tex, true, r};
}

int eBuilding::provide(const eProvide p, const int n) {
    (void)n;
    if(p == eProvide::maintanance) {
        const int nn = 100 - mMaintance;
        mMaintance += nn;
        return nn;
    }
    return 0;
}

bool eBuilding::sWalkableBuilding(const eBuildingType t) {
    if(t == eBuildingType::none) return true;
    if(t == eBuildingType::road) return true;
    if(t == eBuildingType::bridge) return true;
    if(t == eBuildingType::ruins) return true;
    if(t == eBuildingType::vine) return true;
    if(t == eBuildingType::park) return true;
    if(t == eBuildingType::oliveTree) return true;
    if(t == eBuildingType::orangeTree) return true;
    if(t == eBuildingType::sheep) return true;
    if(t == eBuildingType::goat) return true;
    if(t == eBuildingType::cattle) return true;
    if(t == eBuildingType::templeTile) return true;
    if(t == eBuildingType::palaceTile) return true;
    if(t == eBuildingType::godMonumentTile) return true;
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(t);
    if(bi >= min && bi <= max) return true;
    return false;
}

bool eBuilding::sFlatBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeZeus);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r ||
           bt == eBuildingType::none ||
           bt == eBuildingType::road ||
           bt == eBuildingType::bridge ||
           bt == eBuildingType::templeTile ||
           bt == eBuildingType::vine ||
           bt == eBuildingType::park ||
           bt == eBuildingType::oliveTree ||
           bt == eBuildingType::orangeTree ||
           bt == eBuildingType::cattle ||
           bt == eBuildingType::sheep ||
           bt == eBuildingType::goat ||
           bt == eBuildingType::ruins ||
           bt == eBuildingType::palaceTile ||
           bt == eBuildingType::godMonumentTile;
}

bool eBuilding::sSanctuaryBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::templeAphrodite);
    const int max = static_cast<int>(eBuildingType::templeAltar);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r;
}

bool eBuilding::sAestheticsBuilding(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::park);
    const int max = static_cast<int>(eBuildingType::stoneCircle);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r;
}

bool eBuilding::sHeroHall(const eBuildingType bt) {
    const int min = static_cast<int>(eBuildingType::achillesHall);
    const int max = static_cast<int>(eBuildingType::theseusHall);
    const int bi = static_cast<int>(bt);
    const bool r = bi >= min && bi <= max;
    return r;
}

bool eBuilding::sFlammable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(sHeroHall(bt)) return false;
    if(sAestheticsBuilding(bt)) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::cattle) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::tower) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    if(bt == eBuildingType::bridge) return false;
    return true;
}

bool eBuilding::sTimedBuilding(const eBuildingType bt) {
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::templeTile) return false;
    if(bt == eBuildingType::templeMonument) return false;
    if(bt == eBuildingType::templeStatue) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    if(bt == eBuildingType::bridge) return false;
    if(sAestheticsBuilding(bt)) return false;
    return true;
}

bool eBuilding::sBlessable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::cattle) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::wall) return false;
    if(bt == eBuildingType::gatehouse) return false;
    if(bt == eBuildingType::tower) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    if(bt == eBuildingType::bridge) return false;
    if(sHeroHall(bt)) return false;
    if(sAestheticsBuilding(bt)) return false;
    return true;
}

bool eBuilding::sAttackable(const eBuildingType bt) {
    const bool s = sSanctuaryBuilding(bt);
    if(s) return false;
    if(bt == eBuildingType::road) return false;
    if(bt == eBuildingType::sheep) return false;
    if(bt == eBuildingType::goat) return false;
    if(bt == eBuildingType::cattle) return false;
    if(bt == eBuildingType::ruins) return false;
    if(bt == eBuildingType::park) return false;
    if(bt == eBuildingType::palaceTile) return false;
    if(bt == eBuildingType::godMonumentTile) return false;
    if(bt == eBuildingType::bridge) return false;
    return true;
}

std::string eBuilding::sNameForBuilding(eBuilding* const b) {
    if(!b) return "";
    const auto type = b->type();
    switch(type) {
    case eBuildingType::commemorative: {
        const auto c = static_cast<eCommemorative*>(b);
        const int id = c->id();
        const int group = 90;
        int string = -1;
        if(id == 0) {
            string = 1;
        } else if(id == 1) {
            string = 2;
        } else if(id == 2) {
            string = 3;
        } else if(id == 3) {
            string = 4;
        } else if(id == 4) {
            string = 5;
        } else if(id == 5) {
            string = 6;
        } else if(id == 6) {
            string = 7;
        } else if(id == 7) {
            string = 8;
        } else if(id == 8) {
            string = 9;
        }
        return eLanguage::zeusText(group, string);
    } break;
    default:
        break;
    }
    return sNameForBuilding(type);
}

std::string eBuilding::sNameForBuilding(const eBuildingType type) {
    int group = 28;
    int string = -1;
    switch(type) {
    case eBuildingType::road:
        string = 28;
        break;

    case eBuildingType::commonHouse:
        string = 2;
        break;
    case eBuildingType::eliteHousing:
        string = 9;
        break;

    case eBuildingType::fountain:
        string = 74;
        break;
    case eBuildingType::hospital:
        string = 76;
        break;
    case eBuildingType::maintenanceOffice:
        string = 121;
        break;
    case eBuildingType::watchPost:
        string = 124;
        break;

    case eBuildingType::palace:
        string = 117;
        break;
    case eBuildingType::taxOffice:
        string = 122;
        break;
    case eBuildingType::bridge:
        string = 120;
        break;

    case eBuildingType::gymnasium:
        string = 79;
        break;
    case eBuildingType::stadium:
        string = 80;
        break;

    case eBuildingType::bibliotheke:
        string = 202;
        break;
    case eBuildingType::observatory:
        string = 203;
        break;
    case eBuildingType::university:
        string = 204;
        break;
    case eBuildingType::laboratory:
        string = 205;
        break;
    case eBuildingType::inventorsWorkshop:
        string = 206;
        break;
    case eBuildingType::museum:
        string = 207;
        break;

    case eBuildingType::wheatFarm:
        string = 31;
        break;
    case eBuildingType::carrotsFarm:
        string = 33;
        break;
    case eBuildingType::onionsFarm:
        string = 32;
        break;

    case eBuildingType::vine:
        string = 35;
        break;
    case eBuildingType::oliveTree:
        string = 36;
        break;
    case eBuildingType::orangeTree:
        string = 217;
        break;
    case eBuildingType::orangeTendersLodge:
        string = 214;
        break;
    case eBuildingType::growersLodge:
        string = 37;
        break;
    case eBuildingType::corral:
        string = 216;
        break;

    case eBuildingType::dairy:
        string = 42;
        break;
    case eBuildingType::goat:
        string = 39;
        break;
    case eBuildingType::cardingShed:
        string = 41;
        break;
    case eBuildingType::sheep:
        string = 40;
        break;
    case eBuildingType::cattle:
        string = 220;
        break;

    case eBuildingType::fishery:
        string = 44;
        break;
    case eBuildingType::urchinQuay:
        string = 45;
        break;
    case eBuildingType::huntingLodge:
        string = 46;
        break;

    case eBuildingType::mint:
        string = 48;
        break;
    case eBuildingType::foundry:
        string = 50;
        break;
    case eBuildingType::timberMill:
        string = 51;
        break;
    case eBuildingType::masonryShop:
        string = 49;
        break;

    case eBuildingType::winery:
        string = 53;
        break;
    case eBuildingType::olivePress:
        string = 54;
        break;
    case eBuildingType::sculptureStudio:
        string = 55;
        break;

    case eBuildingType::warehouse:
        string = 58;
        break;
    case eBuildingType::granary:
        string = 57;
        break;

    case eBuildingType::commonAgora:
        string = 63;
        break;
    case eBuildingType::grandAgora:
        string = 64;
        break;
    case eBuildingType::foodVendor:
        string = 68;
        break;
    case eBuildingType::fleeceVendor:
        string = 69;
        break;
    case eBuildingType::oilVendor:
        string = 70;
        break;
    case eBuildingType::wineVendor:
        string = 71;
        break;
    case eBuildingType::armsVendor:
        string = 72;
        break;
    case eBuildingType::horseTrainer:
        string = 73;
        break;

    case eBuildingType::podium:
        string = 81;
        break;
    case eBuildingType::college:
        string = 77;
        break;
    case eBuildingType::theater:
        string = 82;
        break;
    case eBuildingType::dramaSchool:
        string = 78;
        break;

    case eBuildingType::templeZeus:
        string = 84;
        break;
    case eBuildingType::templePoseidon:
        string = 85;
        break;
    case eBuildingType::templeHades:
        string = 95;
        break;
    case eBuildingType::templeHera:
        string = 96;
        break;
    case eBuildingType::templeDemeter:
        string = 86;
        break;
    case eBuildingType::templeAthena:
        string = 92;
        break;
    case eBuildingType::templeArtemis:
        string = 88;
        break;
    case eBuildingType::templeApollo:
        string = 87;
        break;
    case eBuildingType::templeAtlas:
        string = 97;
        break;
    case eBuildingType::templeAres:
        string = 89;
        break;
    case eBuildingType::templeHephaestus:
        string = 93;
        break;
    case eBuildingType::templeAphrodite:
        string = 90;
        break;
    case eBuildingType::templeHermes:
        string = 91;
        break;
    case eBuildingType::templeDionysus:
        string = 94;
        break;

    case eBuildingType::artisansGuild:
        string = 56;
        break;

    case eBuildingType::achillesHall:
        group = 185;
        string = 8;
        break;
    case eBuildingType::atalantaHall:
        group = 185;
        string = 14;
        break;
    case eBuildingType::bellerophonHall:
        group = 185;
        string = 15;
        break;
    case eBuildingType::herculesHall:
        group = 185;
        string = 9;
        break;
    case eBuildingType::jasonHall:
        group = 185;
        string = 10;
        break;
    case eBuildingType::odysseusHall:
        group = 185;
        string = 11;
        break;
    case eBuildingType::perseusHall:
        group = 185;
        string = 12;
        break;
    case eBuildingType::theseusHall:
        group = 185;
        string = 13;
        break;

    case eBuildingType::godMonument:
        string = 119;
        break;

    case eBuildingType::wall:
        string = 130;
        break;
    case eBuildingType::tower:
        string = 132;
        break;
    case eBuildingType::gatehouse:
        string = 131;
        break;

    case eBuildingType::armory:
        string = 135;
        break;
    case eBuildingType::horseRanch:
        string = 133;
        break;

    case eBuildingType::park:
        string = 128;
        break;
    case eBuildingType::waterPark:
        string = 25;
        break;
    case eBuildingType::doricColumn:
        string = 129;
        break;
    case eBuildingType::ionicColumn:
        string = 145;
        break;
    case eBuildingType::corinthianColumn:
        string = 146;
        break;
    case eBuildingType::avenue:
        string = 118;
        break;

    case eBuildingType::bench:
        string = 127;
        break;
    case eBuildingType::birdBath:
        string = 152;
        break;
    case eBuildingType::shortObelisk:
        string = 24;
        break;
    case eBuildingType::tallObelisk:
        string = 19;
        break;
    case eBuildingType::flowerGarden:
        string = 15;
        break;
    case eBuildingType::gazebo:
        string = 16;
        break;
    case eBuildingType::shellGarden:
        string = 150;
        break;
    case eBuildingType::sundial:
        string = 20;
        break;
    case eBuildingType::hedgeMaze:
        string = 17;
        break;
    case eBuildingType::dolphinSculpture:
        string = 148;
        break;
    case eBuildingType::orrery:
        string = 149;
        break;
    case eBuildingType::spring:
        string = 22;
        break;
    case eBuildingType::topiary:
        string = 21;
        break;
    case eBuildingType::fishPond:
        string = 18;
        break;
    case eBuildingType::baths:
        string = 151;
        break;
    case eBuildingType::stoneCircle:
        string = 23;
        break;

    case eBuildingType::commemorative:
        string = 119;
        break;

    }
    return eLanguage::zeusText(group, string);
}

void eBuilding::sInfoText(eBuilding* const b,
                          std::string& title,
                          std::string& info,
                          std::string& employmentInfo,
                          std::string& additionalInfo) {
    if(!b) return;
    auto& board = b->getBoard();
    int e = 0;
    int maxE = 0;
    if(const auto eb = dynamic_cast<eEmployingBuilding*>(b)) {
        e = eb->employed();
        maxE = eb->maxEmployees();
    }
    const auto type = b->type();
    const bool blessed = b->blessed();
    const bool cursed = b->cursed();
    const bool onFire = b->isOnFire();
    int group = 0;
    int titleString = 0;
    int infoString = 1;
    int employmentInfoString = -1;
    int additionalInfoString = -1;
    switch(type) {
    case eBuildingType::park: {
        group = 75;
    } break;
    case eBuildingType::hospital: {
        group = 76;
        if(cursed) {
            employmentInfoString = 9;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e == 1) {
            employmentInfoString = 6;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e > 7) {
            employmentInfoString = 3;
        } else if(e > 4) {
            employmentInfoString = 4;
        } else {
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::college: {
        group = 77;
        if(cursed) {
            employmentInfoString = 9;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e == 1) {
            employmentInfoString = 6;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e > 7) {
            employmentInfoString = 3;
        } else if(e > 4) {
            employmentInfoString = 4;
        } else {
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::dramaSchool: {
        group = 78;
        if(cursed) {
            employmentInfoString = 9;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e == 1) {
            employmentInfoString = 6;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e > 7) {
            employmentInfoString = 3;
        } else if(e > 4) {
            employmentInfoString = 4;
        } else {
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::gymnasium: {
        group = 79;
        if(cursed) {
            employmentInfoString = 9;
        } else if(blessed) {
            employmentInfoString = 10;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e == 1) {
            employmentInfoString = 6;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e > 4) {
            employmentInfoString = 3;
        } else if(e > 2) {
            employmentInfoString = 4;
        } else {
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::stadium: {
        const auto s = static_cast<eStadium*>(b);
        const bool a = s->available();
        group = 80;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::podium: {
        const auto p = static_cast<ePodium*>(b);
        const bool a = p->available();
        group = 81;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::theater: {
        const auto t = static_cast<eTheater*>(b);
        const bool a = t->available();
        group = 82;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::bibliotheke: {
        group = 336;
        if(cursed) {
            employmentInfoString = 9;
        } else if(blessed) {
            employmentInfoString = 10;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e == 1) {
            employmentInfoString = 6;
        } else if(e == 2) {
            employmentInfoString = 5;
        } else if(e == 3) {
            employmentInfoString = 4;
        } else if(e == 4) {
            employmentInfoString = 3;
        } else { // if(e == 5) {
            employmentInfoString = 2;
        }
    } break;
    case eBuildingType::university: {
        group = 334;
        if(cursed) {
            employmentInfoString = 9;
        } else if(blessed) {
            employmentInfoString = 10;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e < 3) {
            employmentInfoString = 6;
        } else if(e < 5) {
            employmentInfoString = 5;
        } else if(e < 8) {
            employmentInfoString = 4;
        } else if(e < 12) {
            employmentInfoString = 3;
        } else { // if(e == 12) {
            employmentInfoString = 2;
        }
    } break;
    case eBuildingType::inventorsWorkshop: {
        group = 335;
        if(cursed) {
            employmentInfoString = 9;
        } else if(blessed) {
            employmentInfoString = 10;
        } else if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(e < 3) {
            employmentInfoString = 6;
        } else if(e < 5) {
            employmentInfoString = 5;
        } else if(e < 8) {
            employmentInfoString = 4;
        } else if(e < 12) {
            employmentInfoString = 3;
        } else { // if(e == 12) {
            employmentInfoString = 2;
        }
    } break;
    case eBuildingType::observatory: {
        const auto t = static_cast<eObservatory*>(b);
        const bool a = t->available();
        group = 337;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::laboratory: {
        const auto t = static_cast<eLaboratory*>(b);
        const bool a = t->available();
        group = 338;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::museum: {
        const auto t = static_cast<eMuseum*>(b);
        const bool a = t->available();
        group = 339;
        if(cursed) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 14;
        } else if(onFire) {
            employmentInfoString = 12;
        } else if(e == 0) {
            employmentInfoString = 4;
        } else if(!a) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::horseRanch: {
        const auto hr = static_cast<eHorseRanch*>(b);
        const int w = hr->wheat();
        group = 89;
        if(w == 0) {
            employmentInfoString = 11;
        } else if(e < 2) {
            employmentInfoString = 10;
        } else if(e < 5) {
            employmentInfoString = 9;
        } else if(e < 9) {
            employmentInfoString = 8;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else {
            employmentInfoString = 7;
        }
    } break;
    case eBuildingType::commemorative: {
        const auto cm = static_cast<eCommemorative*>(b);
        const int id = cm->id();
        group = 90;
        if(id == 0) {
            employmentInfoString = 1;
        } else if(id == 1) {
            employmentInfoString = 2;
        } else if(id == 2) {
            employmentInfoString = 3;
        } else if(id == 3) {
            employmentInfoString = 4;
        } else if(id == 4) {
            employmentInfoString = 5;
        } else if(id == 5) {
            employmentInfoString = 6;
        } else if(id == 6) {
            employmentInfoString = 7;
        } else if(id == 7) {
            employmentInfoString = 8;
        } else if(id == 8) {
            employmentInfoString = 9;
        }
    } break;
    case eBuildingType::godMonument: {
        const auto gm = static_cast<eGodMonument*>(b);
        const auto god = gm->god();
        const auto id = gm->id();
        group = 90;
        employmentInfoString = -1;
        switch(id) {
        case eGodQuestId::godQuest1: {
            switch(god) {
            case eGodType::zeus:
                infoString = 10;
                break;
            case eGodType::poseidon:
                infoString = 11;
                break;
            case eGodType::demeter:
                infoString = 12;
                break;
            case eGodType::apollo:
                infoString = 13;
                break;
            case eGodType::artemis:
                infoString = 14;
                break;
            case eGodType::ares:
                infoString = 15;
                break;
            case eGodType::aphrodite:
                infoString = 16;
                break;
            case eGodType::hermes:
                infoString = 17;
                break;
            case eGodType::athena:
                infoString = 18;
                break;
            case eGodType::hephaestus:
                infoString = 19;
                break;
            case eGodType::dionysus:
                infoString = 20;
                break;
            case eGodType::hades:
                infoString = 21;
                break;
            case eGodType::hera:
                infoString = 34;
                break;
            case eGodType::atlas:
                infoString = 35;
                break;
            }
        } break;
        case eGodQuestId::godQuest2: {
            switch(god) {
            case eGodType::zeus:
                infoString = 38;
                break;
            case eGodType::poseidon:
                infoString = 39;
                break;
            case eGodType::demeter:
                infoString = 40;
                break;
            case eGodType::apollo:
                infoString = 41;
                break;
            case eGodType::artemis:
                infoString = 42;
                break;
            case eGodType::ares:
                infoString = 43;
                break;
            case eGodType::aphrodite:
                infoString = 44;
                break;
            case eGodType::hermes:
                infoString = 45;
                break;
            case eGodType::athena:
                infoString = 46;
                break;
            case eGodType::hephaestus:
                infoString = 47;
                break;
            case eGodType::dionysus:
                infoString = 48;
                break;
            case eGodType::hades:
                infoString = 49;
                break;
            case eGodType::hera:
                infoString = 62;
                break;
            case eGodType::atlas:
                infoString = 63;
                break;
            }
        } break;
        }
    } break;
    case eBuildingType::commonAgora:
    case eBuildingType::grandAgora: {
        const auto ca = static_cast<eAgoraBase*>(b);
        const bool hv = ca->hasVendors();
        group = 97;
        titleString = type == eBuildingType::commonAgora ? 0 : 1;
        infoString = -1;
        if(cursed) {
            employmentInfoString = 24;
        } else if(blessed) {
            employmentInfoString = 25;
        } else if(onFire) {
            employmentInfoString = 23;
        } else if(e == 0) {
            employmentInfoString = 3;
        } else if(!hv) {
            employmentInfoString = 4;
        } else {
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::tradePost: {
        group = 69;
        if(e == maxE) {
            employmentInfoString = 15;
        } else if(e == 0) {
            employmentInfoString = 9;
        } else if(e < 14) {
            employmentInfoString = 13;
        } else {
            employmentInfoString = 14;
        }
    } break;
    case eBuildingType::fishery: {
        const auto f = static_cast<eFishery*>(b);
        const bool nt = f->noTarget();
        const auto state = f->state();
        group = 102;
        if(cursed) {
            employmentInfoString = 11;
        } else if(blessed) {
            employmentInfoString = 12;
        } else if(onFire) {
            employmentInfoString = 10;
        } else if(state == eFisheryState::buildingBoat) {
            employmentInfoString = 2;
        } else if(nt) {
            employmentInfoString = 8;
        } else {
            employmentInfoString = 4;
        }
    } break;
    case eBuildingType::palace: {
        group = 103;
        if(cursed) {
            employmentInfoString = 15;
        } else if(onFire) {
            employmentInfoString = 14;
        } else {
            employmentInfoString = 1;
        }
    } break;
    case eBuildingType::maintenanceOffice: {
        group = 104;
        if(onFire) {
            employmentInfoString = 10;
        } else if(e == 0) {
            employmentInfoString = 9;
        } else if(e == 1) {
            employmentInfoString = 8;
        } else if(e == maxE) {
            employmentInfoString = 4;
        } else if(e == 2) {
            employmentInfoString = 7;
        } else if(e == 3) {
            employmentInfoString = 6;
        } else { // e == 4
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::taxOffice: {
        const auto p = board.palace();
        group = 106;
        if(onFire) {
            employmentInfoString = 13;
        } else if(blessed) {
            employmentInfoString = 15;
        } else if(!p) {
            employmentInfoString = 11;
        } else if(e == 0) {
            employmentInfoString = 10;
        } else if(e == 1) {
            employmentInfoString = 9;
        } else if(e == maxE) {
            employmentInfoString = 5;
        } else if(e < 4) {
            employmentInfoString = 8;
        } else if(e < 7) {
            employmentInfoString = 7;
        } else { // e <= 8
            employmentInfoString = 6;
        }
    } break;
    case eBuildingType::orangeTree: {
        group = 107;
        employmentInfoString = 1;
    } break;
    case eBuildingType::fountain: {
        group = 108;
        if(e == 0) {
            employmentInfoString = 2;
        } else if(e == 1) {
            employmentInfoString = 3;
        } else if(e == 2) {
            employmentInfoString = 4;
        } else if(e == 3) {
            employmentInfoString = 5;
        } else { // e == maxE
            employmentInfoString = 6;
        }
    } break;
    case eBuildingType::wheatFarm: {
        group = 112;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 8) {
            employmentInfoString = 7;
        } else if(e > 6) {
            employmentInfoString = 8;
        } else if(e > 4) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::onionsFarm: {
        group = 113;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 8) {
            employmentInfoString = 7;
        } else if(e > 6) {
            employmentInfoString = 8;
        } else if(e > 4) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::carrotsFarm: {
        group = 114;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 8) {
            employmentInfoString = 7;
        } else if(e > 6) {
            employmentInfoString = 8;
        } else if(e > 4) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::oliveTree: {
        group = 115;
        employmentInfoString = 1;
    } break;
    case eBuildingType::vine: {
        group = 116;
        employmentInfoString = 1;
    } break;
    case eBuildingType::foundry: {
        group = 117;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 12) {
            employmentInfoString = 7;
        } else if(e > 9) {
            employmentInfoString = 8;
        } else if(e > 6) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::masonryShop: {
        group = 118;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 12) {
            employmentInfoString = 7;
        } else if(e > 9) {
            employmentInfoString = 8;
        } else if(e > 6) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::mint: {
        group = 119;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 12) {
            employmentInfoString = 7;
        } else if(e > 9) {
            employmentInfoString = 8;
        } else if(e > 6) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::timberMill: {
        group = 120;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 9) {
            employmentInfoString = 7;
        } else if(e > 7) {
            employmentInfoString = 8;
        } else if(e > 5) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::dairy: {
        group = 121;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 6) {
            employmentInfoString = 7;
        } else if(e > 4) {
            employmentInfoString = 8;
        } else if(e > 2) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::winery: {
        const auto w = static_cast<eWinery*>(b);
        const int r = w->rawCount();
        if(r == 0) additionalInfoString = 11;
        group = 122;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 10) {
            employmentInfoString = 7;
        } else if(e > 7) {
            employmentInfoString = 8;
        } else if(e > 5) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::cardingShed: {
        group = 123;
        if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 6) {
            employmentInfoString = 7;
        } else if(e > 4) {
            employmentInfoString = 8;
        } else if(e > 2) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::armory: {
        const auto a = static_cast<eArmory*>(b);
        const int r = a->rawCount();
        group = 124;
        if(r == 0) {
            employmentInfoString = 11;
        } else if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 15) {
            employmentInfoString = 7;
        } else if(e > 11) {
            employmentInfoString = 8;
        } else if(e > 7) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::olivePress: {
        const auto a = static_cast<eOlivePress*>(b);
        const int r = a->rawCount();
        group = 125;
        if(r == 0) {
            employmentInfoString = 11;
        } else if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 10) {
            employmentInfoString = 7;
        } else if(e > 7) {
            employmentInfoString = 8;
        } else if(e > 5) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::sculptureStudio: {
        const auto a = static_cast<eSculptureStudio*>(b);
        const int r = a->rawCount();
        group = 126;
        if(r == 0) {
            employmentInfoString = 11;
        } else if(e == 0) {
            employmentInfoString = 5;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 10) {
            employmentInfoString = 7;
        } else if(e > 7) {
            employmentInfoString = 8;
        } else if(e > 5) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::templeAphrodite:
    case eBuildingType::templeApollo:
    case eBuildingType::templeAres:
    case eBuildingType::templeArtemis:
    case eBuildingType::templeAthena:
    case eBuildingType::templeAtlas:
    case eBuildingType::templeDemeter:
    case eBuildingType::templeDionysus:
    case eBuildingType::templeHades:
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeHera:
    case eBuildingType::templeHermes:
    case eBuildingType::templePoseidon:
    case eBuildingType::templeZeus: {
        group = 132;
        titleString = -1;
        infoString = -1;
        if(e == 0) {
            employmentInfoString = 0;
        } else if(e == maxE) {
            employmentInfoString = 9;
        } else if(e > 0.8*maxE) {
            employmentInfoString = 1;
        } else if(e > 0.6*maxE) {
            employmentInfoString = 2;
        } else if(e > 0.4*maxE) {
            employmentInfoString = 3;
        } else {
            employmentInfoString = 4;
        }
    } break;
    case eBuildingType::corinthianColumn:
    case eBuildingType::doricColumn:
    case eBuildingType::ionicColumn:
        group = 134;
        break;
    case eBuildingType::avenue:
        group = 135;
        break;
    case eBuildingType::bench:
        group = 137;
        titleString = 0;
        infoString = 1;
        break;
    case eBuildingType::flowerGarden:
        group = 137;
        titleString = 2;
        infoString = 3;
        break;
    case eBuildingType::gazebo:
        group = 137;
        titleString = 4;
        infoString = 5;
        break;
    case eBuildingType::hedgeMaze:
        group = 137;
        titleString = 6;
        infoString = 7;
        break;
    case eBuildingType::fishPond:
        group = 137;
        titleString = 8;
        infoString = 9;
        break;
    case eBuildingType::tallObelisk:
        group = 137;
        titleString = 10;
        infoString = 11;
        break;
    case eBuildingType::sundial:
        group = 137;
        titleString = 12;
        infoString = 13;
        break;
    case eBuildingType::topiary:
        group = 137;
        titleString = 14;
        infoString = 15;
        break;
    case eBuildingType::spring:
        group = 137;
        titleString = 16;
        infoString = 17;
        break;
    case eBuildingType::stoneCircle:
        group = 137;
        titleString = 18;
        infoString = 19;
        break;
    case eBuildingType::shortObelisk:
        group = 137;
        titleString = 20;
        infoString = 21;
        break;
    case eBuildingType::waterPark:
        group = 137;
        titleString = 22;
        infoString = 23;
        break;
    case eBuildingType::dolphinSculpture:
        group = 137;
        titleString = 24;
        infoString = 25;
        break;
    case eBuildingType::orrery:
        group = 137;
        titleString = 26;
        infoString = 27;
        break;
    case eBuildingType::shellGarden:
        group = 137;
        titleString = 28;
        infoString = 29;
        break;
    case eBuildingType::baths:
        group = 137;
        titleString = 30;
        infoString = 31;
        break;
    case eBuildingType::birdBath:
        group = 137;
        titleString = 32;
        infoString = 33;
        break;
    case eBuildingType::ruins:
        group = 140;
        break;
    case eBuildingType::huntingLodge: {
        const auto hl = static_cast<eHuntingLodge*>(b);
        const bool noTarget = hl->noTarget();
        group = 154;

        if(e == 0) {
            employmentInfoString = 5;
        } else if(noTarget) {
            employmentInfoString = 12;
        } else if(cursed) {
            employmentInfoString = 15;
        } else if(blessed) {
            employmentInfoString = 16;
        } else if(onFire) {
            employmentInfoString = 14;
        } else if(e == maxE) {
            employmentInfoString = 6;
        } else if(e > 6) {
            employmentInfoString = 7;
        } else if(e > 4) {
            employmentInfoString = 8;
        } else if(e > 2) {
            employmentInfoString = 9;
        } else {
            employmentInfoString = 10;
        }
    } break;
    case eBuildingType::road: {
        const auto r = static_cast<eRoad*>(b);
        if(r->isRoadblock()) group = 155;
    } break;
    case eBuildingType::urchinQuay: {
        const auto uq = static_cast<eUrchinQuay*>(b);
        const bool noTarget = uq->noTarget();
        group = 159;
        infoString = -1;

        if(noTarget) {
            employmentInfoString = 1;
        } else if(cursed) {
            employmentInfoString = 7;
        } else if(blessed) {
            employmentInfoString = 8;
        } else if(onFire) {
            employmentInfoString = 6;
        } else {
            employmentInfoString = 4;
        }
    } break;
    case eBuildingType::watchPost: {
        group = 164;
        infoString = -1;

        if(onFire) {
            employmentInfoString = 10;
        } else if(e == 0) {
            employmentInfoString = 9;
        } else if(e < 3) {
            employmentInfoString = 8;
        } else if(e == maxE) {
            employmentInfoString = 4;
        } else if(e == 3) {
            employmentInfoString = 7;
        } else if(e == 4) {
            employmentInfoString = 6;
        } else { // e == 5
            employmentInfoString = 5;
        }
    } break;
    case eBuildingType::wall:
        group = 166;
        break;
    case eBuildingType::gatehouse:
        group = 168;
        break;
    case eBuildingType::tower: {
        group = 170;
        infoString = -1;

        if(onFire) {
            employmentInfoString = 5;
        } else if(cursed) {
            employmentInfoString = 6;
        } else if(e < maxE) {
            employmentInfoString = 2;
        } else {
            employmentInfoString = 3;
        }
    } break;
    case eBuildingType::artisansGuild: {
        group = 171;
        infoString = -1;

        if(onFire) {
            employmentInfoString = 7;
        } else if(cursed) {
            employmentInfoString = 8;
        } else if(blessed) {
            employmentInfoString = 9;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e < 20) {
            employmentInfoString = 3;
        } else if(e < 15) {
            employmentInfoString = 4;
        } else if(e < 10) {
            employmentInfoString = 5;
        } else {
            employmentInfoString = 6;
        }
    } break;
    case eBuildingType::growersLodge: {
        const auto gl = static_cast<eGrowersLodge*>(b);
        const bool noTarget = gl->noTarget();
        group = 179;

        if(onFire) {
            employmentInfoString = 13;
        } else if(e == 0) {
            employmentInfoString = 3;
        } else if(noTarget) {
            employmentInfoString = 10;
        } else if(e == maxE) {
            employmentInfoString = 4;
        } else if(e > 9) {
            employmentInfoString = 5;
        } else if(e > 7) {
            employmentInfoString = 6;
        } else if(e > 5) {
            employmentInfoString = 7;
        } else {
            employmentInfoString = 8;
        }
    } break;
    case eBuildingType::orangeTendersLodge: {
        const auto gl = static_cast<eGrowersLodge*>(b);
        const bool noTarget = gl->noTarget();
        group = 179;
        titleString = 17;
        infoString = 18;

        if(onFire) {
            employmentInfoString = 29;
        } else if(e == 0) {
            employmentInfoString = 20;
        } else if(noTarget) {
            employmentInfoString = 27;
        } else if(blessed) {
            employmentInfoString = 31;
        } else if(cursed) {
            employmentInfoString = 30;
        } else if(e == maxE) {
            employmentInfoString = 21;
        } else if(e > 9) {
            employmentInfoString = 22;
        } else if(e > 7) {
            employmentInfoString = 23;
        } else if(e > 5) {
            employmentInfoString = 24;
        } else {
            employmentInfoString = 25;
        }
    } break;
    case eBuildingType::corral: {
        group = 141;

        if(onFire) {
            employmentInfoString = 8;
        } else if(e == 0) {
            employmentInfoString = 7;
        } else if(blessed) {
            employmentInfoString = 10;
        } else if(cursed) {
            employmentInfoString = 9;
        } else if(e == maxE) {
            employmentInfoString = 2;
        } else if(e > 20) {
            employmentInfoString = 3;
        } else if(e > 15) {
            employmentInfoString = 4;
        } else if(e > 10) {
            employmentInfoString = 5;
        } else {
            employmentInfoString = 6;
        }
    } break;
    case eBuildingType::achillesHall:
        group = 185;
        titleString = 8;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::herculesHall:
        group = 185;
        titleString = 9;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::jasonHall:
        group = 185;
        titleString = 10;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::odysseusHall:
        group = 185;
        titleString = 11;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::perseusHall:
        group = 185;
        titleString = 12;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::theseusHall:
        group = 185;
        titleString = 13;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::atalantaHall:
        group = 185;
        titleString = 14;
        infoString = -1;
        employmentInfoString = -1;
        break;
    case eBuildingType::bellerophonHall:
        group = 185;
        titleString = 15;
        infoString = -1;
        employmentInfoString = -1;
        break;
    }
    title = eLanguage::zeusText(group, titleString);
    info = eLanguage::zeusText(group, infoString);
    employmentInfo = eLanguage::zeusText(group, employmentInfoString);
    additionalInfo = eLanguage::zeusText(group, additionalInfoString);
}

eTile* eBuilding::tileNeighbour(const eMoveDirection o,
                                const eTileValidator& v) const {
    int dx = 0;
    int dy = 0;
    switch(o) {
    case eMoveDirection::topRight:
        dy--;
        break;
    case eMoveDirection::bottomRight:
        dx++;
        break;
    case eMoveDirection::bottomLeft:
        dy++;
        break;
    case eMoveDirection::topLeft:
        dx--;
        break;
    default:
        return nullptr;
    }
    for(const auto u : mUnderBuilding) {
        auto tt = static_cast<eTile*>(u->tileRel(dx, dy));
        if(!tt) continue;
        if(v(tt)) return tt;
    }
    return nullptr;
}

std::vector<eTile*> eBuilding::surroundingRoad(const bool diagonal) const {
    const auto& board = getBoard();
    const auto tr = tileRect();
    std::vector<eTile*> r;
    const int xMin = tr.x + (diagonal ? -1 : 0);
    const int xMax = tr.x + tr.w + (diagonal ? 1 : 0);
    for(int x = xMin; x < xMax; x++) {
        const auto t = board.tile(x, tr.y - 1);
        if(t && t->hasRoad()) r.push_back(t);
        const auto tt = board.tile(x, tr.y + tr.h);
        if(tt && tt->hasRoad()) r.push_back(tt);
    }
    for(int y = tr.y; y < tr.y + tr.h; y++) {
        const auto t = board.tile(tr.x - 1, y);
        if(t && t->hasRoad()) r.push_back(t);
        const auto tt = board.tile(tr.x + tr.w, y);
        if(tt && tt->hasRoad()) r.push_back(tt);
    }
    return r;
}

void eBuilding::incTime(const int by) {
    if(dead()) return;
    auto& b = getBoard();
    mTime += by;
    if(mBlessTime > 0) {
        mBlessTime -= by;
        if(mBlessTime <= 0) {
            mBlessed = 0;
        }
    }
    if(isOnFire()) {
        if(rand() % (10000/by) == 0) {
            if(rand() % 3) {
                const bool r = spreadFire();
                eEventData ed;
                ed.fTile = centerTile();
                if(r) b.event(eEvent::fire, ed);
            } else if(mType == eBuildingType::ruins) {
                setOnFire(false);
            } else {
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::collapse, ed);
                collapse();
                return;
            }
        }
    } else if(rand() % (2000/by) == 0) {
        bool lower = true;
        if(const auto sh = dynamic_cast<eSmallHouse*>(this)) {
            if(sh->people() <= 0) lower = false;
        } else if(const auto eh = dynamic_cast<eEliteHousing*>(this)) {
            if(eh->people() <= 0) lower = false;
        }
        if(lower) {
            mMaintance = std::max(0, mMaintance - 1);
        }
    } else {
        const int m4 = 10000 + pow(mMaintance, 4);
        const auto diff = b.difficulty();
        const int fireRisk = eDifficultyHelpers::fireRisk(diff, mType);
        if(fireRisk && by) {
            const int firePeriod = m4/(by*fireRisk);
            if(firePeriod && rand() % firePeriod == 0) {
                setOnFire(true);
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::fire, ed);
            }
        }
        const int damageRisk = eDifficultyHelpers::damageRisk(diff, mType);
        if(damageRisk && by) {
            const int damagePeriod = m4/(by*damageRisk);
            if(damagePeriod && rand() % damagePeriod == 0) {
                eEventData ed;
                ed.fTile = centerTile();
                b.event(eEvent::collapse, ed);
                collapse();
                return;
            }
        }
    }
    timeChanged(by);
}

int eBuilding::textureTime() const {
    auto& board = getBoard();
    return mFrameShift + board.frame();
}

void eBuilding::addUnderBuilding(eTile* const t) {
    mUnderBuilding.push_back(t);
}

void eBuilding::erase() {
    deleteLater();
    for(const auto t : mUnderBuilding) {
        t->setUnderBuilding(nullptr);
    }
    mUnderBuilding.clear();
}

void eBuilding::collapse() {
    const auto tiles = mUnderBuilding;
    auto& b = getBoard();
    const auto tp = type();
    const bool noRuins = tp == eBuildingType::oliveTree ||
                         tp == eBuildingType::vine ||
                         tp == eBuildingType::orangeTree;
    const bool onFire = mOnFire;
    setOnFire(false);
    erase();
    if(noRuins) return;
    for(const auto t : tiles) {
        const auto terrain = t->terrain();
        if(terrain == eTerrain::water) continue;
        const auto ruins = e::make_shared<eRuins>(b);
        ruins->setOnFire(onFire);
        ruins->setCenterTile(t);
        t->setUnderBuilding(ruins);
        ruins->addUnderBuilding(t);
        ruins->setTileRect({t->x(), t->y(), 1, 1});
    }
}

bool eBuilding::spreadFire() {
    auto dirs = gExtractDirections(eMoveDirection::allDirections);
    std::random_shuffle(dirs.begin(), dirs.end());
    eTile* t = nullptr;
    for(const auto dir : dirs) {
        t = tileNeighbour(dir, [this](eTile* const tile) {
            const auto ub = tile->underBuilding();
            if(!ub) return false;
            if(ub == this) return false;
            const auto t = ub->type();
            if(!sFlammable(t)) return false;
            return true;
        });
        if(t) break;
    }
    if(t) {
        const auto ub = t->underBuilding();
        if(ub) {
            ub->setOnFire(true);
            return true;
        }
    }
    return false;
}

bool eBuilding::isOnFire() {
    return mOnFire;
}

void eBuilding::setOnFire(const bool f) {
    mOnFire = f;
}

void eBuilding::setCenterTile(eTile* const ct) {
    mCenterTile = ct;
}

eTile* eBuilding::centerTile() const {
    return mCenterTile;
}

void eBuilding::setEnabled(const bool e) {
    mEnabled = e;
}

void eBuilding::setOverlayEnabledFunc(const std::function<bool()>& e) {
    mOverlayEnabled = e;
}

bool eBuilding::defend(const double a) {
    if(mHp <= 0) return true;
    mHp -= a;
    if(mHp <= 0) {
        collapse();
        return true;
    } else {
        return false;
    }
}

bool eBuilding::dead() const {
    return mHp <= 0;
}

std::vector<eTile*> eBuilding::neighbours() const {
    std::vector<eTile*> result;

    const int left = mTileRect.x - 1;
    const int right = mTileRect.x + mTileRect.w + 1;
    const int top = mTileRect.y - 1;
    const int bottom = mTileRect.y + mTileRect.h + 1;

    const auto& brd = getBoard();

    int i;
    int j;

    const auto iiter = [&]() {
        for(i = left + 1; i <= right - 1; i++) {
            const auto t = brd.tile(i, j);
            if(!t) continue;
            result.push_back(t);
        }
    };

    const auto jiter = [&]() {
        for(j = top + 1; j <= bottom - 1; j++) {
            const auto t = brd.tile(i, j);
            if(!t) continue;
            result.push_back(t);
        }
    };

    j = top;
    iiter();
    j = bottom;
    iiter();

    i = left;
    jiter();
    i = right;
    jiter();

    return result;
}

void eBuilding::setBlessed(const double b) {
    mBlessTime = 30000;
    mBlessed = b;
}

void eBuilding::read(eReadStream& src) {
    src >> mIOID;
    src >> mTileRect;

    auto& board = getBoard();

    int ntiles;
    src >> ntiles;
    for(int i = 0; i < ntiles; i++) {
        const auto tile = src.readTile(board);
        mUnderBuilding.push_back(tile);
        bool setUnder;
        src >> setUnder;
        if(setUnder) {
            tile->setUnderBuilding(ref<eBuilding>());
        }
    }

    mCenterTile = src.readTile(board);

    src >> mSeed;
    src >> mPlayerId;
    src >> mHp;
    src >> mMaintance;
    src >> mEnabled;
    src >> mBlessed;
    src >> mBlessTime;
    src >> mOnFire;
}

void eBuilding::write(eWriteStream& dst) const {
    dst << mIOID;
    dst << mTileRect;

    dst << mUnderBuilding.size();
    for(const auto t : mUnderBuilding) {
        dst.writeTile(t);
        dst << (t->underBuilding() == this);
    }

    dst.writeTile(mCenterTile);

    dst << mSeed;
    dst << mPlayerId;
    dst << mHp;
    dst << mMaintance;
    dst << mEnabled;
    dst << mBlessed;
    dst << mBlessTime;
    dst << mOnFire;
}

void eBuilding::setIOID(const int id) {
    mIOID = id;
}
