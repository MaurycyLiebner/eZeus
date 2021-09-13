#ifndef ETEXTURELOADINGHELPERS_H
#define ETEXTURELOADINGHELPERS_H

#include "etexturecollection.h"

class eTextureLoader;

using eOffset = std::pair<int, int>;
using eOffsets = std::vector<eOffset>;

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

class eTextureClass {
public:
    eTextureClass(const std::string& pathBase,
                  eTextureLoader& texLoader,
                  const eOffsets* const offs = nullptr) :
        mPathBase(pathBase),
        mTexLoader(texLoader),
        mOffset(offs) {}

    void load(const int i, eTextureCollection& coll) {
        if(mOffset) {
            eTextureLoadingHelpers::queLoadTexWithOffset(
                        mPathBase, i, coll,
                        *mOffset, mTexLoader);
        } else {
            eTextureLoadingHelpers::queLoadTex(
                        mPathBase, i, coll,
                        mTexLoader);
        }
    }

    std::shared_ptr<eTexture> load(const int i) {
        const auto tex = std::make_shared<eTexture>();
        if(mOffset) {
            return eTextureLoadingHelpers::queLoadTexWithOffset(
                        mPathBase, i,
                        *mOffset, mTexLoader);
        } else {
            return eTextureLoadingHelpers::queLoadTex(
                        mPathBase, i,
                        mTexLoader);
        }
    }
private:
    const std::string mPathBase;
    eTextureLoader& mTexLoader;
    const eOffsets* const mOffset;
};

#endif // ETEXTURELOADINGHELPERS_H
