#include "edate.h"

#include "elanguage.h"

eDate::eDate(const int day, const eMonth month, const int year) :
    mDay(day), mMonth(month), mYear(year) {

}

std::string eDate::shortString() const {
    const auto d = std::to_string(mDay);
    const auto m = eMonthHelper::shortName(mMonth);
    const auto y = std::to_string(std::abs(mYear));
    std::string bcad;
    if(mYear < 0) bcad = eLanguage::zeusText(20, 0);
    else bcad = eLanguage::zeusText(20, 1);
    return d + "  " + m + "  " + y + "  " + bcad;
}

void eDate::nextDays(const int d, bool& nextMonth, bool& nextYear) {
    nextMonth = false;
    nextYear = false;
    if(d == 0) return;
    const int maxDays = eMonthHelper::days(mMonth);
    if(mDay + d <= maxDays) {
        mDay += d;
    } else {
        const int dd = d - maxDays + mDay - 1;
        mDay = 1;
        mMonth = eMonthHelper::nextMonth(mMonth, nextYear);
        nextMonth = true;
        if(nextYear) {
            if(++mYear == 0) mYear++;
        }
        if(dd > 0) {
            bool nm;
            bool ny;
            nextDays(dd, nm, ny);
            nextMonth = nm || nextMonth;
            nextYear = ny || nextYear;
        }
    }
}

void eDate::prevDays(const int d, bool& prevMonth, bool& prevYear) {
    prevMonth = false;
    prevYear = false;
    if(d == 0) return;
    if(mDay - d >= 1) {
        mDay -= d;
    } else {
        mMonth = eMonthHelper::prevMonth(mMonth, prevYear);
        const int maxDays = eMonthHelper::days(mMonth);
        const int dd = d - mDay;
        mDay = maxDays;
        prevMonth = true;
        if(prevYear) {
            if(--mYear == 0) mYear--;
        }
        if(dd > 0) {
            bool pm;
            bool py;
            prevDays(dd, pm, py);
            prevMonth = pm || prevMonth;
            prevYear = py || prevYear;
        }
    }
}

bool eDate::operator>(const eDate& other) const {
    return mYear > other.mYear ||
           (mYear == other.mYear && mMonth > other.mMonth) ||
           (mYear == other.mYear && mMonth == other.mMonth && mDay > other.mDay);
}

bool eDate::operator<(const eDate& other) const {
    return other > *this;
}

bool eDate::operator<=(const eDate& other) const {
    return other < *this || other == *this;
}

bool eDate::operator>=(const eDate& other) const {
    return other > *this || other == *this;
}

bool eDate::operator==(const eDate& other) const {
    return other.mDay == mDay &&
           other.mMonth == mMonth &&
           other.mYear == mYear;
}

bool eDate::operator!=(const eDate& other) const {
    return !(*this == other);
}

eDate& eDate::operator++() {
    return *this += 1;
}

eDate& eDate::operator--() {
    return *this -= 1;
}

eDate& eDate::operator+=(const int d) {
    bool nm;
    bool ny;
    nextDays(d, nm, ny);
    return *this;
}

eDate eDate::operator+(const int d) const {
    auto date = *this;
    date += d;
    return date;
}

eDate& eDate::operator-=(const int d) {
    bool pm;
    bool py;
    prevDays(d, pm, py);
    return *this;
}

eDate eDate::operator-(const int d) const {
    auto date = *this;
    date -= d;
    return date;
}

int eDate::operator-(const eDate& d) const {
    if(d > *this) return d - *this;
    int nd = 0;
    eDate dd = *this;
    while(dd != d) {
        dd -= 1;
        nd++;
    }
    return nd;
}

void eDate::write(eWriteStream& dst) const {
    dst << mDay;
    dst << mMonth;
    dst << mYear;
}

void eDate::read(eReadStream& src) {
    src >> mDay;
    src >> mMonth;
    src >> mYear;
}

std::string eMonthHelper::name(const eMonth m) {
    const int group = 160;
    const int string = static_cast<int>(m);
    return eLanguage::zeusText(group, string);
}

std::string eMonthHelper::shortName(const eMonth m) {
    const int group = 25;
    const int string = static_cast<int>(m);
    return eLanguage::zeusText(group, string);
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

eMonth eMonthHelper::prevMonth(const eMonth m, bool& prevYear) {
    if(m == eMonth::january) {
        prevYear = true;
        return eMonth::december;
    } else {
        prevYear = false;
        const int i = static_cast<int>(m);
        return static_cast<eMonth>(i - 1);
    }
}
