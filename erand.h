#ifndef ERAND_H
#define ERAND_H

#include <random>

class eRand {
public:
    static int rand();
private:
    static std::random_device sDev;
    static std::mt19937 sRng;
    static std::uniform_int_distribution<int> sDist;
};

#endif // ERAND_H
