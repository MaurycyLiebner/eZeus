#ifndef EWORLDBOARD_H
#define EWORLDBOARD_H

#include <vector>

#include "eworldcity.h"
#include "pointers/estdselfref.h"

enum class eWorldMap {
    greece1,
    greece2,
    greece3,
    greece4,
    greece5,
    greece6,
    greece7,
    greece8,

    poseidon1,
    poseidon2,
    poseidon3,
    poseidon4
};

class eWorldBoard {
public:
    eWorldBoard();

    void nextMonth(eGameBoard* const board);
    void nextYear();

    std::vector<stdsptr<eWorldCity>> getTribute() const;

    void setHomeCity(const stdsptr<eWorldCity>& hc);
    void addCity(const stdsptr<eWorldCity>& c);

    stdsptr<eWorldCity> currentCity() const;
    const std::vector<stdsptr<eWorldCity>>& cities() const
    { return mCities; }

    eWorldMap map() const { return mMap; }
    void setMap(const eWorldMap m) { mMap = m; }

    int cityId(const eWorldCity& city) const;

    stdsptr<eWorldCity> cityWithIOID(const int id) const;
    void setIOIDs() const;

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);

    void attackedAlly();

    stdsptr<eWorldCity> colonyWithId(const int id) const;
    void activateColony(const int id);

    void setColonyAsCurrentCity(const int id);
    void setParentAsCurrentCity();

    bool editorMode() const { return mEditorMode; }
    void setEditorMode(const bool m) { mEditorMode = m; }
    bool poseidonMode() const { return mPoseidonMode; }
    void setPoseidonMode(const bool p) { mPoseidonMode = p; }
private:
    bool mEditorMode = false;
    bool mPoseidonMode = true;
    eWorldMap mMap{eWorldMap::greece8};
    std::vector<stdsptr<eWorldCity>> mCities;
};

#endif // EWORLDBOARD_H
