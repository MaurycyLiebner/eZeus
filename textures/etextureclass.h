#ifndef ETEXTURECLASS_H
#define ETEXTURECLASS_H

#include "etexturecollection.h"

class eTextureLoader;

using eOffset = std::pair<int, int>;
using eOffsets = std::vector<eOffset>;

class eTextureClass {
public:
    eTextureClass(const std::string& pathBase,
                  eTextureLoader& texLoader,
                  const eOffsets* const offs = nullptr);

    void load(const int i, eTextureCollection& coll);

    std::shared_ptr<eTexture> load(const int i);

    void loadSkipFlipped(std::vector<eTextureCollection>& colls,
                         const int i0, const int i1);
private:
    const std::string mPathBase;
    eTextureLoader& mTexLoader;
    const eOffsets* const mOffset;
};

#endif // ETEXTURECLASS_H