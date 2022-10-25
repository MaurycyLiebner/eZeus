#ifndef EDATE_H
#define EDATE_H

#include <string>

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
    std::string shortName(const eMonth m);
    int days(const eMonth m);
    eMonth nextMonth(const eMonth m, bool& nextYear);
}

class eDate {
public:
    eDate(const int day, const eMonth month, const int year);

    std::string shortString() const;
    void nextDays(const int d, bool& nextMonth, bool& nextYear);

    int day() const { return mDay; }
    eMonth month() const { return mMonth; }
    int year() const { return mYear; }

    bool operator>(const eDate& other) const;
    bool operator<(const eDate& other) const;
    bool operator==(const eDate& other) const;
    bool operator!=(const eDate& other) const;
    eDate& operator++();
    eDate& operator+=(const int d);
private:
    int mDay;
    eMonth mMonth;
    int mYear;
};

#endif // EDATE_H
