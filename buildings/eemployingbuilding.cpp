#include "eemployingbuilding.h"

#include "engine/egameboard.h"

eEmployingBuilding::eEmployingBuilding(eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees) :
    eBuildingWithResource(board, type, sw, sh),
    mMaxEmployees(maxEmployees) {
    auto& emplData = getBoard().employmentData();
    emplData.incTotalJobVacancies(mMaxEmployees);
}

eEmployingBuilding::~eEmployingBuilding() {
    auto& emplData = getBoard().employmentData();
    emplData.incTotalJobVacancies(-mMaxEmployees);
}

void eEmployingBuilding::timeChanged(const int by) {
    (void)by;
    if(time() > mEmployedUpdate) {
        mEmployedUpdate = time() + 1000;
        const auto& emplData = getBoard().employmentData();
        const double ef = emplData.employedFraction();
        const int e = std::round(ef*mMaxEmployees);
        mEmployed = std::clamp(e, 0, mMaxEmployees);
    }
}

double eEmployingBuilding::employedFraction() const {
    if(mMaxEmployees <= 0) return 1;
    return double(mEmployed)/mMaxEmployees;
}
