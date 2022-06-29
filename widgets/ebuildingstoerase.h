#ifndef EBUILDINGSTOERASE_H
#define EBUILDINGSTOERASE_H

#include <vector>

class eBuilding;
class eTile;

class eBuildingVectorClass : public std::vector<eBuilding*> {
public:
    using std::vector<eBuilding*>::vector;

    void add(eBuilding* const b);
};

class eBuildingsToErase {
public:
    eBuildingsToErase() {}

    void addBuilding(eBuilding* const b);

    int erase(const bool important);

    bool hasImportantBuildings() const;
    bool hasNonEmptyAgoras() const;
private:
    void erase(eBuilding* const b);

    eBuildingVectorClass mBs;
    eBuildingVectorClass mImpBs;
    eBuildingVectorClass mAgoBs;
};

#endif // EBUILDINGSTOERASE_H
