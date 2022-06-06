#include "eresourcetype.h"

#include "textures/egametextures.h"

#include "elanguage.h"

bool extractResourceType(const eResourceType from,
                         const eResourceType t,
                         std::vector<eResourceType>& result) {
    if(static_cast<bool>(from & t)) {
        result.push_back(t);
        return true;
    }
    return false;
}

std::vector<eResourceType> eResourceTypeHelpers::extractResourceTypes(const eResourceType from) {
    std::vector<eResourceType> result;
    extractResourceType(from, eResourceType::silver, result);
    extractResourceType(from, eResourceType::urchin, result);
    extractResourceType(from, eResourceType::fish, result);
    extractResourceType(from, eResourceType::meat, result);
    extractResourceType(from, eResourceType::cheese, result);
    extractResourceType(from, eResourceType::carrots, result);
    extractResourceType(from, eResourceType::onions, result);
    extractResourceType(from, eResourceType::wheat, result);
    extractResourceType(from, eResourceType::oranges, result);

    extractResourceType(from, eResourceType::grapes, result);
    extractResourceType(from, eResourceType::olives, result);
    extractResourceType(from, eResourceType::wine, result);
    extractResourceType(from, eResourceType::oliveOil, result);
    extractResourceType(from, eResourceType::fleece, result);

    extractResourceType(from, eResourceType::wood, result);
    extractResourceType(from, eResourceType::bronze, result);
    extractResourceType(from, eResourceType::marble, result);
    extractResourceType(from, eResourceType::armor, result);
    extractResourceType(from, eResourceType::sculpture, result);
    extractResourceType(from, eResourceType::horse, result);
    return result;
}

std::string eResourceTypeHelpers::typeName(const eResourceType type) {
    std::string key;
    switch(type) {
    case eResourceType::urchin:
        key = "urchin";
        break;
    case eResourceType::fish:
        key = "fish";
        break;
    case eResourceType::meat:
        key = "meat";
        break;
    case eResourceType::cheese:
        key = "cheese";
        break;
    case eResourceType::carrots:
        key = "carrots";
        break;
    case eResourceType::onions:
        key = "onions";
        break;
    case eResourceType::wheat:
        key = "wheat";
        break;
    case eResourceType::oranges:
        key = "oranges";
        break;
    case eResourceType::food:
        key = "food";
        break;
    case eResourceType::grapes:
        key = "grapes";
        break;
    case eResourceType::olives:
        key = "olives";
        break;
    case eResourceType::wine:
        key = "wine";
        break;
    case eResourceType::oliveOil:
        key = "olive_oil";
        break;
    case eResourceType::fleece:
        key = "fleece";
        break;
    case eResourceType::wood:
        key = "wood";
        break;
    case eResourceType::bronze:
        key = "bronze";
        break;
    case eResourceType::marble:
        key = "marble";
        break;
    case eResourceType::silver:
        key = "silver";
        break;
    case eResourceType::armor:
        key = "armor";
        break;
    case eResourceType::sculpture:
        key = "sculpture";
        break;
    case eResourceType::horse:
        key = "horse";
        break;
    default:
        key = "invalid";
        break;
    }
    return eLanguage::text(key);
}

std::shared_ptr<eTexture> eResourceTypeHelpers::icon(
        const eUIScale scale, const eResourceType type) {
    int icoll;
    switch(scale) {
    case eUIScale::tiny:
    case eUIScale::small:
        icoll = 1;
        break;
    default:
        icoll = 2;
    }

    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[icoll];
    switch(type) {
    case eResourceType::urchin:
        return coll.fUrchinUnit;
    case eResourceType::fish:
        return coll.fFishUnit;
    case eResourceType::meat:
        return coll.fMeatUnit;
    case eResourceType::cheese:
        return coll.fCheeseUnit;
    case eResourceType::carrots:
        return coll.fCarrotsUnit;
    case eResourceType::onions:
        return coll.fOnionsUnit;
    case eResourceType::wheat:
        return coll.fWheatUnit;
    case eResourceType::oranges:
        return coll.fOrangesUnit;

    case eResourceType::wood:
        return coll.fWoodUnit;
    case eResourceType::bronze:
        return coll.fBronzeUnit;
    case eResourceType::marble:
        return coll.fMarbleUnit;
    case eResourceType::grapes:
        return coll.fGrapesUnit;
    case eResourceType::olives:
        return coll.fOlivesUnit;
    case eResourceType::fleece:
        return coll.fFleeceUnit;
    case eResourceType::horse:
        return coll.fHorseUnit;
    case eResourceType::armor:
        return coll.fArmsUnit;
    case eResourceType::sculpture:
        return coll.fSculptureUnit;
    case eResourceType::oliveOil:
        return coll.fOliveOilUnit;
    case eResourceType::wine:
        return coll.fWineUnit;
    case eResourceType::food:
        return coll.fFoodUnit;
    default:
        return nullptr;
    }
}

int eResourceTypeHelpers::transportSize(const eResourceType type) {
    switch(type) {
    case eResourceType::urchin:
    case eResourceType::fish:
    case eResourceType::meat:
    case eResourceType::cheese:
    case eResourceType::carrots:
    case eResourceType::onions:
    case eResourceType::wheat:
    case eResourceType::oranges:

    case eResourceType::food:

    case eResourceType::grapes:
    case eResourceType::olives:
    case eResourceType::wine:
    case eResourceType::oliveOil:
    case eResourceType::fleece:

    case eResourceType::wood:
    case eResourceType::bronze:
    case eResourceType::marble:

    case eResourceType::armor:
        return 4;
    case eResourceType::sculpture:
        return 1;
    default: break;
    }
    return 0;
}
