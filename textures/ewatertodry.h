#ifndef EWATERTODRY_H
#define EWATERTODRY_H

class eTile;
enum class eWorldDirection;

namespace eWaterToDry {
    int get(eTile* const tile, const eWorldDirection dir);
};

#endif // EWATERTODRY_H
