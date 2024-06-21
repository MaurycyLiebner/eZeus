#ifndef EPARKTEXTURE_H
#define EPARKTEXTURE_H

class eTile;
enum class eWorldDirection;

namespace eParkTexture {
    void get(eTile* const tile,
             int& futureDim,
             int& drawDim,
             const eWorldDirection dir);
};

#endif // EPARKTEXTURE_H
