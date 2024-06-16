#include "eemployingbuilding.h"

#include "engine/egameboard.h"

eEmployingBuilding::eEmployingBuilding(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees) :
    eBuildingWithResource(board, type, sw, sh),
    mMaxEmployees(maxEmployees) {
    auto& emplData = board.employmentData();
    emplData.incTotalJobVacancies(mMaxEmployees);
    auto& distr = board.employmentDistributor();
    eSector s;
    const bool r = eSectorHelpers::sBuildingSector(type, s);
    if(r) distr.incMaxEmployees(s, maxEmployees);
}

eEmployingBuilding::~eEmployingBuilding() {
    auto& board = getBoard();
    auto& emplData = board.employmentData();
    emplData.incTotalJobVacancies(-mMaxEmployees);
    auto& distr = board.employmentDistributor();
    eSector s;
    const bool r = eSectorHelpers::sBuildingSector(type(), s);
    const int me = maxEmployees();
    if(r) distr.incMaxEmployees(s, -me);
}

void eEmployingBuilding::timeChanged(const int by) {
    mEmployedUpdate += by;
    if(mEmployedUpdate > mEmployedUpdateWait) {
        mEmployedUpdate -= mEmployedUpdateWait;
        const auto& emplData = getBoard().employmentData();
        const double ef = emplData.employedFraction();
        const int e = std::round(ef*mMaxEmployees);
        mEmployed = std::clamp(e, 0, mMaxEmployees);
        setEnabled(mEmployed > 0);
    }
    eBuildingWithResource::timeChanged(by);
}

double eEmployingBuilding::employedFraction() const {
    if(mMaxEmployees <= 0) return 1;
    return double(mEmployed)/mMaxEmployees;
}

double eEmployingBuilding::effectiveness() const {
    const double ef = std::max(0.1, employedFraction());
    double blessed = 0.;
    if(eBuilding::blessed()) {
        blessed = 1.;
    } else if(eBuilding::cursed()) {
        blessed = -1.;
    }
    return ef*(1 + 0.5*blessed);
}

void eEmployingBuilding::read(eReadStream& src) {
    eBuildingWithResource::read(src);
    src >> mMaxEmployees;
    src >> mEmployedUpdateWait;
    src >> mEmployedUpdate;
    src >> mEmployed;
}

void eEmployingBuilding::write(eWriteStream& dst) const {
    eBuildingWithResource::write(dst);
    dst << mMaxEmployees;
    dst << mEmployedUpdateWait;
    dst << mEmployedUpdate;
    dst << mEmployed;
}
