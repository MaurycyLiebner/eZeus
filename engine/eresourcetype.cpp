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
    extractResourceType(from, eResourceType::chariot, result);
    return result;
}

std::string eResourceTypeHelpers::typeName(const eResourceType type) {
    int group = 23;
    int string = -1;
    switch(type) {
    case eResourceType::urchin:
        string = 1;
        break;
    case eResourceType::fish:
        string = 2;
        break;
    case eResourceType::meat:
        string = 3;
        break;
    case eResourceType::cheese:
        string = 4;
        break;
    case eResourceType::carrots:
        string = 5;
        break;
    case eResourceType::onions:
        string = 6;
        break;
    case eResourceType::wheat:
        string = 7;
        break;
    case eResourceType::oranges:
        string = 8;
        break;
    case eResourceType::food:
        string = 25;
        break;
    case eResourceType::grapes:
        string = 12;
        break;
    case eResourceType::olives:
        string = 13;
        break;
    case eResourceType::wine:
        string = 21;
        break;
    case eResourceType::oliveOil:
        string = 20;
        break;
    case eResourceType::fleece:
        string = 14;
        break;
    case eResourceType::wood:
        string = 9;
        break;
    case eResourceType::bronze:
        string = 10;
        break;
    case eResourceType::marble:
        string = 11;
        break;
    case eResourceType::silver:
        group = 50;
        string = 55;
        break;
    case eResourceType::drachmas:
        string = 23;
        break;
    case eResourceType::armor:
        string = 18;
        break;
    case eResourceType::sculpture:
        string = 19;
        break;
    case eResourceType::horse:
        string = 15;
        break;
    case eResourceType::chariot:
        string = 22;
        break;
    default:
        break;
    }
    return eLanguage::zeusText(group, string);
}

std::string eResourceTypeHelpers::typeLongName(const eResourceType type) {
    int group = 98;
    int string = -1;
    switch(type) {
    case eResourceType::urchin:
        string = 1;
        break;
    case eResourceType::fish:
        string = 2;
        break;
    case eResourceType::meat:
        string = 3;
        break;
    case eResourceType::cheese:
        string = 4;
        break;
    case eResourceType::carrots:
        string = 5;
        break;
    case eResourceType::onions:
        string = 6;
        break;
    case eResourceType::wheat:
        string = 7;
        break;
    case eResourceType::oranges:
        string = 8;
        break;
    case eResourceType::food:
        string = 25;
        break;
    case eResourceType::grapes:
        string = 12;
        break;
    case eResourceType::olives:
        string = 13;
        break;
    case eResourceType::wine:
        string = 21;
        break;
    case eResourceType::oliveOil:
        string = 20;
        break;
    case eResourceType::fleece:
        string = 14;
        break;
    case eResourceType::wood:
        string = 9;
        break;
    case eResourceType::bronze:
        string = 10;
        break;
    case eResourceType::marble:
        string = 11;
        break;
    case eResourceType::silver:
        group = 50;
        string = 55;
        break;
    case eResourceType::drachmas:
        string = 23;
        break;
    case eResourceType::armor:
        string = 18;
        break;
    case eResourceType::sculpture:
        string = 19;
        break;
    case eResourceType::horse:
        string = 15;
        break;
    case eResourceType::chariot:
        string = 22;
        break;
    default:
        break;
    }
    return eLanguage::zeusText(group, string);
}

std::shared_ptr<eTexture> eResourceTypeHelpers::icon(
        const eUIScale scale, const eResourceType type) {
    const int icoll = static_cast<int>(scale);
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
    case eResourceType::chariot:
        return coll.fChariotUnit;
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

    case eResourceType::silver:
    case eResourceType::drachmas:
        return coll.fDrachmasUnit;
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

int eResourceTypeHelpers::defaultPrice(const eResourceType type) {
    switch(type) {
    case eResourceType::urchin:
    case eResourceType::fish:
        return 36;
    case eResourceType::meat:
    case eResourceType::cheese:
        return 45;
    case eResourceType::carrots:
    case eResourceType::onions:
    case eResourceType::wheat:
        return 30;
    case eResourceType::oranges:
        return 45;

    case eResourceType::grapes:
        return 42;
    case eResourceType::olives:
        return 38;
    case eResourceType::wine:
        return 160;
    case eResourceType::oliveOil:
        return 145;
    case eResourceType::fleece:
        return 60;

    case eResourceType::wood:
        return 75;
    case eResourceType::bronze:
        return 110;
    case eResourceType::marble:
        return 84;

    case eResourceType::armor:
        return 200;

    case eResourceType::sculpture:
        return 640;

    case eResourceType::food:
    case eResourceType::warehouse:
    case eResourceType::allBasic:
    case eResourceType::allTransportable:
    case eResourceType::none:
    case eResourceType::horse:
    case eResourceType::chariot:
    case eResourceType::silver:
    case eResourceType::drachmas:
        return 0;
    }
    return 0;
}
