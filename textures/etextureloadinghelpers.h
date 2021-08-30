#ifndef ETEXTURELOADINGHELPERS_H
#define ETEXTURELOADINGHELPERS_H

#include "etexturecollection.h"

namespace eTextureLoadingHelpers {
    std::string addZeroes(const std::string& str);

    std::shared_ptr<eTexture> loadTex(
            const std::string& pathBase, const int i,
            eTextureCollection& coll);
    std::shared_ptr<eTexture> loadTexWithOffset(
            const std::string& pathBase, const int i,
            eTextureCollection& coll,
            const std::vector<std::pair<int, int>>& offs);
};

#endif // ETEXTURELOADINGHELPERS_H
