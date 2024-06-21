#include "eresourcebutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"

void eResourceButton::initialize(const eResourceAction& ract,
                                 const bool drachmas) {
    setPressAction([this, ract, drachmas]() {
        std::vector<eResourceType> resources {
            eResourceType::urchin,
            eResourceType::fish,
            eResourceType::meat,
            eResourceType::cheese,
            eResourceType::carrots,
            eResourceType::onions,
            eResourceType::wheat,
            eResourceType::oranges,

            eResourceType::grapes,
            eResourceType::olives,
            eResourceType::wine,
            eResourceType::oliveOil,
            eResourceType::fleece,

            eResourceType::wood,
            eResourceType::bronze,
            eResourceType::marble,

            eResourceType::armor,
            eResourceType::sculpture
        };
        if(drachmas) {
            resources.push_back(eResourceType::drachmas);
        }
        std::vector<std::string> resourceNames;
        for(const auto res : resources) {
            const auto str = eResourceTypeHelpers::typeName(res);
            resourceNames.push_back(str);
        }
        const auto choose = new eChooseButton(window());
        const auto act = [this, resources, ract](const int val) {
            const auto r = resources[val];
            setResource(r);
            if(ract) ract(r);
        };
        choose->initialize(8, resourceNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setResource(eResourceType::none);
    setUnderline(false);
}

void eResourceButton::setResource(const eResourceType res) {
    mRes = res;
    const auto str = eResourceTypeHelpers::typeName(res);
    setText(str);
    fitContent();
}
