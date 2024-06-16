#include "eemploymentdistributor.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "buildings/ebuilding.h"
#include "elanguage.h"
#include "boardData/eemploymentdata.h"

eEmploymentDistributor::eEmploymentDistributor(eEmploymentData& empl) :
    mEmplData(empl) {
    const int iMin = static_cast<int>(eSector::husbandry);
    const int iMax = static_cast<int>(eSector::military);
    for(int i = iMin; i <= iMax; i++) {
        const auto s = static_cast<eSector>(i);
        mEmployees[s] = 0;
        mMaxEmployees[s] = 0;
        mPriorities[s] = ePriority::moderate;
    }
}

void eEmploymentDistributor::setPriority(
        const eSector s, const ePriority p) {
    mPriorities[s] = p;
    mChanged = true;
}

ePriority eEmploymentDistributor::priority(const eSector s) const {
    return mPriorities.at(s);
}

void eEmploymentDistributor::setMaxEmployees(const eSector s, const int e) {
    mMaxEmployees[s] = e;
    mChanged = true;
}

int eEmploymentDistributor::maxEmployees(const eSector s) const {
    return mMaxEmployees.at(s);
}

void eEmploymentDistributor::incMaxEmployees(const eSector s, const int by) {
    mMaxEmployees[s] += by;
    mChanged = true;
}

int eEmploymentDistributor::employees(const eSector s) {
    const int e = mEmplData.employable();
    if(e != mTotalEmployees) mChanged = true;
    mTotalEmployees = e;
    if(mChanged) distribute();
    return mEmployees[s];
}

void eEmploymentDistributor::distribute() {
    mChanged = false;

    int totalNeeded = 0;
    for(auto& task : mMaxEmployees) {
        totalNeeded += task.second;
    }
    if(mTotalEmployees >= totalNeeded) {
        for(auto& e : mEmployees) {
            e.second = mMaxEmployees[e.first];
        }
        return;
    }

    int totalPriorityWeight = 0;
    for(const auto& task : mPriorities) {
        const int priority = ePriorityHelpers::sWeight(task.second);
        const int maxEmployees = mMaxEmployees[task.first];
        totalPriorityWeight += maxEmployees*priority;
    }

    int allocatedCounter = 0;

    struct eSectorReminder {
        double fRem;
        eSector fS;
    };

    std::vector<eSectorReminder> reminders;
    for(const auto& task : mPriorities) {
        const auto s = task.first;
        if(totalPriorityWeight == 0) {
            reminders.push_back({0, s});
            continue;
        }
        const int priority = ePriorityHelpers::sWeight(task.second);
        const int maxEmployees = mMaxEmployees[s];
        const double allocatedF = static_cast<double>(mTotalEmployees * maxEmployees * priority) / totalPriorityWeight;
        const int allocated = std::floor(allocatedF);
        const int a = std::min(allocated, maxEmployees);
        reminders.push_back({allocatedF - a, s});
        allocatedCounter += a;
        mEmployees[s] = a;
    }
    const auto comp = [](const eSectorReminder& r1, const eSectorReminder& r2) {
        return r1.fRem > r2.fRem;
    };
    std::sort(reminders.begin(), reminders.end(), comp);
    while(allocatedCounter < mTotalEmployees) {
        for(auto& r : reminders) {
            if(allocatedCounter >= mTotalEmployees) break;
            const auto s = r.fS;
            const int me = mMaxEmployees[s];
            if(mEmployees[s] >= me) continue;
            mEmployees[s]++;
            allocatedCounter++;
        }
    }
}

std::string eSectorHelpers::sName(const eSector s, const bool atlantean) {
    int string = -1;
    if(atlantean && s == eSector::cultureScience) {
        string = 9;
    } else {
        string = static_cast<int>(s) + 1;
    }
    return eLanguage::zeusText(50, string);
}

std::string ePriorityHelpers::sName(const ePriority p) {
    const int string = static_cast<int>(p) + 24;
    return eLanguage::zeusText(50, string);
}

bool eSectorHelpers::sBuildingSector(const eBuildingType type,
                                     eSector& sector) {
    switch(type) {
    case eBuildingType::gymnasium:
    case eBuildingType::college:
    case eBuildingType::dramaSchool:
    case eBuildingType::podium:
    case eBuildingType::theater:
    case eBuildingType::stadium:

    case eBuildingType::bibliotheke:
    case eBuildingType::observatory:
    case eBuildingType::university:
    case eBuildingType::laboratory:
    case eBuildingType::inventorsWorkshop:
    case eBuildingType::museum:
        sector = eSector::cultureScience;
        break;
    case eBuildingType::fountain:
    case eBuildingType::hospital:
    case eBuildingType::watchPost:
    case eBuildingType::maintenanceOffice:
        sector = eSector::hygieneAndSafety;
        break;
    case eBuildingType::wheatFarm:
    case eBuildingType::carrotsFarm:
    case eBuildingType::onionsFarm:
    case eBuildingType::huntingLodge:
    case eBuildingType::fishery:
    case eBuildingType::urchinQuay:
    case eBuildingType::cardingShed:
    case eBuildingType::dairy:
    case eBuildingType::growersLodge:
    case eBuildingType::orangeTendersLodge:
    case eBuildingType::corral:
        sector = eSector::husbandry;
        break;
    case eBuildingType::granary:
    case eBuildingType::warehouse:
    case eBuildingType::tradePost:
    case eBuildingType::pier:
    case eBuildingType::foodVendor:
    case eBuildingType::fleeceVendor:
    case eBuildingType::oilVendor:
    case eBuildingType::wineVendor:
    case eBuildingType::armsVendor:
    case eBuildingType::horseTrainer:
    case eBuildingType::chariotVendor:
        sector = eSector::storageAndDistribution;
        break;
    case eBuildingType::timberMill:
    case eBuildingType::masonryShop:
    case eBuildingType::mint:
    case eBuildingType::foundry:
    case eBuildingType::olivePress:
    case eBuildingType::winery:
    case eBuildingType::sculptureStudio:
        sector = eSector::industry;
        break;
    case eBuildingType::tower:
    case eBuildingType::triremeWharf:
    case eBuildingType::horseRanch:
    case eBuildingType::chariotFactory:
    case eBuildingType::armory:
        sector = eSector::military;
        break;
    case eBuildingType::artisansGuild:
    case eBuildingType::templeAphrodite:
    case eBuildingType::templeApollo:
    case eBuildingType::templeAres:
    case eBuildingType::templeArtemis:
    case eBuildingType::templeAthena:
    case eBuildingType::templeAtlas:
    case eBuildingType::templeDemeter:
    case eBuildingType::templeDionysus:
    case eBuildingType::templeHades:
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeHera:
    case eBuildingType::templeHermes:
    case eBuildingType::templePoseidon:
    case eBuildingType::templeZeus:
        sector = eSector::mythology;
        break;
    case eBuildingType::taxOffice:
        sector = eSector::administration;
        break;
    default:
        return false;
    }
    return true;
}

int ePriorityHelpers::sWeight(const ePriority p) {
    switch(p) {
    case ePriority::noPriority:
        return 0;
    case ePriority::veryLow:
        return 1;
    case ePriority::low:
        return 3;
    case ePriority::moderate:
        return 5;
    case ePriority::high:
        return 8;
    case ePriority::veryHigh:
        return 12;
    }
    return 0;
}
