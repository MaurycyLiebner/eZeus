#include "eresourcetype.h"

#include "textures/egametextures.h"

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

    extractResourceType(from, eResourceType::fleece, result);
    extractResourceType(from, eResourceType::olives, result);
    extractResourceType(from, eResourceType::oliveOil, result);
    extractResourceType(from, eResourceType::grapes, result);
    extractResourceType(from, eResourceType::wine, result);

    extractResourceType(from, eResourceType::wood, result);
    extractResourceType(from, eResourceType::bronze, result);
    extractResourceType(from, eResourceType::armor, result);
    extractResourceType(from, eResourceType::marble, result);
    extractResourceType(from, eResourceType::sculpture, result);
    extractResourceType(from, eResourceType::horse, result);
    return result;
}

std::string eResourceTypeHelpers::typeName(const eResourceType type) {
    switch(type) {
    case eResourceType::urchin: return "Urchin";
    case eResourceType::fish: return "Fish";
    case eResourceType::meat: return "Meat";
    case eResourceType::cheese: return "Cheese";
    case eResourceType::carrots: return "Carrots";
    case eResourceType::onions: return "Onions";
    case eResourceType::wheat: return "Wheat";
    case eResourceType::oranges: return "Oranges";
    case eResourceType::food: return "Food";
    case eResourceType::grapes: return "Grapes";
    case eResourceType::olives: return "Olives";
    case eResourceType::wine: return "Wine";
    case eResourceType::oliveOil: return "Olive Oil";
    case eResourceType::fleece: return "Fleece";
    case eResourceType::wood: return "Wood";
    case eResourceType::bronze: return "Bronze";
    case eResourceType::marble: return "Marble";
    case eResourceType::silver: return "Silver";
    case eResourceType::armor: return "Armor";
    case eResourceType::sculpture: return "Sculpture";
    case eResourceType::horse: return "Horse";
    default: return "Invalid";
    }
}

std::shared_ptr<eTexture> eResourceTypeHelpers::icon(
        const eUIScale scale, const eResourceType type) {
    int icoll;
    switch(scale) {
    case eUIScale::small:
    case eUIScale::medium:
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
