#include "eappeal.h"

double eAppealHelpers::appealAtDist(
        const eBuildingType type, const int dist) {
    const auto app = appeal(type);
    if(app.fValue == 0) return 0;
    const double dd = app.fRange - dist;
    return dd*app.fValue/app.fRange;
}

eAppeal eAppealHelpers::appeal(const eBuildingType type) {
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
