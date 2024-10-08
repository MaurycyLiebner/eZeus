#include "ebuildingreader.h"

#include "buildings/allbuildings.h"
#include "engine/egameboard.h"

template <typename T>
stdsptr<eBuilding> createVendor(eGameBoard& board,
                                eReadStream& src) {
    const auto v = e::make_shared<T>(board);
    int aid;
    src >> aid;
    int sid;
    src >> sid;
    src.addPostFunc([aid, sid, v]() {
        const auto& board = v->getBoard();
        const auto a = board.buildingWithIOID(aid);
        const auto aa = a->template ref<eAgoraBase>();
        v->setAgora(aa);
        aa->setBuilding(sid, v);
    });
    return v;
}

stdsptr<eBuilding> eBuildingReader::sRead(
        eGameBoard& board, const eBuildingType type,
        eReadStream& src) {
    const auto wrld = board.getWorldBoard();
    stdsptr<eBuilding> b;
    switch(type) {
    case eBuildingType::road: {
        const auto r = e::make_shared<eRoad>(board);
        b = r;
        bool roadblock;
        src >> roadblock;
        r->setRoadblock(roadblock);
        src.readBuilding(&board, [r](eBuilding* const bb) {
            r->setUnderAgora(static_cast<eAgoraBase*>(bb));
        });
        src.readBuilding(&board, [r](eBuilding* const bb) {
            r->setUnderGatehouse(static_cast<eGatehouse*>(bb));
        });
    } break;
    case eBuildingType::commonAgora: {
        eAgoraOrientation o;
        src >> o;
        b = e::make_shared<eCommonAgora>(o, board);
    } break;
    case eBuildingType::grandAgora: {
        eAgoraOrientation o;
        src >> o;
        b = e::make_shared<eGrandAgora>(o, board);
    } break;
    case eBuildingType::agoraSpace:
        return nullptr;
    case eBuildingType::commonHouse: {
        b = e::make_shared<eSmallHouse>(board);
    } break;
    case eBuildingType::gymnasium: {
        b = e::make_shared<eGymnasium>(board);
    } break;
    case eBuildingType::podium: {
        b = e::make_shared<ePodium>(board);
    } break;
    case eBuildingType::fountain: {
        b = e::make_shared<eFountain>(board);
    } break;
    case eBuildingType::watchPost: {
        b = e::make_shared<eWatchpost>(board);
    } break;
    case eBuildingType::maintenanceOffice: {
        b = e::make_shared<eMaintenanceOffice>(board);
    } break;
    case eBuildingType::college: {
        b = e::make_shared<eCollege>(board);
    } break;
    case eBuildingType::dramaSchool: {
        b = e::make_shared<eDramaSchool>(board);
    } break;
    case eBuildingType::theater: {
        b = e::make_shared<eTheater>(board);
    } break;
    case eBuildingType::hospital: {
        b = e::make_shared<eHospital>(board);
    } break;
    case eBuildingType::stadium: {
        bool rotated;
        src >> rotated;
        b = e::make_shared<eStadium>(board, rotated);
    } break;
    case eBuildingType::bibliotheke: {
        b = e::make_shared<eBibliotheke>(board);
    } break;
    case eBuildingType::observatory: {
        b = e::make_shared<eObservatory>(board);
    } break;
    case eBuildingType::university: {
        b = e::make_shared<eUniversity>(board);
    } break;
    case eBuildingType::laboratory: {
        b = e::make_shared<eLaboratory>(board);
    } break;
    case eBuildingType::inventorsWorkshop: {
        b = e::make_shared<eInventorsWorkshop>(board);
    } break;
    case eBuildingType::museum: {
        b = e::make_shared<eMuseum>(board);
    } break;
    case eBuildingType::palace: {
        bool rotated;
        src >> rotated;
        b = e::make_shared<ePalace>(board, rotated);
    } break;
    case eBuildingType::palaceTile: {
        bool other;
        src >> other;
        const auto pt = e::make_shared<ePalaceTile>(board, other);
        b = pt;
        src.readBuilding(&board, [pt](eBuilding* const bb) {
             pt->setPalace(static_cast<ePalace*>(bb));
        });
    } break;
    case eBuildingType::eliteHousing: {
        b = e::make_shared<eEliteHousing>(board);
    } break;
    case eBuildingType::taxOffice: {
        b = e::make_shared<eTaxOffice>(board);
    } break;
    case eBuildingType::mint: {
        b = e::make_shared<eMint>(board);
    } break;
    case eBuildingType::foundry: {
        b = e::make_shared<eFoundry>(board);
    } break;
    case eBuildingType::timberMill: {
        b = e::make_shared<eTimberMill>(board);
    } break;
    case eBuildingType::masonryShop: {
        b = e::make_shared<eMasonryShop>(board);
    } break;

    case eBuildingType::oliveTree: {
        b = e::make_shared<eResourceBuilding>(
                board, eResourceBuildingType::oliveTree);
    } break;
    case eBuildingType::vine: {
        b = e::make_shared<eResourceBuilding>(
                board, eResourceBuildingType::vine);
    } break;
    case eBuildingType::orangeTree: {
        b = e::make_shared<eResourceBuilding>(
                board, eResourceBuildingType::orangeTree);
    } break;

    case eBuildingType::huntingLodge: {
        b = e::make_shared<eHuntingLodge>(board);
    } break;
    case eBuildingType::corral: {
        b = e::make_shared<eCorral>(board);
    } break;

    case eBuildingType::urchinQuay: {
        eOrientation o;
        src >> o;
        b = e::make_shared<eUrchinQuay>(board, o);
    } break;
    case eBuildingType::fishery: {
        eOrientation o;
        src >> o;
        b = e::make_shared<eFishery>(board, o);
    } break;

    case eBuildingType::pier: {
        eOrientation o;
        src >> o;
        const auto p = e::make_shared<ePier>(board, o);
        b = p;
        src.readBuilding(&board, [p](eBuilding* const bb) {
             p->setTradePost(bb);
        });
    } break;

    case eBuildingType::tradePost: {
        eTradePostType tpt;
        src >> tpt;
        eOrientation o;
        src >> o;

        int ctid;
        src >> ctid;
        const auto& cts = wrld->cities();
        const auto ct = cts[ctid];

        const auto tp = e::make_shared<eTradePost>(board, *ct, tpt);
        b = tp;
        tp->setOrientation(o);

        if(tpt == eTradePostType::pier) {
            src.readBuilding(&board, [tp](eBuilding* const bb) {
                 tp->setUnpackBuilding(bb);
            });
        }
    } break;

    case eBuildingType::dairy: {
        b = e::make_shared<eDairy>(board);
    } break;
    case eBuildingType::cardingShed: {
        b = e::make_shared<eCardingShed>(board);
    } break;
    case eBuildingType::sheep: {
        b = e::make_shared<eAnimalBuilding>(
                board, nullptr, eBuildingType::sheep);
    } break;
    case eBuildingType::goat: {
        b = e::make_shared<eAnimalBuilding>(
                board, nullptr, eBuildingType::goat);
    } break;
    case eBuildingType::cattle: {
        b = e::make_shared<eAnimalBuilding>(
                board, nullptr, eBuildingType::cattle);
    } break;
    case eBuildingType::wheatFarm: {
        b = e::make_shared<eWheatFarm>(board);
    } break;
    case eBuildingType::onionsFarm: {
        b = e::make_shared<eOnionFarm>(board);
    } break;
    case eBuildingType::carrotsFarm: {
        b = e::make_shared<eCarrotFarm>(board);
    } break;
    case eBuildingType::growersLodge: {
        b = e::make_shared<eGrowersLodge>(
                board, eGrowerType::grapesAndOlives);
    } break;
    case eBuildingType::orangeTendersLodge: {
        b = e::make_shared<eGrowersLodge>(
                board, eGrowerType::oranges);
    } break;
    case eBuildingType::granary: {
        b = e::make_shared<eGranary>(board);
    } break;
    case eBuildingType::warehouse: {
        b = e::make_shared<eWarehouse>(board);
    } break;
    case eBuildingType::wall: {
        b = e::make_shared<eWall>(board);
    } break;
    case eBuildingType::tower: {
        b = e::make_shared<eTower>(board);
    } break;

    case eBuildingType::gatehouse: {
        bool rotated;
        src >> rotated;
        b = e::make_shared<eGatehouse>(board, rotated);
    } break;

    case eBuildingType::armory: {
        b = e::make_shared<eArmory>(board);
    } break;

    case eBuildingType::horseRanch: {
        const auto hr = e::make_shared<eHorseRanch>(board);
        b = hr;

        src.readBuilding(&board, [hr](eBuilding* const bb) {
             hr->setEnclosure(static_cast<eHorseRanchEnclosure*>(bb));
        });
    } break;
    case eBuildingType::horseRanchEnclosure: {
        const auto hre = e::make_shared<eHorseRanchEnclosure>(board);
        b = hre;
        src.readBuilding(&board, [hre](eBuilding* const bb) {
            hre->setRanch(static_cast<eHorseRanch*>(bb));
        });
    } break;

    case eBuildingType::olivePress: {
        b = e::make_shared<eOlivePress>(board);
    } break;
    case eBuildingType::winery: {
        b = e::make_shared<eWinery>(board);
    } break;
    case eBuildingType::sculptureStudio: {
        b = e::make_shared<eSculptureStudio>(board);
    } break;
    case eBuildingType::artisansGuild: {
        b = e::make_shared<eArtisansGuild>(board);
    } break;

    case eBuildingType::foodVendor: {
        b = createVendor<eFoodVendor>(board, src);
    } break;
    case eBuildingType::fleeceVendor: {
        b = createVendor<eFleeceVendor>(board, src);
    } break;
    case eBuildingType::oilVendor: {
        b = createVendor<eOilVendor>(board, src);
    } break;
    case eBuildingType::wineVendor: {
        b = createVendor<eWineVendor>(board, src);
    } break;
    case eBuildingType::armsVendor: {
        b = createVendor<eArmsVendor>(board, src);
    } break;
    case eBuildingType::horseTrainer: {
        b = createVendor<eHorseVendor>(board, src);
    } break;
    case eBuildingType::chariotVendor: {
        b = createVendor<eChariotVendor>(board, src);
    } break;

    case eBuildingType::chariotFactory: {
        b = e::make_shared<eChariotFactory>(board);
    } break;

    case eBuildingType::park: {
        b = e::make_shared<ePark>(board);
    } break;
    case eBuildingType::doricColumn: {
        b = e::make_shared<eDoricColumn>(board);
    } break;
    case eBuildingType::ionicColumn: {
        b = e::make_shared<eIonicColumn>(board);
    } break;
    case eBuildingType::corinthianColumn: {
        b = e::make_shared<eCorinthianColumn>(board);
    } break;
    case eBuildingType::avenue: {
        b = e::make_shared<eAvenue>(board);
    } break;

    case eBuildingType::commemorative: {
        int id;
        src >> id;
        b = e::make_shared<eCommemorative>(id, board);
    } break;

    case eBuildingType::godMonument: {
        eGodType type;
        src >> type;
        eGodQuestId id;
        src >> id;
        b = e::make_shared<eGodMonument>(type, id, board);
    } break;
    case eBuildingType::godMonumentTile: {
        const auto pt = e::make_shared<eGodMonumentTile>(board);
        b = pt;
        src.readBuilding(&board, [pt](eBuilding* const bb) {
             pt->setMonument(static_cast<eGodMonument*>(bb));
        });
    } break;

    case eBuildingType::bench: {
        b = e::make_shared<eBench>(board);
    } break;
    case eBuildingType::flowerGarden: {
        b = e::make_shared<eFlowerGarden>(board);
    } break;
    case eBuildingType::gazebo: {
        b = e::make_shared<eGazebo>(board);
    } break;
    case eBuildingType::hedgeMaze: {
        b = e::make_shared<eHedgeMaze>(board);
    } break;
    case eBuildingType::fishPond: {
        b = e::make_shared<eFishPond>(board);
    } break;

    case eBuildingType::waterPark: {
        int id;
        src >> id;
        const auto wp = e::make_shared<eWaterPark>(board);
        b = wp;
        wp->setId(id);
    } break;

    case eBuildingType::birdBath: {
        b = e::make_shared<eBirdBath>(board);
    } break;
    case eBuildingType::shortObelisk: {
        b = e::make_shared<eShortObelisk>(board);
    } break;
    case eBuildingType::tallObelisk: {
        b = e::make_shared<eTallObelisk>(board);
    } break;
    case eBuildingType::shellGarden: {
        b = e::make_shared<eShellGarden>(board);
    } break;
    case eBuildingType::sundial: {
        b = e::make_shared<eSundial>(board);
    } break;
    case eBuildingType::dolphinSculpture: {
        b = e::make_shared<eDolphinSculpture>(board);
    } break;
    case eBuildingType::spring: {
        b = e::make_shared<eSpring>(board);
    } break;
    case eBuildingType::orrery: {
        b = e::make_shared<eOrrery>(board);
    } break;
    case eBuildingType::topiary: {
        b = e::make_shared<eTopiary>(board);
    } break;
    case eBuildingType::baths: {
        b = e::make_shared<eBaths>(board);
    } break;
    case eBuildingType::stoneCircle: {
        b = e::make_shared<eStoneCircle>(board);
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
        int sw;
        src >> sw;
        int sh;
        src >> sh;

        b = eSanctuary::sCreate(type, sw, sh, board);
    } break;
    case eBuildingType::templeStatue: {
        eGodType godType;
        src >> godType;
        int id;
        src >> id;
        const auto ts = e::make_shared<eTempleStatueBuilding>(godType, id, board);
        b = ts;
        src.readBuilding(&board, [ts](eBuilding* const bb) {
            const auto ss = static_cast<eSanctuary*>(bb);
            ts->setSanctuary(ss);
            ss->registerElement(ts);
        });
    } break;
    case eBuildingType::templeMonument: {
        eGodType godType;
        src >> godType;
        int id;
        src >> id;
        const auto ts = e::make_shared<eTempleMonumentBuilding>(godType, id, board);
        b = ts;
        src.readBuilding(&board, [ts](eBuilding* const bb) {
            const auto ss = static_cast<eSanctuary*>(bb);
            ts->setSanctuary(ss);
            ss->registerElement(ts);
        });
    } break;
    case eBuildingType::templeAltar: {
        const auto ts = e::make_shared<eTempleAltarBuilding>(board);
        b = ts;
        src.readBuilding(&board, [ts](eBuilding* const bb) {
            const auto ss = static_cast<eSanctuary*>(bb);
            ts->setSanctuary(ss);
            ss->registerElement(ts);
        });
    } break;
    case eBuildingType::temple: {
        const auto ts = e::make_shared<eTempleBuilding>(board);
        b = ts;
        src.readBuilding(&board, [ts](eBuilding* const bb) {
            const auto ss = static_cast<eSanctuary*>(bb);
            ts->setSanctuary(ss);
            ss->registerElement(ts);
        });
    } break;
    case eBuildingType::templeTile: {
        int id;
        src >> id;
        const auto ts = e::make_shared<eTempleTileBuilding>(id, board);
        b = ts;
        src.readBuilding(&board, [ts](eBuilding* const bb) {
            const auto ss = static_cast<eSanctuary*>(bb);
            ts->setSanctuary(ss);
            ss->registerElement(ts);
        });
    } break;

    case eBuildingType::achillesHall:
    case eBuildingType::atalantaHall:
    case eBuildingType::bellerophonHall:
    case eBuildingType::herculesHall:
    case eBuildingType::jasonHall:
    case eBuildingType::odysseusHall:
    case eBuildingType::perseusHall:
    case eBuildingType::theseusHall: {
        const auto hero = eHerosHall::sHallTypeToHeroType(type);
        b = e::make_shared<eHerosHall>(hero, board);
    } break;

    case eBuildingType::ruins: {
        b = e::make_shared<eRuins>(board);
    } break;
    case eBuildingType::placeholder: {
        b = e::make_shared<ePlaceholder>(board);
    } break;

    case eBuildingType::triremeWharf: {
        eOrientation o;
        src >> o;
        b = e::make_shared<eTriremeWharf>(board, o);
    } break;
    case eBuildingType::none:
    case eBuildingType::erase:
    case eBuildingType::bridge:
        return nullptr;
    }
    if(b) b->read(src);
    return b;
}
