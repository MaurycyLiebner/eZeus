#include "eemploymentdata.h"

#include "epopulationdata.h"
#include "engine/edifficulty.h"
#include "engine/egameboard.h"

#include <math.h>

eEmploymentData::eEmploymentData(const ePopulationData& popData,
                                 const eGameBoard& board) :
    mPopData(popData), mBoard(board) {

}

void eEmploymentData::incTotalJobVacancies(const int v) {
    mTotalJobVacs += v;
}

int eEmploymentData::employable() const {
    const auto diff = mBoard.difficulty();
    const auto wageRate = mBoard.wageRate();
    const double frac = eDifficultyHelpers::workerFrac(
                            diff, wageRate);
    return frac*mPopData.population();
}

int eEmploymentData::employed() const {
    return std::min(employable(), totalJobVacancies());
}

int eEmploymentData::pensions() const {
    const auto wageRate = mBoard.wageRate();
    const double frac = eDifficultyHelpers::wageMultiplier(
                            wageRate);
    return frac*employed();
}

int eEmploymentData::unemployed() const {
    return employable() - employed();
}

int eEmploymentData::freeJobVacancies() const {
    return totalJobVacancies() - employed();
}

int eEmploymentData::totalJobVacancies() const {
    return mTotalJobVacs;
}

double eEmploymentData::employedFraction() const {
    const int v = mTotalJobVacs;
    if(v == 0) return 1;
    return double(employed())/v;
}

