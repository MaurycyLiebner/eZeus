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


    // Step 2: Normalize priorities and calculate total priority weight
    int totalPriorityWeight = 0;
    for(const auto& task : mPriorities) {
        const int priorityValue = static_cast<int>(task.second);
        const int maxEmployees = mMaxEmployees[task.first];
        totalPriorityWeight += maxEmployees*priorityValue;
    }

    // Step 3: Distribute employees based on normalized priority values
    for(const auto& task : mPriorities) {
        const int priority = static_cast<int>(task.second);
        const int maxEmployees = mMaxEmployees[task.first];
        const int allocated = std::round(static_cast<double>(mTotalEmployees * maxEmployees * priority) / totalPriorityWeight);
        mEmployees[task.first] = std::min(allocated, maxEmployees);
    }

    // Step 4: Adjust to ensure the total number of employees equals totalEmployees
//    int currentAllocation = std::accumulate(mEmployees.begin(), mEmployees.end(), 0,
//        [](int sum, const std::pair<eSector, int>& p) { return sum + p.second; });

//    while(currentAllocation > mTotalEmployees) {
//        for(auto& task : mEmployees) {
//            if(task.second > 0) {
//                task.second--;
//                currentAllocation--;
//                if(currentAllocation == mTotalEmployees) break;
//            }
//        }
//    }

//    while(currentAllocation < mTotalEmployees) {
//        for(auto& task : mEmployees) {
//            // Ensure we do not exceed the maximum limit for each task
//            auto maxEmployees = std::find_if(normalizedTasks.begin(), normalizedTasks.end(),
//                                             [&task](const auto& t) { return t.first == task.first; })->second.second;
//            if(mEmployees[task.first] < maxEmployees) {
//                task.second++;
//                currentAllocation++;
//                if (currentAllocation == mTotalEmployees) break;
//            }
//        }
//    }
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
