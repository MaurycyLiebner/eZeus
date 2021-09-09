#include "eresourcetype.h"

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
