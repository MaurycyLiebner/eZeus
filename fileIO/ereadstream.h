#ifndef EREADSTREAM_H
#define EREADSTREAM_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>

#include "pointers/estdpointer.h"

class eTile;
class eBuilding;
class eCharacter;
class eCharacterAction;
class eGameBoard;
class eWalkableObject;
class eHasResourceObject;

class eReadStream {
public:
    eReadStream(SDL_RWops* const src);

    inline size_t read(void* const data, const size_t len) {
        return SDL_RWread(mSrc, data, len, 1);
    }

    inline eReadStream& operator>>(bool& val) {
        read(&val, sizeof(bool));
        return *this;
    }

    inline eReadStream& operator>>(float& val) {
        read(&val, sizeof(float));
        return *this;
    }

    inline eReadStream& operator>>(double& val) {
        read(&val, sizeof(double));
        return *this;
    }

    inline eReadStream& operator>>(int32_t& val) {
        read(&val, sizeof(int32_t));
        return *this;
    }

    template <typename T>
    inline eReadStream& operator>>(T& val) {
        int32_t val32_t;
        read(&val32_t, sizeof(int32_t));
        val = static_cast<T>(val32_t);
        return *this;
    }

    template <typename T>
    inline eReadStream& operator<<(std::vector<T>& val) {
        int size;
        *this >> size;
        for(int i = 0; i < size; i++) {
            T& t = val.emplace_back();
            *this >> t;
        }
        return *this;
    }

    inline eReadStream& operator>>(SDL_Rect& val) {
        *this >> val.x;
        *this >> val.y;
        *this >> val.w;
        *this >> val.h;
        return *this;
    }

    inline eReadStream& operator>>(std::string& val) {
        int32_t size;
        *this >> size;
        if(size == 0) {
            val = "";
        } else {
            val.resize(size);
            read(&val[0], size);
        }
        return *this;
    }

    eTile* readTile(eGameBoard& board);
    using eBuildingFunc = std::function<void(eBuilding*)>;
    void readBuilding(eGameBoard* board,
                      const eBuildingFunc& func);
    using eCharFunc = std::function<void(eCharacter*)>;
    void readCharacter(eGameBoard* board,
                       const eCharFunc& func);
    using eCharActFunc = std::function<void(eCharacterAction*)>;
    void readCharacterAction(eGameBoard* board,
                             const eCharActFunc& func);
    stdsptr<eWalkableObject> readWalkable();
    stdsptr<eHasResourceObject> readHasResource();

    using eFunc = std::function<void()>;
    void addPostFunc(const eFunc& func);
    void handlePostFuncs();
private:
    std::vector<eFunc> mPostFuncs;

    SDL_RWops* const mSrc;
};

#endif // EREADSTREAM_H
