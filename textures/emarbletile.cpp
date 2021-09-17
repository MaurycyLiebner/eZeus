#include "emarbletile.h"

bool isEdge(eTile* const tile) {
    const auto terr = tile->terrain();

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l);

    const bool edge = tl || tr || br || bl || t || r || b || l;
    return edge;
}

std::shared_ptr<eTexture> eMarbleTile::get(
        eTile* const tile,
        const eTerrainTextures& textures) {
    const int seed = tile->seed();

    const int ml = tile->marbleLevel();

    if(ml == 0) {
        const auto& fm = textures.fFlatMarble;
        const int id = seed % fm.size();
        return fm.getTexture(id);
    }

    const auto terr = tile->terrain();

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l);

    const bool edge = tl || tr || br || bl || t || r || b || l;

    if(!edge) {
        if(ml == 1) {
            return textures.fMarble.getTexture(seed % 6);
        }

        const auto tlt = tile->topLeft<eTile>();
        tl = !tlt || isEdge(tlt);
        const auto trt = tile->topRight<eTile>();
        tr = !trt || isEdge(trt);
        const auto blt = tile->bottomLeft<eTile>();
        bl = !blt || isEdge(blt);
        const auto brt = tile->bottomRight<eTile>();
        br = !brt || isEdge(brt);

        const auto tt = tile->top<eTile>();
        t = !tt || isEdge(tt);
        const auto rt = tile->right<eTile>();
        r = !rt || isEdge(rt);
        const auto bt = tile->bottom<eTile>();
        b = !bt || isEdge(bt);
        const auto lt = tile->left<eTile>();
        l = !lt || isEdge(lt);
    }

    const auto& coll = edge ? textures.fMarble : textures.fDeepMarble;

    if(t && b && r && l && br && bl && tl && tr) {
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
