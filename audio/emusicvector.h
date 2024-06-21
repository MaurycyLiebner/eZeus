#ifndef EMUSICVECTOR_H
#define EMUSICVECTOR_H

#include <SDL2/SDL_mixer.h>

#include <vector>
#include <string>

class eMusicVector {
public:
    ~eMusicVector();

    int soundCount() const { return mPaths.size(); }
    void addPath(const std::string& path);
    void play(const int id, const bool loop = false);
    void playRandomSound(const bool loop = false);
private:
    std::vector<std::pair<Mix_Music*, std::string>> mPaths;
};

#endif // EMUSICVECTOR_H
