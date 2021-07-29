#ifndef ETEXTURELOADINGHELPERS_H
#define ETEXTURELOADINGHELPERS_H

#include "etexturecollection.h"

namespace eTextureLoadingHelpers {
    std::string addZeroes(const std::string& str);

    void loadTex(const std::string& pathBase, const int i,
                 eTextureCollection& coll);
};

#endif // ETEXTURELOADINGHELPERS_H
