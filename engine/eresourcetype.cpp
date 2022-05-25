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
    case eResourceType::urchin: key = "urchin";
    case eResourceType::fish: key = "fish";
    case eResourceType::meat: key = "meat";
    case eResourceType::cheese: key = "cheese";
    case eResourceType::carrots: key = "carrots";
    case eResourceType::onions: key = "onions";
    case eResourceType::wheat: key = "wheat";
    case eResourceType::oranges: key = "oranges";
    case eResourceType::food: key = "food";
    case eResourceType::grapes: key = "grapes";
    case eResourceType::olives: key = "olives";
    case eResourceType::wine: key = "wine";
    case eResourceType::oliveOil: key = "olive_oil";
    case eResourceType::fleece: key = "fleece";
    case eResourceType::wood: key = "wood";
    case eResourceType::bronze: key = "bronze";
    case eResourceType::marble: key = "marble";
    case eResourceType::silver: key = "silver";
    case eResourceType::armor: key = "armor";
    case eResourceType::sculpture: key = "sculpture";
    case eResourceType::horse: key = "horse";
    default: key = "invalid";
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
