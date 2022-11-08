#include "egamewidget.h"

#include "buildings/allbuildings.h"

#include "infowidgets/ecommonhouseinfowidget.h"
#include "infowidgets/etradepostinfowidget.h"
#include "infowidgets/estorageinfowidget.h"
#include "infowidgets/eagorainfowidget.h"
#include "infowidgets/eheroshallinfowidget.h"

#include "elanguage.h"

std::string nameForBuilding(eBuilding* const b) {
    if(!b) return "";
    std::string t;
    switch(b->type()) {
    case eBuildingType::commonHouse:
        return "common_housing";
    case eBuildingType::eliteHousing:
        return "elite_housing";

    case eBuildingType::fountain:
        return "fountain";
    case eBuildingType::hospital:
        return "infirmary";
    case eBuildingType::maintenanceOffice:
        return "maintenance_office";
    case eBuildingType::watchPost:
        return "watchpost";

    case eBuildingType::palace:
        return "palace";
    case eBuildingType::taxOffice:
        return "tax_office";
    case eBuildingType::bridge:
        return "water_crossing";

    case eBuildingType::gymnasium:
        return "gymnasium";
    case eBuildingType::stadium:
        return "stadium";

    case eBuildingType::wheatFarm:
        return "wheat_farm";
    case eBuildingType::carrotsFarm:
        return "carrot_farm";
    case eBuildingType::onionsFarm:
        return "onion_farm";

    case eBuildingType::vine:
        return "vine";
    case eBuildingType::oliveTree:
        return "olive_tree";
    case eBuildingType::orangeTree:
        return "orange_tree";
    case eBuildingType::orangeTendersLodge:
        return "orange_tenders_lodge";
    case eBuildingType::growersLodge:
        return "growers_lodge";

    case eBuildingType::dairy:
        return "dairy";
    case eBuildingType::goat:
        return "goat";
    case eBuildingType::cardingShed:
        return "carding_shed";
    case eBuildingType::sheep:
        return "sheep";

    case eBuildingType::fishery:
        return "fishery";
    case eBuildingType::urchinQuay:
        return "urchin_quay";
    case eBuildingType::huntingLodge:
        return "hunting_lodge";

    case eBuildingType::mint:
        return "mint";
    case eBuildingType::foundry:
        return "foundry";
    case eBuildingType::timberMill:
        return "timber_mill";
    case eBuildingType::masonryShop:
        return "masonry_shop";

    case eBuildingType::winery:
        return "winery";
    case eBuildingType::olivePress:
        return "olive_press";
    case eBuildingType::sculptureStudio:
        return "sculpture_studio";

    case eBuildingType::commonAgora:
        return "common_agora";
    case eBuildingType::grandAgora:
        return "grand_agora";
    case eBuildingType::foodVendor:
        return "food_vendor";
    case eBuildingType::fleeceVendor:
        return "fleece_vendor";
    case eBuildingType::oilVendor:
        return "oil_vendor";
    case eBuildingType::wineVendor:
        return "wine_vendor";
    case eBuildingType::armsVendor:
        return "arms_vendor";
    case eBuildingType::horseTrainer:
        return "horse_trainer";

    case eBuildingType::podium:
        return "podium";
    case eBuildingType::college:
        return "college";
    case eBuildingType::theater:
        return "theater";
    case eBuildingType::dramaSchool:
        return "drama_school";

    case eBuildingType::templeHephaestus:
        return "forge_of_hephaestus";
    case eBuildingType::templeArtemis:
        return "artemis_menagerie";

    case eBuildingType::wall:
        return "wall";
    case eBuildingType::tower:
        return "tower";
    case eBuildingType::gatehouse:
        return "gatehouse";

    case eBuildingType::armory:
        return "armory";
    case eBuildingType::horseRanch:
        return "horse_ranch";

    case eBuildingType::park:
        return "park";
    case eBuildingType::waterPark:
        return "water_park";
    case eBuildingType::doricColumn:
        return "doric_column";
    case eBuildingType::ionicColumn:
        return "ionic_column";
    case eBuildingType::corinthianColumn:
        return "corinthian_column";
    case eBuildingType::avenue:
        return "avenue";

    case eBuildingType::bench:
        return "bench";
    case eBuildingType::birdBath:
        return "bird_bath";
    case eBuildingType::shortObelisk:
        return "short_obelisk";
    case eBuildingType::tallObelisk:
        return "tall_obelisk";
    case eBuildingType::flowerGarden:
        return "flower_garden";
    case eBuildingType::gazebo:
        return "gazebo";
    case eBuildingType::shellGarden:
        return "shell_garden";
    case eBuildingType::sundial:
        return "sundial";
    case eBuildingType::hedgeMaze:
        return "hedge_maze";
    case eBuildingType::dolphinSculpture:
        return "dolphin_sculpture";
    case eBuildingType::spring:
        return "spring";
    case eBuildingType::topiary:
        return "topiary";
    case eBuildingType::fishPond:
        return "fish_pond";
    case eBuildingType::baths:
        return "baths";
    case eBuildingType::stoneCircle:
        return "stone_circle";

    case eBuildingType::commemorative:
        const auto c = static_cast<eCommemorative*>(b);
        const int id = c->id();
        if(id == 0) return "population_monument";
        else if(id == 1) return "";
        else if(id == 2) return "colony_monument";
        else if(id == 3) return "athlete_monument";
        else if(id == 4) return "conquest_monument";
        else if(id == 5) return "happiness_monument";
        else if(id == 6) return "";
        else if(id == 7) return "";
        else if(id == 8) return "scholar_monument";
        break;

    }
    return "";
}

std::string titleForBuilding(eBuilding* const b) {
    const auto name = nameForBuilding(b);
    return eLanguage::text(name);
}

std::string employmentInfoText(const int nem, eEmployingBuilding* const b) {
    if(nem == 0) return "";
    const auto name = nameForBuilding(b);
    const auto prefix = name + "_info_text_empl";
    const double e = b->employedFraction();
    const double es = 1./nem;
    const int eid = std::round(e/es);
    return eLanguage::text(prefix + std::to_string(eid));
}

int numberEmplInfos(eBuilding* const b) {
    switch(b->type()) {
    case eBuildingType::gymnasium:
        return 5;
    case eBuildingType::dramaSchool:
        return 5;
    case eBuildingType::maintenanceOffice:
        return 5;
    case eBuildingType::fountain:
        return 4;
    }
    return 0;
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
            const stdptr<eAgoraBase> aptr(a);
            closeAct = [aptr, aWid]() {
                if(!aptr) return;

            };
        } else if(const auto sb = dynamic_cast<eSanctBuilding*>(b)) {
            return openInfoWidget(sb->sanctuary());
        } else if(const auto eb = dynamic_cast<eEmployingBuilding*>(b)) {
            const auto ebWid = new eEmployingBuildingInfoWidget(
                                    window(), true, true);
            const auto title = titleForBuilding(b);
            const int nei = numberEmplInfos(b);
            const auto text = employmentInfoText(nei, eb);
            ebWid->initialize(title, text, eb, "");
            wid = ebWid;
        } else {
            const auto bWid = new eInfoWidget(window(), true, true);
            const auto title = titleForBuilding(b);
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
