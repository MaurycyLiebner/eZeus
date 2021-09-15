#include "etextureclass.h"

#include "etextureloadinghelpers.h"
#include "etextureloader.h"

eTextureClass::eTextureClass(const std::string& pathBase,
                             eTextureLoader& texLoader,
                             const eOffsets* const offs) :
    mPathBase(pathBase),
    mTexLoader(texLoader),
    mOffset(offs) {}

void eTextureClass::load(const int i, eTextureCollection& coll) {
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

std::shared_ptr<eTexture> eTextureClass::load(const int i) {
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

void eTextureClass::loadSkipFlipped(std::vector<eTextureCollection>& colls,
                                    const int i0, const int i1) {
    const auto renderer = mTexLoader.renderer();
    for(int j = 0; j < 8; j++) {
        colls.emplace_back(renderer);
    }
    int k = 0;
    for(int i = i0; i < i1;) {
        for(int j = 0; j < 8; j++, i++) {
            if(j > 3 && j < 7) {
                eTextureLoadingHelpers::deleteTex(mPathBase, i);
                auto& tex = colls[j].addTexture();
                const auto& flipTex = colls[6 - j].getTexture(k);
                tex->setFlipTex(flipTex);
                if(mOffset) {
                    const auto& offset = (*mOffset)[i - 1];
                    tex->setOffset(offset.first, offset.second);
                }
            } else {
                load(i, colls[j]);
            }
        }
        k++;
    }
}
