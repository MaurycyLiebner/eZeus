#include "ehusbandrydata.h"

#include "epopulationdata.h"

#include "engine/egameboard.h"

eHusbandryData::eHusbandryData(const ePopulationData& popData,
                               const eGameBoard& board) :
    mPopData(popData), mBoard(board) {}

int eHusbandryData::canSupport() const {
    return 0;
}

int eHusbandryData::storedFood() const {
    const int pop = mPopData.population();
    if(pop <= 0) return 0;
    const double foodPerPersonPerMonth = 0.002727381;
    const double foodPerPopPerMonth = pop*foodPerPersonPerMonth;
    const int nFood = mBoard.resourceCount(eResourceType::food);
    const double nMonths = nFood/foodPerPopPerMonth;
    const int iNMonths = std::floor(nMonths);
    return iNMonths;
}
