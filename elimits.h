#ifndef ELIMITS_H
#define ELIMITS_H

#include "erand.h"

#if (defined (_WIN32) || defined (_WIN64))
    #include <limits.h>
    #include <algorithm>

    #define __INT_MAX__ INT_MAX

    namespace std {
        template<class RandomIt>
        void random_shuffle(RandomIt first, RandomIt last)
        {
            typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;

            for (diff_t i = last - first - 1; i > 0; --i)
            {
                using std::swap;
                swap(first[i], first[eRand::rand() % (i + 1)]);
            }
        }
    }
#endif

#endif // ELIMITS_H
