#ifndef EEMPLOYMENTDISTRIBUTOR_H
#define EEMPLOYMENTDISTRIBUTOR_H

#include <map>
#include <vector>

#include "fileIO/ewritestream.h"
#include "fileIO/ereadstream.h"

enum class eBuildingType;
class eEmploymentData;
enum class eResourceType;

enum class eSector {
    husbandry,
    industry,
    storageAndDistribution,
    hygieneAndSafety,
    administration,
    cultureScience,
    mythology,
    military
};

namespace eSectorHelpers {
    std::string sName(const eSector s, const bool atlantean);
    bool sBuildingSector(const eBuildingType type,
                         eSector& sector);
}

namespace eIndustryHelpers {
    std::vector<eResourceType> sIndustries(const eBuildingType type);
    std::vector<eBuildingType> sBuildings(const eResourceType type);
}

enum class ePriority {
    noPriority,
    veryLow,
    low,
    moderate,
    high,
    veryHigh
};

namespace ePriorityHelpers {
    std::string sName(const ePriority p);
    int sWeight(const ePriority p);
}

class eEmploymentDistributor {
public:
    eEmploymentDistributor(eEmploymentData& empl);

    void setPriority(const eSector s, const ePriority p);
    ePriority priority(const eSector s) const;
    void setMaxEmployees(const eSector s, const int e);
    int maxEmployees(const eSector s) const;
    void incMaxEmployees(const eSector s, const int by);

    int employees(const eSector s);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    void distribute();

    bool mChanged = true;
    int mTotalEmployees = 0;

    eEmploymentData& mEmplData;

    std::map<eSector, int> mEmployees;
    std::map<eSector, int> mMaxEmployees;
    std::map<eSector, ePriority> mPriorities;
};

#endif // EEMPLOYMENTDISTRIBUTOR_H
