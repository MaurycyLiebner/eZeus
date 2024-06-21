#ifndef EHUSBANDRYDATA_H
#define EHUSBANDRYDATA_H

class ePopulationData;
class eGameBoard;

class eHusbandryData {
public:
    eHusbandryData(const ePopulationData& popData,
                   const eGameBoard& board);

    int canSupport() const;
    int storedFood() const;
private:
    const ePopulationData& mPopData;
    const eGameBoard& mBoard;
};

#endif // EHUSBANDRYDATA_H
