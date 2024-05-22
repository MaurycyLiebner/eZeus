#include "egamewidget.h"

#include "buildings/allbuildings.h"

#include "infowidgets/ecommonhouseinfowidget.h"
#include "infowidgets/etradepostinfowidget.h"
#include "infowidgets/estorageinfowidget.h"
#include "infowidgets/eagorainfowidget.h"
#include "infowidgets/eheroshallinfowidget.h"
#include "infowidgets/esanctuaryinfowidget.h"

#include "engine/egameboard.h"

#include "elanguage.h"

void sInfoText(eBuilding* const b,
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

eInfoWidget* eGameWidget::openInfoWidget(eBuilding* const b) {
    eInfoWidget* wid = nullptr;
    eAction closeAct;
    if(const auto house = dynamic_cast<eHouseBase*>(b)) {
        const auto w = new eCommonHouseInfoWidget(window());
        w->initialize(house);
        wid = w;
    } else if(const auto stor = dynamic_cast<eTradePost*>(b)) {
        const auto storWid = new eTradePostInfoWidget(window());
        storWid->initialize(stor);
        wid = storWid;
        const stdptr<eTradePost> storptr(stor);
        closeAct = [storptr, storWid]() {
            if(storptr) {
                std::map<eResourceType, int> maxCount;
                eResourceType imports;
                eResourceType exports;
                storWid->get(imports, exports, maxCount);
                storptr->setOrders(imports, exports);
                storptr->setMaxCount(maxCount);
            }
        };
    } else if(const auto stor = dynamic_cast<eStorageBuilding*>(b)) {
        const auto storWid = new eStorageInfoWidget(window());
        storWid->initialize(stor);
        wid = storWid;
        const stdptr<eStorageBuilding> storptr(stor);
        closeAct = [storptr, storWid]() {
            if(!storptr) return;
            std::map<eResourceType, int> maxCount;
            eResourceType get;
            eResourceType empty;
            eResourceType accept;
            eResourceType dontaccept;
            storWid->get(get, empty, accept, dontaccept, maxCount);
            storptr->setOrders(get, empty, accept);
            storptr->setMaxCount(maxCount);
        };
    } else if(const auto hh = dynamic_cast<eHerosHall*>(b)) {
        const auto hhWid = new eHerosHallInfoWidget(window(), false, false);
        hhWid->initialize(hh);
        wid = hhWid;
    } else {
        eAgoraBase* a = nullptr;
        if(const auto aa = dynamic_cast<eAgoraBase*>(b)) {
            a = aa;
        } else if(const auto v = dynamic_cast<eVendor*>(b)) {
            a = v->agora();
        } else if(const auto v = dynamic_cast<eAgoraSpace*>(b)) {
            a = v->agora();
        } else if(const auto v = dynamic_cast<eRoad*>(b)) {
            a = v->underAgora();
        }
        if(a) {
            const auto aWid = new eAgoraInfoWidget(window());
            aWid->initialize(a);
            wid = aWid;
        } else if(const auto s = dynamic_cast<eSanctuary*>(b)) {
            const auto sWid = new eSanctuaryInfoWidget(window());
            sWid->initialize(s);
            wid = sWid;
        } else if(const auto sb = dynamic_cast<eSanctBuilding*>(b)) {
            return openInfoWidget(sb->sanctuary());
        } else if(const auto eb = dynamic_cast<eEmployingBuilding*>(b)) {
            const auto ebWid = new eEmployingBuildingInfoWidget(
                                    window(), true, true);
            std::string title;
            std::string info;
            std::string employmentInfo;
            std::string additionalInfo;
            sInfoText(eb, title, info, employmentInfo, additionalInfo);
            ebWid->initialize(title, info, employmentInfo, eb, "");
            wid = ebWid;
        } else {
            const auto bWid = new eInfoWidget(window(), true, true);
            const auto title = eBuilding::sNameForBuilding(b);
            bWid->initialize(title);
            wid = bWid;
        }
    }
    if(wid) {
        addWidget(wid);
        wid->setX((width() - mGm->width() - wid->width())/2);
        wid->align(eAlignment::vcenter);
        wid->setCloseAction([this, wid, closeAct]() {
            if(closeAct) closeAct();
            mInfoWidget = nullptr;
            removeWidget(wid);
            wid->deleteLater();
        });
    }
    return wid;
}
