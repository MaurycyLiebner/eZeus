#ifndef EEVENTTIME_H
#define EEVENTTIME_H

#include "edate.h"

struct eEventTime {
    eDate fDate;
    int fPeriod;
    int fRepeat; // 0 - triggered
};

#endif // EEVENTTIME_H
