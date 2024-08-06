#include "eresourcebutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"

void eResourceButton::initialize(const eResourceAction& ract,
                                 const eResourceType res) {
    setPressAction([this, ract, res]() {
        const auto resources = eResourceTypeHelpers::extractResourceTypes(res);

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
