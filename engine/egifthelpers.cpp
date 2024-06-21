#include "egifthelpers.h"

int eGiftHelpers::giftCount(const eResourceType r) {
    int count;
    switch(r) {
    case eResourceType::drachmas:
        count = 500;
        break;
    case eResourceType::urchin:
    case eResourceType::fish:
    case eResourceType::meat:
    case eResourceType::cheese:
    case eResourceType::carrots:
    case eResourceType::onions:
    case eResourceType::wheat:
    case eResourceType::oranges:
    case eResourceType::food:
        count = 8;
        break;
    case eResourceType::grapes:
    case eResourceType::olives:
    case eResourceType::wine:
    case eResourceType::oliveOil:
    case eResourceType::fleece:

    case eResourceType::wood:
    case eResourceType::bronze:
        count = 8;
        break;
    case eResourceType::marble:
    case eResourceType::armor:
        count = 4;
        break;
    case eResourceType::sculpture:
        count = 1;
        break;
    default:
        count = 0;
        break;
    };
    return count;
}
