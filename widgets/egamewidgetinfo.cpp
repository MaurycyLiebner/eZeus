#include "egamewidget.h"

#include "buildings/allbuildings.h"

#include "infowidgets/ecommonhouseinfowidget.h"
#include "infowidgets/etradepostinfowidget.h"
#include "infowidgets/estorageinfowidget.h"
#include "infowidgets/eagorainfowidget.h"
#include "infowidgets/eheroshallinfowidget.h"
#include "infowidgets/esanctuaryinfowidget.h".h"

#include "elanguage.h"

std::string titleForBuilding(eBuilding* const b) {
    const auto name = eBuilding::sNameForBuilding(b);
    return eLanguage::text(name);
}

std::string employmentInfoText(const int nem, eEmployingBuilding* const b) {
    if(nem == 0) return "";
    const auto name = eBuilding::sNameForBuilding(b);
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
        } else if(const auto s = dynamic_cast<eSanctuary*>(b)) {
            const auto sWid = new eSanctuaryInfoWidget(window());
            sWid->initialize(s);
            wid = sWid;
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
