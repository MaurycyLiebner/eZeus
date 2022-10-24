#include "eemployingbuilding.h"

#include "engine/egameboard.h"

eEmployingBuilding::eEmployingBuilding(
        eGameBoard& board,
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
    mEmployedUpdate += by;
    if(mEmployedUpdate > mEmployedUpdateWait) {
        mEmployedUpdate -= mEmployedUpdateWait;
        const auto& emplData = getBoard().employmentData();
        const double ef = emplData.employedFraction();
        const int e = std::round(ef*mMaxEmployees);
        mEmployed = std::clamp(e, 0, mMaxEmployees);
        setEnabled(ef > 0.49);
    }
    eBuildingWithResource::timeChanged(by);
}

double eEmployingBuilding::employedFraction() const {
    if(mMaxEmployees <= 0) return 1;
    return double(mEmployed)/mMaxEmployees;
}

double eEmployingBuilding::effectiveness() const {
    const double ef = std::max(0.1, employedFraction());
    return ef*(1 + 0.5*blessed());
}
