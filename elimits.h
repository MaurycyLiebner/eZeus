#ifndef ELIMITS_H
#define ELIMITS_H

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
                swap(first[i], first[std::rand() % (i + 1)]);
                // rand() % (i + 1) is not actually correct, because the generated number is
                // not uniformly distributed for most values of i. The correct code would be
                // a variation of the C++11 std::uniform_int_distribution implementation.
            }
        }
    }
#endif

#endif // ELIMITS_H
