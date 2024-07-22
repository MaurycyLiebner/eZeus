#ifndef EWRITESTREAM_H
#define EWRITESTREAM_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <cassert>

class eTile;
class eBuilding;
class eCharacter;
class eCharacterAction;
class eWalkableObject;
class eHasResourceObject;
class eCharacterActionFunction;
class eGodAct;
class eObsticleHandler;
class eDirectionLastUseTime;
class eWorldCity;
class eBanner;
class eSoldierBanner;
class eGameEvent;

using eDirectionTimes = std::map<eTile*, eDirectionLastUseTime>;

class eWriteTarget {
public:
    eWriteTarget(std::ofstream* const file) :
        fFile(file) {}
    eWriteTarget(void* mem) :
        fMem(mem) {}

    inline size_t write(const void* const data, const size_t len) {
        assert(fFile || fMem);
        if(fFile) {
            fFile->write(static_cast<const char*>(data), len);
            return len;
        } else if(fMem) {
            std::memcpy(static_cast<char*>(fMem) + fMemPos, data, len);
            fMemPos += len;
            return len;
        }
        return 0;
    }
private:
    std::ofstream* fFile = nullptr;
    void* fMem = nullptr;
    size_t fMemPos = 0;
};

class eWriteStream {
public:
    eWriteStream(const eWriteTarget& dst);

    inline size_t write(const void* const data, const size_t len) {
        return mDst.write(data, len);
    }

    inline eWriteStream& operator<<(const bool val) {
        write(&val, sizeof(bool));
        return *this;
    }

    inline eWriteStream& operator<<(const float val) {
        write(&val, sizeof(float));
        return *this;
    }

    inline eWriteStream& operator<<(const double val) {
        write(&val, sizeof(double));
        return *this;
    }

    inline eWriteStream& operator<<(const int32_t val) {
        write(&val, sizeof(int32_t));
        return *this;
    }

    template <typename T>
    inline eWriteStream& operator<<(const T val) {
        const int32_t val32_t = static_cast<int32_t>(val);
        write(&val32_t, sizeof(int32_t));
        return *this;
    }

    template <typename T>
    inline eWriteStream& operator<<(const std::vector<T>& val) {
        *this << val.size();
        for(const auto& t : val) {
            *this << t;
        }
        return *this;
    }

    inline eWriteStream& operator<<(const SDL_Rect& val) {
        *this << val.x;
        *this << val.y;
        *this << val.w;
        *this << val.h;
        return *this;
    }

    inline eWriteStream& operator<<(const std::string& val) {
        const int32_t size = val.size();
        *this << size;
        write(&val[0], size);
        return *this;
    }

    void writeTile(eTile* const tile);
    void writeBuilding(eBuilding* const b);
    void writeCharacter(eCharacter* const c);
    void writeCharacterAction(eCharacterAction* const ca);
    void writeWalkable(eWalkableObject* const w);
    void writeHasResource(eHasResourceObject* const hr);
    void writeCharActFunc(eCharacterActionFunction* const caf);
    void writeGodAct(eGodAct* const ga);
    void writeObsticleHandler(eObsticleHandler* const w);
    void writeDirectionTimes(eDirectionTimes* const d);
    void writeCity(eWorldCity* const c);
    void writeBanner(eBanner* const b);
    void writeSoldierBanner(eSoldierBanner* const b);
    void writeGameEvent(eGameEvent* const e);
private:
    eWriteTarget mDst;
};

#endif // EWRITESTREAM_H
