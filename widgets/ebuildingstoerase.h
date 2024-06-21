#ifndef EBUILDINGSTOERASE_H
#define EBUILDINGSTOERASE_H

#include <vector>
#include <set>

class eBuilding;
class eTile;

class eBuildingsToErase {
public:
    eBuildingsToErase() {}

    void addBuilding(eBuilding* const b);

    int erase(const bool important);

    bool hasImportantBuildings() const;
    bool hasNonEmptyAgoras() const;
private:
    void erase(eBuilding* const b);

    std::set<eBuilding*> mBs;
    std::set<eBuilding*> mImpBs;
    std::set<eBuilding*> mAgoBs;
};

#endif // EBUILDINGSTOERASE_H
