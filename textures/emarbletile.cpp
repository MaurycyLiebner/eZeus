#include "emarbletile.h"

bool edge(eTile* const tile,
          bool& tl, bool& tr,
          bool& br, bool& bl,
          bool& t, bool& r,
          bool& b, bool& l,
          const eWorldDirection dir) {
    const auto terr = tile->terrain();
    const int level = tile->marbleLevel();

    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l, dir);
    const auto tlt = tile->topLeftRotated(dir);
    tl = tl || !tlt || level > tlt->marbleLevel();
    const auto trt = tile->topRightRotated(dir);
    tr = tr || !trt || level > trt->marbleLevel();
    const auto brt = tile->bottomRightRotated(dir);
    br = br || !brt || level > brt->marbleLevel();
    const auto blt = tile->bottomLeftRotated(dir);
    bl = bl || !blt || level > blt->marbleLevel();
    const auto tt = tile->topRotated(dir);
    t = t || !tt || level > tt->marbleLevel();
    const auto rt = tile->rightRotated(dir);
    r = r || !rt || level > rt->marbleLevel();
    const auto bt = tile->bottomRotated(dir);
    b = b || !bt || level > bt->marbleLevel();
    const auto lt = tile->leftRotated(dir);
    l = l || !lt || level > lt->marbleLevel();
    return tl || tr || br || bl || t || r || b || l;
}

bool eMarbleTile::edge(eTile* const tile) {
    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    return edge(tile, tl, tr, br, bl, t, r, b, l, eWorldDirection::N);
}

std::shared_ptr<eTexture> eMarbleTile::get(
        eTile* const tile,
        const eTerrainTextures& textures,
        const eWorldDirection dir) {
    const int seed = tile->seed();

    const int ml = tile->marbleLevel();

    if(ml == 0) {
        const auto& fm = textures.fFlatMarble;
        const int id = seed % fm.size();
        return fm.getTexture(id);
    }

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    const bool e = edge(tile, tl, tr, br, bl, t, r, b, l, dir);

    const auto& coll = ml > 1 ? textures.fDeepMarble : textures.fMarble;

    if(!e) return coll.getTexture(seed % 6);

    if(br && bl && tl && tr) {
        return coll.getTexture(37);
    }

    if(br && bl && tl) {
        return coll.getTexture(50);
    }
    if(bl && tl && tr) {
        return coll.getTexture(51);
    }
    if(tl && tr && br) {
        return coll.getTexture(58);
    }
    if(tr && br && bl) {
        return coll.getTexture(59);
    }
    if(tl && bl && r) {
        return coll.getTexture(52);
    }
    if(tl && tr && b) {
        return coll.getTexture(53);
    }
    if(tr && br && l) {
        return coll.getTexture(54);
    }
    if(bl && br && t) {
        return coll.getTexture(55);
    }
    if(tl && br) {
        return coll.getTexture(56);
    }
    if(tr && bl) {
        return coll.getTexture(57);
    }
    if(tl && tr) {
        return coll.getTexture(6);
    }
    if(tr && br) {
        return coll.getTexture(10);
    }
    if(br && bl) {
        return coll.getTexture(14);
    }
    if(tl && bl) {
        return coll.getTexture(18);
    }


    if(tl) {
        if(r && b) {
            return coll.getTexture(40);
        }
        if(r) {
            return coll.getTexture(38);
        }
        if(b) {
            return coll.getTexture(39);
        }
    }
    if(tr) {
        if(l && b) {
            return coll.getTexture(43);
        }
        if(b) {
            return coll.getTexture(41);
        }
        if(l) {
            return coll.getTexture(42);
        }
    }
    if(br) {
        if(l && t) {
            return coll.getTexture(46);
        }
        if(l) {
            return coll.getTexture(44);
        }
        if(t) {
            return coll.getTexture(45);
        }
    }
    if(bl) {
        if(r && t) {
            return coll.getTexture(49);
        }
        if(t) {
            return coll.getTexture(47);
        }
        if(r) {
            return coll.getTexture(48);
        }
    }

    if(tr) {
        return coll.getTexture(seed % 3 + 7);
    }
    if(br) {
        return coll.getTexture(seed % 3 + 11);
    }
    if(bl) {
        return coll.getTexture(seed % 3 + 15);
    }
    if(tl) {
        return coll.getTexture(seed % 3 + 19);
    }

    if(t && b && r && l) {
        return coll.getTexture(22);
    }
    if(t && b && l) {
        return coll.getTexture(23);
    }
    if(t && r && l) {
        return coll.getTexture(24);
    }
    if(t && b && r) {
        return coll.getTexture(25);
    }
    if(b && r && l) {
        return coll.getTexture(26);
    }
    if(b && r) {
        return coll.getTexture(27);
    }
    if(b && l) {
        return coll.getTexture(28);
    }
    if(t && l) {
        return coll.getTexture(29);
    }
    if(t && r) {
        return coll.getTexture(30);
    }
    if(t && b) {
        return coll.getTexture(31);
    }
    if(r && l) {
        return coll.getTexture(32);
    }
    if(b) {
        return coll.getTexture(33);
    }
    if(r) {
        return coll.getTexture(34);
    }
    if(l) {
        return coll.getTexture(35);
    }
    if(t) {
        return coll.getTexture(36);
    }
    return coll.getTexture(seed % 6);
}
