#include "ebuildingwriter.h"

#include "buildings/allbuildings.h"
#include "engine/egameboard.h"

void eBuildingWriter::sWrite(const eBuilding* const b,
                             eWriteStream& dst) {
    auto& board = b->getBoard();
    const auto& wrld = board.getWorldBoard();
    const auto type = b->type();
    switch(type) {
    case eBuildingType::road: {
        const auto r = static_cast<const eRoad*>(b);
        const auto a = r->underAgora();
        dst.writeBuilding(a);
    } break;
    case eBuildingType::commonAgora: {
        const auto ca = static_cast<const eCommonAgora*>(b);
        dst << ca->orientation();
    } break;
    case eBuildingType::grandAgora: {
        const auto ga = static_cast<const eGrandAgora*>(b);
        dst << ga->orientation();
    } break;
    case eBuildingType::commonHouse:
    case eBuildingType::gymnasium:
    case eBuildingType::podium:
    case eBuildingType::fountain:
    case eBuildingType::watchPost:
    case eBuildingType::maintenanceOffice:
    case eBuildingType::college:
    case eBuildingType::dramaSchool:
    case eBuildingType::theater:
    case eBuildingType::hospital:
        break;
    case eBuildingType::stadium: {
        const auto s = static_cast<const eStadium*>(b);
        dst << s->rotated();
    } break;
    case eBuildingType::palace: {
        const auto p = static_cast<const ePalace*>(b);
        dst << p->rotated();
    } break;
    case eBuildingType::palaceTile: {
        const auto p = static_cast<const ePalaceTile*>(b);
        dst << p->other();
        dst.writeBuilding(p->palace());
    } break;
    case eBuildingType::eliteHousing:
    case eBuildingType::taxOffice:
    case eBuildingType::mint:
    case eBuildingType::foundry:
    case eBuildingType::timberMill:
    case eBuildingType::masonryShop:
    case eBuildingType::oliveTree:
    case eBuildingType::vine:
    case eBuildingType::orangeTree:
    case eBuildingType::huntingLodge:
        break;
    case eBuildingType::fishery: {
        const auto p = static_cast<const eFishery*>(b);
        dst << p->orientation();
    } break;
    case eBuildingType::pier: {
        const auto p = static_cast<const ePier*>(b);
        dst << p->orientation();
        const auto tp = p->tradePost();
        dst.writeBuilding(tp);
    } break;
    case eBuildingType::tradePost: {
        const auto tp = static_cast<const eTradePost*>(b);
        const auto tpt = tp->tpType();
        dst << tpt;
        dst << tp->orientation();
        dst << wrld.cityId(tp->city());

        if(tpt == eTradePostType::pier) {
            const auto ub = tp->unpackBuilding();
            dst.writeBuilding(ub);
        }
    } break;
    case eBuildingType::dairy:
    case eBuildingType::cardingShed:
    case eBuildingType::sheep:
    case eBuildingType::goat:
    case eBuildingType::wheatFarm:
    case eBuildingType::onionsFarm:
    case eBuildingType::carrotsFarm:
    case eBuildingType::growersLodge:
    case eBuildingType::orangeTendersLodge:
    case eBuildingType::granary:
    case eBuildingType::warehouse:
    case eBuildingType::wall:
    case eBuildingType::tower:
        break;
    case eBuildingType::gatehouse: {
        const auto p = static_cast<const eGatehouse*>(b);
        dst << p->rotated();
    } break;
    case eBuildingType::armory:
        break;

    case eBuildingType::horseRanch: {
        const auto hr = static_cast<const eHorseRanch*>(b);
        const auto hre = hr->enclosure();
        dst.writeBuilding(hre);
    } break;
    case eBuildingType::horseRanchEnclosure: {
        const auto hre = static_cast<const eHorseRanchEnclosure*>(b);
        const auto hr = hre->ranch();
        dst.writeBuilding(hr);
    } break;

    case eBuildingType::olivePress:
    case eBuildingType::winery:
    case eBuildingType::sculptureStudio:
    case eBuildingType::artisansGuild:
        break;

    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::horseTrainer: {
        const auto v = static_cast<const eVendor*>(b);
        const auto a = v->agora();
        dst.writeBuilding(a);
        const int sid = v->agoraSpaceId();
        dst << sid;
    } break;

    case eBuildingType::park:
    case eBuildingType::doricColumn:
    case eBuildingType::ionicColumn:
    case eBuildingType::corinthianColumn:
    case eBuildingType::avenue:
        break;

    case eBuildingType::commemorative: {
        const auto p = static_cast<const eCommemorative*>(b);
        dst << p->id();
    } break;

    case eBuildingType::bench:
    case eBuildingType::flowerGarden:
    case eBuildingType::gazebo:
    case eBuildingType::hedgeMaze:
    case eBuildingType::fishPond:
        break;

    case eBuildingType::waterPark: {
        const auto p = static_cast<const eWaterPark*>(b);
        dst << p->id();
    } break;

    case eBuildingType::birdBath:
    case eBuildingType::shortObelisk:
    case eBuildingType::tallObelisk:
    case eBuildingType::shellGarden:
    case eBuildingType::sundial:
    case eBuildingType::dolphinSculpture:
    case eBuildingType::spring:
    case eBuildingType::topiary:
    case eBuildingType::baths:
    case eBuildingType::stoneCircle:
        break;

    case eBuildingType::templeArtemis:
    case eBuildingType::templeHephaestus: {
        const auto s = static_cast<const eSanctuary*>(b);
        dst << s->spanW();
        dst << s->spanH();
    } break;
    case eBuildingType::templeStatue: {
        const auto s = static_cast<const eTempleStatueBuilding*>(b);
        dst << s->godType();
        dst << s->id();
        const auto sanct = s->sanctuary();
        dst << sanct->ioID();
    } break;
    case eBuildingType::templeMonument: {
        const auto s = static_cast<const eTempleMonumentBuilding*>(b);
        dst << s->godType();
        dst << s->id();
        const auto sanct = s->sanctuary();
        dst.writeBuilding(sanct);
    } break;
    case eBuildingType::templeAltar: {
        const auto s = static_cast<const eTempleAltarBuilding*>(b);
        const auto sanct = s->sanctuary();
        dst.writeBuilding(sanct);
    } break;
    case eBuildingType::temple: {
        const auto s = static_cast<const eTempleBuilding*>(b);
        const auto sanct = s->sanctuary();
        dst.writeBuilding(sanct);
    } break;
    case eBuildingType::templeTile: {
        const auto s = static_cast<const eTempleTileBuilding*>(b);
        dst << s->id();
        const auto sanct = s->sanctuary();
        dst.writeBuilding(sanct);
    } break;

    case eBuildingType::ruins:
        break;
    default:
        return;
    }
    b->write(dst);
}
