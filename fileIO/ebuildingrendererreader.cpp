#include "ebuildingrendererreader.h"

#include "buildings/eelitehousingrenderer.h"
#include "buildings/egatehouserenderer.h"
#include "buildings/epalacerenderer.h"
#include "buildings/estadiumrenderer.h"
#include "buildings/sanctuaries/estairsrenderer.h"

#include "buildings/eelitehousing.h"
#include "buildings/egatehouse.h"
#include "buildings/epalace.h"
#include "buildings/estadium.h"
#include "buildings/sanctuaries/etemplebuilding.h"

stdsptr<eBuildingRenderer> eBuildingRendererReader::sRead(
        const stdsptr<eBuilding>& b,
        const eBuildingRendererType type,
        eReadStream& src) {
    switch(type) {
    case eBuildingRendererType::basic:
        return e::make_shared<eBuildingRenderer>(b);
    case eBuildingRendererType::eliteHousing: {
        eEliteRendererType etype;
        src >> etype;
        const auto eb = b->ref<eEliteHousing>();
        return e::make_shared<eEliteHousingRenderer>(etype, eb);
    } break;
    case eBuildingRendererType::gatehouse: {
        eGatehouseRendererType gtype;
        src >> gtype;
        const auto gb = b->ref<eGatehouse>();
        return e::make_shared<eGatehouseRenderer>(gtype, gb);
    } break;
    case eBuildingRendererType::palace1:
        return e::make_shared<ePalace1Renderer>(b->ref<ePalace>());
    case eBuildingRendererType::palace2:
        return e::make_shared<ePalace2Renderer>(b->ref<ePalace>());
    case eBuildingRendererType::stadium1:
        return e::make_shared<eStadium1Renderer>(b->ref<eStadium>());
    case eBuildingRendererType::stadium2:
        return e::make_shared<eStadium2Renderer>(b->ref<eStadium>());
    case eBuildingRendererType::stairs: {
        int id;
        src >> id;
        return e::make_shared<eStairsRenderer>(id, b);
    } break;
    }
    return nullptr;
}
