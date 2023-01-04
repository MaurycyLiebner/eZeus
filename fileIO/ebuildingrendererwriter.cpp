#include "ebuildingrendererwriter.h"

#include "buildings/eelitehousingrenderer.h"
#include "buildings/egatehouserenderer.h"
#include "buildings/sanctuaries/estairsrenderer.h"

void eBuildingRendererWriter::sWrite(const eBuildingRenderer* const b,
                                     eWriteStream& dst) {
    const auto type = b->type();
    switch(type) {
    case eBuildingRendererType::basic:
        break;
    case eBuildingRendererType::eliteHousing: {
        const auto e = static_cast<const eEliteHousingRenderer*>(b);
        dst << e->etype();
    } break;
    case eBuildingRendererType::gatehouse: {
        const auto g = static_cast<const eGatehouseRenderer*>(b);
        dst << g->gtype();
    } break;
    case eBuildingRendererType::palace1:
    case eBuildingRendererType::palace2:
        break;
    case eBuildingRendererType::stadium1:
    case eBuildingRendererType::stadium2:
        break;
    case eBuildingRendererType::stairs: {
        const auto s = static_cast<const eStairsRenderer*>(b);
        dst << s->id();
    } break;
    }
}
