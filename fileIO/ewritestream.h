#ifndef EWRITESTREAM_H
#define EWRITESTREAM_H

#include <SDL2/SDL.h>
#include <string>

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
        const int32_t val32_t = val;
        write(&val32_t, sizeof(int32_t));
        return *this;
    }

    inline eWriteStream& operator<<(const std::string& val) {
        const int32_t size = val.size();
        *this << size;
        write(&val[0], size);
        return *this;
    }
private:
    SDL_RWops* const mDst;
};

#endif // EWRITESTREAM_H
