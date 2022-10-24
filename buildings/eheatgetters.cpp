#include "eheatgetters.h"

eHeat eHeatGetters::appeal(const eBuildingType type) {
    switch(type) {
    case eBuildingType::wheatFarm: return {-3, 3};
    case eBuildingType::carrotsFarm: return {-4, 3};
    case eBuildingType::onionsFarm: return {-2, 2};
    case eBuildingType::growersLodge: return {-3, 2};
    case eBuildingType::oliveTree:
    case eBuildingType::vine: return {1, 1};
    case eBuildingType::orangeTree: return {1, 2};
    case eBuildingType::cardingShed: return {-5, 3};
    case eBuildingType::dairy: return {-5, 3};
    case eBuildingType::urchinQuay:
    case eBuildingType::fishery: return {-15, 4};
    case eBuildingType::huntingLodge: return {-6, 4};
    case eBuildingType::orangeTendersLodge: return {2, 2};

    case eBuildingType::timberMill: return {-5, 4};
    case eBuildingType::masonryShop: return {-6, 4};
    case eBuildingType::mint:
    case eBuildingType::foundry: return {-10, 6};
    case eBuildingType::sculptureStudio: return {-2, 2};
    case eBuildingType::olivePress: return {-4, 4};
    case eBuildingType::winery: return {4, 4};
    case eBuildingType::armory: return {-8, 4};
    case eBuildingType::tower: return {-4, 4};

    case eBuildingType::granary: return {-12, 4};
    case eBuildingType::warehouse: return {-2, 4};
    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::wineVendor: return {2, 2};
    case eBuildingType::horseTrainer: return {-2, 2};

    case eBuildingType::fountain: return {4, 4};
    case eBuildingType::hospital: return {-2, 4};
    case eBuildingType::maintenanceOffice: return {0, 0};
    case eBuildingType::watchPost: return {-2, 2};
    case eBuildingType::palace: return {18, 6};
    case eBuildingType::taxOffice: return {-4, 2};

    case eBuildingType::college: return {-5, 2};
    case eBuildingType::podium: return {3, 3};
    case eBuildingType::gymnasium: return {0, 0};
    case eBuildingType::dramaSchool: return {0, 0};
    case eBuildingType::theater: return {6, 3};
    case eBuildingType::stadium: return {0, 0};

    case eBuildingType::doricColumn:
    case eBuildingType::ionicColumn:
    case eBuildingType::corinthianColumn: return {4, 3};

    case eBuildingType::avenue: return {3, 3};

    case eBuildingType::commemorative: return {30, 6};

    case eBuildingType::park: return {3, 3};

    case eBuildingType::bench: return {2, 4};
    case eBuildingType::flowerGarden: return {8, 3};
    case eBuildingType::gazebo: return {6, 6};
    case eBuildingType::hedgeMaze: return {12, 4};
    case eBuildingType::fishPond: return {18, 6};

    case eBuildingType::waterPark: return {5, 4};

    case eBuildingType::birdBath: return {3, 3};
    case eBuildingType::shortObelisk: return {6, 2};
    case eBuildingType::tallObelisk: return {8, 2};
    case eBuildingType::shellGarden: return {5, 5};
    case eBuildingType::sundial: return {7, 4};
    case eBuildingType::dolphinSculpture: return {12, 4};
    case eBuildingType::spring: return {10, 5};
    case eBuildingType::topiary: return {15, 3};
    case eBuildingType::baths: return {15, 6};
    case eBuildingType::stoneCircle: return {24, 4};

    default: return {0, 0};
    }
}

eHeat eHeatGetters::housing(const eBuildingType type) {
    switch(type) {
    case eBuildingType::commonHouse: return {10, 5};
    case eBuildingType::eliteHousing: return {10, 5};
    default: return {2, 5};
    }
}

eHeat eHeatGetters::industry(const eBuildingType type) {
    switch(type) {
    case eBuildingType::timberMill: return {10, 5};
    case eBuildingType::masonryShop: return {10, 5};
    case eBuildingType::mint: return {10, 5};
    case eBuildingType::foundry: return {10, 5};
    case eBuildingType::sculptureStudio: return {10, 5};
    case eBuildingType::armory: return {10, 5};
    default: return {2, 5};
    }
}

eHeat eHeatGetters::farming(const eBuildingType type) {
    switch(type) {
    case eBuildingType::wheatFarm: return {10, 5};
    case eBuildingType::carrotsFarm: return {10, 5};
    case eBuildingType::onionsFarm: return {10, 5};
    case eBuildingType::growersLodge: return {10, 5};
    case eBuildingType::cardingShed: return {10, 5};
    case eBuildingType::dairy: return {10, 5};
    case eBuildingType::urchinQuay: return {10, 5};
    case eBuildingType::fishery: return {10, 5};
    case eBuildingType::huntingLodge: return {10, 5};
    case eBuildingType::orangeTendersLodge: return {10, 5};
    default: return {2, 5};
    }
}

eHeat eHeatGetters::storage(const eBuildingType type) {
    switch(type) {
    case eBuildingType::granary: return {10, 5};
    case eBuildingType::warehouse: return {10, 5};
    case eBuildingType::tradePost: return {10, 5};
    default: return {2, 5};
    }
}

eHeat eHeatGetters::culture(const eBuildingType type) {
    switch(type) {
    case eBuildingType::college: return {10, 5};
    case eBuildingType::podium: return {10, 5};
    case eBuildingType::gymnasium: return {10, 5};
    case eBuildingType::dramaSchool: return {10, 5};
    case eBuildingType::theater: return {10, 5};
    case eBuildingType::stadium: return {10, 5};
    default: return {2, 5};
    }
}
