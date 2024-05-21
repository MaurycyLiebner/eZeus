#ifndef EDATE_H
#define EDATE_H

#include <string>

#include "fileIO/estreams.h"

enum class eMonth {
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

namespace eMonthHelper {
    std::string name(const eMonth m);
    std::string shortName(const eMonth m);
    int days(const eMonth m);
    eMonth nextMonth(const eMonth m, bool& nextYear);
    eMonth prevMonth(const eMonth m, bool& prevYear);
}

class eDate {
public:
    eDate(const int day, const eMonth month, const int year);
    eDate() {}

    std::string shortString() const;
    void nextDays(const int d, bool& nextMonth, bool& nextYear);
    void prevDays(const int d, bool& prevMonth, bool& prevYear);

    int day() const { return mDay; }
    eMonth month() const { return mMonth; }
    int year() const { return mYear; }

    bool operator>(const eDate& other) const;
    bool operator<(const eDate& other) const;
    bool operator<=(const eDate& other) const;
    bool operator>=(const eDate& other) const;
    bool operator==(const eDate& other) const;
    bool operator!=(const eDate& other) const;
    eDate& operator++();
    eDate& operator--();
    eDate& operator+=(const int d);
    eDate operator+(const int d) const;
    eDate& operator-=(const int d);
    eDate operator-(const int d) const;
    int operator-(const eDate& d) const;

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);
private:
    int mDay;
    eMonth mMonth;
    int mYear;
};

#endif // EDATE_H
