#ifndef EWRITESTREAM_H
#define EWRITESTREAM_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

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

using eDirectionTimes = std::map<eTile*, eDirectionLastUseTime>;

class eWriteStream {
public:
    eWriteStream(SDL_RWops* const dst);

    inline size_t write(const void* const data, const size_t len) {
        return SDL_RWwrite(mDst, data, len, 1);
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
private:
    SDL_RWops* const mDst;
};

#endif // EWRITESTREAM_H
