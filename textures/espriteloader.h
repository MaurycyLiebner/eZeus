#ifndef ESPRITELOADER_H
#define ESPRITELOADER_H

#include "etexturecollection.h"
#include "spriteData/espritedata.h"
#include "egamedir.h"
#include "ebinaryimageloader.h"

using eOffset = std::pair<int, int>;
using eOffsets = std::vector<eOffset>;

class eSpriteLoader {
public:
    eSpriteLoader(const int size,
                  const std::string& name,
                  const std::vector<eSpriteData>& sds,
                  const eOffsets* const offs,
                  SDL_Renderer* const r) :
        mSize(std::to_string(size)), mName(name),
        mSds(sds), mOffs(offs), mRenderer(r) {}

    void loadSkipFlipped(const int doff,
                         const int min, const int max,
                         std::vector<eTextureCollection>& colls) {
        for(int j = 0; j < 8; j++) {
            colls.emplace_back(mRenderer);
        }
        int k = 0;
        for(int i = min; i < max;) {
            for(int j = 0; j < 8; j++, i++) {
                auto& coll = colls[j];
                if(j > 3 && j < 7) {
                    const auto& flipTex = colls[6 - j].getTexture(k);
                    auto& tex = coll.addTexture();
                    tex->setFlipTex(flipTex);
                    if(mOffs) {
                        const auto& offset = (*mOffs)[i - 1];
                        tex->setOffset(offset.first, offset.second);
                    }
                } else {
                    load(doff, i, coll);
                }
            }
            k++;
        }
    }

    const std::shared_ptr<eTexture>& load(
            const int doff, const int i,
            eTextureCollection& coll) {
        const auto& sd = mSds[i - doff];
        const int tid = sd.fTexId;
        const auto t = tid == -1 ? nullptr : getTex(tid);
        const SDL_Rect rect{sd.fX, sd.fY, sd.fW, sd.fH};
        const auto& tex = coll.addTexture();
        tex->setParentTexture(rect, t);
        if(mOffs) {
            const auto& off = (*mOffs)[i - 1];
            tex->setOffset(off.first, off.second);
        }
        return tex;
    }

    std::shared_ptr<eTexture> load(
            const int doff, const int i) {
        const auto& sd = mSds[i - doff];
        const int tid = sd.fTexId;
        const auto t = getTex(tid);
        std::shared_ptr<eTexture> tex;
        if(mSds.size() == 1) {
            tex = t;
        } else {
            const SDL_Rect rect{sd.fX, sd.fY, sd.fW, sd.fH};
            tex = std::make_shared<eTexture>();
            tex->setParentTexture(rect, t);
        }
        if(mOffs) {
            const auto& off = (*mOffs)[i - 1];
            tex->setOffset(off.first, off.second);
        }
        return tex;
    }
private:
    void loadTex(const int i) {
        const bool binary = true;
        std::shared_ptr<eTexture> tex;
        if(binary) {
            const auto path = mSize + "/" + mName + "_" + std::to_string(i) + ".png";
            tex = eBinaryImageLoader::load(mRenderer, path);
        } else {
            tex = std::make_shared<eTexture>();
            const std::string dir = eGameDir::texturesDir() + mSize + "/";
            const auto path = dir + mName + "_" + std::to_string(i) + ".png";
            tex->load(mRenderer, path);
        }
        mTexs[i] = tex;
    }

    const std::shared_ptr<eTexture>& getTex(const int i) {
        if(mTexs.find(i) == mTexs.end()) {
            loadTex(i);
        }
        return mTexs[i];
    };

    const std::string mSize;
    const std::string mName;
    const std::vector<eSpriteData> mSds;
    const eOffsets* const mOffs;
    SDL_Renderer* const mRenderer;
    std::map<int, std::shared_ptr<eTexture>> mTexs;
};

inline const std::vector<eSpriteData>& spriteData(
        const int size,
        const std::vector<eSpriteData>& s15,
        const std::vector<eSpriteData>& s30,
        const std::vector<eSpriteData>& s45,
        const std::vector<eSpriteData>& s60) {
    if(size == 15) return s15;
    if(size == 30) return s30;
    if(size == 45) return s45;
    if(size == 60) return s60;
    return s30;
}

#endif // ESPRITELOADER_H
