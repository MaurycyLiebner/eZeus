#include "edate.h"

eDate::eDate(const int day, const eMonth month, const int year) :
    mDay(day), mMonth(month), mYear(year) {

}

std::string eDate::shortString() const {
    const auto d = std::to_string(mDay);
    const auto m = eMonthHelper::shortName(mMonth);
    const auto y = std::to_string(std::abs(mYear));
    std::string bcad;
    if(mYear < 0) bcad = "BC";
    else bcad = "AD";
    return d + "  " + m + "  " + y + "  " + bcad;
}

void eDate::nextDay(bool& nextMonth, bool& nextYear) {
    const int maxDays = eMonthHelper::days(mMonth);
    nextMonth = ++mDay > maxDays;
    if(nextMonth) {
        mDay = 1;
        mMonth = eMonthHelper::nextMonth(mMonth, nextYear);
        if(nextYear) {
            if(++mYear == 0) mYear++;
        }
    }
}

std::string eMonthHelper::shortName(const eMonth m) {
    switch(m) {
    case eMonth::january:
        return "Jan.";
    case eMonth::february:
        return "Feb.";
    case eMonth::march:
        return "Mar.";
    case eMonth::april:
        return "Apr.";
    case eMonth::may:
        return "May ";
    case eMonth::june:
        return "Jun.";
    case eMonth::july:
        return "Jul.";
    case eMonth::august:
        return "Aug.";
    case eMonth::september:
        return "Sep.";
    case eMonth::october:
        return "Oct.";
    case eMonth::november:
        return "Nov.";
    case eMonth::december:
        return "Dec.";
    }
}

int eMonthHelper::days(const eMonth m) {
    switch(m) {
    case eMonth::january:
        return 31;
    case eMonth::february:
        return 28;
    case eMonth::march:
        return 31;
    case eMonth::april:
        return 30;
    case eMonth::may:
        return 31;
    case eMonth::june:
        return 30;
    case eMonth::july:
        return 31;
    case eMonth::august:
        return 31;
    case eMonth::september:
        return 30;
    case eMonth::october:
        return 31;
    case eMonth::november:
        return 30;
    case eMonth::december:
        return 31;
    }
}

eMonth eMonthHelper::nextMonth(const eMonth m, bool& nextYear) {
    if(m == eMonth::december) {
        nextYear = true;
        return eMonth::january;
    } else {
        nextYear = false;
        const int i = static_cast<int>(m);
        return static_cast<eMonth>(i + 1);
    }
}
