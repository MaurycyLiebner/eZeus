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

    void incTime(const int by);
    void nextYear();

    std::vector<stdsptr<eWorldCity>> getTribute() const;

    void setHomeCity(const stdsptr<eWorldCity>& hc);
    void addCity(const stdsptr<eWorldCity>& c);

    const stdsptr<eWorldCity>& homeCity() const
    { return mHomeCity; }
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

    bool editorMode() const { return mEditorMode; }
    void setEditorMode(const bool m) { mEditorMode = m; }
    bool poseidonMode() const { return mPoseidonMode; }
    void setPoseidonMode(const bool p) { mPoseidonMode = p; }
private:
    bool mEditorMode = true;
    bool mPoseidonMode = true;
    eWorldMap mMap{eWorldMap::greece8};
    stdsptr<eWorldCity> mHomeCity;
    std::vector<stdsptr<eWorldCity>> mCities;
};

#endif // EWORLDBOARD_H
