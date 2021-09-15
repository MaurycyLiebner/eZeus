#ifndef ETEXTURELOADINGHELPERS_H
#define ETEXTURELOADINGHELPERS_H

#include "etexturecollection.h"
#include "etextureclass.h"

class eTextureLoader;

namespace eTextureLoadingHelpers {
    std::string addZeroes(const std::string& str);

    std::shared_ptr<eTexture> loadTex(
            const std::string& pathBase, const int i,
            eTextureCollection& coll);
    std::shared_ptr<eTexture> loadTexWithOffset(
            const std::string& pathBase, const int i,
            eTextureCollection& coll,
            const eOffsets& offs);

    const std::shared_ptr<eTexture>& getTex(
            const std::string& pathBase, const int i,
            eTextureCollection& coll, std::string& path);
    const std::shared_ptr<eTexture>& getTexWithOffset(
            const std::string& pathBase, const int i,
            eTextureCollection& coll, std::string& path,
            const eOffsets& offs);

    void deleteTex(const std::string& pathBase, const int i);

    const std::shared_ptr<eTexture>& queLoadTex(
            const std::string& pathBase,
            const int i,
            eTextureCollection& coll,
            eTextureLoader& texLoader);
    const std::shared_ptr<eTexture>& queLoadTexWithOffset(
            const std::string& pathBase,
            const int i,
            eTextureCollection& coll,
            const eOffsets& offs,
            eTextureLoader& texLoader);

    std::shared_ptr<eTexture> queLoadTex(
            const std::string& pathBase,
            const int i,
            eTextureLoader& texLoader);
    std::shared_ptr<eTexture> queLoadTexWithOffset(
            const std::string& pathBase,
            const int i,
            const eOffsets& offs,
            eTextureLoader& texLoader);
};

#endif // ETEXTURELOADINGHELPERS_H
