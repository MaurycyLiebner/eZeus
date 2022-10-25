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
    if(mYear < 0) bcad = "BC";
    else bcad = "AD";
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

bool eDate::operator>(const eDate& other) const {
    return mYear > other.mYear ||
           (mYear == other.mYear && mMonth > other.mMonth) ||
           (mYear == other.mYear && mMonth == other.mMonth && mDay > other.mDay);
}

bool eDate::operator<(const eDate& other) const {
    return other > *this;
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

eDate& eDate::operator+=(const int d) {
    bool nm;
    bool ny;
    nextDays(d, nm, ny);
    return *this;
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

std::string eMonthHelper::shortName(const eMonth m) {
    switch(m) {
    case eMonth::january:
        return eLanguage::text("jan_short");
    case eMonth::february:
        return eLanguage::text("feb_short");
    case eMonth::march:
        return eLanguage::text("mar_short");
    case eMonth::april:
        return eLanguage::text("apr_short");
    case eMonth::may:
        return eLanguage::text("may_short");
    case eMonth::june:
        return eLanguage::text("jun_short");
    case eMonth::july:
        return eLanguage::text("jul_short");
    case eMonth::august:
        return eLanguage::text("aug_short");
    case eMonth::september:
        return eLanguage::text("sep_short");
    case eMonth::october:
        return eLanguage::text("oct_short");
    case eMonth::november:
        return eLanguage::text("nov_short");
    case eMonth::december:
        return eLanguage::text("dec_short");
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
